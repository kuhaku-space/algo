#include "template/template.hpp"

/**
 * @brief HLD
 * @details [参考](https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp)
 *
 */
struct HLD {
    HLD(int n) : g(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

    void dfs_sz(int v) {
        auto &es = this->g[v];
        if (~(this->par[v])) es.erase(find(es.begin(), es.end(), this->par[v]));

        for (auto &u : es) {
            this->par[u] = v;
            this->dfs_sz(u);
            this->sub[v] += this->sub[u];
            if (this->sub[u] > this->sub[es[0]]) swap(u, es[0]);
        }
    }

    void dfs_hld(int v, int &pos) {
        this->vid[v] = pos++;
        this->inv[this->vid[v]] = v;
        for (auto u : this->g[v]) {
            if (u == this->par[v]) continue;
            this->nxt[u] = (u == this->g[v][0] ? this->nxt[v] : u);
            this->dfs_hld(u, pos);
        }
    }

    void add_edge(int u, int v) {
        this->g[u].emplace_back(v);
        this->g[v].emplace_back(u);
    }
    void add_edges(int u, int v) { this->add_edge(u, v); }

    void build(int r = 0) {
        int pos = 0;
        this->dfs_sz(r);
        this->nxt[r] = r;
        this->dfs_hld(r, pos);
    }

    int lca(int u, int v) {
        while (true) {
            if (this->vid[u] > this->vid[v]) swap(u, v);
            if (this->nxt[u] == this->nxt[v]) return u;
            v = this->par[this->nxt[v]];
        }
    }

    template <class F>
    void for_each(int u, int v, const F &f) {
        while (true) {
            if (this->vid[u] > this->vid[v]) swap(u, v);
            f(max(this->vid[this->nxt[v]], this->vid[u]), this->vid[v] + 1);
            if (this->nxt[u] != this->nxt[v])
                v = this->par[this->nxt[v]];
            else
                break;
        }
    }

    template <class F>
    void for_each_edge(int u, int v, const F &f) {
        while (true) {
            if (this->vid[u] > this->vid[v]) swap(u, v);
            if (this->nxt[u] != this->nxt[v]) {
                f(this->vid[this->nxt[v]], this->vid[v] + 1);
                v = this->par[this->nxt[v]];
            } else {
                if (u != v) f(this->vid[u] + 1, this->vid[v] + 1);
                break;
            }
        }
    }

  private:
    vector<vector<int>> g;

    // vid: vertex -> idx
    // inv: idx -> vertex
    vector<int> vid, nxt, sub, par, inv;
};
