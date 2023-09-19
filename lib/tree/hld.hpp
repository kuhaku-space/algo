#pragma once
#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief HL分解
 * @see https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
 */
struct HLD {
    HLD() = default;
    HLD(int n) : _size(n), g(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

    template <class T>
    HLD(const Graph<T> &g, int r = 0) : HLD(g.size()) {
        for (auto &es : g) {
            for (auto &e : es) {
                g[e.from()].emplace_back(e.to());
            }
        }
        build(r);
    }

    void add_edge(int u, int v) { add_edges(u, v); }
    void add_edges(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    void input_edge(int base = 1) { input_edges(base); }
    void input_edges(int base = 1) {
        for (int i = 0; i < _size - 1; ++i) {
            int u, v;
            std::cin >> u >> v;
            add_edges(u - base, v - base);
        }
    }

    void build(int r = 0) {
        int pos = 0;
        dfs_sz(r);
        nxt[r] = r;
        dfs_hld(r, pos);
    }

    int get(int v) const { return vid[v]; }
    int get_parent(int v) const { return par[v]; }

    int dist(int u, int v) const {
        int d = 0;
        while (true) {
            if (vid[u] > vid[v]) std::swap(u, v);
            if (nxt[u] == nxt[v]) return d + vid[v] - vid[u];
            d += vid[v] - vid[nxt[v]] + 1;
            v = par[nxt[v]];
        }
    }

    int jump(int u, int v, int k) const {
        int d = dist(u, v);
        if (d < k) return -1;
        int l = lca(u, v);
        if (dist(u, l) >= k) return la(u, k);
        else return la(v, d - k);
    }

    int la(int v, int k) const {
        while (true) {
            int u = nxt[v];
            if (vid[v] - k >= vid[u]) return inv[vid[v] - k];
            k -= vid[v] - vid[u] + 1;
            v = par[u];
        }
    }

    int lca(int u, int v) const {
        while (true) {
            if (vid[u] > vid[v]) std::swap(u, v);
            if (nxt[u] == nxt[v]) return u;
            v = par[nxt[v]];
        }
    }

    template <class F>
    void for_each(int u, int v, const F &f) const {
        while (true) {
            if (vid[u] > vid[v]) std::swap(u, v);
            f(std::max(vid[nxt[v]], vid[u]), vid[v] + 1);
            if (nxt[u] != nxt[v]) v = par[nxt[v]];
            else break;
        }
    }

    template <class F>
    void for_each_edge(int u, int v, const F &f) const {
        while (true) {
            if (vid[u] > vid[v]) std::swap(u, v);
            if (nxt[u] != nxt[v]) {
                f(vid[nxt[v]], vid[v] + 1);
                v = par[nxt[v]];
            } else {
                if (u != v) f(vid[u] + 1, vid[v] + 1);
                break;
            }
        }
    }

  private:
    int _size;
    std::vector<std::vector<int>> g;
    std::vector<int> vid, nxt, sub, par, inv;

    void dfs_sz(int v) {
        auto &es = g[v];
        if (~(par[v])) es.erase(find(es.begin(), es.end(), par[v]));

        for (auto &u : es) {
            par[u] = v;
            dfs_sz(u);
            sub[v] += sub[u];
            if (sub[u] > sub[es[0]]) std::swap(u, es[0]);
        }
    }

    void dfs_hld(int v, int &pos) {
        vid[v] = pos++;
        inv[vid[v]] = v;
        for (auto u : g[v]) {
            if (u == par[v]) continue;
            nxt[u] = (u == g[v][0] ? nxt[v] : u);
            dfs_hld(u, pos);
        }
    }
};
