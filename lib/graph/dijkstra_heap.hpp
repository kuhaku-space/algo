#pragma once
#include "graph/graph.hpp"
#include "heap/binary_heap.hpp"
#include "heap/fibonacci_heap.hpp"
#include "heap/radix_heap.hpp"
#include "template/template.hpp"

template <class T>
using b_heap = binary_heap<int, T, std::greater<>>;
template <class T>
using f_heap = fibonacci_heap<int, T, std::greater<>>;
template <class T>
using r_heap = radix_heap<int, T>;

/**
 * @brief ダイクストラ法（ヒープ）
 *
 * @tparam T
 * @param g グラフ
 * @param s 始点
 * @param inf 正の無限表現
 * @retval std::vector<T> 各頂点までの最短距離
 */
template <class T, class Heap>
std::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    Heap heap;
    std::vector<typename Heap::node_ptr> nodes(g.size());
    std::vector<T> dists(g.size(), inf);
    dists[s] = T();
    heap.emplace(s, T());
    while (!heap.empty()) {
        auto [to, dist] = heap.top();
        heap.pop();
        if (dists[to] < dist) continue;
        for (auto &e : g[to]) {
            if (chmin(dists[e.to()], dist + e.weight())) {
                if (!nodes[e.to()]) nodes[e.to()] = heap.push(e.to(), dist + e.weight());
                else heap.update(nodes[e.to()], dist + e.weight());
            }
        }
    }
    return dists;
}
