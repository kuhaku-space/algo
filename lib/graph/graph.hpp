#pragma once
#include <algorithm>
#include <cassert>
#include <concepts>
#include <iostream>
#include <iterator>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>

/// @file
/// @brief グラフ表現 (list_graph / csr_graph)
/// @details 重み付き・重みなしグラフを、更新しやすい隣接リストまたは連続領域の CSR として表現する。
///          共通の concept により各グラフアルゴリズムへ渡せる。

/// @brief 重みなし辺を表す空タグ型（重み 1 として振る舞う）
/// @complexity すべての演算が $O(1)$
struct Unweighted {
    /// @brief 重み1のタグを構築する
    /// @complexity $O(1)$
    constexpr Unweighted() = default;

    /// @brief 任意の整数から重み1のタグを構築する
    /// @complexity $O(1)$
    constexpr Unweighted(int) {}

    /// @brief 重み1として整数へ変換する
    /// @complexity $O(1)$
    constexpr operator int() const { return 1; }

    /// @brief 2つの重みなし辺を小なり比較する
    /// @complexity $O(1)$
    friend constexpr bool operator<(Unweighted, Unweighted) { return false; }

    /// @brief 2つの重みなし辺を大なり比較する
    /// @complexity $O(1)$
    friend constexpr bool operator>(Unweighted, Unweighted) { return false; }
};

namespace internal {

/// @brief `list_graph<T>` / `csr_graph<T>` の共通部分（CRTP）
/// @details 辺型・辺 ID の採番・ID 順の辺リスト・標準入力からの辺の読み込みを持つ。
///          派生型は隣接構造へ有向辺を 1 本格納する `store_edge(e)` を持つ。
///          入力の前後に呼ばれる `begin_input(num_edges, edge_count)` / `end_input()` は
///          既定で何もせず、必要な派生型だけが上書きする。
/// @tparam Derived 派生型
/// @tparam T 辺の重みの型。`void` を指定すると重みなしグラフ（重み 1 固定）になる。
template <class Derived, class T>
struct GraphBase {
  private:
    /// 重みの実体型: `void` は `Unweighted` に正規化する
    using weight_type = std::conditional_t<std::is_void_v<T>, Unweighted, T>;

    struct Edge {
        constexpr Edge() : _from(), _to(), _id(-1), _weight() {}
        constexpr Edge(int from, int to, weight_type weight, int id = -1)
            : _from(from), _to(to), _id(id), _weight(weight) {}
        constexpr bool operator<(const Edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const Edge &rhs) const { return rhs < *this; }

        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr int id() const { return _id; }
        constexpr weight_type weight() const { return _weight; }

      private:
        int _from, _to, _id;
        [[no_unique_address]] weight_type _weight;
    };

  public:
    /// @brief このグラフが返す辺型
    /// @complexity 型エイリアスで実行時計算量はない
    using edge_type = Edge;

    /// @brief 頂点数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return _size; }

    /// @brief 格納された有向辺数（無向辺は 2 本としてカウントされる）
    /// @complexity $O(1)$
    constexpr int edge_count() const { return _edge_count; }

    /// @brief 辺 ID の個数（add_edge / add_edges の呼び出し回数）
    /// @complexity $O(1)$
    constexpr int num_edges() const { return _num_edges; }

    /// @brief ID から辺を取得する（無向辺は from→to 側を返す）
    /// @complexity $O(1)$
    const edge_type &get_edge(int id) const {
        assert(0 <= id && id < _num_edges);
        return edge_list[id];
    }

    /// @brief 有向辺を追加する。重みは e のものを使い、ID は新たに振り直す。
    /// @complexity 償却 $O(1)$
    void add_edge(const edge_type &e) { add_edge(e.from(), e.to(), e.weight()); }

