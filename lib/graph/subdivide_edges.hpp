#pragma once
#include <type_traits>
#include <vector>
#include "graph/graph.hpp"

/// @file
/// @brief 辺の細分（各辺に中点を追加する）
/// @details すべての辺の間に新しい頂点を 1 つずつ挟んだグラフを作る。
/// 経路の長さがちょうど 2 倍になるので、木の直径が偶数になって中心が 1 頂点に定まるなど、
/// 偶奇による場合分けを消したいときに使う。

namespace internal {

template <graph_type G>
struct SubdividedWeight {
    using type = void;
};

template <properly_weighted_graph_type G>
struct SubdividedWeight<G> {
    using type = std::remove_cvref_t<graph_weight_t<G>>;
};

}  // namespace internal

/// @brief 各辺に中点を追加したグラフを返す
/// @details 辺 ID が `i` の辺 $u \to v$ を、新しい頂点 $n + i$ を挟んだ 2 本の辺
/// $u \to n + i$・$n + i \to v$ に置き換える。元の頂点の番号は変わらない。
/// 無向辺（同じ ID の往復 2 本として格納された辺）は無向辺 2 本に、有向辺は有向辺 2 本になり、
/// 辺 ID が飛ばずに振られていれば、返すグラフでは前半の辺の ID が $2i$、後半の辺の ID が
/// $2i + 1$ になる。
/// 実重み付きなら 2 本とも元の重みを持ち、重みなしなら重みなしのままなので、
/// どちらでも任意の 2 頂点間の距離はちょうど 2 倍になる。
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @param g 頂点数 $n$ のグラフ。$m$ は辺 ID の最大値 $+ 1$（`add_edge` / `add_edges` で作ったグラフなら辺数）
/// @return 頂点数 $n + m$ の `list_graph`。重みの型は `g` と同じ。格納されていない辺 ID の頂点 $n + i$ は孤立点になる
/// @complexity $O(n + m)$
/// @code
/// #include <iostream>
/// #include "graph/graph.hpp"
/// #include "graph/subdivide_edges.hpp"
///
/// int main() {
///     list_graph<int> g(3);
///     g.add_edges(0, 1, 5);  // 辺 0（無向）
///     g.add_edge(1, 2, 7);   // 辺 1（有向）
///     auto h = subdivide_edges(g);
///     std::cout << h.size() << '\n';
///     for (int v = 0; v < h.size(); ++v) {
///         for (auto &e : h[v]) std::cout << v << " -> " << e.to() << " (" << e.weight() << ")\n";
///     }
/// }
/// @endcode
template <graph_type G>
auto subdivide_edges(const G &g) {
    using W = typename internal::SubdividedWeight<G>::type;
    int n = g.size();
    // 辺 ID ごとに始点・終点と、格納された向きの本数（無向辺なら 2）を集める
    std::vector<int> from, to, cnt;
    std::vector<std::conditional_t<std::is_void_v<W>, char, W>> weight;
    for (int v = 0; v < n; ++v) {
        for (auto &e : g[v]) {
            int id = e.id();
            if (id >= (int)cnt.size()) {
                from.resize(id + 1), to.resize(id + 1), cnt.resize(id + 1), weight.resize(id + 1);
            }
            if (cnt[id]++ == 0) {
                from[id] = v, to[id] = e.to();
                if constexpr (!std::is_void_v<W>) weight[id] = e.weight();
            }
        }
    }
    int m = cnt.size();
    list_graph<W> res(n + m);
    for (int i = 0; i < m; ++i) {
        if (cnt[i] == 0) continue;
        // 無向辺は走査順だと逆向きに見つかることがあるので、追加時の向きが分かればそれに揃える
        if constexpr (requires { g.get_edge(i).from(); }) from[i] = g.get_edge(i).from(), to[i] = g.get_edge(i).to();
        auto add = [&](int a, int b) {
            if constexpr (std::is_void_v<W>) {
                cnt[i] == 2 ? res.add_edges(a, b) : res.add_edge(a, b);
            } else {
                cnt[i] == 2 ? res.add_edges(a, b, weight[i]) : res.add_edge(a, b, weight[i]);
            }
        };
        add(from[i], n + i);
        add(n + i, to[i]);
    }
    return res;
}
