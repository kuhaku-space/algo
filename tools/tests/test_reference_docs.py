from __future__ import annotations

import re
import sys
import unittest
from collections.abc import Iterator
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from reference.check import load_config, unformatted_math
from reference.model import DocBlock, Entity, Header, Overload
from reference.parse import (
    extract_entities,
    format_signature,
    library_headers,
    parse_doc_block,
    parse_header,
    problem_index,
    scope_contexts,
    split_requires_clause,
    split_template_prefix,
    symbol_and_kind,
)
from reference.render import (
    SEGMENT_RE,
    ReferenceRenderer,
    Section,
    escape_text,
    overload_groups,
    render_notes,
    render_parameters,
    render_result,
    signature_block,
    slugify,
)

# kramdown が出力時に取り除くエスケープ（ESCAPED_CHARS）。
KRAMDOWN_ESCAPED = re.compile(r"\\([\\.*_+`<>()\[\]{}#!:|\"'$=-])")


def kramdown_unescape(text: str) -> str:
    """kramdown のエスケープ解除を模す。コードスパンの中は解除されない。"""
    parts = SEGMENT_RE.split(text)
    for index, part in enumerate(parts):
        if index % 2 == 0 or part.startswith("$"):
            parts[index] = KRAMDOWN_ESCAPED.sub(r"\1", part)
    return "".join(parts)


def doc_texts(header: Header) -> Iterator[str]:
    """ヘッダに書かれた本文（例と署名を除く）をすべて並べる。"""
    blocks = [header.doc]
    for entity in header.entities:
        for item in entity.iter_all():
            blocks.extend(overload.doc for overload in item.overloads)
    for block in blocks:
        yield block.brief
        yield from block.details
        yield from (text for _, text in block.tparams)
        yield from (text for _, text in block.params)
        yield from block.returns
        yield from block.complexities
        yield from block.preconditions
        yield from block.notes
        yield from block.warnings
        yield from block.references


def split_cells(line: str) -> list[str]:
    """表の行をセルに分ける。コードスパンの中の `|` は区切りにならない。"""
    cells: list[str] = []
    current = ""
    for index, part in enumerate(SEGMENT_RE.split(line)):
        if index % 2:
            current += part
            continue
        pieces = re.split(r"(?<!\\)\|", part)
        current += pieces[0]
        for piece in pieces[1:]:
            cells.append(current)
            current = piece
    cells.append(current)
    return cells[1:-1]


def escapable_chunks(page: str) -> Iterator[str]:
    """ページのうち、退避済みでなければならない断片（地の文・表のセル）。"""
    body = page.split("---\n", 2)[-1]
    in_code = False
    for line in body.splitlines():
        if line.startswith("```"):
            in_code = not in_code
            continue
        if in_code or line.startswith("#"):
            continue
        for cell in split_cells(line) if line.startswith("|") else [line]:
            # `<br>` はセルの中身を退避したあとに挟むので、区切りとして扱う。
            yield from cell.split("<br>")


def doc(text: str) -> DocBlock:
    return parse_doc_block([f"/// {line}" for line in text.splitlines()])


class DocBlockTest(unittest.TestCase):
    def test_reads_the_common_tags(self) -> None:
        block = doc(
            "@brief 値を足す\n"
            "@details 詳細\n"
            "@tparam T 要素型\n"
            "@param k 位置\n"
            "  0-indexed\n"
            "@return 足した値\n"
            "@pre `0 <= k`\n"
            "@complexity $O(\\log n)$\n"
            "@see https://example.com\n"
        )
        self.assertEqual(block.brief, "値を足す")
        self.assertEqual(block.details, ["詳細"])
        self.assertEqual(block.tparams, [("T", "要素型")])
        self.assertEqual(block.params, [("k", "位置 0-indexed")])
        self.assertEqual(block.returns, ["足した値"])
        self.assertEqual(block.preconditions, ["`0 <= k`"])
        self.assertEqual(block.complexities, ["$O(\\log n)$"])
        self.assertEqual(block.references, ["https://example.com"])

    def test_keeps_example_code_verbatim(self) -> None:
        block = doc(
            "@brief 例つき\n"
            "@code\n"
            '#include "a.hpp"\n'
            "int main() {\n"
            "    return 0;\n"
            "}\n"
            "@endcode\n"
        )
        self.assertEqual(
            block.examples,
            ['#include "a.hpp"\nint main() {\n    return 0;\n}'],
        )

    def test_file_documentation_is_flagged(self) -> None:
        self.assertTrue(doc("@file\n@brief ヘッダの概要\n").is_file_doc)


