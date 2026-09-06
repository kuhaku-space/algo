from __future__ import annotations

import json
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from render_reference_site import (
    LIBRARY_ALL_AC,
    TEST_ACCEPTED,
    TEST_WAITING_JUDGE,
    TEST_WRONG_ANSWER,
    build_site,
    embedded_code,
    library_icon,
    parse_front_matter,
    rewrite_links,
    test_icon,
)


class StatusIconTest(unittest.TestCase):
    def test_test_statuses(self) -> None:
        self.assertEqual(test_icon(frozenset({"success"})), TEST_ACCEPTED)
        self.assertEqual(test_icon(frozenset({"failure"})), TEST_WRONG_ANSWER)
        self.assertEqual(test_icon(frozenset({"skipped"})), TEST_WAITING_JUDGE)

    def test_library_status(self) -> None:
        self.assertEqual(library_icon(frozenset({"success"})), LIBRARY_ALL_AC)


class MarkdownTest(unittest.TestCase):
    def test_front_matter_keeps_quoted_values(self) -> None:
        values, content = parse_front_matter('---\ntitle: "素集合"\n---\n\n本文\n')
        self.assertEqual(values["title"], "素集合")
        self.assertEqual(content, "本文\n")

    def test_markdown_links_become_html_links(self) -> None:
        self.assertEqual(
            rewrite_links("[a](union_find/union_find.md) [b](../x.md#member-y)"),
            "[a](union_find/union_find.html) [b](../x.html#member-y)",
        )

    def test_code_spans_are_left_alone(self) -> None:
        self.assertEqual(rewrite_links("`operator[](int)`"), "`operator[](int)`")


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


class BuildSiteTest(unittest.TestCase):
    def build(self, root: Path) -> tuple[int, int]:
        (root / "lib" / "ds").mkdir(parents=True)
        (root / "test").mkdir()
        (root / "docs" / "generated" / "ds" / "sample").mkdir(parents=True)
        (root / "site-config" / "static" / "_layouts").mkdir(parents=True)
        (root / "lib" / "ds" / "sample.hpp").write_text(
            "#pragma once\nint sample();\n", encoding="utf-8"
        )
        (root / "test" / "sample.test.cpp").write_text(
            '#include "ds/sample.hpp"\nint main() {}\n', encoding="utf-8"
        )
        (root / "docs" / "generated" / "ds" / "sample.md").write_text(
            "---\n"
            'title: "見本"\n'
            'reference_kind: "header"\n'
            'reference_category: "ds"\n'
            'reference_slug: "ds/sample"\n'
            'reference_source: "lib/ds/sample.hpp"\n'
            'reference_include: "ds/sample.hpp"\n'
            "---\n\n"
            "# 見本\n\n[`sample`](sample/sample.md)\n",
            encoding="utf-8",
        )
        (root / "docs" / "generated" / "ds" / "sample" / "sample.md").write_text(
            "---\n"
            'title: "sample"\n'
            'reference_kind: "function"\n'
            'reference_category: "ds"\n'
            'reference_slug: "ds/sample"\n'
            'reference_source: "lib/ds/sample.hpp"\n'
            'reference_include: "ds/sample.hpp"\n'
            "---\n\n"
            "# sample\n",
            encoding="utf-8",
        )
        (root / "docs" / "generated" / "reference.json").write_text(
            json.dumps(
                {
                    "categories": [
                        {
                            "name": "ds",
                            "headers": [
                                {
                                    "name": "sample",
                                    "include": "ds/sample.hpp",
                                    "title": "見本",
                                    "url": "ds/sample.html",
                                    "entities": [
                                        {
                                            "name": "sample",
                                            "kind": "function",
                                            "url": "ds/sample/sample.html",
                                        }
                                    ],
                                }
                            ],
                        }
                    ],
                    "entries": [
                        {
                            "name": "sample",
                            "kind": "function",
                            "header": "ds/sample.hpp",
                            "title": "見本",
                            "url": "ds/sample/sample.html",
                        }
                    ],
                }
            ),
            encoding="utf-8",
        )
        (root / "site-config" / "_config.yml").write_text("title: Test\n", encoding="utf-8")
        (root / "site-config" / "index.md").write_text("Index\n", encoding="utf-8")

        verify_files = root / "verify_files.json"
        verify_files.write_text(
            json.dumps(
                {
                    "files": {
                        "lib/ds/sample.hpp": {
                            "dependencies": ["lib/ds/sample.hpp"],
                            "verification": [],
                            "document_attributes": {"links": []},
                        },
                        "test/sample.test.cpp": {
                            "dependencies": ["lib/ds/sample.hpp", "test/sample.test.cpp"],
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
                                {"verification_name": "g++", "status": "success"}
                            ]
                        }
                    }
                }
            ),
            encoding="utf-8",
        )
        return build_site(
            root=root,
            docs_dir=root / "site-config",
            generated_dir=root / "docs" / "generated",
            destination=root / "_jekyll",
            verify_files_path=verify_files,
            verify_result_path=verify_result,
        )

    def test_builds_pages_from_verification_json(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            reference_count, verification_count = self.build(root)

            self.assertEqual((reference_count, verification_count), (2, 1))
            header_page = (root / "_jekyll" / "reference" / "ds" / "sample.md").read_text(
                encoding="utf-8"
            )
            self.assertIn('"icon":"LIBRARY_ALL_AC"', header_page)
            self.assertIn('"type":"検証プログラム"', header_page)
            self.assertIn("[`sample`](sample/sample.html)", header_page)

            entity_page = (
                root / "_jekyll" / "reference" / "ds" / "sample" / "sample.md"
            ).read_text(encoding="utf-8")
            self.assertIn('"pageUrl":"ds/sample/sample.html"', entity_page)
            self.assertNotIn("relations", entity_page)

            navigation = json.loads(
                (root / "_jekyll" / "_data" / "reference.json").read_text(encoding="utf-8")
            )
            self.assertEqual(
                navigation["categories"][0]["headers"][0]["icon"], LIBRARY_ALL_AC
            )

            test_page = (root / "_jekyll" / "test" / "sample.test.cpp.md").read_text(
                encoding="utf-8"
            )
            self.assertIn('"url":"reference/ds/sample.html"', test_page)

    def test_offline_mode_needs_no_verification_data(self) -> None:
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            self.build(root)
            reference_count, verification_count = build_site(
                root=root,
                docs_dir=root / "site-config",
                generated_dir=root / "docs" / "generated",
                destination=root / "_offline",
                verify_files_path=None,
                verify_result_path=None,
            )
            self.assertEqual((reference_count, verification_count), (2, 1))


if __name__ == "__main__":
    unittest.main()
