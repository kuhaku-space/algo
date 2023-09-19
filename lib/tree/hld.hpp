#pragma once
#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief HL分解
 * @see https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
 */
struct heavy_light_decomposition {
    heavy_light_decomposition() = default;
    template <class T>
    heavy_light_decomposition(const Graph<T> &g, int r = 0) : heavy_light_decomposition(g.size()) {
        build(g, r);
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
    std::vector<int> vid, nxt, sub, par, inv;

    heavy_light_decomposition(int n)
        : _size(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n) {}

    template <class T>
    void build(const Graph<T> &g, int r = 0) {
        std::vector<int> heavy_path(_size, -1);
        dfs_sz(g, r, heavy_path);
        nxt[r] = r;
        int pos = 0;
        dfs_hld(g, r, pos, heavy_path);
    }

    template <class T>
    void dfs_sz(const Graph<T> &g, int v, std::vector<int> &heavy_path) {
        int max_sub = 0;
        for (auto &e : g[v]) {
            int u = e.to();
            if (u == par[v]) continue;
            par[u] = v;
            dfs_sz(g, u, heavy_path);
            sub[v] += sub[u];
            if (chmax(max_sub, sub[u])) heavy_path[v] = u;
        }
    }

    template <class T>
    void dfs_hld(const Graph<T> &g, int v, int &pos, const std::vector<int> &heavy_path) {
        vid[v] = pos++;
        inv[vid[v]] = v;
        int hp = heavy_path[v];
        if (hp != -1) {
            nxt[hp] = nxt[v];
            dfs_hld(g, hp, pos, heavy_path);
        }
        for (auto &e : g[v]) {
            int u = e.to();
            if (u == par[v] || u == heavy_path[v]) continue;
            nxt[u] = u;
            dfs_hld(g, u, pos, heavy_path);
        }
    }
};
