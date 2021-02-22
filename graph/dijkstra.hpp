#include "_base.hpp"
#include "graph/graph.hpp"

template <class T>
vector<T> dijkstra(const Graph<T> &g, int s = 0,
                   T inf = numeric_limits<T>::max()) {
    vector<T> dist(g.size(), inf);
    using _edge = Graph<T>::edge;
    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;
    p_que.push(edge{s, s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (chmin(dist[e.to], e.dist))
            for (auto i : g.edges[e.to]) p_que.push(e + i);
    }
    return dist;
}