    /// @brief 有向辺を追加する。
    /// @complexity 償却 $O(1)$
    void add_edge(int from, int to, weight_type weight = weight_type(1)) {
        assert(0 <= from && from < _size);
        assert(0 <= to && to < _size);
        int id = _num_edges++;
        edge_type e(from, to, weight, id);
        derived().store_edge(e);
        edge_list.emplace_back(e);
        ++_edge_count;
    }

    /// @brief 無向辺を追加する。往復 2 本（from→to, to→from）には同じ ID を振る。
    /// @note 「add_edges 1 回 = 論理辺 1 個 = ID 1 個」で、ID は入力辺番号に一致する
    ///       （ACL mf_graph が add_edge 1 回に 1 ID を割り当てるのと同じ思想）。
    ///       この方式により無向グラフの辺 ID アルゴリズムが正しく成立する:
    ///       - 橋・閉路検出の出力を入力辺番号でそのまま返せる
    ///       - 多重辺は別 ID になるため長さ 2 の閉路として検出される
    ///       - 単一辺の往復は同 ID なので「来た辺そのもの」として親辺除外できる
    /// @complexity 償却 $O(1)$
    void add_edges(int from, int to, weight_type weight = weight_type(1)) {
        assert(0 <= from && from < _size);
        assert(0 <= to && to < _size);
        int id = _num_edges++;
        derived().store_edge(edge_type(from, to, weight, id));
        derived().store_edge(edge_type(to, from, weight, id));
        edge_list.emplace_back(from, to, weight, id);
        _edge_count += 2;
    }

    /// @brief 標準入力からm本の有向辺を追加する
    /// @details `csr_graph<T>` では読み込み後に `build()` まで行う。
    /// @complexity $O(m)$（`csr_graph<T>` は構築を含めて $O(V+m)$）
    void input_edge(int m, int origin = 1) {
        derived().begin_input(m, m);
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            if constexpr (std::is_void_v<T>) {
                add_edge(from - origin, to - origin);
            } else {
                T weight;
                std::cin >> weight;
                add_edge(from - origin, to - origin, weight);
            }
        }
        derived().end_input();
    }

    /// @brief 標準入力からm本の無向辺を追加する
    /// @details `csr_graph<T>` では読み込み後に `build()` まで行う。
    /// @complexity $O(m)$（`csr_graph<T>` は構築を含めて $O(V+m)$）
    void input_edges(int m, int origin = 1) {
        derived().begin_input(m, 2 * m);
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            if constexpr (std::is_void_v<T>) {
                add_edges(from - origin, to - origin);
            } else {
                T weight;
                std::cin >> weight;
                add_edges(from - origin, to - origin, weight);
            }
        }
        derived().end_input();
    }

  protected:
    int _size, _edge_count, _num_edges;
    std::vector<edge_type> edge_list;  // ID 順の辺リスト（ID→辺の逆引き）

    GraphBase() : _size(), _edge_count(), _num_edges(), edge_list() {}
    explicit GraphBase(int v) : _size(v), _edge_count(), _num_edges(), edge_list() {}

    void begin_input(int, int) {}
    void end_input() {}

  private:
    Derived &derived() { return static_cast<Derived &>(*this); }
};

}  // namespace internal

/// @brief 隣接リスト形式の重み付きグラフ
/// @tparam T 辺の重みの型。`void` を指定すると重みなしグラフ（重み 1 固定）になる。
///
/// 各頂点の隣接辺を可変長 vector で保持する。動的な辺追加に強く、
/// 連続領域に詰める `csr_graph<T>` と参照系 API は共通。
/// @complexity 構築は $O(V)$、辺追加は償却 $O(1)$、参照は $O(1)$
template <class T>
struct list_graph : internal::GraphBase<list_graph<T>, T> {
  private:
    using Base = internal::GraphBase<list_graph<T>, T>;
    using Base::_size;
    friend Base;

  public:
    using typename Base::edge_type;

    /// @brief 頂点を持たないグラフを構築する
    /// @complexity $O(1)$
    list_graph() : Base(), edges() {}