class DeclarationTest(unittest.TestCase):
    def test_template_argument_with_shift_is_not_a_bracket(self) -> None:
        prefix, rest = split_template_prefix("template <int N = (1 << 22)> struct Sieve")
        self.assertEqual(prefix, "template <int N = (1 << 22)>")
        self.assertEqual(rest, "struct Sieve")

    def test_requires_clause_is_separated_from_the_declaration(self) -> None:
        clause, rest = split_requires_clause(
            "requires std::invocable<F, int, int, bool> bool unite(int x, int y, F f)"
        )
        self.assertEqual(clause, "requires std::invocable<F, int, int, bool>")
        self.assertEqual(rest, "bool unite(int x, int y, F f)")

    def test_requires_clause_with_a_parenthesised_constraint(self) -> None:
        clause, rest = split_requires_clause("requires (m >= 1) struct static_modint")
        self.assertEqual(clause, "requires (m >= 1)")
        self.assertEqual(rest, "struct static_modint")

    def test_signature_is_broken_into_cpprefjp_style_lines(self) -> None:
        self.assertEqual(
            format_signature(
                "template <class F> requires std::invocable<F, int> void each(F f)"
            ),
            "template <class F>\nrequires std::invocable<F, int>\nvoid each(F f);",
        )

    def test_kinds_are_recognised(self) -> None:
        cases = [
            ("struct union_find", "", ("union_find", "class", False)),
            ("template <class T> class Matrix", "", ("Matrix", "class", False)),
            ("concept graph_type = requires", "", ("graph_type", "concept", False)),
            ("using mint = static_modint", "", ("mint", "alias", False)),
            ("using base::_v;", "", ("_v", "alias", False)),
            ("int &operator[](std::size_t x)", "S", ("operator[]", "operator", False)),
            ("constexpr operator int() const", "S", ("operator int", "operator", False)),
            ("explicit union_find(int n)", "union_find", ("union_find", "constructor", False)),
            ("static constexpr int mod()", "S", ("mod", "function", True)),
            ("constexpr int kInf = 1", "", ("kInf", "variable", False)),
        ]
        for declaration, owner, expected in cases:
            with self.subTest(declaration=declaration):
                self.assertEqual(symbol_and_kind(declaration, owner), expected)


class ScopeTest(unittest.TestCase):
    SOURCE = """\
namespace internal {
/// @brief 内部の型
struct Helper {
    /// @brief 使える
    int visible();

  private:
    /// @brief 見せない
    int hidden();
};
}  // namespace internal

/// @brief 表の型
struct Public {
    /// @brief メンバ
    int member();
};
"""

    def test_namespace_and_access_are_tracked(self) -> None:
        contexts = scope_contexts(self.SOURCE.splitlines())
        line = self.SOURCE.splitlines().index("    int hidden();")
        self.assertEqual(contexts[line].namespace, "internal")
        self.assertEqual(contexts[line].class_path, ("Helper",))
        self.assertFalse(contexts[line].public)

    def test_private_members_are_dropped_and_members_are_nested(self) -> None:
        _, entities = extract_entities(self.SOURCE)
        names = {entity.name: entity for entity in entities}
        self.assertEqual(set(names), {"Helper", "Public"})
        self.assertTrue(names["Helper"].is_internal)
        self.assertEqual([m.name for m in names["Helper"].members], ["visible"])
        self.assertEqual([m.name for m in names["Public"].members], ["member"])

    def test_documented_members_of_an_undocumented_class_are_kept(self) -> None:
        _, entities = extract_entities(
            "struct Silent {\n    /// @brief 説明あり\n    int value();\n};\n"
        )
        self.assertEqual([entity.name for entity in entities], ["Silent"])
        self.assertEqual([m.name for m in entities[0].members], ["value"])


