#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C"
#include "graph/matrix_graph.hpp"
#include "graph/warshall_floyd.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int v, e;
    cin >> v >> e;
    matrix_graph<ll> g(v, INF);
    while (e--) {
        int s, t, d;
        cin >> s >> t >> d;
        g.add_edge(s, t, d);
    }
    warshall_floyd(g);
    rep(i, v) {
        if (g[i][i] < 0) {
            co("NEGATIVE CYCLE");
            return 0;
        }
    }

    rep(i, v) {
        vector<string> ans;
        rep(j, v) {
            if (g[i][j] >= INF / 2)
                ans.emplace_back("INF");
            else
                ans.emplace_back(to_string(g[i][j]));
        }
        co(ans);
    }

    return 0;
}
