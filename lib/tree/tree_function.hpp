#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @file
/// @brief 木の基本関数
/// @details 木の高さ、直径、中心、重心など、木全体に対する基本的な問い合わせを提供する。

/// @brief 根rからのBFS順を返す
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <graph_type G>
std::vector<int> tree_bfs(const G &g, int r = 0) {
    int pos = 0;
    std::vector<int> res;
    std::vector<bool> visited(g.size());
    res.emplace_back(r);
    visited[r] = true;
    while (pos < (int)res.size()) {
        auto index = res[pos++];
        for (auto &e : g[index]) {
            if (visited[e.to()]) continue;
            res.emplace_back(e.to());
            visited[e.to()] = true;
        }
    }
    return res;
}

/// @brief 親配列が表す木のBFS順を返す
/// @complexity $O(V)$
std::vector<int> tree_bfs(const std::vector<int> &parents) {
    int n = parents.size();
    list_graph<void> g(n);
    int r = 0;
    for (int i = 0; i < n; ++i) {
        if (parents[i] == -1 || parents[i] == i) {
            r = i;
            continue;
        }
        g.add_edges(i, parents[i]);
    }
    return tree_bfs(g, r);
}

/// @brief 根rからのDFS行きがけ順を返す
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <graph_type G>
std::vector<int> tree_dfs(const G &g, int r = 0) {
    std::vector<int> res;
    // 反復 DFS（再帰だと深い木でスタックオーバーフローしうる）。
    // 行きがけ順を保つため (頂点, 親) を積み、子は左から処理する。
    std::vector<std::pair<int, int>> stk;
    stk.reserve(g.size());
    stk.emplace_back(r, -1);
    while (!stk.empty()) {
        auto [index, parent] = stk.back();
        stk.pop_back();
        res.emplace_back(index);
        // 元の左→右の行きがけ順にするため逆順に積む
        for (auto it = g[index].rbegin(); it != g[index].rend(); ++it) {
            if (it->to() == parent) continue;
            stk.emplace_back(it->to(), index);
        }
    }
    return res;
}

/// @brief 木の距離を求める
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <weighted_graph_type G, class U = graph_weight_t<G>>
std::vector<U> tree_dist(const G &g, int r = 0) {
    std::vector<U> res(g.size(), -1);
    std::vector<int> stk;
    stk.reserve(g.size());
    res[r] = 0;
    stk.emplace_back(r);
    while (!stk.empty()) {
        auto index = stk.back();
        stk.pop_back();
        for (auto &e : g[index]) {
            if (res[e.to()] != -1) continue;
            res[e.to()] = res[index] + e.weight();
            stk.emplace_back(e.to());
        }
    }
    return res;
}

/// @brief 木の頂点の親を求める
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <graph_type G>
std::vector<int> tree_parent(const G &g, int r = 0) {
    std::vector<int> res(g.size(), -1);
    std::vector<int> stk;
    stk.reserve(g.size());
    res[r] = r;
    stk.emplace_back(r);
    while (!stk.empty()) {
        auto index = stk.back();
        stk.pop_back();
        for (auto &e : g[index]) {
            if (res[e.to()] != -1) continue;
            res[e.to()] = index;
            stk.emplace_back(e.to());
        }
    }
    res[r] = -1;
    return res;
}

/// @brief 部分木の大きさを求める
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(V+E)$
template <graph_type G>
std::vector<int> tree_subtree(const G &g, int r = 0) {
    std::vector<int> res(g.size());
    // 反復 DFS（再帰だと深い木でスタックオーバーフローしうる）。
    // 各フレームは (頂点, 親, 隣接走査位置)。隣接の再走査を避けるため位置を保持し、
    // 帰りがけに子の部分木サイズを親へ加算する。
    struct frame {
        int v, parent, idx;
    };
    std::vector<frame> stk;
    stk.reserve(g.size());
    stk.push_back({r, -1, 0});
    res[r] = 1;
    while (!stk.empty()) {
        frame &f = stk.back();
        if (f.idx < (int)g[f.v].size()) {
            int to = g[f.v][f.idx++].to();
            if (to == f.parent) continue;
            res[to] = 1;
            stk.push_back({to, f.v, 0});
        } else {
            int v = f.v, p = f.parent;
            stk.pop_back();
            if (p != -1) res[p] += res[v];
        }
    }
    return res;
}

/// @brief 木の各辺に中点を追加した木を返す
/// @details 辺 ID が `i` の辺 $(u, v)$ を、新しい頂点 $n + i$ を挟んだ 2 本の辺
/// $(u, n + i)$・$(n + i, v)$ に置き換える。元の頂点の番号は変わらない。
/// 2 頂点間の距離（辺の本数）はちょうど 2 倍になるので、直径は必ず偶数になり、
/// `tree_center` で求まる中心は常に 1 頂点になる。辺の重みは無視する。
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @param g 頂点数 $n$ の木。無向辺として追加され、辺 ID が $0, 1, \dots, n - 2$ であること
/// @return 頂点数 $2n - 1$ の重みなしの木
/// @complexity $O(n)$
/// @code
/// #include <iostream>
/// #include "graph/graph.hpp"
/// #include "tree/tree_function.hpp"
///
/// int main() {
///     // 0 - 1 - 2 - 3（直径 3、中心は 2 頂点）
///     list_graph<void> g(4);
///     g.add_edges(0, 1);
///     g.add_edges(1, 2);
///     g.add_edges(2, 3);
///     // 0 - 4 - 1 - 5 - 2 - 6 - 3（直径 6、中心は辺 1 の中点 5）
///     auto tc = tree_center(tree_subdivide(g));
///     std::cout << tc.diameter << ' ' << tc.centers[0] << '\n';
/// }
/// @endcode
template <graph_type G>
list_graph<void> tree_subdivide(const G &g) {
    int n = g.size();
    list_graph<void> res(2 * n - 1);
    for (int v = 0; v < n; ++v) {
        for (auto &e : g[v]) {
            if (v > e.to()) continue;
            res.add_edges(v, n + e.id());
            res.add_edges(n + e.id(), e.to());
        }
    }
    return res;
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
