from __future__ import annotations

import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from oj import clean_bundled, optimize_option_to_flag, pragma_flags, strip_preamble_pragmas

TEMPLATE_LIKE = """\
#pragma GCC optimize("Ofast")
#pragma GCC optimize("fast-math,unroll-all-loops")
#include <bits/stdc++.h>
#pragma GCC optimize("O0")
int main() {}
"""


class CleanBundledTest(unittest.TestCase):
    def test_drops_line_markers_pragma_once_and_blank_lines(self) -> None:
        text = '#line 1 "a.cpp"\n#pragma once\n\nint x;\n\n\nint y;\n'
        self.assertEqual(clean_bundled(text), "int x;\nint y;\n")


class OptimizeOptionToFlagTest(unittest.TestCase):
    def test_mapping(self) -> None:
        self.assertEqual(optimize_option_to_flag("O3"), "-O3")
        self.assertEqual(optimize_option_to_flag("Ofast"), "-Ofast")
        self.assertEqual(optimize_option_to_flag("unroll-loops"), "-funroll-loops")
        self.assertEqual(optimize_option_to_flag("-ffast-math"), "-ffast-math")


class PragmaFlagsTest(unittest.TestCase):
    def test_only_pragmas_before_stdcxx_include(self) -> None:
        self.assertEqual(
            pragma_flags(TEMPLATE_LIKE), ["-Ofast", "-ffast-math", "-funroll-all-loops"]
        )

    def test_separately_quoted_options(self) -> None:
        source = '#pragma GCC optimize("O3", "unroll-loops")\n#include <bits/stdc++.h>\n'
        self.assertEqual(pragma_flags(source), ["-O3", "-funroll-loops"])

    def test_without_include_reads_whole_source(self) -> None:
        self.assertEqual(pragma_flags('int a;\n#pragma GCC optimize("O2")\n'), ["-O2"])

    def test_no_pragmas(self) -> None:
        self.assertEqual(pragma_flags("#include <bits/stdc++.h>\n"), [])


class StripPreamblePragmasTest(unittest.TestCase):
    def test_blanks_only_preamble_pragmas_keeping_line_count(self) -> None:
        self.assertEqual(
            strip_preamble_pragmas(TEMPLATE_LIKE),
            '\n\n#include <bits/stdc++.h>\n#pragma GCC optimize("O0")\nint main() {}\n',
        )


if __name__ == "__main__":
    unittest.main()
