#pragma once
#include <cassert>
#include <concepts>
#include <iostream>
#include <iterator>
#include <ranges>
#include <type_traits>
#include <utility>
#include <vector>

/// @brief 重みなし辺を表す空タグ型（重み 1 として振る舞う）
struct Unweighted {
    constexpr Unweighted() = default;
    constexpr Unweighted(int) {}
    constexpr operator int() const { return 1; }
    friend constexpr bool operator<(Unweighted, Unweighted) { return false; }
    friend constexpr bool operator>(Unweighted, Unweighted) { return false; }
};

/// @brief 隣接リスト形式の重み付きグラフ
/// @tparam T 辺の重みの型。`void` を指定すると重みなしグラフ（重み 1 固定）になる。
///
/// 各頂点の隣接辺を可変長 vector で保持する。動的な辺追加に強く、
/// 連続領域に詰める `csr_graph<T>` と参照系 API は共通。
template <class T>
struct list_graph {
  private:
    /// 重みの実体型: `void` は `Unweighted` に正規化する
    using weight_type = std::conditional_t<std::is_void_v<T>, Unweighted, T>;

    struct _edge {
        constexpr _edge() : _from(), _to(), _id(-1), _weight() {}
        constexpr _edge(int from, int to, weight_type weight, int id = -1)
            : _from(from), _to(to), _id(id), _weight(weight) {}
        constexpr bool operator<(const _edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }

        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr int id() const { return _id; }
        constexpr weight_type weight() const { return _weight; }

      private:
        int _from, _to, _id;
        [[no_unique_address]] weight_type _weight;
    };

  public:
    using edge_type = typename list_graph<T>::_edge;

    list_graph() : _size(), _edge_count(), _num_edges(), edges(), edge_list_() {}
    explicit list_graph(int v) : _size(v), _edge_count(), _num_edges(), edges(v), edge_list_() {}

    const auto &operator[](int i) const {
        assert(0 <= i && i < _size);
        return edges[i];
    }
    auto &operator[](int i) {
        assert(0 <= i && i < _size);
        return edges[i];
    }
    auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    constexpr int size() const { return _size; }

    /// @brief 格納された有向辺数（無向辺は 2 本としてカウントされる）
    constexpr int edge_count() const { return _edge_count; }

    /// @brief 辺 ID の個数（add_edge / add_edges の呼び出し回数）
    constexpr int num_edges() const { return _num_edges; }

    /// @brief ID から辺を取得する（無向辺は from→to 側を返す）
    const edge_type &get_edge(int id) const {
        assert(0 <= id && id < _num_edges);
        return edge_list_[id];
    }

    /// @brief 全辺を平坦に走査する view
    auto all_edges() const { return edges | std::views::join; }
    auto all_edges() { return edges | std::views::join; }

    /// @brief 各頂点の隣接リストにまとめて容量を予約する
    void reserve(int from, int degree) {
        assert(0 <= from && from < _size);
        edges[from].reserve(degree);
    }

    /// @brief 有向辺を追加する。重みは e のものを使い、ID は新たに振り直す。
    void add_edge(const edge_type &e) { add_edge(e.from(), e.to(), e.weight()); }
    /// @brief 有向辺を追加する。
    void add_edge(int from, int to, weight_type weight = weight_type(1)) {
        assert(0 <= from && from < _size);
        assert(0 <= to && to < _size);
        int id = _num_edges++;
        edge_type e(from, to, weight, id);
        edges[from].emplace_back(e);
        edge_list_.emplace_back(e);
        ++_edge_count;
    }
    /// @brief 無向辺を追加する。往復 2 本（from→to, to→from）には同じ ID を振る。
    /// @note 「add_edges 1 回 = 論理辺 1 個 = ID 1 個」で、ID は入力辺番号に一致する
    ///       （ACL mf_graph が add_edge 1 回に 1 ID を割り当てるのと同じ思想）。
    ///       この方式により無向グラフの辺 ID アルゴリズムが正しく成立する:
    ///       - 橋・閉路検出の出力を入力辺番号でそのまま返せる
    ///       - 多重辺は別 ID になるため長さ 2 の閉路として検出される
    ///       - 単一辺の往復は同 ID なので「来た辺そのもの」として親辺除外できる
    void add_edges(int from, int to, weight_type weight = weight_type(1)) {
        assert(0 <= from && from < _size);
        assert(0 <= to && to < _size);
        int id = _num_edges++;
        edges[from].emplace_back(from, to, weight, id);
        edges[to].emplace_back(to, from, weight, id);
        edge_list_.emplace_back(from, to, weight, id);
        _edge_count += 2;
    }

