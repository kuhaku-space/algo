#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T, class U>
std::vector<T> dijkstra(const Graph<T> &graph, const vector<U> &potentials, int s = 0,
                        T inf = std::numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        constexpr _edge() : to(), dist() {}
        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist) {}
        bool operator<(const _edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    int n = graph.size();
    std::vector<T> dists(n, inf);
    std::priority_queue<_edge, std::vector<_edge>, std::greater<_edge>> p_que;
    dists[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        auto e = p_que.top();
        p_que.pop();
        if (dists[e.to] < e.dist) continue;
        for (auto &next : graph[e.to]) {
            if (chmin(dists[next.to], e.dist + next.dist + potentials[e.to] - potentials[next.to]))
                p_que.emplace(next.to, e.dist + next.dist + potentials[e.to] - potentials[next.to]);
        }
    }
    for (int i = 0; i < n; ++i) { dists[i] += potentials[i] - potentials[s]; }
    return dists;
}
