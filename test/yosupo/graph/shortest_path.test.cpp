// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/shortest_path
#include "template/template.hpp"
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
#include "graph/edge_input.hpp"
#include "heap/fibonacci_heap.hpp"

template <class T>
std::pair<std::vector<T>, std::vector<int>> dijkstra_pq(const csr_graph<T> &g, int s = 0,
                                                        T inf = std::numeric_limits<T>::max()) {
    struct _node {
        constexpr _node() : _to(), _dist() {}
        constexpr _node(int to, T dist) : _to(to), _dist(dist) {}

        constexpr bool operator<(const _node &rhs) const { return this->dist() < rhs.dist(); }
        constexpr bool operator>(const _node &rhs) const { return rhs < *this; }

        constexpr int to() const { return this->_to; }
        constexpr T dist() const { return this->_dist; }

      private:
        int _to;
        T _dist;
    };
    std::vector<T> dists(g.size(), inf);
    std::vector<int> v(g.size(), -1);
    std::priority_queue<_node, std::vector<_node>, std::greater<>> p_que;
    dists[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        auto node = p_que.top();
        p_que.pop();
        if (dists[node.to()] < node.dist()) continue;
        for (auto &e : g[node.to()]) {
            if (chmin(dists[e.to()], node.dist() + e.weight())) {
                v[e.to()] = node.to();
                p_que.emplace(e.to(), node.dist() + e.weight());
            }
        }
    }
    return {dists, v};
}

// fibonacci_heap を decrease-key で使ったダイクストラ法（経路復元つき）。
// 頂点ごとにハンドルを保持し、push / top / pop / update をすべて検証する。
// （距離のみでよければライブラリの shortest_path<fibonacci_heap>(g, s) を
//   ヒープ差し替えで呼ぶだけでよい。本問は経路復元が要るので prev も求める。）
template <class T>
std::pair<std::vector<T>, std::vector<int>> dijkstra_fib(const csr_graph<T> &g, int s) {
    int n = g.size();
    // key = 距離（順序基準）、value = 頂点（付随データ）。
    using heap_type = fibonacci_heap<T, int, std::greater<>>;
    using node_handle = decltype(std::declval<heap_type &>().push(T(), 0));
    std::vector<T> dists(n, INF);
    std::vector<int> prev(n, -1);
    std::vector<node_handle> handle(n, node_handle{});
    heap_type heap;
    dists[s] = T();
    handle[s] = heap.push(T(), s);
    while (!heap.empty()) {
        auto [d, v] = heap.top();
        heap.pop();
        handle[v] = node_handle{};
        for (auto &e : g[v]) {
            int to = e.to();
            if (dists[to] <= d + e.weight()) continue;
            dists[to] = d + e.weight();
            prev[to] = v;
            if (handle[to]) heap.update(handle[to], dists[to]);  // decrease-key
            else handle[to] = heap.push(dists[to], to);
        }
    }
    return {dists, prev};
}

int main(void) {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    edge_input<std::int64_t> ei(m, 0);
    auto g = ei.to_directed(n);
    auto &&[dist, v] = dijkstra_pq(g, s, INF);
    // 経路は一意でないため復元パスまでは突き合わせず、距離配列の完全一致のみ assert する。
    assert(dist == dijkstra_fib<std::int64_t>(g, s).first);
    if (dist[t] == INF) {
        std::cout << -1 << '\n';
    } else {
        std::vector<std::pair<int, int>> ans;
        int idx = t;
        while (idx != s) {
            ans.emplace_back(v[idx], idx);
            idx = v[idx];
        }
        std::reverse(ans.begin(), ans.end());
        std::cout << dist[t] << ' ' << ans.size() << '\n';
        for (auto p : ans) std::cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}
