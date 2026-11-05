#!/usr/bin/env python3
"""Reclassify transient AOJ timeout failures as skipped in verify results.

Reads the logs of this run's verify jobs, rewrites download failures caused by
AOJ timeouts from ``failure`` to ``skipped`` in the merged result, and copies
the merged entries back into every shard's result.json so that the final
Check step sees the same statuses.  Why only AOJ, and why the log is fetched
the way it is, is documented in docs/current/verify-workflow.md.
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
from collections.abc import Callable, Iterable
from pathlib import Path
from typing import TypedDict

FAILURE = "failure"
SKIPPED = "skipped"

# AOJ only, on purpose: generalizing to unobserved patterns would risk
# silently skipping real failures.
TIMEOUT_PATTERN = re.compile(
    r"judgedat\.u-aizu\.ac\.jp.*(?:Read timed out|"
    r"timed out\. \(connect timeout=\d+\))|"
    r"handshake operation timed out"
)
DOWNLOAD_FAILURE_PATTERN = re.compile(r"Failed to download:.*'(test/[^']+\.test\.cpp)'")
# "Failed to download" follows the timeout line within a few lines.
DOWNLOAD_FAILURE_WINDOW = 30

VERIFY_JOB_PREFIX = "verify ("


# Only the keys read here; the rest of result.json is carried through untouched.
class Verification(TypedDict, total=False):
    status: str


class FileResult(TypedDict, total=False):
    verifications: list[Verification]


class Result(TypedDict, total=False):
    files: dict[str, FileResult]


def failed_paths(result: Result) -> set[str]:
    return {
        path
        for path, file_result in result.get("files", {}).items()
        if any(v.get("status") == FAILURE for v in file_result.get("verifications", []))
    }


def timeout_paths(log: str) -> set[str]:
    """Test files whose download failed right after an AOJ timeout in ``log``."""
    lines = log.splitlines()
    paths: set[str] = set()
    for i, line in enumerate(lines):
        if not TIMEOUT_PATTERN.search(line):
            continue
        for following in lines[i : i + DOWNLOAD_FAILURE_WINDOW]:
            if m := DOWNLOAD_FAILURE_PATTERN.search(following):
                paths.add(m.group(1))
    return paths


def reclassify(result: Result, paths: Iterable[str]) -> list[str]:
    """Turn failures of ``paths`` into skips in place; return the changed paths."""
    files = result.get("files", {})
    changed = []
    for path in sorted(paths):
        verifications = files.get(path, {}).get("verifications", [])
        failures = [v for v in verifications if v.get("status") == FAILURE]
        for v in failures:
            v["status"] = SKIPPED
        if failures:
            changed.append(path)
    return changed


def propagate(merged: Result, shard: Result) -> None:
    """Overwrite the shard's entries with the merged ones, in place."""
    merged_files = merged.get("files", {})
    shard_files = shard.get("files", {})
    for path in shard_files:
        if path in merged_files:
            shard_files[path] = merged_files[path]


def gh_api(*args: str) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        ["gh", "api", *args], capture_output=True, text=True, errors="replace", check=False
    )


def verify_job_ids(repo: str, run_id: str) -> list[int]:
    proc = gh_api("--paginate", f"repos/{repo}/actions/runs/{run_id}/jobs")
    if proc.returncode != 0:
        raise RuntimeError(f"Failed to list jobs of run {run_id}: {proc.stderr.strip()}")
    jobs = json.loads(proc.stdout)["jobs"]
    return [job["id"] for job in jobs if job["name"].startswith(VERIFY_JOB_PREFIX)]


def fetch_job_log(repo: str, job_id: int) -> str | None:
    # 新しい gh は --allow-escape-sequences なしだと ANSI 色付きのログを拒否する。
    # 古い gh には無いフラグなので順に試す。
    path = f"repos/{repo}/actions/jobs/{job_id}/logs"
    stderr = ""
    for args in (["--allow-escape-sequences", path], [path]):
        proc = gh_api(*args)
        if proc.returncode == 0:
            return proc.stdout
        stderr = proc.stderr.strip().replace("\n", " ")
    # 握り潰すと transient なタイムアウトを判別できないので可視化する。
    print(f"::warning::Failed to fetch log of job {job_id}: {stderr}")
    return None


def collect_timeout_paths(logs: Iterable[str | None]) -> set[str]:
    paths: set[str] = set()
    for log in logs:
        if log is not None:
            paths |= timeout_paths(log)
    return paths


def load(path: Path) -> Result:
    data: Result = json.loads(path.read_text(encoding="utf-8"))
    return data


def dump(path: Path, data: Result) -> None:
    path.write_text(json.dumps(data), encoding="utf-8")


def run(
    merged_path: Path,
    shard_paths: Iterable[Path],
    fetch_logs: Callable[[], Iterable[str | None]],
) -> list[str]:
    merged = load(merged_path)
    failed = failed_paths(merged)
    if not failed:
        print("No failures; nothing to reclassify.")
        return []

    changed = reclassify(merged, failed & collect_timeout_paths(fetch_logs()))
    if not changed:
        print("No transient AOJ timeouts detected.")
        return []

    dump(merged_path, merged)
    for shard_path in shard_paths:
        shard = load(shard_path)
        propagate(merged, shard)
        dump(shard_path, shard)
    print(f"Reclassified {len(changed)} timeout failures as skipped:")
    for path in changed:
        print(f"  - {path}")
    return changed


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--merged", required=True, type=Path, help="merged-result.json")
    parser.add_argument(
        "--shard", nargs="*", default=[], type=Path, help="各 shard の result.json（反映先）"
    )
    parser.add_argument("--repo", required=True, help="owner/name")
    parser.add_argument("--run-id", required=True)
    args = parser.parse_args(argv)

    def fetch_logs() -> Iterable[str | None]:
        for job_id in verify_job_ids(args.repo, args.run_id):
            yield fetch_job_log(args.repo, job_id)

    run(args.merged, args.shard, fetch_logs)
    return 0


if __name__ == "__main__":
    sys.exit(main())
