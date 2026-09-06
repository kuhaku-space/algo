from __future__ import annotations

import json
import re
import sys
import tempfile
import unittest
from pathlib import Path


sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from render_reference_site import ROOT, build_site  # noqa: E402


STATIC_DIR = ROOT / ".verify-helper" / "docs" / "static"
TAG_RE = re.compile(r"{%-?\s*(\w+)([^%]*?)-?%}")
BLOCK_TAGS = {"if", "for", "unless", "case", "capture", "tablerow", "raw", "comment"}


class LiquidTemplateTest(unittest.TestCase):
    """Jekyll をローカルで動かせないので、壊れやすい書き方を静的に弾く。"""

    def templates(self) -> list[Path]:
        return sorted(STATIC_DIR.glob("**/*.html"))

    def test_templates_exist(self) -> None:
        names = {path.name for path in self.templates()}
        self.assertIn("default.html", names)
        self.assertIn("reference.html", names)
        self.assertIn("sidebar.html", names)

    def test_block_tags_are_balanced(self) -> None:
        for path in self.templates():
            with self.subTest(template=path.name):
                stack: list[str] = []
                for tag, _ in TAG_RE.findall(path.read_text(encoding="utf-8")):
                    if tag in BLOCK_TAGS:
                        stack.append(tag)
                    elif tag.startswith("end"):
                        expected = tag.removeprefix("end")
                        self.assertTrue(stack, f"{path.name}: {tag} が余分です")
                        self.assertEqual(stack.pop(), expected, f"{path.name}: {tag} の対応が違います")
                self.assertEqual(stack, [], f"{path.name}: 閉じられていないタグがあります")

    def test_conditions_do_not_use_filters(self) -> None:
        # Liquid の if / unless は条件式にフィルタを書けない（黙って偽になる）。
        for path in self.templates():
            for tag, body in TAG_RE.findall(path.read_text(encoding="utf-8")):
                if tag in ("if", "unless", "elsif"):
                    with self.subTest(template=path.name, condition=body.strip()):
                        self.assertNotIn("|", body)

    def test_includes_exist(self) -> None:
        include_re = re.compile(r"{%-?\s*include\s+([\w./-]+)")
        for path in self.templates():
            for name in include_re.findall(path.read_text(encoding="utf-8")):
                with self.subTest(template=path.name, include=name):
                    self.assertTrue((STATIC_DIR / "_includes" / name).is_file())

    def test_layouts_referenced_by_the_renderer_exist(self) -> None:
        for layout in ("reference", "verification", "toppage", "page", "default"):
            with self.subTest(layout=layout):
                self.assertTrue((STATIC_DIR / "_layouts" / f"{layout}.html").is_file())


class OfflineSiteTest(unittest.TestCase):
    """生成物からサイトのソースツリーが組み上がることを確かめる。"""

    @classmethod
    def setUpClass(cls) -> None:
        cls._directory = tempfile.TemporaryDirectory()
        cls.destination = Path(cls._directory.name) / "_jekyll"
        build_site(
            root=ROOT,
            docs_dir=ROOT / ".verify-helper" / "docs",
            generated_dir=ROOT / "docs" / "generated",
            destination=cls.destination,
            verify_files_path=None,
            verify_result_path=None,
        )

    @classmethod
    def tearDownClass(cls) -> None:
        cls._directory.cleanup()

    def test_navigation_data_is_written(self) -> None:
        data = json.loads(
            (self.destination / "_data" / "reference.json").read_text(encoding="utf-8")
        )
        self.assertTrue(data["categories"])
        for category in data["categories"]:
            for header in category["headers"]:
                self.assertTrue(header["url"].endswith(".html"))
                self.assertTrue(header["icon"])

    def test_every_page_declares_a_layout(self) -> None:
        for path in self.destination.glob("**/*.md"):
            with self.subTest(page=path.name):
                self.assertTrue(
                    path.read_text(encoding="utf-8").startswith("---\nlayout:"),
                    f"{path} に layout がありません",
                )

    def test_internal_links_resolve(self) -> None:
        # `operator[](int)` のような本文中のコードと混ざらないよう、拡張子で絞る。
        link_re = re.compile(r"\]\((?!https?:|#)([^)\s]+?\.html)(#[^)]*)?\)")
        missing: list[str] = []
        for path in sorted((self.destination / "reference").glob("**/*.md")):
            for target, _ in link_re.findall(path.read_text(encoding="utf-8")):
                source = (path.parent / target.removesuffix(".html")).with_suffix(".md")
                if not source.is_file():
                    missing.append(f"{path.name} -> {target}")
        self.assertEqual(missing, [])

    def test_reference_pages_keep_their_navigation_key(self) -> None:
        page = self.destination / "reference" / "data_structure" / "union_find.md"
        front_matter = page.read_text(encoding="utf-8").split("---")[1]
        data = json.loads(re.search(r"^data: (.*)$", front_matter, re.M).group(1))
        self.assertEqual(data["kind"], "header")
        self.assertEqual(data["pageUrl"], "data_structure/union_find.html")
        self.assertIn("relations", data)


if __name__ == "__main__":
    unittest.main()
