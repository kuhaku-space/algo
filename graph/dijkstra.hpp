#include "_base.hpp"
#include "data_struct/radix_heap.hpp"
#include "graph/graph.hpp"

/*
 * verify :
 * https://atcoder.jp/contests/abc192/tasks/abc192_e 21/02/24
 * https://atcoder.jp/contests/abc191/tasks/abc191_e 21/04/08
 * https://atcoder.jp/contests/abc190/tasks/abc190_e 21/04/08
 * https://atcoder.jp/contests/abc148/tasks/abc148_f 21/04/08
 */

template <class T>
vector<T> dijkstra(const Graph<T> &g, int s = 0,
                   T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;
    dist[s] = T();
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist))
                p_que.push(_edge{i.to, e.dist + i.dist});
        }
    }
    return dist;
}

template <class T>
vector<T> dijkstra_late(const Graph<T> &g, int s = 0,
                        T inf = numeric_limits<T>::max()) {
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

template <class T>
vector<T> dijkstra_fast(const Graph<T> &g, int s = 0,
                        T inf = numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        bool operator<(const _edge &rhs) const { return dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    vector<T> dist(g.size(), inf);
    radix_heap_dijkstra<_edge> p_que;
    dist[s] = T();
    p_que.push(_edge{s, T()});
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist))
                p_que.push(_edge{i.to, e.dist + i.dist});
        }
    }
    return dist;
}
