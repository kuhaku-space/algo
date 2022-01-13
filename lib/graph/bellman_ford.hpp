#include "template/template.hpp"
#include "graph/graph.hpp"

// verify : https://atcoder.jp/contests/abc137/tasks/abc137_e 21/02/24
// verify : https://atcoder.jp/contests/abc061/tasks/abc061_d 21/02/24

/**
 * @brief ベルマンフォード法
 * 
 * @tparam T 
 * @param g グラフ
 * @param s 始点
 * @param inf 
 * @return vector<T> 
 */
template <class T>
vector<T> bellman_ford(const Graph<T> &g, int s = 0,
                       T inf = numeric_limits<T>::max()) {
    int n = g.size();
    vector<T> dist(n, inf);
    dist[s] = T();
    bool flg = true;
    for (int cnt = 0; flg && cnt <= n << 1; ++cnt) {
        flg = false;
        for (int i = 0; i < n; ++i) {
            if (dist[i] == inf) continue;
            for (auto &j : g[i]) {
                if (dist[i] == -inf || chmin(dist[j.to], dist[i] + j.dist)) {
                    if (dist[j.to] == -inf) continue;
                    flg = true;
                    if (cnt >= n) dist[j.to] = -inf;
                }
            }
        }
    }
    return dist;
}
