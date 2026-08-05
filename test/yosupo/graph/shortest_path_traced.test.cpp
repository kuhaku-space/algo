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
#include "dp/traced.hpp"
#include "graph/edge_input.hpp"
#include "graph/graph.hpp"
#include "graph/shortest_path.hpp"

using Dist = Traced<std::int64_t>;

// DP 値を Traced にしたダイクストラ法。prev 配列も復元ループも持たず、経路は Traced が運ぶ。
// 比較は cost のみなので、距離だけを求める版と時間計算量は変わらない。
std::vector<Dist> dijkstra_traced(const csr_graph<std::int64_t> &g, int s, std::int64_t inf) {
    using node = std::pair<std::int64_t, int>;
    std::vector<Dist> dp(g.size(), Dist(inf));
    std::priority_queue<node, std::vector<node>, std::greater<>> que;
    dp[s] = Dist(0);
    que.emplace(0, s);
    while (!que.empty()) {
        auto [d, v] = que.top();
        que.pop();
        if (dp[v].cost < d) continue;
        for (auto &e : g[v]) {
            if (auto cand = dp[v].then(e.weight(), e.to()); cand < dp[e.to()]) {
                dp[e.to()] = cand;
                que.emplace(cand.cost, e.to());
            }
        }
    }
    return dp;
}

int main(void) {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    edge_input<std::int64_t> ei(m, 0);
    auto g = ei.to_directed(n);
    constexpr std::int64_t inf = std::numeric_limits<std::int64_t>::max();

    auto dp = dijkstra_traced(g, s, inf);
    // 距離は verify 済みの shortest_path と完全一致するはず。
    auto dist = shortest_path(g, s, inf);
    for (int i = 0; i < n; ++i) assert(dp[i].cost == dist[i]);

    if (dp[t].cost == inf) {
        std::cout << -1 << '\n';
        return 0;
    }

    auto path = dp[t].to_vector();
    // 経路が実際に辺で繋がっており、重みの和が cost と一致することを確かめる。
    // 最短路の頂点は互いに異なるので、隣接リストの走査は合計 O(E) で収まる。
    std::int64_t sum = 0;
    int from = s;
    for (int to : path) {
        std::int64_t weight = inf;
        for (auto &e : g[from]) {
            if (e.to() == to) weight = std::min(weight, e.weight());
        }
        assert(weight != inf);
        sum += weight;
        from = to;
    }
    assert(from == t && sum == dp[t].cost);

    std::cout << dp[t].cost << ' ' << path.size() << '\n';
    from = s;
    for (int to : path) {
        std::cout << from << ' ' << to << '\n';
        from = to;
    }
    return 0;
}
