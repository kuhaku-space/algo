#pragma once
#include <algorithm>
#include <type_traits>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @file
/// @brief 木の基本関数
/// @details 根付き木の親・深さ・部分木の大きさなどの一括構築と、木の中心を提供する。

namespace internal {

/// @brief `tree_info` の距離の型を決める
/// @details `U` が `void` でなければ `U`。`void` なら実重み付きグラフは辺重みの型、それ以外は `int`。
/// @complexity コンパイル時に評価し実行時計算量はない
template <class U, class G>
consteval auto tree_info_dist_type() {
    if constexpr (!std::is_void_v<U>) return std::type_identity<U>{};
    else if constexpr (properly_weighted_graph_type<G>)
        return std::type_identity<std::remove_cvref_t<graph_weight_t<G>>>{};
    else return std::type_identity<int>{};
}

}  // namespace internal

/// @brief 根付き木の基本情報
/// @details 根から到達できない頂点は `parent` と `depth` が $-1$、`size` が $0$ で、
/// `preorder` と `bfs_order` に含まれない。
/// @tparam U 根からの距離の型
template <class U>
struct TreeInfo {
    /// @brief 根
    int root;
    /// @brief `parent[v]` は頂点 `v` の親。根は $-1$
    std::vector<int> parent;
    /// @brief `depth[v]` は根から頂点 `v` までの辺の本数
    std::vector<int> depth;
    /// @brief `dist[v]` は根から頂点 `v` までの辺の重みの和。重みなしなら `depth` と等しい
    std::vector<U> dist;
    /// @brief `size[v]` は頂点 `v` を根とする部分木の頂点数
    std::vector<int> size;
    /// @brief DFS の行きがけ順。子は隣接リストの順に訪れる
    std::vector<int> preorder;
    /// @brief BFS 順。同じ深さの頂点は `preorder` の順に並ぶ
    std::vector<int> bfs_order;
};

/// @brief 根 `r` の根付き木の親・深さ・距離・部分木の大きさ・DFS 順・BFS 順を一括で求める
/// @details 反復 DFS 1 回で構築するので、深い木でもスタックオーバーフローしない。
/// @tparam U 距離の型。省略すると実重み付きグラフでは辺重みの型、重みなしでは `int`。
/// 和があふれるときは `tree_info<std::int64_t>(g, r)` のように指定する
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @param g 木
/// @param r 根
/// @complexity $O(V)$
/// @code
/// #include <iostream>
/// #include "graph/graph.hpp"
/// #include "tree/tree_function.hpp"
///
/// int main() {
///     // 1 -(5)- 0 -(1)- 2 -(2)- 3
///     list_graph<int> g(4);
///     g.add_edges(0, 1, 5);
///     g.add_edges(0, 2, 1);
///     g.add_edges(2, 3, 2);
///     auto t = tree_info(g, 0);
///     for (int v = 0; v < 4; ++v)
///         std::cout << t.parent[v] << ' ' << t.depth[v] << ' ' << t.dist[v] << ' ' << t.size[v] << '\n';
///     for (int v : t.preorder) std::cout << v << ' ';
///     std::cout << '\n';
///     for (int v : t.bfs_order) std::cout << v << ' ';
///     std::cout << '\n';
/// }
/// @endcode
template <class U = void, graph_type G>
auto tree_info(const G &g, int r = 0) {
    using W = typename decltype(internal::tree_info_dist_type<U, G>())::type;
    int n = g.size();
    TreeInfo<W> res;
    res.root = r;
    res.parent.assign(n, -1);
    res.depth.assign(n, -1);
    res.dist.assign(n, W());
    res.size.assign(n, 0);
    res.preorder.reserve(n);
    // 反復 DFS（再帰だと深い木でスタックオーバーフローしうる）
    std::vector<int> stk;
    stk.reserve(n);
    stk.emplace_back(r);
    res.depth[r] = 0;
    while (!stk.empty()) {
        int v = stk.back();
        stk.pop_back();
        res.preorder.emplace_back(v);
        int top = stk.size();
        for (auto &&e : g[v]) {
            int to = e.to();
            if (res.depth[to] != -1) continue;
            res.parent[to] = v;
            res.depth[to] = res.depth[v] + 1;
            if constexpr (weighted_graph_type<G>) res.dist[to] = res.dist[v] + static_cast<W>(e.weight());
            else res.dist[to] = res.dist[v] + 1;
            stk.emplace_back(to);
        }
        // 子を隣接リストの順に訪れるため、積んだ分を逆順にする
        std::reverse(stk.begin() + top, stk.end());
    }
    // 帰りがけ順に部分木の大きさを親へ加算する
    for (int i = (int)res.preorder.size() - 1; i >= 0; --i) {
        int v = res.preorder[i];
        ++res.size[v];
        if (res.parent[v] != -1) res.size[res.parent[v]] += res.size[v];
    }
    // 行きがけ順を深さで安定に数え上げソートすると BFS 順になる
    int max_depth = 0;
    for (int v : res.preorder) max_depth = std::max(max_depth, res.depth[v]);
    std::vector<int> cnt(max_depth + 2);
    for (int v : res.preorder) ++cnt[res.depth[v] + 1];
    for (int d = 0; d <= max_depth; ++d) cnt[d + 1] += cnt[d];
    res.bfs_order.resize(res.preorder.size());
    for (int v : res.preorder) res.bfs_order[cnt[res.depth[v]]++] = v;
    return res;
}

