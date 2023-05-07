#pragma once
#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief HLD
 * @see https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
 */
struct HLD {
    HLD(int n) : _size(n), g(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

    template <class T>
    HLD(const Graph<T> &g, int r = 0) : HLD(g.size()) {
        for (auto &es : g) {
            for (auto &e : es) {
                this->g[e.from()].emplace_back(e.to());
            }
        }
        this->build(r);
    }

    void add_edge(int u, int v) { this->add_edges(u, v); }
    void add_edges(int u, int v) {
        this->g[u].emplace_back(v);
        this->g[v].emplace_back(u);
    }

    void input_edge(int base = 1) { this->input_edges(base); }
    void input_edges(int base = 1) {
        for (int i = 0; i < this->_size - 1; ++i) {
            int u, v;
            std::cin >> u >> v;
            this->add_edges(u - base, v - base);
        }
    }

    void build(int r = 0) {
        int pos = 0;
        this->dfs_sz(r);
        this->nxt[r] = r;
        this->dfs_hld(r, pos);
    }

    int get(int v) const { return this->vid[v]; }
    int get_parent(int v) const { return this->par[v]; }

    int dist(int u, int v) const {
        int d = 0;
        while (true) {
            if (this->vid[u] > this->vid[v]) swap(u, v);
            if (this->nxt[u] == this->nxt[v]) return d + this->vid[v] - this->vid[u];
            d += this->vid[v] - this->vid[this->nxt[v]] + 1;
            v = this->par[this->nxt[v]];
        }
    }

    int jump(int u, int v, int k) const {
        int d = this->dist(u, v);
        if (d < k) return -1;
        int l = this->lca(u, v);
        if (this->dist(u, l) >= k) return this->la(u, k);
        else return this->la(v, d - k);
    }

    int la(int v, int k) const {
        while (true) {
            int u = this->nxt[v];
            if (this->vid[v] - k >= this->vid[u]) return this->inv[this->vid[v] - k];
            k -= this->vid[v] - this->vid[u] + 1;
            v = this->par[u];
        }
    }

    int lca(int u, int v) const {
        while (true) {
            if (this->vid[u] > this->vid[v]) swap(u, v);
            if (this->nxt[u] == this->nxt[v]) return u;
            v = this->par[this->nxt[v]];
        }
    }

    template <class F>
    void for_each(int u, int v, const F &f) const {
        while (true) {
            if (this->vid[u] > this->vid[v]) swap(u, v);
            f(max(this->vid[this->nxt[v]], this->vid[u]), this->vid[v] + 1);
            if (this->nxt[u] != this->nxt[v]) v = this->par[this->nxt[v]];
            else break;
        }
    }

    template <class F>
    void for_each_edge(int u, int v, const F &f) const {
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
    int _size;
    std::vector<std::vector<int>> g;
    std::vector<int> vid, nxt, sub, par, inv;

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
};
