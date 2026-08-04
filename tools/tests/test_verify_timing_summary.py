from __future__ import annotations

import sys
import unittest
from pathlib import Path


sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from verify_timing_summary import (  # noqa: E402
    aggregate,
    collect,
    format_change,
    format_seconds,
    is_regression,
    reexecuted,
    render,
)


def verification(
    *,
    status: str = "success",
    elapsed: float = 1.0,
    slowest: float | None = 0.5,
    executed_at: str | None = "2026-08-04T12:00:00Z",
    name: str | None = "g++",
) -> dict[str, object]:
    return {
        "verification_name": name,
        "status": status,
        "elapsed": elapsed,
        "slowest": slowest,
        "last_execution_time": executed_at,
    }


def result(files: dict[str, list[dict[str, object]]]) -> dict[str, object]:
    return {"files": {path: {"verifications": vs} for path, vs in files.items()}}


class CollectTest(unittest.TestCase):
    def test_skips_verifications_without_timings(self) -> None:
        document = result(
            {
                "test/a.test.cpp": [verification(elapsed=2.0)],
                # A skipped verification only carries bookkeeping overhead.
                "test/b.test.cpp": [
                    verification(status="skipped", elapsed=3e-06, slowest=None)
                ],
            }
        )

        timings = collect(document)

        self.assertEqual([t.path for t in timings.values()], ["test/a.test.cpp"])

    def test_keeps_every_verification_of_a_file_apart(self) -> None:
        document = result(
            {
                "test/a.test.cpp": [
                    verification(name="g++", elapsed=1.0),
                    verification(name="clang++", elapsed=2.0),
                ]
            }
        )

        timings = collect(document)

        self.assertEqual(len(timings), 2)
        self.assertEqual(
            sorted(t.label for t in timings.values()),
            ["a", "a (clang++)"],
        )


class AggregateTest(unittest.TestCase):
    def test_sums_elapsed_and_picks_the_worst_testcase(self) -> None:
        document = result(
            {
                "test/a.test.cpp": [verification(elapsed=2.0, slowest=0.5)],
                "test/b.test.cpp": [verification(elapsed=3.0, slowest=1.5)],
                "test/c.test.cpp": [verification(elapsed=1.0, slowest=None)],
            }
        )

        totals = aggregate(collect(document).values())

        self.assertEqual(totals.count, 3)
        self.assertAlmostEqual(totals.total, 6.0)
        self.assertIsNotNone(totals.worst)
        assert totals.worst is not None
        self.assertEqual(totals.worst.path, "test/b.test.cpp")


class ReexecutedTest(unittest.TestCase):
    def test_carried_over_timings_are_not_reported_as_changes(self) -> None:
        base = collect(
            result({"test/a.test.cpp": [verification(executed_at="2026-07-30T00:00:00Z")]})
        )
        now = collect(
            result({"test/a.test.cpp": [verification(executed_at="2026-07-30T00:00:00Z")]})
        )

        self.assertEqual(reexecuted(now, base), [])

    def test_reports_a_rerun_even_when_the_timing_is_unchanged(self) -> None:
        base = collect(
            result({"test/a.test.cpp": [verification(executed_at="2026-07-30T00:00:00Z")]})
        )
        now = collect(
            result({"test/a.test.cpp": [verification(executed_at="2026-08-04T00:00:00Z")]})
        )

        rows = reexecuted(now, base)

        self.assertEqual(len(rows), 1)
        self.assertIsNotNone(rows[0][1])

    def test_new_tests_have_no_baseline_counterpart(self) -> None:
        rows = reexecuted(collect(result({"test/a.test.cpp": [verification()]})), {})

        self.assertEqual(len(rows), 1)
        self.assertIsNone(rows[0][1])

    def test_orders_rows_by_absolute_total_change(self) -> None:
        base = collect(
            result(
                {
                    "test/small.test.cpp": [
                        verification(elapsed=1.0, executed_at="2026-07-30T00:00:00Z")
                    ],
                    "test/big.test.cpp": [
                        verification(elapsed=10.0, executed_at="2026-07-30T00:00:00Z")
                    ],
                }
            )
        )
        now = collect(
            result(
                {
                    "test/small.test.cpp": [
                        verification(elapsed=1.5, executed_at="2026-08-04T00:00:00Z")
                    ],
                    "test/big.test.cpp": [
                        verification(elapsed=4.0, executed_at="2026-08-04T00:00:00Z")
                    ],
                }
            )
        )

        self.assertEqual(
            [row[0].label for row in reexecuted(now, base)],
            ["big", "small"],
        )


