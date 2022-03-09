#include "data_structure/fibonacci_heap.hpp"
#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief ダイクストラ法（フィボナッチヒープ）
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
    using f_heap = fibonacci_heap<int, T, std::greater<>>;
    f_heap heap;
    std::vector<typename f_heap::node_pointer> nodes(g.size());
    dists[s] = T();
    heap.push(s, T());
    while (!heap.empty()) {
        auto [to, dist] = heap.top();
        heap.pop();
        if (dists[to] < dist) continue;
        for (auto &i : g[to]) {
            if (chmin(dists[i.to], dist + i.dist)) {
                if (nodes[i.to])
                    heap.update(nodes[i.to], dist + i.dist);
                else
                    nodes[i.to] = heap.push(i.to, dist + i.dist);
            }
        }
    }
    return dists;
}