class OverloadTest(unittest.TestCase):
    def entity(self, briefs: list[str]) -> Entity:
        return Entity(
            name="f",
            kind="function",
            overloads=[
                Overload(signature=f"void f({index});", doc=DocBlock(brief=brief))
                for index, brief in enumerate(briefs)
            ],
        )

    def test_identical_documentation_is_merged(self) -> None:
        groups = overload_groups(self.entity(["同じ", "同じ"]))
        self.assertEqual([numbers for numbers, _ in groups], [[1, 2]])

    def test_different_documentation_is_numbered(self) -> None:
        entity = self.entity(["一つ目", "二つ目"])
        groups = overload_groups(entity)
        self.assertEqual([numbers for numbers, _ in groups], [[1], [2]])
        self.assertIn("// (2)", signature_block(entity))


class SlugTest(unittest.TestCase):
    def test_operators_get_readable_file_names(self) -> None:
        self.assertEqual(slugify("operator[]"), "operator-subscript")
        self.assertEqual(slugify("operator<<"), "operator-shift-left")
        self.assertEqual(slugify("operator int"), "operator-int")
        self.assertEqual(slugify("union_find"), "union_find")


class LibraryTest(unittest.TestCase):
    """実際のヘッダ群に対して、生成物が満たすべき形を確かめる。"""

    @classmethod
    def setUpClass(cls) -> None:
        problems = problem_index()
        cls.config = load_config()
        cls.headers = [parse_header(path, problems) for path in library_headers()]
        cls.public = [
            header
            for header in cls.headers
            if header.category not in cls.config.excluded_directories
        ]
        cls.renderer = ReferenceRenderer(cls.headers)
        cls.files = cls.renderer.render_all()

    def test_every_public_header_has_a_summary(self) -> None:
        for header in self.public:
            with self.subTest(header=header.include):
                self.assertNotEqual(header.title, header.include)

    def test_every_entity_has_a_page(self) -> None:
        for header in self.headers:
            for entity in header.entities:
                with self.subTest(entity=f"{header.include}::{entity.name}"):
                    self.assertIn(
                        self.renderer.entity_page_path(header, entity), self.files
                    )

    def test_header_pages_show_the_include_directive(self) -> None:
        for header in self.public:
            content = self.files[self.renderer.header_page_path(header)]
            with self.subTest(header=header.include):
                self.assertIn(f'#include "{header.include}"', content)
                self.assertIn("## インクルード", content)

    def test_entity_pages_open_with_a_signature(self) -> None:
        for header in self.headers:
            for entity in header.entities:
                content = self.files[self.renderer.entity_page_path(header, entity)]
                with self.subTest(entity=f"{header.include}::{entity.name}"):
                    self.assertIn("```cpp", content)
                    self.assertTrue(content.count("# " + entity.name) >= 1)

    def test_page_paths_are_unique_ignoring_case(self) -> None:
        seen: dict[str, str] = {}
        for name in self.files:
            key = name.lower()
            self.assertNotIn(key, seen, f"{name} と {seen.get(key)} が衝突します")
            seen[key] = name

    def test_pages_are_escaped_for_kramdown(self) -> None:
        """生成ページの地の文・表のセルが過不足なく退避されていること。"""
        for name, content in self.files.items():
            if not name.endswith(".md"):
                continue
            for chunk in escapable_chunks(content):
                with self.subTest(page=name, chunk=chunk):
                    self.assertEqual(escape_text(kramdown_unescape(chunk)), chunk)

    def test_escaping_round_trips_for_every_doc_text(self) -> None:
        """退避した本文は kramdown が元に戻す（MathJax に原文が届く）。"""
        for header in self.headers:
            for text in (header.title, header.summary, *doc_texts(header)):
                with self.subTest(header=header.include, text=text):
                    self.assertEqual(kramdown_unescape(escape_text(text)), text)


