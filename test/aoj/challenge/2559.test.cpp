// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2559
#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>
#include "graph/graph.hpp"
#include "heap/skew_heap.hpp"
#include "tree/union_find.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::tuple<int, int, int>> edges(m);
    for (auto &[u, v, w] : edges) std::cin >> u >> v >> w, --u, --v;
    std::vector<int> ord(m);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(),
              [&](int x, int y) { return std::get<2>(edges[x]) < std::get<2>(edges[y]); });
    std::int64_t sum = 0;
    union_find uf(n);
    std::vector<skew_heap<std::pair<int, int>, std::greater<>>> heap(n);
    Graph<int> g(n);
    std::vector<bool> used(m);
    for (auto x : ord) {
        auto [u, v, w] = edges[x];
        if (uf.same(u, v)) {
            heap[u].emplace(w, v);
            heap[v].emplace(w, u);
        } else {
            sum += w;
            uf.unite(u, v);
            g.add_edges(u, v, x);
            used[x] = true;
        }
    }
    if (uf.size(0) != n) {
        for (int i = 0; i < m; ++i) std::cout << -1 << '\n';
        return 0;
    }
    std::vector<std::int64_t> ans(m, -1);
    for (int i = 0; i < m; ++i) {
        if (!used[i]) ans[i] = sum;
    }
    uf = union_find(n);
    auto dfs = [&](auto self, int x, int p) -> void {
        for (auto e : g[x]) {
            if (e.to() == p) continue;
            self(self, e.to(), x);
            while (!heap[e.to()].empty() && uf.same(e.to(), heap[e.to()].top().second))
                heap[e.to()].pop();
            if (!heap[e.to()].empty()) {
                auto [u, v, w] = edges[e.weight()];
                ans[e.weight()] = sum - w + heap[e.to()].top().first;
            }
            heap[x].meld(heap[e.to()]);
            uf.unite(x, e.to());
        }
    };
    dfs(dfs, 0, -1);
    for (int i = 0; i < m; ++i) std::cout << ans[i] << '\n';

    return 0;
}
