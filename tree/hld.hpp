#include "_base.hpp"

/* 
 * reference :
 * https://github.com/beet-aizu/library/blob/master/tree/heavylightdecomposition.cpp
 * verify :
 * https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_E 21/04/08
 */

struct HLD {
    vector<vector<int>> G;

    // vid: vertex -> idx
    // inv: idx -> vertex
    vector<int> vid, nxt, sub, par, inv;

    HLD(int n) : G(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

    void dfs_sz(int v) {
        auto &es = G[v];
        if (~par[v]) es.erase(find(es.begin(), es.end(), par[v]));

        for (auto &u : es) {
            par[u] = v;
            dfs_sz(u);
            sub[v] += sub[u];
            if (sub[u] > sub[es[0]]) swap(u, es[0]);
        }
    }

    void dfs_hld(int v, int &pos) {
        vid[v] = pos++;
        inv[vid[v]] = v;
        for (auto u : G[v]) {
            if (u == par[v]) continue;
            nxt[u] = (u == G[v][0] ? nxt[v] : u);
            dfs_hld(u, pos);
        }
    }

    void add_edge(int u, int v) {
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    void build(int r = 0) {
        int pos = 0;
        dfs_sz(r);
        nxt[r] = r;
        dfs_hld(r, pos);
    }

    int lca(int u, int v) {
        while (true) {
            if (vid[u] > vid[v]) swap(u, v);
            if (nxt[u] == nxt[v]) return u;
            v = par[nxt[v]];
        }
    }

    template <class F>
    void for_each(int u, int v, const F &f) {
        while (true) {
            if (vid[u] > vid[v]) swap(u, v);
            f(max(vid[nxt[v]], vid[u]), vid[v] + 1);
            if (nxt[u] != nxt[v])
                v = par[nxt[v]];
            else
                break;
        }
    }

    template <class F>
    void for_each_edge(int u, int v, const F &f) {
        while (true) {
            if (vid[u] > vid[v]) swap(u, v);
            if (nxt[u] != nxt[v]) {
                f(vid[nxt[v]], vid[v] + 1);
                v = par[nxt[v]];
            } else {
                if (u != v) f(vid[u] + 1, vid[v] + 1);
                break;
            }
        }
    }
};
