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
#include "heap/meldable_heap.hpp"
#include "union_find/union_find.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::tuple<int, int, int>> edges(m);
    for (auto &[u, v, w] : edges) std::cin >> u >> v >> w, --u, --v;
    std::vector<int> ord(m);
    std::iota(ord.begin(), ord.end(), 0);
    std::sort(ord.begin(), ord.end(), [&](int x, int y) { return std::get<2>(edges[x]) < std::get<2>(edges[y]); });
    std::int64_t sum = 0;
    union_find uf(n);
    std::vector<MeldableHeap<std::pair<int, int>, std::greater<>, true>> heap(n);
    list_graph<int> g(n);
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
    // 反復 DFS（再帰だと深い木でスタックオーバーフローしうる）。
    // 帰りがけに親側の辺を辿って heap の pop/meld と ans の更新を行う。
    std::vector<int> par(n, -1), pe(n, -1);
    struct frame {
        int v, p, idx;
    };
    std::vector<frame> stk;
    stk.reserve(n);
    stk.push_back({0, -1, 0});
    while (!stk.empty()) {
        frame &f = stk.back();
        int x = f.v;
        if (f.idx < (int)g[x].size()) {
            int i = f.idx++;
            auto e = g[x][i];
            if (e.to() == f.p) continue;
            par[e.to()] = x;
            pe[e.to()] = i;
            stk.push_back({e.to(), x, 0});
        } else {
            int p = par[x];
            stk.pop_back();
            if (p != -1) {
                auto e = g[p][pe[x]];
                while (!heap[x].empty() && uf.same(x, heap[x].top().second)) heap[x].pop();
                if (!heap[x].empty()) {
                    auto [u, v, w] = edges[e.weight()];
                    ans[e.weight()] = sum - w + heap[x].top().first;
                }
                heap[p].meld(heap[x]);
                uf.unite(p, x);
            }
        }
    }
    for (int i = 0; i < m; ++i) std::cout << ans[i] << '\n';

    return 0;
}
