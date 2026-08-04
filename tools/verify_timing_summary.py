#!/usr/bin/env python3
"""Summarize verification timings and their change against a baseline result.

The report is informational only.  Timings measured on shared GitHub runners
vary by a factor of two between identical runs, so nothing here gates the
workflow; the numbers exist to spot order-of-magnitude regressions.

Two properties of the verification pipeline shape the output:

* Tests whose previous result is still valid are skipped and their timings are
  carried over verbatim, so a diff against the baseline lists exactly the tests
  re-executed in this run.
* Verifications with status ``skipped`` carry no timing at all (``elapsed`` is
  the bookkeeping overhead and ``slowest`` is null), so they are excluded from
  every aggregate.

``elapsed`` equals the sum of the testcase timings, i.e. compilation and
testcase downloads are not part of it; ``slowest`` is the worst single testcase.
"""

from __future__ import annotations

import argparse
import json
import os
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Any, Iterable


SKIPPED = "skipped"

# A regression must be both relatively and absolutely large to be flagged;
# runner noise easily reaches +80% on tests that take milliseconds.
REGRESSION_RATIO = 0.3
REGRESSION_ABSOLUTE = 0.5

DEFAULT_MAX_ROWS = 30


@dataclass(frozen=True)
class Timing:
    path: str
    name: str | None
    elapsed: float
    slowest: float | None
    last_execution_time: str | None
    # Verifications of one file are distinguished by name, falling back to the
    # position when a name is absent.
    key: tuple[str, str]

    @property
    def label(self) -> str:
        stripped = self.path.removeprefix("test/").removesuffix(".test.cpp")
        if self.name and self.name != "g++":
            return f"{stripped} ({self.name})"
        return stripped


@dataclass(frozen=True)
class Aggregate:
    count: int
    total: float
    worst: Timing | None


def collect(result: dict[str, Any]) -> dict[tuple[str, str], Timing]:
    """Index every timed verification of a result document by test and name."""
    timings: dict[tuple[str, str], Timing] = {}
    for path, file_result in (result.get("files") or {}).items():
        for index, verification in enumerate(file_result.get("verifications") or []):
            if verification.get("status") == SKIPPED:
                continue
            elapsed = verification.get("elapsed")
            if not isinstance(elapsed, (int, float)):
                continue
            name = verification.get("verification_name")
            slowest = verification.get("slowest")
            key = (path, name or str(index))
            timings[key] = Timing(
                path=path,
                name=name,
                elapsed=float(elapsed),
                slowest=float(slowest) if isinstance(slowest, (int, float)) else None,
                last_execution_time=verification.get("last_execution_time"),
                key=key,
            )
    return timings


def skipped_paths(result: dict[str, Any]) -> set[str]:
    return {
        path
        for path, file_result in (result.get("files") or {}).items()
        if any(
            verification.get("status") == SKIPPED
            for verification in file_result.get("verifications") or []
        )
    }


def aggregate(timings: Iterable[Timing]) -> Aggregate:
    timings = list(timings)
    worst = max(
        (t for t in timings if t.slowest is not None),
        key=lambda t: t.slowest or 0.0,
        default=None,
    )
    return Aggregate(
        count=len(timings),
        total=sum(t.elapsed for t in timings),
        worst=worst,
    )


def reexecuted(
    now: dict[tuple[str, str], Timing],
    base: dict[tuple[str, str], Timing],
) -> list[tuple[Timing, Timing | None]]:
    """Pair each freshly measured verification with its baseline counterpart.

    Re-execution is detected via ``last_execution_time`` rather than a timing
    comparison: an unchanged timestamp means the number was carried over, and a
    re-run that happens to reproduce its timing exactly is still interesting.
    """
    rows: list[tuple[Timing, Timing | None]] = []
    for key, timing in now.items():
        previous = base.get(key)
        if previous and previous.last_execution_time == timing.last_execution_time:
            continue
        rows.append((timing, previous))
    rows.sort(key=lambda row: -abs(row[0].elapsed - (row[1].elapsed if row[1] else 0.0)))
    return rows


def format_seconds(value: float) -> str:
    if value < 1.0:
        return f"{value * 1000:.0f}ms"
    if value < 10.0:
        return f"{value:.2f}s"
    if value < 100.0:
        return f"{value:.1f}s"
    return f"{value:.0f}s"


def format_ratio(new: float, old: float) -> str:
    if old <= 0.0:
        return "新規" if new > 0.0 else "±0%"
    return f"{(new - old) / old * 100:+.0f}%"


def format_change(new: float | None, old: float | None) -> str:
    if new is None:
        return "—"
    if old is None:
        return f"{format_seconds(new)}（基準なし）"
    return f"{format_seconds(old)} → {format_seconds(new)} ({format_ratio(new, old)})"


def is_regression(new: float | None, old: float | None) -> bool:
    if new is None or old is None or old <= 0.0:
        return False
    return new - old >= REGRESSION_ABSOLUTE and (new - old) / old >= REGRESSION_RATIO


