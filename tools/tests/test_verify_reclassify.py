from __future__ import annotations

import contextlib
import io
import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from verify_reclassify import (
    DOWNLOAD_FAILURE_WINDOW,
    failed_paths,
    propagate,
    reclassify,
    run,
    timeout_paths,
)

AOJ_READ_TIMEOUT = (
    "HTTPSConnectionPool(host='judgedat.u-aizu.ac.jp', port=443): "
    "Read timed out. (read timeout=10)"
)
AOJ_CONNECT_TIMEOUT = (
    "HTTPSConnectionPool(host='judgedat.u-aizu.ac.jp', port=443): Max retries exceeded "
    "(Caused by ConnectTimeoutError(..., 'Connection to judgedat.u-aizu.ac.jp timed out. "
    "(connect timeout=10)'))"
)
HANDSHAKE_TIMEOUT = "ssl.SSLError: _ssl.c:983: The handshake operation timed out"


def download_failure(path: str) -> str:
    return f"ERROR Failed to download: problem='https://onlinejudge.u-aizu.ac.jp/x' file='{path}'"


def result(statuses: dict[str, list[str]]) -> dict[str, object]:
    return {
        "files": {
            path: {"verifications": [{"status": s, "elapsed": 1.0} for s in ss]}
            for path, ss in statuses.items()
        }
    }


def statuses(data: dict[str, object]) -> dict[str, list[str]]:
    return {
        path: [v["status"] for v in fr["verifications"]] for path, fr in data["files"].items()
    }


class FailedPathsTest(unittest.TestCase):
    def test_any_failure_marks_the_file(self) -> None:
        data = result(
            {
                "test/a.test.cpp": ["success", "failure"],
                "test/b.test.cpp": ["success"],
                "test/c.test.cpp": ["skipped"],
            }
        )
        self.assertEqual(failed_paths(data), {"test/a.test.cpp"})

    def test_missing_files(self) -> None:
        self.assertEqual(failed_paths({}), set())


class TimeoutPathsTest(unittest.TestCase):
    def test_each_timeout_kind(self) -> None:
        for timeout in (AOJ_READ_TIMEOUT, AOJ_CONNECT_TIMEOUT, HANDSHAKE_TIMEOUT):
            with self.subTest(timeout=timeout):
                log = "\n".join([timeout, "retrying", download_failure("test/a.test.cpp")])
                self.assertEqual(timeout_paths(log), {"test/a.test.cpp"})

    def test_failure_without_timeout_is_ignored(self) -> None:
        log = "\n".join(["Wrong Answer", download_failure("test/a.test.cpp")])
        self.assertEqual(timeout_paths(log), set())

    def test_non_aoj_read_timeout_is_ignored(self) -> None:
        timeout = "HTTPSConnectionPool(host='judge.yosupo.jp', port=443): Read timed out."
        log = "\n".join([timeout, download_failure("test/a.test.cpp")])
        self.assertEqual(timeout_paths(log), set())

    def test_failure_outside_the_window_is_ignored(self) -> None:
        filler = ["noise"] * (DOWNLOAD_FAILURE_WINDOW - 1)
        log = "\n".join([AOJ_READ_TIMEOUT, *filler, download_failure("test/a.test.cpp")])
        self.assertEqual(timeout_paths(log), set())

    def test_last_line_of_the_window(self) -> None:
        filler = ["noise"] * (DOWNLOAD_FAILURE_WINDOW - 2)
        log = "\n".join([AOJ_READ_TIMEOUT, *filler, download_failure("test/a.test.cpp")])
        self.assertEqual(timeout_paths(log), {"test/a.test.cpp"})


class ReclassifyTest(unittest.TestCase):
    def test_only_failures_of_given_paths_change(self) -> None:
        data = result(
            {
                "test/a.test.cpp": ["success", "failure"],
                "test/b.test.cpp": ["failure"],
                "test/c.test.cpp": ["success"],
            }
        )
        changed = reclassify(data, ["test/c.test.cpp", "test/a.test.cpp", "test/x.test.cpp"])
        self.assertEqual(changed, ["test/a.test.cpp"])
        self.assertEqual(
            statuses(data),
            {
                "test/a.test.cpp": ["success", "skipped"],
                "test/b.test.cpp": ["failure"],
                "test/c.test.cpp": ["success"],
            },
        )


class PropagateTest(unittest.TestCase):
    def test_only_shard_entries_are_overwritten(self) -> None:
        merged = result({"test/a.test.cpp": ["skipped"], "test/b.test.cpp": ["success"]})
        shard = result({"test/a.test.cpp": ["failure"]})
        propagate(merged, shard)
        self.assertEqual(statuses(shard), {"test/a.test.cpp": ["skipped"]})


class RunTest(unittest.TestCase):
    def setUp(self) -> None:
        self.dir = Path(self.enterContext(tempfile.TemporaryDirectory()))
        self.merged = self.dir / "merged.json"
        self.shards = [self.dir / "shard0.json", self.dir / "shard1.json"]

    def write(self, path: Path, data: dict[str, object]) -> None:
        path.write_text(json.dumps(data))

    def read(self, path: Path) -> dict[str, list[str]]:
        return statuses(json.loads(path.read_text()))

    def run_quietly(self, logs: list[str | None]) -> list[str]:
        with contextlib.redirect_stdout(io.StringIO()):
            return run(self.merged, self.shards, lambda: logs)

    def test_reclassifies_and_propagates(self) -> None:
        self.write(
            self.merged,
            result({"test/a.test.cpp": ["failure"], "test/b.test.cpp": ["failure"]}),
        )
        self.write(self.shards[0], result({"test/a.test.cpp": ["failure"]}))
        self.write(self.shards[1], result({"test/b.test.cpp": ["failure"]}))
        log = "\n".join([AOJ_READ_TIMEOUT, download_failure("test/a.test.cpp")])

        self.assertEqual(self.run_quietly([None, log]), ["test/a.test.cpp"])
        self.assertEqual(
            self.read(self.merged),
            {"test/a.test.cpp": ["skipped"], "test/b.test.cpp": ["failure"]},
        )
        self.assertEqual(self.read(self.shards[0]), {"test/a.test.cpp": ["skipped"]})
        self.assertEqual(self.read(self.shards[1]), {"test/b.test.cpp": ["failure"]})

    def test_does_not_fetch_logs_without_failures(self) -> None:
        self.write(self.merged, result({"test/a.test.cpp": ["success"]}))

        def fail() -> list[str | None]:
            raise AssertionError("logs must not be fetched")

        with contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(run(self.merged, self.shards, fail), [])

    def test_leaves_files_untouched_without_timeouts(self) -> None:
        original = json.dumps(result({"test/a.test.cpp": ["failure"]}))
        self.merged.write_text(original)
        self.assertEqual(self.run_quietly(["Wrong Answer"]), [])
        self.assertEqual(self.merged.read_text(), original)


if __name__ == "__main__":
    unittest.main()
