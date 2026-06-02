#pragma once
#include <iostream>
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
        constexpr _edge() : _from(), _to(), _weight() {}
        constexpr _edge(int from, int to, weight_type weight)
            : _from(from), _to(to), _weight(weight) {}
        constexpr bool operator<(const _edge &rhs) const { return weight() < rhs.weight(); }
        constexpr bool operator>(const _edge &rhs) const { return rhs < *this; }

        constexpr int from() const { return _from; }
        constexpr int to() const { return _to; }
        constexpr weight_type weight() const { return _weight; }

      private:
        int _from, _to;
        [[no_unique_address]] weight_type _weight;
    };

  public:
    using edge_type = typename Graph<T>::_edge;

    Graph() : _size(), edges() {}
    explicit Graph(int v) : _size(v), edges(v) {}

    const auto &operator[](int i) const { return edges[i]; }
    auto &operator[](int i) { return edges[i]; }
    auto begin() const { return edges.begin(); }
    auto begin() { return edges.begin(); }
    auto end() const { return edges.end(); }
    auto end() { return edges.end(); }
    constexpr int size() const { return _size; }

    void add_edge(const edge_type &e) { edges[e.from()].emplace_back(e); }
    void add_edge(int from, int to, weight_type weight = weight_type(1)) {
        edges[from].emplace_back(from, to, weight);
    }
    void add_edges(int from, int to, weight_type weight = weight_type(1)) {
        edges[from].emplace_back(from, to, weight);
        edges[to].emplace_back(to, from, weight);
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
    int _size;
    std::vector<std::vector<edge_type>> edges;
};
