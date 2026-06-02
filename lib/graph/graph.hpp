#pragma once
#include <cassert>
#include <iostream>
#include <ranges>
#include <type_traits>
#include <vector>

/// @brief 重みなし辺を表す空タグ型（重み 1 として振る舞う）
struct Unweighted {
    constexpr Unweighted() = default;
    constexpr Unweighted(int) {}
    constexpr operator int() const { return 1; }
    friend constexpr bool operator<(Unweighted, Unweighted) { return false; }
    friend constexpr bool operator>(Unweighted, Unweighted) { return false; }
};

/// @brief 重み付きグラフ
/// @tparam T 辺の重みの型。`void` を指定すると重みなしグラフ（重み 1 固定）になる。
template <class T>
struct Graph {
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
    using edge_type = typename Graph<T>::_edge;

    Graph() : _size(), _edge_count(), _num_edges(), edges(), edge_list_() {}
    explicit Graph(int v) : _size(v), _edge_count(), _num_edges(), edges(v), edge_list_() {}

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
    /// @brief 無向辺を追加する。往復 2 本には同じ ID を振る。
    void add_edges(int from, int to, weight_type weight = weight_type(1)) {
        assert(0 <= from && from < _size);
        assert(0 <= to && to < _size);
        int id = _num_edges++;
        edges[from].emplace_back(from, to, weight, id);
        edges[to].emplace_back(to, from, weight, id);
        edge_list_.emplace_back(from, to, weight, id);
        _edge_count += 2;
    }

    void input_edge(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            if constexpr (std::is_void_v<T>) {
                add_edge(from - base, to - base);
            } else {
                T weight;
                std::cin >> weight;
                add_edge(from - base, to - base, weight);
            }
        }
    }
    void input_edges(int m, int base = 1) {
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            if constexpr (std::is_void_v<T>) {
                add_edges(from - base, to - base);
            } else {
                T weight;
                std::cin >> weight;
                add_edges(from - base, to - base, weight);
            }
        }
    }

  private:
    int _size, _edge_count, _num_edges;
    std::vector<std::vector<edge_type>> edges;
    std::vector<edge_type> edge_list_;  // ID 順の辺リスト（ID→辺の逆引き）
};