    void input_edge(int m, int origin = 1) {
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
    }
    void input_edges(int m, int origin = 1) {
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
    }

  private:
    int _size, _edge_count, _num_edges;
    std::vector<std::vector<edge_type>> edges;
    std::vector<edge_type> edge_list_;  // ID 順の辺リスト（ID→辺の逆引き）
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
/// `internal::graph_csr` とは異なり重み・辺 ID を保持する公開グラフ型である。
template <class T>
struct csr_graph {
  private:
    /// 重みの実体型: `void` は `Unweighted` に正規化する
    using weight_type = std::conditional_t<std::is_void_v<T>, Unweighted, T>;

    struct _edge {
        constexpr _edge() : _from(), _to(), _id(-1), _weight() {}
        constexpr _edge(int from, int to, weight_type weight, int id = -1)
            : _from(from), _to(to), _id(id), _weight(weight) {}
        constexpr bool operator<(const _edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }

        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr int id() const { return _id; }
        constexpr weight_type weight() const { return _weight; }

      private:
        int _from, _to, _id;
        [[no_unique_address]] weight_type _weight;
    };

  public:
    using edge_type = typename csr_graph<T>::_edge;

    /// @brief 頂点 v の隣接辺を走査する軽量 view（CSR の連続領域を指す）
    /// @note `list_graph<T>::operator[]` が返す `std::vector<edge_type>` と同様に、
    ///       順方向・逆方向の走査と添字アクセスをサポートする。
    struct adjacency {
        using const_iterator = typename std::vector<edge_type>::const_iterator;
        using const_reverse_iterator = typename std::vector<edge_type>::const_reverse_iterator;

        adjacency(const_iterator first, const_iterator last) : _first(first), _last(last) {}

        const_iterator begin() const { return _first; }
        const_iterator end() const { return _last; }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(_last); }
        const_reverse_iterator rend() const { return const_reverse_iterator(_first); }
        int size() const { return (int)(_last - _first); }
        bool empty() const { return _first == _last; }
        const edge_type &operator[](int i) const { return _first[i]; }

      private:
        const_iterator _first, _last;
    };

    csr_graph() : _size(), _edge_count(), _num_edges(), _built(false), start(1), elist(), edge_list_() {}
    explicit csr_graph(int v)
        : _size(v), _edge_count(), _num_edges(), _built(false), start(v + 1), elist(), edge_list_() {}

    adjacency operator[](int i) const {
        assert(_built);
        assert(0 <= i && i < _size);
        return adjacency(std::next(elist.begin(), start[i]), std::next(elist.begin(), start[i + 1]));
    }

    constexpr int size() const { return _size; }

    /// @brief 格納された有向辺数（無向辺は 2 本としてカウントされる）
    constexpr int edge_count() const { return _edge_count; }

    /// @brief 辺 ID の個数（add_edge / add_edges の呼び出し回数）
    constexpr int num_edges() const { return _num_edges; }

    /// @brief ID から辺を取得する（無向辺は from→to 側を返す）
    const edge_type &get_edge(int id) const {
        assert(0 <= id && id < _num_edges);
        return edge_list_[id];
    }

    /// @brief 全辺を平坦に走査する（CSR の連続領域をそのまま返す）
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
    void reserve_edges(int num_edges, int edge_count) {
        buf.reserve(edge_count);
        edge_list_.reserve(num_edges);
    }

    /// @brief 有向辺を追加する。重みは e のものを使い、ID は新たに振り直す。
    void add_edge(const edge_type &e) { add_edge(e.from(), e.to(), e.weight()); }
    /// @brief 有向辺を追加する。
    void add_edge(int from, int to, weight_type weight = weight_type(1)) {
        assert(0 <= from && from < _size);
        assert(0 <= to && to < _size);
        int id = _num_edges++;
        buf.emplace_back(from, to, weight, id);
        edge_list_.emplace_back(from, to, weight, id);
        ++start[from + 1];
        ++_edge_count;
        _built = false;
    }
    /// @brief 無向辺を追加する。往復 2 本（from→to, to→from）には同じ ID を振る。
    /// @note 「add_edges 1 回 = 論理辺 1 個 = ID 1 個」で、ID は入力辺番号に一致する。
    ///       `list_graph<T>::add_edges` と同じ ID 付与方式（往復に同一 ID）に従う。
    void add_edges(int from, int to, weight_type weight = weight_type(1)) {
        assert(0 <= from && from < _size);
        assert(0 <= to && to < _size);
        int id = _num_edges++;
        buf.emplace_back(from, to, weight, id);
        buf.emplace_back(to, from, weight, id);
        edge_list_.emplace_back(from, to, weight, id);
        ++start[from + 1];
        ++start[to + 1];
        _edge_count += 2;
        _built = false;
    }