def render_diff_rows(
    rows: list[tuple[Timing, Timing | None]],
    max_rows: int,
) -> list[str]:
    lines = ["| test | 合計 | 最悪ケース |", "| --- | --- | --- |"]
    for timing, previous in rows[:max_rows]:
        base_elapsed = previous.elapsed if previous else None
        base_slowest = previous.slowest if previous else None
        flagged = is_regression(timing.elapsed, base_elapsed) or is_regression(
            timing.slowest, base_slowest
        )
        label = f"⚠️ {timing.label}" if flagged else timing.label
        lines.append(
            f"| {label} "
            f"| {format_change(timing.elapsed, base_elapsed)} "
            f"| {format_change(timing.slowest, base_slowest)} |"
        )
    if len(rows) > max_rows:
        lines.append("")
        lines.append(f"（合計 {len(rows)} 件のうち差分の大きい {max_rows} 件のみ表示）")
    return lines


def render_slowest_rows(timings: Iterable[Timing], max_rows: int) -> list[str]:
    ranked = sorted(timings, key=lambda t: -(t.slowest or 0.0))[:max_rows]
    lines = ["| test | 合計 | 最悪ケース |", "| --- | --- | --- |"]
    for timing in ranked:
        lines.append(
            f"| {timing.label} "
            f"| {format_seconds(timing.elapsed)} "
            f"| {format_seconds(timing.slowest) if timing.slowest is not None else '—'} |"
        )
    return lines


def render(
    result: dict[str, Any],
    baseline: dict[str, Any] | None,
    max_rows: int = DEFAULT_MAX_ROWS,
) -> str:
    now = collect(result)
    current = aggregate(now.values())
    skipped_now = skipped_paths(result)

    lines = ["## ⏱ 実行時間", ""]

    if baseline is None:
        lines.append(
            "ベースライン（`main` の verify 結果キャッシュ）が無いため差分は表示しません。"
        )
        lines.append("")
        lines.append(
            f"- 合計（テストケース実行時間の総和, {current.count} 件）: "
            f"{format_seconds(current.total)}"
        )
        if current.worst is not None:
            lines.append(
                f"- 最悪ケース: {format_seconds(current.worst.slowest or 0.0)}"
                f" — `{current.worst.label}`"
            )
        if skipped_now:
            lines.append(f"- skip（計測なし・集計除外）: {len(skipped_now)} 件")
        lines.append("")
        lines.append(f"### 最も遅い test（上位 {max_rows} 件）")
        lines.append("")
        lines.extend(render_slowest_rows(now.values(), max_rows))
        lines.append("")
        return "\n".join(lines) + "\n"

    base = collect(baseline)
    previous = aggregate(base.values())
    rows = reexecuted(now, base)

    total_delta = current.total - previous.total
    lines.append(
        f"- 合計（テストケース実行時間の総和, {current.count} 件）: "
        f"{format_seconds(previous.total)} → {format_seconds(current.total)} "
        f"({total_delta:+.1f}s, {format_ratio(current.total, previous.total)})"
    )
    if current.worst is not None:
        worst_base = base.get(current.worst.key)
        worst_before = worst_base.slowest if worst_base else None
        lines.append(
            f"- 最悪ケース: {format_change(current.worst.slowest, worst_before)}"
            f" — `{current.worst.label}`"
        )
    lines.append(f"- この run で再実行された test: {len(rows)} 件 / {current.count} 件")

    disappeared = sorted({key[0] for key in base.keys() - now.keys()})
    if disappeared:
        lines.append(
            f"- ベースラインにのみ存在（改名・削除・今回 skip）: {len(disappeared)} 件"
            f" — 合計の差はこの分を含む"
        )
    lines.append("")

    if rows:
        lines.extend(render_diff_rows(rows, max_rows))
    else:
        lines.append("すべての test が前回結果を再利用したため、新しい計測はありません。")
    lines.append("")
    lines.append(
        "共有 runner の実行時間は同一コードでも 2 倍程度ばらつくため参考値。"
        "合計には前回結果を再利用した test の持ち越し値も含む。"
        f"⚠️ は +{REGRESSION_RATIO:.0%} 以上かつ +{REGRESSION_ABSOLUTE:g}s 以上の悪化。"
    )
    lines.append("")
    return "\n".join(lines) + "\n"


def load(path: Path) -> dict[str, Any]:
    with path.open() as f:
        return json.load(f)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--result", required=True, type=Path, help="merged-result.json")
    parser.add_argument(
        "--baseline",
        type=Path,
        help="比較対象の merged-result.json（存在しなければ差分なしで出力）",
    )
    parser.add_argument(
        "--output",
        type=Path,
        help="追記先（既定: $GITHUB_STEP_SUMMARY があればそこ）",
    )
    parser.add_argument("--max-rows", type=int, default=DEFAULT_MAX_ROWS)
    args = parser.parse_args(argv)

    if not args.result.exists():
        print(f"{args.result} が無いため実行時間サマリーを省略します。", file=sys.stderr)
        return 0

    baseline = None
    if args.baseline is not None and args.baseline.exists():
        baseline = load(args.baseline)

    markdown = render(load(args.result), baseline, max_rows=args.max_rows)
    print(markdown, end="")

    output = args.output
    if output is None:
        summary = os.environ.get("GITHUB_STEP_SUMMARY")
        output = Path(summary) if summary else None
    if output is not None:
        with output.open("a") as f:
            f.write(markdown)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
