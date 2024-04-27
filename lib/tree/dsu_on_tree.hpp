#include <cassert>
#include <vector>
#include "graph/graph.hpp"
#include "template/template.hpp"

struct dsu_on_tree {
    template <class T>
    dsu_on_tree(const Graph<T> &g, int r = 0)
        : size(g.size()), root(r), par(size, -1), sub(size, 1), euler(size), left(size),
          right(size) {
        if (size == 0) return;
        std::vector<int> heavy_path(size, -1);
        dfs_sz(g, root, heavy_path);
        euler[0] = root;
        if (size > 1) {
            int pos = 1;
            dfs_hld(g, root, pos, heavy_path);
        }
    }

    template <class F, class G, class H, class I>
    void solve(F &rem, G &clear, H &query_vertex, I &query_edge) {
        auto dsu = [&](auto self, int v) -> void {
            if (left[v] == right[v]) {
                query_vertex(v);
                rem(v);
                return;
            }
            for (int i = left[v] + 1; i < size && par[euler[i]] == v; ++i) {
                self(self, euler[i]);
                clear();
            }
            self(self, euler[left[v]]);
            for (int i = left[v] + 1; i < left[euler[left[v]]]; ++i) {
                query_vertex(euler[i]);
                query_edge(par[euler[i]], euler[i]);
            }
            for (int i = right[euler[left[v]]]; i < right[v]; ++i) {
                query_vertex(euler[i]);
                query_edge(par[euler[i]], euler[i]);
            }
            query_vertex(v);
            rem(v);
        };
        dsu(dsu, 0);
    }

  private:
    int size, root;
    std::vector<int> par, sub, euler, left, right;

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
    void dfs_hld(const Graph<T> &g, int v, int &pos, std::vector<int> &heavy_path) {
        left[v] = pos;
        int hp = heavy_path[v];
        if (hp != -1) euler[pos++] = hp;
        for (auto &e : g[v]) {
            int u = e.to();
            if (u == par[v] || u == hp) continue;
            euler[pos++] = u;
        }
        if (hp != -1) dfs_hld(g, hp, pos, heavy_path);
        for (auto &e : g[v]) {
            int u = e.to();
            if (u == par[v] || u == hp) continue;
            dfs_hld(g, u, pos, heavy_path);
        }
        right[v] = pos;
    }
};
