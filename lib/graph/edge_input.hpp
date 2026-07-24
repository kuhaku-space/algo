#pragma once
#include <iostream>
#include <type_traits>
#include <vector>
#include "graph/graph.hpp"

/// @brief 辺の列を読み込んで保持する入力中間型
/// @tparam T 辺の重みの型。`void` で重みなし（入力から重みを読まない）。
///
/// 標準入力から `(from, to[, weight])` を origin 補正して読み込み、
/// グラフ表現に依存しない生の辺データとして保持する。
/// `build_directed(graph)` / `build_undirected(graph)` で任意のグラフ型に
/// 流し込める（`add_edge` / `add_edges` を持つ型なら何でも受け取れる）。
/// @complexity 辺数を $E$ として入力・構築は $O(E)$
template <class T>
struct edge_input {
    /// 重みの実体型: `void` は空タグ Unweighted に正規化する
    /// @complexity コンパイル時定数で実行時計算量はない
    static constexpr bool weighted = !std::is_void_v<T>;

    /// @brief 重みの実体型
    /// @complexity 型エイリアスで実行時計算量はない
    using weight_type = std::conditional_t<weighted, T, Unweighted>;

    /// @brief 入力した1本の辺
    /// @complexity データ型で実行時計算量はない
    struct raw_edge {
        /// @brief 辺の始点と終点
        /// @complexity $O(1)$ で参照可能
        int from, to;
        /// @brief 辺の重み
        /// @complexity $O(1)$ で参照可能
        [[no_unique_address]] weight_type weight;
    };

    /// @brief 空の辺列を構築する
    /// @complexity $O(1)$
    edge_input() = default;

    /// @brief 標準入力から m 本の辺を読み込む（頂点番号は origin から）
    /// @complexity $O(m)$
    explicit edge_input(int m, int origin = 1) { input(m, origin); }

    /// @brief 標準入力から m 本の辺を追加で読み込む
    /// @complexity $O(m)$
    void input(int m, int origin = 1) {
        edges.reserve(edges.size() + m);
        for (int i = 0; i < m; ++i) {
            int from, to;
            std::cin >> from >> to;
            if constexpr (weighted) {
                T weight;
                std::cin >> weight;
                edges.emplace_back(from - origin, to - origin, weight);
            } else {
                edges.emplace_back(from - origin, to - origin, weight_type());
            }
        }
    }

    /// @brief 1 本の辺を追加する
    /// @complexity 償却 $O(1)$
    void emplace(int from, int to, weight_type weight = weight_type()) { edges.emplace_back(from, to, weight); }

    /// @brief 保持する辺数を返す
    /// @complexity $O(1)$
    int size() const { return (int)edges.size(); }

    /// @brief i番目の辺を返す
    /// @complexity $O(1)$
    const raw_edge &operator[](int i) const { return edges[i]; }

    /// @brief 先頭iteratorを返す
    /// @complexity $O(1)$
    auto begin() const { return edges.begin(); }

    /// @brief 終端iteratorを返す
    /// @complexity $O(1)$
    auto end() const { return edges.end(); }

    /// @brief 有向辺として graph に流し込む（add_edge を呼ぶ）
    /// @complexity $O(E)$
    template <class G>
    void build_directed(G &g) const {
        for (auto &e : edges) {
            if constexpr (weighted) g.add_edge(e.from, e.to, e.weight);
            else g.add_edge(e.from, e.to);
        }
    }

    /// @brief 無向辺として graph に流し込む（add_edges を呼ぶ）
    /// @complexity $O(E)$
    template <class G>
    void build_undirected(G &g) const {
        for (auto &e : edges) {
            if constexpr (weighted) g.add_edges(e.from, e.to, e.weight);
            else g.add_edges(e.from, e.to);
        }
    }

    /// @brief n 頂点の有向グラフを構築して返す
    /// @tparam GraphT 構築するグラフ型テンプレート（`csr_graph`（既定）/ `list_graph`）
    ///
    /// `csr_graph` の場合は辺数（有向辺 = m 本）を予約してから `build()` まで行う。
    /// @complexity $O(V+E)$
    template <template <class> class GraphT = csr_graph>
    GraphT<T> to_directed(int n) const {
        GraphT<T> g(n);
        if constexpr (std::is_same_v<GraphT<T>, csr_graph<T>>) g.reserve_edges(size(), size());
        build_directed(g);
        if constexpr (std::is_same_v<GraphT<T>, csr_graph<T>>) g.build();
        return g;
    }

    /// @brief n 頂点の無向グラフを構築して返す
    /// @tparam GraphT 構築するグラフ型テンプレート（`csr_graph`（既定）/ `list_graph`）
    ///
    /// `csr_graph` の場合は辺数（辺 ID = m 個・有向辺 = 2m 本）を予約してから `build()` まで行う。
    /// @complexity $O(V+E)$
    template <template <class> class GraphT = csr_graph>
    GraphT<T> to_undirected(int n) const {
        GraphT<T> g(n);
        if constexpr (std::is_same_v<GraphT<T>, csr_graph<T>>) g.reserve_edges(size(), 2 * size());
        build_undirected(g);
        if constexpr (std::is_same_v<GraphT<T>, csr_graph<T>>) g.build();
        return g;
    }

  private:
    std::vector<raw_edge> edges;
};