    /// @brief v頂点のグラフを構築する
    /// @complexity $O(V)$
    explicit list_graph(int v) : Base(v), edges(v) {}

    /// @brief 頂点iの隣接辺列を取得する
    /// @complexity $O(1)$
    const auto &operator[](int i) const {
        assert(0 <= i && i < _size);
        return edges[i];
    }

    /// @brief 頂点iの隣接辺列を変更可能な参照で取得する
    /// @complexity $O(1)$
    auto &operator[](int i) {
        assert(0 <= i && i < _size);
        return edges[i];
    }

    /// @brief 頂点ごとの隣接辺列の先頭iteratorを返す
    /// @complexity $O(1)$
    auto begin() const { return edges.begin(); }

    /// @brief 頂点ごとの隣接辺列の先頭iteratorを返す
    /// @complexity $O(1)$
    auto begin() { return edges.begin(); }

    /// @brief 頂点ごとの隣接辺列の終端iteratorを返す
    /// @complexity $O(1)$
    auto end() const { return edges.end(); }

    /// @brief 頂点ごとの隣接辺列の終端iteratorを返す
    /// @complexity $O(1)$
    auto end() { return edges.end(); }

    /// @brief 全辺を平坦に走査する view
    /// @complexity viewの構築は $O(1)$、走査は $O(E)$
    auto all_edges() const { return edges | std::views::join; }

    /// @brief 全辺を変更可能なviewとして平坦に走査する
    /// @complexity viewの構築は $O(1)$、走査は $O(E)$
    auto all_edges() { return edges | std::views::join; }

    /// @brief 各頂点の隣接リストにまとめて容量を予約する
    /// @complexity 再確保が起きる場合は現在の次数を $d$ として $O(d)$
    void reserve(int from, int degree) {
        assert(0 <= from && from < _size);
        edges[from].reserve(degree);
    }

  private:
    std::vector<std::vector<edge_type>> edges;

    void store_edge(const edge_type &e) { edges[e.from()].emplace_back(e); }
};

/// @brief CSR（Compressed Sparse Row）形式の重み付きグラフ
/// @tparam T 辺の重みの型。`void` を指定すると重みなしグラフ（重み 1 固定）になる。
///
/// `list_graph<T>` と同等の参照系 API（`operator[]` での隣接走査、`get_edge`、
/// `edge_count`、`num_edges`、`all_edges`）を提供するが、隣接リストを
/// 1 本の連続領域（CSR）に詰めるためキャッシュ効率と省メモリ性に優れる。
///
/// 辺は `add_edge` / `add_edges` で蓄積したあと `build()` で確定させる。
/// `build()` 後は構造が固定され、再度辺を追加するには `build()` をやり直す。
/// `internal::Csr` とは異なり重み・辺 ID を保持する公開グラフ型である。
/// @complexity 構築と辺追加は償却 $O(1)$、`build` は $O(V+E)$、参照は $O(1)$
template <class T>
struct csr_graph : internal::GraphBase<csr_graph<T>, T> {
  private:
    using Base = internal::GraphBase<csr_graph<T>, T>;
    using Base::_size;
    using Base::edge_list;
    friend Base;

  public:
    using typename Base::edge_type;

    /// @brief 頂点 v の隣接辺を走査する軽量 view（CSR の連続領域を指す）
    /// @note `list_graph<T>::operator[]` が返す `std::vector<edge_type>` と同様に、
    ///       順方向・逆方向の走査と添字アクセスをサポートする。
    /// @complexity すべての操作が $O(1)$
    struct adjacency {
        /// @brief 読み取り専用の順方向イテレータ型
        /// @complexity 型エイリアスで実行時計算量はない
        using const_iterator = typename std::vector<edge_type>::const_iterator;
        /// @brief 読み取り専用の逆方向イテレータ型
        /// @complexity 型エイリアスで実行時計算量はない
        using const_reverse_iterator = typename std::vector<edge_type>::const_reverse_iterator;