class EscapeTest(unittest.TestCase):
    def test_pipes_in_math_are_escaped(self) -> None:
        section = Section()
        render_result(section, doc("@complexity 初期間隔を $D=|ok-ng|$ として $O(\\log D)$"))
        self.assertIn(r"- 初期間隔を $D=\|ok-ng\|$ として $O(\\log D)$", section.render())

    def test_pipes_in_a_table_cell_are_escaped(self) -> None:
        section = Section()
        render_parameters(section, doc("@param x $|x|$ の上限"))
        self.assertIn(r"| `x` | $\|x\|$ の上限 |", section.render())

    def test_pipes_in_a_code_span_are_kept(self) -> None:
        section = Section()
        render_notes(section, doc("@note `a | b` はビット和"))
        self.assertIn("- `a | b` はビット和", section.render())

    def test_backslashes_in_math_are_doubled(self) -> None:
        section = Section()
        render_result(section, doc(r"@complexity $O(\log \mathrm{max\_denominator})$"))
        self.assertIn(r"- $O(\\log \\mathrm{max\\\_denominator})$", section.render())

    def test_quotes_and_tags_in_math_are_escaped(self) -> None:
        section = Section()
        render_notes(section, doc(r"@note $\int h' / h \, dx$ と $a < b$"))
        self.assertIn(r"- $\\int h\' / h \\, dx$ と $a \< b$", section.render())

    def test_type_arguments_in_prose_are_escaped(self) -> None:
        section = Section()
        render_result(section, doc("@return std::vector<mint> 逆元"))
        self.assertIn(r"std::vector\<mint> 逆元", section.render())

    def test_escaping_round_trips(self) -> None:
        for text in (
            r"$O(n \log n)$ と `a | b` と std::vector<mint>",
            r"$\{0, \ldots, n-1\}$ の $|x|$",
            r"$2^{\mathrm{FFT\_MAX\_LOG}}$",
            "**強調** と [リンク](https://example.com)",
        ):
            with self.subTest(text=text):
                self.assertEqual(kramdown_unescape(escape_text(text)), text)


if __name__ == "__main__":
    unittest.main()


class UnformattedMathTest(unittest.TestCase):
    def scan(self, source: str) -> list[str]:
        import tempfile

        with tempfile.TemporaryDirectory() as name:
            root = Path(name)
            (root / "sample.hpp").write_text(source, encoding="utf-8")
            return unformatted_math(root)

    def test_reports_bare_complexity(self) -> None:
        self.assertEqual(len(self.scan("/// @complexity O(n log n)\n")), 1)

    def test_reports_latex_outside_math(self) -> None:
        self.assertEqual(len(self.scan("/// @brief \\sum_{i=1}^{n} f(i)\n")), 1)

    def test_accepts_math_and_code_spans(self) -> None:
        source = (
            "/// @brief $\\sum_{i=1}^{n} f(i)$ を返す\n"
            "/// @details `a[x]^{-1}` は識別子、$2^{24}$ は数式\n"
            "/// @complexity $O(n \\log n)$\n"
        )
        self.assertEqual(self.scan(source), [])

    def test_ignores_examples(self) -> None:
        source = (
            "/// @code\n"
            "/// int x = 1 << 24;  // O(1)\n"
            "/// @endcode\n"
        )
        self.assertEqual(self.scan(source), [])

    def test_library_headers_are_clean(self) -> None:
        self.assertEqual(unformatted_math(), [])
