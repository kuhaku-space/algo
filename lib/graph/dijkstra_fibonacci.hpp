#include "template/template.hpp"
#include "graph/graph.hpp"

template <class T>
std::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        constexpr _edge() : to(), dist() {}
        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist) {}
        bool operator<(const _edge &rhs) const {
            return this->dist < rhs.dist;
        }
        bool operator>(const _edge &rhs) const {
            return rhs < *this;
        }
    };
    std::vector<T> dists(g.size(), inf);
    using f_heap = fibonacci_heap<int, T, greater<>>;
    std::vector<typename f_heap::node_pointer> nodes(g.size());
    f_heap heap;
    dists[s] = T();
    heap.push(s, T());
    while (!heap.empty()) {
        auto [to, dist] = heap.top();
        heap.pop();
        if (dists[to] < dist)
            continue;
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
