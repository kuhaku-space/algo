#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T>
vector<T> dijkstra_late(const Graph<T> &g, int s = 0, T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (chmin(dist[e.to], e.dist))
            for (auto &i : g[e.to]) p_que.push(_edge{i.to, e.dist + i.dist});
    }
    return dist;
}
