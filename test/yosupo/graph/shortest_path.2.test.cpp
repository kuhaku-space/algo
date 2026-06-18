// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/shortest_path
#include <iostream>
#include <utility>
#include <vector>
#include "graph/edge_input.hpp"
#include "heap/fibonacci_heap.hpp"
#include "template/template.hpp"

// fibonacci_heap を decrease-key で使ったダイクストラ法（経路復元つき）。
// 頂点ごとにハンドルを保持し、push / top / pop / update をすべて検証する。
// （距離のみでよければライブラリの shortest_path<fibonacci_heap>(g, s) を
//   ヒープ差し替えで呼ぶだけでよい。本問は経路復元が要るので prev も求める。）
template <class T>
std::pair<std::vector<T>, std::vector<int>> dijkstra(const csr_graph<T> &g, int s) {
    int n = g.size();
    using heap_type = fibonacci_heap<int, T, std::greater<>>;
    using node_ptr = typename heap_type::node_ptr;
    std::vector<T> dists(n, INF);
    std::vector<int> prev(n, -1);
    std::vector<node_ptr> handle(n, nullptr);
    heap_type heap;
    dists[s] = T();
    handle[s] = heap.push(s, T());
    while (!heap.empty()) {
        auto [v, d] = heap.top();
        heap.pop();
        handle[v] = nullptr;
        for (auto &e : g[v]) {
            int to = e.to();
            if (dists[to] <= d + e.weight()) continue;
            dists[to] = d + e.weight();
            prev[to] = v;
            if (handle[to]) heap.update(handle[to], dists[to]);  // decrease-key
            else handle[to] = heap.push(to, dists[to]);
        }
    }
    return {dists, prev};
}

int main(void) {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    edge_input<std::int64_t> ei(m, 0);
    auto g = ei.to_directed(n);
    auto &&[dist, prev] = dijkstra<std::int64_t>(g, s);
    if (dist[t] == INF) {
        std::cout << -1 << '\n';
    } else {
        std::vector<std::pair<int, int>> ans;
        int idx = t;
        while (idx != s) {
            ans.emplace_back(prev[idx], idx);
            idx = prev[idx];
        }
        std::reverse(ans.begin(), ans.end());
        std::cout << dist[t] << ' ' << ans.size() << '\n';
        for (auto p : ans) std::cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}
