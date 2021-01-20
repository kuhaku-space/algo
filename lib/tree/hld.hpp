#include "_base.hpp"

// https://github.com/beet-aizu/library/blob/master/tree/heavylightdecomposition.cpp

struct HLD {
    vector<vector<int64_t>> G;

    // vid: vertex -> idx
    // inv: idx -> vertex
    vector<int64_t> vid, nxt, sub, par, inv;

    HLD(int64_t n) : G(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

    void dfs_sz(int64_t v) {
        auto &es = G[v];
        if (~par[v]) es.erase(find(es.begin(), es.end(), par[v]));

        for (auto &u : es) {
            par[u] = v;
            dfs_sz(u);
            sub[v] += sub[u];
            if (sub[u] > sub[es[0]]) swap(u, es[0]);
        }
    }

    void dfs_hld(int64_t v, int64_t &pos) {
        vid[v] = pos++;
        inv[vid[v]] = v;
        for (auto u : G[v]) {
            if (u == par[v]) continue;
            nxt[u] = (u == G[v][0] ? nxt[v] : u);
            dfs_hld(u, pos);
        }
    }

    void add_edge(int64_t u, int64_t v) {
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    void build(int64_t r = 0) {
        int64_t pos = 0;
        dfs_sz(r);
        nxt[r] = r;
        dfs_hld(r, pos);
    }

    int64_t lca(int64_t u, int64_t v) {
        while (true) {
            if (vid[u] > vid[v]) swap(u, v);
            if (nxt[u] == nxt[v]) return u;
            v = par[nxt[v]];
        }
    }

    template <class F>
    void for_each(int64_t u, int64_t v, const F &f) {
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
    void for_each_edge(int64_t u, int64_t v, const F &f) {
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
