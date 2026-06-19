#pragma once
#include <vector>
#include "graph/graph.hpp"
#include "internal/internal_csr.hpp"

/// @brief HL分解
/// @see https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
struct heavy_light_decomposition {
    heavy_light_decomposition() = default;
    template <graph_type G>
    heavy_light_decomposition(const G &g, int r = 0) : heavy_light_decomposition(g.size()) {
        std::vector<int> heavy_path(_size, -1);
        std::vector<int> stk;
        stk.reserve(_size);
        stk.emplace_back(r);
        int pos = 0;
        while (!stk.empty()) {
            int v = stk.back();
            stk.pop_back();
            vid[pos++] = v;
            for (auto &e : g[v]) {
                int u = e.to();
                if (u == par[v]) continue;
                par[u] = v, dep[u] = dep[v] + 1, stk.emplace_back(u);
            }
        }
        for (int i = _size - 1; i >= 0; --i) {
            int v = vid[i];
            int max_sub = 0;
            for (auto &e : g[v]) {
                int u = e.to();
                if (u == par[v]) continue;
                sub[v] += sub[u];
                if (max_sub < sub[u]) max_sub = sub[u], heavy_path[v] = u;
            }
        }
        nxt[r] = r;
        pos = 0;
        stk.emplace_back(r);
        while (!stk.empty()) {
            int v = stk.back();
            stk.pop_back();
            vid[v] = pos++;
            inv[vid[v]] = v;
            int hp = heavy_path[v];
            for (auto &e : g[v]) {
                int u = e.to();
                if (u == par[v] || u == hp) continue;
                nxt[u] = u, stk.emplace_back(u);
            }
            if (hp != -1) nxt[hp] = nxt[v], stk.emplace_back(hp);
        }
    }

    heavy_light_decomposition(const internal::graph_csr &g, int r = 0) : heavy_light_decomposition(g.size()) {
        std::vector<int> heavy_path(_size, -1);
        std::vector<int> stk;
        stk.reserve(_size);
        stk.emplace_back(r);
        int pos = 0;
        while (!stk.empty()) {
            int v = stk.back();
            stk.pop_back();
            vid[pos++] = v;
            for (int u : g[v]) {
                if (u == par[v]) continue;
                par[u] = v, dep[u] = dep[v] + 1, stk.emplace_back(u);
            }
        }
        for (int i = _size - 1; i >= 0; --i) {
            int v = vid[i];
            int max_sub = 0;
            for (int u : g[v]) {
                if (u == par[v]) continue;
                sub[v] += sub[u];
                if (max_sub < sub[u]) max_sub = sub[u], heavy_path[v] = u;
            }
        }
        nxt[r] = r;
        pos = 0;
        stk.emplace_back(r);
        while (!stk.empty()) {
            int v = stk.back();
            stk.pop_back();
            vid[v] = pos++;
            inv[vid[v]] = v;
            int hp = heavy_path[v];
            for (int u : g[v]) {
                if (u == par[v] || u == hp) continue;
                nxt[u] = u, stk.emplace_back(u);
            }
            if (hp != -1) nxt[hp] = nxt[v], stk.emplace_back(hp);
        }
    }

    constexpr int size() const { return _size; }

    int get(int v) const { return vid[v]; }
    int get_parent(int v) const { return par[v]; }
    int get_depth(int v) const { return dep[v]; }

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

    /// 頂点 v を根とする部分木に対応する vid 区間 [l, r) を f(l, r) に渡す。
    template <class F>
    void for_subtree(int v, const F &f) const {
        f(vid[v], vid[v] + sub[v]);
    }

    /// 頂点 v を根とする部分木（v を含む）に対応する vid 区間 [l, r) を返す。
    std::pair<int, int> subtree(int v) const { return {vid[v], vid[v] + sub[v]}; }

    /// 頂点 v を根とする部分木から v を除いた辺集合に対応する vid 区間 [l, r) を f(l, r) に渡す。
    template <class F>
    void for_subtree_edge(int v, const F &f) const {
        if (sub[v] > 1) f(vid[v] + 1, vid[v] + sub[v]);
    }

  private:
    int _size;
    std::vector<int> vid, nxt, par, dep, inv, sub;

    heavy_light_decomposition(int n) : _size(n), vid(n, -1), nxt(n), par(n, -1), dep(n), inv(n), sub(n, 1) {}
};