    /// @brief 蓄積した辺を CSR の連続領域に詰めて参照系 API を有効化する
    void build() {
        for (int i = 0; i < _size; ++i) start[i + 1] += start[i];
        auto counter = start;
        elist.assign(buf.size(), edge_type());
        for (auto &e : buf) elist[counter[e.from()]++] = e;
        _built = true;
    }

    void input_edge(int m, int origin = 1) {
        reserve_edges(m, m);
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
        build();
    }
    void input_edges(int m, int origin = 1) {
        reserve_edges(m, 2 * m);
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
        build();
    }

  private:
    int _size, _edge_count, _num_edges;
    bool _built;
    std::vector<int> start;            // CSR の境界（start[v]..start[v+1]）
    std::vector<edge_type> buf;        // build() 前に蓄積する辺（from でソート前）
    std::vector<edge_type> elist;      // CSR 本体（from 昇順に詰めた有向辺）
    std::vector<edge_type> edge_list_; // ID 順の辺リスト（ID→辺の逆引き）
};

// ---- グラフの concept（list_graph<T> / csr_graph<T> を共通の契約で扱う） ----

/// @brief グラフの辺の要件
/// @details 終点 `to()`・辺 ID `id()` を持つこと（`from()` / `weight()` は任意）。
///          `list_graph<T>` / `csr_graph<T>` の `edge_type` がこれを満たす。
/// @tparam E 判定対象の辺型
template <class E>
concept graph_edge = requires(const E &e) {
    { e.to() } -> std::convertible_to<int>;
    { e.id() } -> std::convertible_to<int>;
};

/// @brief 重み付きグラフの辺の要件
/// @details `graph_edge` に加えて重み `weight()` を持つこと。
/// @tparam E 判定対象の辺型
template <class E>
concept weighted_graph_edge = graph_edge<E> && requires(const E &e) { e.weight(); };

/// @brief グラフの要件
/// @details 頂点数 `size()` と、頂点 `v` の隣接辺を走査できる `operator[](int)` を持つこと。
///          `g[v]` は `graph_edge` を要素とする range（隣接リスト or CSR の view）。
///          隣接リスト版 `list_graph<T>` と CSR 版 `csr_graph<T>` の両方がこれを満たすので、
///          グラフアルゴリズムを `graph_type G` でテンプレート化すればどちらでも受け取れる。
/// @tparam G 判定対象のグラフ型
template <class G>
concept graph_type = requires(const G &g, int v) {
    { g.size() } -> std::convertible_to<int>;
    { g[v] } -> std::ranges::range;
    requires graph_edge<std::ranges::range_value_t<decltype(g[v])>>;
};

/// @brief 重み付きグラフの要件
/// @details `graph_type` に加えて、隣接辺が `weighted_graph_edge`（重み付き）であること。
///          辺重みを参照する最短路系アルゴリズム（shortest_path / bellman_ford / prim 等）で使う。
/// @tparam G 判定対象のグラフ型
template <class G>
concept weighted_graph_type =
    graph_type<G> && weighted_graph_edge<std::ranges::range_value_t<decltype(std::declval<const G &>()[0])>>;

/// @brief グラフ型 G の辺型（`G::edge_type` に依らず隣接 range から取り出す）
template <graph_type G>
using graph_edge_t = std::ranges::range_value_t<decltype(std::declval<const G &>()[0])>;

/// @brief 重み付きグラフ型 G の辺重みの型
template <weighted_graph_type G>
using graph_weight_t = decltype(std::declval<graph_edge_t<G>>().weight());

/// @brief 重みなしグラフの要件
/// @details `weighted_graph_type` のうち、辺重みが `Unweighted`（重み 1 固定）のもの。
/// @tparam G 判定対象のグラフ型
template <class G>
concept unweighted_graph_type =
    weighted_graph_type<G> && std::is_same_v<std::remove_cvref_t<graph_weight_t<G>>, Unweighted>;

/// @brief 実重み付きグラフの要件
/// @details `weighted_graph_type` のうち、辺重みが `Unweighted` でない（=実際の重みを持つ）もの。
///          `unweighted_graph_type` と排他なので、両者でオーバーロードを分けられる
///          （重みなし → BFS、実重み → ダイクストラ法 など）。
/// @tparam G 判定対象のグラフ型
template <class G>
concept properly_weighted_graph_type = weighted_graph_type<G> && !unweighted_graph_type<G>;
