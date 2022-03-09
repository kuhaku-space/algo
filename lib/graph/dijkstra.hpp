#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief ダイクストラ法
 *
 * @tparam T
 * @param g グラフ
 * @param s 始点
 * @param inf 正の無限表現
 * @retval std::vector<T> 各頂点までの最短距離
 */
template <class T>
std::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        constexpr _edge() : to(), dist() {}
        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist) {}
        bool operator<(const _edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    std::vector<T> dist(g.size(), inf);
    std::priority_queue<_edge, std::vector<_edge>, std::greater<>> p_que;
    dist[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        _edge e = p_que.top();
        p_que.pop();
        if (dist[e.to] < e.dist) continue;
        for (auto &i : g[e.to]) {
            if (chmin(dist[i.to], e.dist + i.dist)) p_que.emplace(i.to, e.dist + i.dist);
        }
    }
    return dist;
}
