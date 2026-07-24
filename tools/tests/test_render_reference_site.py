from __future__ import annotations

import json
import tempfile
import unittest
from pathlib import Path

import sys


sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from render_reference_site import (  # noqa: E402
    LIBRARY_ALL_AC,
    TEST_ACCEPTED,
    TEST_WAITING_JUDGE,
    TEST_WRONG_ANSWER,
    build_site,
    embedded_code,
    library_icon,
    test_icon,
)


class StatusIconTest(unittest.TestCase):
    def test_test_statuses(self) -> None:
        self.assertEqual(test_icon(frozenset({"success"})), TEST_ACCEPTED)
        self.assertEqual(test_icon(frozenset({"failure"})), TEST_WRONG_ANSWER)
        self.assertEqual(test_icon(frozenset({"skipped"})), TEST_WAITING_JUDGE)

    def test_library_status(self) -> None:
        self.assertEqual(library_icon(frozenset({"success"})), LIBRARY_ALL_AC)


class EmbeddedCodeTest(unittest.TestCase):
    def test_omits_optional_bundle_errors(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "sample.hpp").write_text("raw source\n", encoding="utf-8")
            (root / "bundled.hpp").write_text("bundled source\n", encoding="utf-8")
            (root / "bundle-error.txt").write_text("traceback\n", encoding="utf-8")

            result = embedded_code(
                root,
                "sample.hpp",
                {
                    "additonal_sources": [
                        {"name": "bundled", "path": "bundled.hpp"},
                        {"name": "bundle error", "path": "bundle-error.txt"},
                    ]
                },
            )

            self.assertEqual(
                result,
                [
                    {"name": "default", "code": "raw source\n"},
                    {"name": "bundled", "code": "bundled source\n"},
                ],
            )


class SiteTemplateTest(unittest.TestCase):
    def test_custom_components_do_not_inherit_minimal_theme_element_styles(
        self,
    ) -> None:
        includes = (
            Path(__file__).resolve().parents[2]
            / ".verify-helper"
            / "docs"
            / "static"
            / "_includes"
        )
        toppage = (includes / "toppage_body.html").read_text(encoding="utf-8")
        document_footer = (includes / "document_footer.html").read_text(
            encoding="utf-8"
        )
        head = (includes / "head-custom2.html").read_text(encoding="utf-8")

        self.assertIn('<div class="reference-browser"', toppage)
        self.assertIn('<div class="reference-category"', toppage)
        self.assertNotIn('<section class="reference-', toppage)
        self.assertIn('<nav class="reference-footer"', document_footer)
        self.assertNotIn('<footer class="reference-footer"', document_footer)
        self.assertIn("mathjax@4.1.3/tex-chtml.js", head)
        self.assertIn('skipHtmlTags: ["script", "noscript", "style"', head)


class BuildSiteTest(unittest.TestCase):
    def test_builds_pages_from_verification_json(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "lib").mkdir()
            (root / "test").mkdir()
            (root / "docs").mkdir()
            (root / "site-config" / "static").mkdir(parents=True)
            (root / "lib" / "sample.hpp").write_text(
                "#pragma once\nint sample();\n",
                encoding="utf-8",
            )
            (root / "test" / "sample.test.cpp").write_text(
                '#include "sample.hpp"\nint main() {}\n',
                encoding="utf-8",
            )
            (root / "docs" / "sample.md").write_text(
                "---\n"
                "title: サンプル\n"
                "documentation_of: //lib/sample.hpp\n"
                "---\n"
                "説明です。\n",
                encoding="utf-8",
            )
            (root / "site-config" / "_config.yml").write_text(
                "title: Test\n",
                encoding="utf-8",
            )
            (root / "site-config" / "index.md").write_text(
                "Index\n",
                encoding="utf-8",
            )
            verify_files = root / "verify_files.json"
            verify_files.write_text(
                json.dumps(
                    {
                        "files": {
                            "lib/sample.hpp": {
                                "dependencies": ["lib/sample.hpp"],
                                "verification": [],
                                "document_attributes": {"links": []},
                            },
                            "test/sample.test.cpp": {
                                "dependencies": [
                                    "lib/sample.hpp",
                                    "test/sample.test.cpp",
                                ],
                                "verification": [
                                    {
                                        "name": "g++",
                                        "type": "problem",
                                        "problem": "https://example.com/problem",
                                    }
                                ],
                                "document_attributes": {"links": []},
                            },
                        }
                    }
                ),
                encoding="utf-8",
            )
            verify_result = root / "merged-result.json"
            verify_result.write_text(
                json.dumps(
                    {
                        "files": {
                            "test/sample.test.cpp": {
                                "verifications": [
                                    {
                                        "verification_name": "g++",
                                        "status": "success",
                                    }
                                ]
                            }
                        }
                    }
                ),
                encoding="utf-8",
            )

            library_count, verification_count = build_site(
                root=root,
                docs_dir=root / "site-config",
                destination=root / "_jekyll",
                verify_files_path=verify_files,
                verify_result_path=verify_result,
            )

            self.assertEqual((library_count, verification_count), (1, 1))
            library_page = (root / "_jekyll" / "lib" / "sample.hpp.md").read_text(
                encoding="utf-8"
            )
            index = (root / "_jekyll" / "index.md").read_text(encoding="utf-8")
            self.assertIn('"verificationStatus":"LIBRARY_ALL_AC"', library_page)
            self.assertIn('"type":"Verified with"', library_page)
            self.assertIn("説明です。", library_page)
            self.assertIn('"url":"lib/sample.hpp.html"', index)


if __name__ == "__main__":
    unittest.main()
