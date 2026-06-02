#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include "graph/graph.hpp"

/// @brief 辺の列を読み込んで保持する入力中間型
/// @tparam T 辺の重みの型。`void` で重みなし（入力から重みを読まない）。
///
/// 標準入力から `(from, to[, weight])` を base 補正して読み込み、
/// グラフ表現に依存しない生の辺データとして保持する。
/// `build_directed(graph)` / `build_undirected(graph)` で任意のグラフ型に
/// 流し込める（`add_edge` / `add_edges` を持つ型なら何でも受け取れる）。
template <class T>
struct edge_input {
    /// 重みの実体型: `void` は空タグ Unweighted に正規化する
    static constexpr bool weighted = !std::is_void_v<T>;
    using weight_type = std::conditional_t<weighted, T, Unweighted>;

    struct raw_edge {
        int from, to;
        [[no_unique_address]] weight_type weight;
    };

    edge_input() = default;

    /// @brief 標準入力から m 本の辺を読み込む（頂点番号は base から）
    explicit edge_input(int m, int base = 1) { input(m, base); }

    /// @brief 標準入力から m 本の辺を追加で読み込む
    void input(int m, int base = 1) {
        edges.reserve(edges.size() + m);
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            if constexpr (weighted) {
                T weight;
                std::cin >> weight;
                edges.emplace_back(from - base, to - base, weight);
            } else {
                edges.emplace_back(from - base, to - base, weight_type());
            }
        }
    }

    /// @brief 1 本の辺を追加する
    void emplace(int from, int to, weight_type weight = weight_type()) {
        edges.emplace_back(from, to, weight);
    }

    int size() const { return (int)edges.size(); }
    const raw_edge &operator[](int i) const { return edges[i]; }
    auto begin() const { return edges.begin(); }
    auto end() const { return edges.end(); }

    /// @brief 有向辺として graph に流し込む（add_edge を呼ぶ）
    template <class G>
    void build_directed(G &g) const {
        for (auto &e : edges) {
            if constexpr (weighted) g.add_edge(e.from, e.to, e.weight);
            else g.add_edge(e.from, e.to);
        }
    }

    /// @brief 無向辺として graph に流し込む（add_edges を呼ぶ）
    template <class G>
    void build_undirected(G &g) const {
        for (auto &e : edges) {
            if constexpr (weighted) g.add_edges(e.from, e.to, e.weight);
            else g.add_edges(e.from, e.to);
        }
    }

    /// @brief n 頂点の有向 Graph<T> を構築して返す
    Graph<T> to_directed_graph(int n) const {
        Graph<T> g(n);
        build_directed(g);
        return g;
    }

    /// @brief n 頂点の無向 Graph<T> を構築して返す
    Graph<T> to_undirected_graph(int n) const {
        Graph<T> g(n);
        build_undirected(g);
        return g;
    }

  private:
    std::vector<raw_edge> edges;
};