class FormattingTest(unittest.TestCase):
    def test_formats_seconds_by_magnitude(self) -> None:
        self.assertEqual(format_seconds(0.0021), "2ms")
        self.assertEqual(format_seconds(1.234), "1.23s")
        self.assertEqual(format_seconds(48.886), "48.9s")
        self.assertEqual(format_seconds(300.4), "300s")

    def test_marks_a_missing_baseline_instead_of_pretending_no_change(self) -> None:
        self.assertEqual(format_change(22.86, None), "22.9s（基準なし）")
        self.assertEqual(format_change(None, 1.0), "—")
        self.assertEqual(format_change(80.9, 48.9), "48.9s → 80.9s (+65%)")

    def test_regression_needs_both_a_relative_and_an_absolute_jump(self) -> None:
        self.assertTrue(is_regression(2.88, 1.0))
        # Large ratio but a few milliseconds of runner noise.
        self.assertFalse(is_regression(0.003, 0.002))
        # Large absolute jump on an already slow test.
        self.assertFalse(is_regression(101.0, 100.0))
        self.assertFalse(is_regression(1.0, 2.0))


class RenderTest(unittest.TestCase):
    def test_diff_report_lists_only_reexecuted_tests(self) -> None:
        base = result(
            {
                "test/slow.test.cpp": [
                    verification(
                        elapsed=48.9, slowest=2.88, executed_at="2026-07-30T00:00:00Z"
                    )
                ],
                "test/stable.test.cpp": [
                    verification(
                        elapsed=1.0, slowest=0.5, executed_at="2026-07-30T00:00:00Z"
                    )
                ],
            }
        )
        now = result(
            {
                "test/slow.test.cpp": [
                    verification(
                        elapsed=80.9, slowest=5.29, executed_at="2026-08-04T00:00:00Z"
                    )
                ],
                "test/stable.test.cpp": [
                    verification(
                        elapsed=1.0, slowest=0.5, executed_at="2026-07-30T00:00:00Z"
                    )
                ],
            }
        )

        markdown = render(now, base)

        self.assertIn("48.9s → 80.9s (+65%)", markdown)
        self.assertIn("2.88s → 5.29s (+84%)", markdown)
        self.assertIn("⚠️ slow", markdown)
        self.assertNotIn("stable", markdown)
        self.assertIn("1 件 / 2 件", markdown)

    def test_reports_when_nothing_was_reexecuted(self) -> None:
        document = result(
            {"test/a.test.cpp": [verification(executed_at="2026-07-30T00:00:00Z")]}
        )

        markdown = render(document, document)

        self.assertIn("新しい計測はありません", markdown)

    def test_counts_tests_that_only_exist_in_the_baseline(self) -> None:
        base = result(
            {
                "test/renamed.test.cpp": [
                    verification(executed_at="2026-07-30T00:00:00Z")
                ]
            }
        )
        now = result({"test/new_name.test.cpp": [verification()]})

        markdown = render(now, base)

        self.assertIn("ベースラインにのみ存在", markdown)

    def test_without_a_baseline_ranks_the_slowest_tests(self) -> None:
        document = result(
            {
                "test/fast.test.cpp": [verification(elapsed=1.0, slowest=0.1)],
                "test/slow.test.cpp": [verification(elapsed=9.0, slowest=3.0)],
            }
        )

        markdown = render(document, None, max_rows=1)

        self.assertIn("最も遅い test", markdown)
        self.assertIn("| slow ", markdown)
        self.assertNotIn("| fast ", markdown)

    def test_truncation_is_reported_instead_of_silently_dropping_rows(self) -> None:
        base = result(
            {
                f"test/t{i}.test.cpp": [
                    verification(elapsed=1.0, executed_at="2026-07-30T00:00:00Z")
                ]
                for i in range(3)
            }
        )
        now = result(
            {
                f"test/t{i}.test.cpp": [
                    verification(elapsed=2.0, executed_at="2026-08-04T00:00:00Z")
                ]
                for i in range(3)
            }
        )

        markdown = render(now, base, max_rows=2)

        self.assertIn("合計 3 件のうち差分の大きい 2 件のみ表示", markdown)


if __name__ == "__main__":
    unittest.main()