        /// @brief 半開区間[first, last)を指すviewを構築する
        /// @complexity $O(1)$
        adjacency(const_iterator first, const_iterator last) : _first(first), _last(last) {}

        /// @brief 先頭iteratorを返す
        /// @complexity $O(1)$
        const_iterator begin() const { return _first; }

        /// @brief 終端iteratorを返す
        /// @complexity $O(1)$
        const_iterator end() const { return _last; }

        /// @brief 逆順の先頭iteratorを返す
        /// @complexity $O(1)$
        const_reverse_iterator rbegin() const { return const_reverse_iterator(_last); }

        /// @brief 逆順の終端iteratorを返す
        /// @complexity $O(1)$
        const_reverse_iterator rend() const { return const_reverse_iterator(_first); }

        /// @brief 辺数を返す
        /// @complexity $O(1)$
        int size() const { return (int)(_last - _first); }

        /// @brief 辺が空か返す
        /// @complexity $O(1)$
        bool empty() const { return _first == _last; }

        /// @brief i番目の辺を返す
        /// @complexity $O(1)$
        const edge_type &operator[](int i) const { return _first[i]; }

      private:
        const_iterator _first, _last;
    };

    /// @brief 頂点を持たないグラフを構築する
    /// @complexity $O(1)$
    csr_graph() : Base(), _built(false), start(1), buf(), elist() {}

    /// @brief v頂点のグラフを構築する
    /// @complexity $O(V)$
    explicit csr_graph(int v) : Base(v), _built(false), start(v + 1), buf(), elist() {}

    /// @brief 頂点iの隣接辺viewを返す
    /// @complexity $O(1)$
    adjacency operator[](int i) const {
        assert(_built);
        assert(0 <= i && i < _size);
        return adjacency(std::next(elist.begin(), start[i]), std::next(elist.begin(), start[i + 1]));
    }

    /// @brief 全辺を平坦に走査する（CSR の連続領域をそのまま返す）
    /// @complexity $O(1)$
    const std::vector<edge_type> &all_edges() const {
        assert(_built);
        return elist;
    }

    /// @brief 追加予定の辺数を見積もって内部バッファを予約する
    /// @param num_edges add_edge / add_edges の総呼び出し回数（= 辺 ID 数）の見積もり
    /// @param edge_count 有向辺の総数の見積もり（無向辺は 2 と数える）
    ///
    /// 辺数が事前に分かっている場合（`edge_input` 経由など）に呼ぶと、
    /// add_edge / add_edges 中の再確保を避けられる。
    /// @complexity 再確保が起きる場合は現在の辺数を $E$ として $O(E)$
    void reserve_edges(int num_edges, int edge_count) {
        buf.reserve(edge_count);
        edge_list.reserve(num_edges);
    }

    /// @brief 蓄積した辺を CSR の連続領域に詰めて参照系 API を有効化する
    /// @details 呼ぶたびにそれまでに追加した全辺から作り直すので、辺を足したあとに何度呼んでもよい。
    /// @complexity $O(V+E)$
    void build() {
        std::fill(start.begin(), start.end(), 0);
        for (auto &e : buf) ++start[e.from() + 1];
        for (int i = 0; i < _size; ++i) start[i + 1] += start[i];
        auto counter = start;
        elist.assign(buf.size(), edge_type());
        for (auto &e : buf) elist[counter[e.from()]++] = e;
        _built = true;
    }

  private:
    bool _built;
    std::vector<int> start;        // CSR の境界（start[v]..start[v+1]）
    std::vector<edge_type> buf;    // 追加した全有向辺（追加順）
    std::vector<edge_type> elist;  // CSR 本体（from 昇順に詰めた有向辺）

    void store_edge(const edge_type &e) {
        buf.emplace_back(e);
        _built = false;
    }
    void begin_input(int num_edges, int edge_count) { reserve_edges(num_edges, edge_count); }
    void end_input() { build(); }
};