/// @brief 親配列が表す根付き木の基本情報を求める
/// @param parents `parents[v]` は頂点 `v` の親。根は $-1$ か自分自身
/// @complexity $O(V)$
inline TreeInfo<int> tree_info(const std::vector<int> &parents) {
    int n = parents.size();
    csr_graph<void> g(n);
    if (n > 0) g.reserve_edges(n - 1, 2 * (n - 1));
    int r = 0;
    for (int i = 0; i < n; ++i) {
        if (parents[i] == -1 || parents[i] == i) {
            r = i;
            continue;
        }
        g.add_edges(i, parents[i]);
    }
    g.build();
    return tree_info(g, r);
}

/// @brief 木の中心と、各頂点から最も近い中心
/// @details 直径を辺の本数で数えたときの中心を表す。直径 $D$ が偶数なら中心は 1 頂点、
/// 奇数なら隣接する 2 頂点で、どちらも任意の頂点からの最大距離（離心数）を最小にする。
struct TreeCenter {
    /// @brief 直径（辺の本数）
    int diameter;
    /// @brief 中心の頂点番号。直径が偶数なら 1 個、奇数なら隣接する 2 個
    std::vector<int> centers;
    /// @brief `nearest[v]` は頂点 `v` から最も近い中心
    std::vector<int> nearest;
    /// @brief `dist[v]` は頂点 `v` から最も近い中心までの距離（辺の本数）
    std::vector<int> dist;
    /// @brief `branch[v]` は `nearest[v]` から `v` へのパスで中心の次に通る頂点。中心自身は $-1$
    std::vector<int> branch;
};

/// @brief 木の中心と、各頂点から最も近い中心とその距離を求める
/// @details 辺の重みは無視し、辺の本数を距離とする。中心が 2 頂点のとき、各頂点の最も近い
/// 中心は一意に定まる（2 中心を結ぶ辺のどちら側にあるかで決まる）。
/// 頂点 `v` が直径の端点になるのは `dist[v] == diameter / 2` のときに限る。
/// @note 中心を常に 1 頂点にしたいときは、`subdivide_edges`（`graph/subdivide_edges.hpp`）で
/// 各辺に中点を追加した木に適用する。距離と直径は 2 倍になる。
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @param g 木。頂点数は $1$ 以上
/// @complexity $O(V)$
/// @code
/// #include <iostream>
/// #include "graph/graph.hpp"
/// #include "tree/tree_function.hpp"
///
/// int main() {
///     // 0 - 1 - 2 - 3
///     list_graph<void> g(4);
///     g.add_edges(0, 1);
///     g.add_edges(1, 2);
///     g.add_edges(2, 3);
///     auto tc = tree_center(g);
///     std::cout << tc.diameter << ' ' << tc.centers.size() << '\n';
///     for (int v = 0; v < 4; ++v) std::cout << tc.nearest[v] << ' ' << tc.dist[v] << '\n';
/// }
/// @endcode
template <graph_type G>
TreeCenter tree_center(const G &g) {
    int n = g.size();
    std::vector<int> d(n), par(n);
    // 頂点群 srcs からの多始点 BFS。d に距離、par に BFS 木の親を入れ、訪問順を返す
    auto bfs = [&](const std::vector<int> &srcs) {
        std::fill(d.begin(), d.end(), -1);
        std::vector<int> que(srcs);
        que.reserve(n);
        for (int s : srcs) d[s] = 0, par[s] = -1;
        for (int i = 0; i < (int)que.size(); ++i) {
            int v = que[i];
            for (auto &e : g[v]) {
                int to = e.to();
                if (d[to] != -1) continue;
                d[to] = d[v] + 1;
                par[to] = v;
                que.emplace_back(to);
            }
        }
        return que;
    };
    int s = bfs({0}).back();
    int t = bfs({s}).back();
    TreeCenter res;
    res.diameter = d[t];
    // t から s へ diameter / 2 歩進んだ頂点が中心。奇数ならその次の頂点も中心
    int c = t;
    for (int i = 0; i < res.diameter / 2; ++i) c = par[c];
    res.centers.emplace_back(c);
    if (res.diameter % 2 == 1) res.centers.emplace_back(par[c]);
    auto order = bfs(res.centers);
    res.nearest.resize(n);
    res.branch.resize(n);
    // BFS 順に親から伝播する
    for (int v : order) {
        if (par[v] == -1) {
            res.nearest[v] = v;
            res.branch[v] = -1;
        } else {
            res.nearest[v] = res.nearest[par[v]];
            res.branch[v] = par[par[v]] == -1 ? v : res.branch[par[v]];
        }
    }
    res.dist = std::move(d);
    return res;
}
