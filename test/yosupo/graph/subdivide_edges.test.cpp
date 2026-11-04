// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/shortest_path
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
#include "graph/edge_input.hpp"
#include "graph/graph.hpp"
#include "graph/shortest_path.hpp"
#include "graph/subdivide_edges.hpp"

int main(void) {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    edge_input<std::int64_t> ei(m, 0);
    auto g = ei.to_directed(n);
    auto h = subdivide_edges(g);
    assert(h.size() == n + m);
    constexpr std::int64_t inf = std::numeric_limits<std::int64_t>::max();

    // 細分したグラフ上で経路復元つきのダイクストラ法を行う
    using node = std::pair<std::int64_t, int>;
    std::vector<std::int64_t> dist(h.size(), inf);
    std::vector<int> prev(h.size(), -1);
    std::priority_queue<node, std::vector<node>, std::greater<>> que;
    dist[s] = 0;
    que.emplace(0, s);
    while (!que.empty()) {
        auto [d, v] = que.top();
        que.pop();
        if (dist[v] < d) continue;
        for (auto &e : h[v]) {
            if (d + e.weight() < dist[e.to()]) {
                dist[e.to()] = d + e.weight();
                prev[e.to()] = v;
                que.emplace(dist[e.to()], e.to());
            }
        }
    }
    // 元の頂点への距離はちょうど 2 倍になる
    auto expected = shortest_path(g, s, inf);
    for (int v = 0; v < n; ++v) assert(dist[v] == (expected[v] == inf ? inf : 2 * expected[v]));

    if (dist[t] == inf) {
        std::cout << -1 << '\n';
        return 0;
    }
    // 経路上の元の頂点だけを取り出す（中点 n 以上は飛ばす）
    std::vector<int> path;
    for (int v = t; v != -1; v = prev[v]) {
        if (v < n) path.emplace_back(v);
    }
    std::reverse(path.begin(), path.end());
    std::cout << dist[t] / 2 << ' ' << path.size() - 1 << '\n';
    for (int i = 0; i + 1 < (int)path.size(); ++i) std::cout << path[i] << ' ' << path[i + 1] << '\n';
    return 0;
}