// ---- グラフの concept（list_graph<T> / csr_graph<T> を共通の契約で扱う） ----

/// @brief グラフの辺の要件
/// @details 終点 `to()`・辺 ID `id()` を持つこと（`from()` / `weight()` は任意）。
///          `list_graph<T>` / `csr_graph<T>` の `edge_type` がこれを満たす。
/// @tparam E 判定対象の辺型
/// @complexity コンパイル時制約で実行時計算量はない
template <class E>
concept graph_edge = requires(const E &e) {
    { e.to() } -> std::convertible_to<int>;
    { e.id() } -> std::convertible_to<int>;
};

/// @brief 重み付きグラフの辺の要件
/// @details `graph_edge` に加えて重み `weight()` を持つこと。
/// @tparam E 判定対象の辺型
/// @complexity コンパイル時制約で実行時計算量はない
template <class E>
concept weighted_graph_edge = graph_edge<E> && requires(const E &e) { e.weight(); };

/// @brief グラフの要件
/// @details 頂点数 `size()` と、頂点 `v` の隣接辺を走査できる `operator[](int)` を持つこと。
///          `g[v]` は `graph_edge` を要素とする range（隣接リスト or CSR の view）。
///          隣接リスト版 `list_graph<T>` と CSR 版 `csr_graph<T>` の両方がこれを満たすので、
///          グラフアルゴリズムを `graph_type G` でテンプレート化すればどちらでも受け取れる。
/// @tparam G 判定対象のグラフ型
/// @complexity コンパイル時制約で実行時計算量はない
template <class G>
concept graph_type = requires(const G &g, int v) {
    { g.size() } -> std::convertible_to<int>;
    { g[v] } -> std::ranges::range;
    requires graph_edge<std::ranges::range_value_t<decltype(g[v])>>;
};

/// @brief 重み付きグラフの要件
/// @details `graph_type` に加えて、隣接辺が `weighted_graph_edge`（重み付き）であること。
///          辺重みを参照する最短路系アルゴリズム（shortest_path / prim 等）で使う。
/// @tparam G 判定対象のグラフ型
/// @complexity コンパイル時制約で実行時計算量はない
template <class G>
concept weighted_graph_type =
    graph_type<G> && weighted_graph_edge<std::ranges::range_value_t<decltype(std::declval<const G &>()[0])>>;

/// @brief グラフ型 G の辺型（`G::edge_type` に依らず隣接 range から取り出す）
/// @complexity 型エイリアスで実行時計算量はない
template <graph_type G>
using graph_edge_t = std::ranges::range_value_t<decltype(std::declval<const G &>()[0])>;

/// @brief 重み付きグラフ型 G の辺重みの型
/// @complexity 型エイリアスで実行時計算量はない
template <weighted_graph_type G>
using graph_weight_t = decltype(std::declval<graph_edge_t<G>>().weight());

/// @brief 重みなしグラフの要件
/// @details `weighted_graph_type` のうち、辺重みが `Unweighted`（重み 1 固定）のもの。
/// @tparam G 判定対象のグラフ型
/// @complexity コンパイル時制約で実行時計算量はない
template <class G>
concept unweighted_graph_type =
    weighted_graph_type<G> && std::is_same_v<std::remove_cvref_t<graph_weight_t<G>>, Unweighted>;

/// @brief 実重み付きグラフの要件
/// @details `weighted_graph_type` のうち、辺重みが `Unweighted` でない（=実際の重みを持つ）もの。
///          `unweighted_graph_type` と排他なので、両者でオーバーロードを分けられる
///          （重みなし → BFS、実重み → ダイクストラ法 など）。
/// @tparam G 判定対象のグラフ型
/// @complexity コンパイル時制約で実行時計算量はない
template <class G>
concept properly_weighted_graph_type = weighted_graph_type<G> && !unweighted_graph_type<G>;
