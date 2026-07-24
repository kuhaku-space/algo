from __future__ import annotations

import sys
import unittest
from pathlib import Path


sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from reference_docs import (  # noqa: E402
    DOXYGEN_RE,
    ROOT,
    DocEntity,
    display_signature,
    extract_doc_entities,
    group_doc_entities,
    load_config,
    public_headers,
    render_entity,
    render_entity_group,
    render_generated_page,
    replace_api_section,
    signature_opens_scope,
    strip_constructor_initializer,
)


class GeneratedApiTableTest(unittest.TestCase):
    def test_replaces_only_the_api_section_in_a_manual_page(self) -> None:
        manual = "intro\n\n## API\n\nold\n\n## 補足\n\nkeep\n"
        generated = "generated\n\n## API\n\nnew\n\n## 補足\n\nignore\n"

        self.assertEqual(
            replace_api_section(manual, generated),
            "intro\n\n## API\n\nnew\n\n## 補足\n\nkeep\n",
        )

    def test_all_generated_api_rows_have_descriptions_and_complexities(self) -> None:
        for header in public_headers(load_config()):
            with self.subTest(header=header.relative_to(ROOT).as_posix()):
                page = render_generated_page(header)
                api = page.split("## API\n\n", 1)[1].split("\n\n## 補足", 1)[0]
                self.assertIn("\n| `", api)
                self.assertNotIn(" | — |", api)

    def test_all_public_headers_have_source_doxygen(self) -> None:
        missing = []
        unextractable = []
        for header in public_headers(load_config()):
            source = header.read_text(encoding="utf-8")
            if not DOXYGEN_RE.search(source):
                missing.append(header.relative_to(ROOT).as_posix())
            elif not extract_doc_entities(source):
                unextractable.append(header.relative_to(ROOT).as_posix())

        self.assertEqual(missing, [])
        self.assertEqual(unextractable, [])

    def test_template_function_is_not_treated_as_a_type_scope(self) -> None:
        page = render_generated_page(ROOT / "lib" / "convolution" / "garner.hpp")

        self.assertIn(
            "`template <class T> int garner(std::vector<T> r, "
            "std::vector<int> m, const int mod)`",
            page,
        )
        self.assertIn(
            "`template <int mod> int garner(std::vector<int> r, "
            "std::vector<int> m)`",
            page,
        )
        self.assertEqual(page.count("\n| `"), 2)

    def test_constrained_type_is_treated_as_a_type_scope(self) -> None:
        page = render_generated_page(
            ROOT / "lib" / "data_structure" / "dynamic_sequence.hpp"
        )

        self.assertNotIn(
            "`template <class S, class F = void> requires monoid<S>",
            page,
        )
        self.assertIn("| `DynamicSequence()` |", page)

    def test_template_template_function_is_not_treated_as_a_type_scope(self) -> None:
        signature = (
            "template <template <class...> class Heap, class G> "
            "std::vector<int> shortest_path(const G &g)"
        )

        self.assertFalse(signature_opens_scope(signature))
        page = render_generated_page(ROOT / "lib" / "graph" / "shortest_path.hpp")
        self.assertIn(
            "`template <template <class...> class Heap = dijkstra_priority_queue, "
            "properly_weighted_graph_type G, class T = graph_weight_t<G>> "
            "std::vector<T> shortest_path",
            page,
        )

    def test_renders_complete_signature_in_api_column(self) -> None:
        row = render_entity(
            DocEntity(
                signature="template <class T> struct flip_set",
                brief="flip set",
            ),
            1,
        )

        self.assertEqual(
            row,
            "| `template <class T> struct flip_set` | flip set | — |",
        )

    def test_generated_page_has_no_declaration_column(self) -> None:
        page = render_generated_page(ROOT / "lib" / "data_structure" / "flip_set.hpp")

        self.assertIn("| API | 内容 | 計算量 |", page)
        self.assertNotIn("| API | 宣言 |", page)
        self.assertIn(
            "| `flip_set()` | 空の集合を構築する | $O(1)$ |",
            page,
        )
        self.assertNotIn("`template <class T> struct flip_set`", page)

    def test_interval_page_groups_public_overloads(self) -> None:
        page = render_generated_page(ROOT / "lib" / "algorithm" / "interval.hpp")

        self.assertNotIn("`namespace open_interval`", page)
        self.assertNotIn("`namespace closed_interval`", page)
        self.assertIn('title: "区間演算"', page)
        self.assertIn(
            "半開区間 $[l,r)$ と閉区間 $[l,r]$ の包含・交差判定と共通部分を提供する。",
            page,
        )
        self.assertIn(
            "| `open_interval::is_include` | "
            "2つの半開区間の一方が他方を包含していれば true を返す | $O(1)$ |",
            page,
        )
        self.assertIn(
            "| `template <std::integral T> bool open_interval::is_intersect"
            "(T l1, T r1, T l2, T r2)`<br>"
            "`template <std::integral T> bool open_interval::is_intersect"
            "(std::pair<T, T> p, std::pair<T, T> q)` | "
            "2つの半開区間が交差していれば true を返す | "
            "$O(1)$ |",
            page,
        )
        self.assertEqual(page.count("| $O(1)$ |"), 8)

    def test_extracts_and_displays_namespace_scope(self) -> None:
        entities = extract_doc_entities(
            """
namespace sample {
/// @brief value
bool value();
}  // namespace sample
"""
        )

        self.assertEqual(len(entities), 1)
        self.assertEqual(entities[0].namespace, "sample")
        self.assertEqual(display_signature(entities[0]), "bool sample::value();")

    def test_excludes_non_public_class_members(self) -> None:
        entities = extract_doc_entities(
            """
struct sample {
    /// @brief visible
    void visible();
  private:
    /// @brief hidden
    void hidden();
  protected:
    /// @brief also hidden
    void protected_value();
  public:
    /// @brief visible again
    void another();
};

class default_private {
    /// @brief hidden by default
    void hidden();
  public:
    /// @brief public
    void visible();
};
"""
        )

        self.assertEqual(
            [entity.signature for entity in entities],
            ["void visible();", "void another();", "void visible();"],
        )

    def test_combination_page_lists_public_operations(self) -> None:
        page = render_generated_page(
            ROOT / "lib" / "combinatorics" / "combination.hpp"
        )

        self.assertNotIn(
            "`template <internal::modint mint = modint998> struct Combinatorics`",
            page,
        )
        self.assertIn("| `Combinatorics()` | 空の計算テーブルを構築する | $O(1)$ |", page)
        self.assertIn(
            "| `mint binom(std::int64_t n, std::int64_t k)` | "
            "二項係数 $\\binom{n}{k}$ を返す。不正な範囲では0を返す",
            page,
        )
        self.assertIn(
            "| `mint binom_lucas(std::int64_t n, std::int64_t k)` | "
            "Lucasの定理で二項係数 $\\binom{n}{k}$ を返す",
            page,
        )
        self.assertEqual(page.count("\n| `"), 8)

    def test_min_cost_flow_page_lists_all_public_operations(self) -> None:
        page = render_generated_page(ROOT / "lib" / "flow" / "min_cost_flow.hpp")
        api = page.split("## API\n\n", 1)[1].split("\n\n## 補足", 1)[0]

        self.assertNotIn(
            "`template <class Cap, class Cost> struct mcf_graph`",
            api,
        )
        for signature in (
            "mcf_graph()",
            "explicit mcf_graph(int n)",
            "int size() const",
            "int add_edge(int from, int to, Cap cap, Cost cost)",
            "struct edge",
            "constexpr edge(int _from, int _to, Cap _cap, Cap _flow, Cost _cost)",
            "edge get_edge(int i)",
            "std::vector<edge> edges()",
            "std::pair<Cap, Cost> flow(int s, int t)",
            "std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit)",
            "std::vector<std::pair<Cap, Cost>> slope(int s, int t)",
            "std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit)",
        ):
            with self.subTest(signature=signature):
                self.assertIn(f"`{signature}`", api)
        self.assertEqual(api.count("\n| `"), 15)
        self.assertNotIn(" | — |", api)

    def test_previously_type_only_pages_list_public_operations(self) -> None:
        expected = {
            "geometry/geometry.hpp": (
                "constexpr Point()",
                "constexpr Line()",
                "constexpr Circle()",
                "Circle<T> min_ball",
            ),
            "geometry/geometry3d.hpp": (
                "constexpr Pos()",
                "constexpr Circle3(Pos<T> _p, T _r)",
                "Circle3<T> min_ball",
            ),
            "geometry/kdtree.hpp": (
                "kdtree()",
                "void add(int x, int y)",
                "void build()",
            ),
            "heap/priority_k_sum.hpp": (
                "priority_k_sum(int k)",
                "void set_k(int x)",
                "using minimum_sum",
            ),
            "linalg/matrix.hpp": (
                "Matrix()",
                "T det() const",
                "Matrix transposed() const",
            ),
            "math/hashint.hpp": (
                "static constexpr std::uint64_t get_mod() noexcept",
                "constexpr HashInt inv() const noexcept",
                "constexpr std::uint64_t val() const noexcept",
            ),
        }

        for filename, signatures in expected.items():
            with self.subTest(filename=filename):
                page = render_generated_page(ROOT / "lib" / filename)
                for signature in signatures:
                    self.assertIn(signature, page)

    def test_untagged_public_operations_are_not_omitted(self) -> None:
        pages = {
            "dp/undo_slope_trick.hpp": (
                "UndoSlopeTrick()",
                "[[nodiscard]] T min_x() const",
                "[[nodiscard]] int snapshot() const",
            ),
            "linalg/xor_basis.hpp": (
                "XorBasis()",
                "int size() const",
                "bool empty() const",
            ),
            "number_theory/factorize.hpp": (
                "number_of_divisors(std::vector<std::uint64_t> v)",
                "number_of_divisors(std::uint64_t n)",
            ),
            "number_theory/root_mod.hpp": ("sqrt_mod(mint x)",),
        }

        for filename, signatures in pages.items():
            with self.subTest(filename=filename):
                page = render_generated_page(ROOT / "lib" / filename)
                for signature in signatures:
                    self.assertIn(signature, page)

    def test_all_combinatorics_pages_have_generated_complexities(self) -> None:
        expected_rows = {
            "bell.hpp": 1,
            "combination.hpp": 8,
            "offline_binomial_sum.hpp": 1,
            "partition_function.hpp": 1,
            "stirling.hpp": 4,
            "stirling_bell.hpp": 3,
            "stirling_small_p_large_n.hpp": 3,
        }

        for filename, row_count in expected_rows.items():
            with self.subTest(filename=filename):
                page = render_generated_page(
                    ROOT / "lib" / "combinatorics" / filename
                )
                api = page.split("## API\n\n", 1)[1].split("\n\n## 補足", 1)[0]
                self.assertEqual(api.count("\n| `"), row_count)
                self.assertNotIn(" | — |", api)

    def test_groups_overloads_with_the_same_contract(self) -> None:
        first = DocEntity(
            signature="bool contains(const T &x) const",
            brief="含まれていれば true を返す",
            params=[("x", "検索する要素")],
            complexities=["$O(\\log n)$"],
        )
        second = DocEntity(
            signature="bool contains(T &&x) const",
            brief="含まれていれば true を返す",
            params=[("x", "検索する要素")],
            complexities=["$O(\\log n)$"],
        )

        groups = group_doc_entities([first, second])

        self.assertEqual(len(groups), 1)
        self.assertEqual(
            render_entity_group(groups[0], 1),
            "| `bool contains(const T &x) const`<br>"
            "`bool contains(T &&x) const` | "
            "含まれていれば true を返す<br>"
            "**引数:** `x`: 検索する要素 | $O(\\log n)$ |",
        )

    def test_deduplicates_identical_signatures_in_a_group(self) -> None:
        entity = DocEntity(signature="bool empty() const", brief="空なら true")

        self.assertEqual(
            render_entity_group([entity, entity], 1),
            "| `bool empty() const` | 空なら true | — |",
        )

    def test_strips_constructor_initializer_from_signature(self) -> None:
        self.assertEqual(
            strip_constructor_initializer("flip_set() : data()"),
            "flip_set()",
        )
        self.assertEqual(
            strip_constructor_initializer("auto value() const -> std::type"),
            "auto value() const -> std::type",
        )


if __name__ == "__main__":
    unittest.main()
