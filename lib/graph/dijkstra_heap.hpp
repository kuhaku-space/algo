#include "data_structure/binary_heap.hpp"
#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief ダイクストラ法（二分ヒープ）
 *
 * @tparam T
 * @param g グラフ
 * @param s 始点
 * @param inf 正の無限表現
 * @retval std::vector<T> 各頂点までの最短距離
 */
template <class T>
std::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    std::vector<T> dists(g.size(), inf);
    using b_heap = binary_heap<int, T, std::greater<>>;
    b_heap heap;
    std::vector<typename b_heap::node_pointer> nodes(g.size());
    dists[s] = T();
    heap.emplace(s, T());
    while (!heap.empty()) {
        auto [to, dist] = heap.top();
        heap.pop();
        if (dists[to] < dist) continue;
        for (auto &i : g[to]) {
            if (chmin(dists[i.to], dist + i.dist)) {
                if (!nodes[i.to])
                    nodes[i.to] = heap.push(i.to, dist + i.dist);
                else
                    heap.update(nodes[i.to], dist + i.dist);
            }
        }
    }
    return dists;
}
