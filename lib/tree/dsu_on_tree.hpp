#include <cassert>
#include <vector>
#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T>
struct dsu_on_tree {
    dsu_on_tree(const Graph<T> &_g, const std::vector<int> &query, int r = 0)
        : g(_g), size(_g.size()), root(r), par(size, -1), sub(), euler(size), left(size),
          right(size), heavy_path(size, -1), query_order(query.size()), query_size(size) {
        if (size == 0) return;
        for (int x : query) ++query_size[x];
        sub = query_size;
        dfs_sz(root);
        if (size > 1) {
            int pos = 0, len = 0;
            dfs_hld(root, pos, len);
        }
        std::vector<int> cnt = left;
        for (int i = 0; i < (int)query.size(); ++i) query_order[cnt[query[i]]++] = i;
    }
    dsu_on_tree(const Graph<T> &_g, int r = 0)
        : g(_g), size(_g.size()), root(r), par(size, -1), sub(size, 1), euler(size), left(size),
          right(size), heavy_path(size, -1), query_order(), query_size(size, 1) {
        if (size == 0) return;
        dfs_sz(root);
        if (size > 1) {
            int pos = 0, len = 0;
            dfs_hld(root, pos, len);
        }
        query_order = euler;
    }

    template <class F, class G, class H>
    void solve(F &rem, G &clear, H &query) {
        auto dsu = [&](auto self, int v) -> void {
            int hp = heavy_path[v];
            if (hp == -1) {
                for (int i = left[v]; i < right[v]; ++i) query(query_order[i]);
                rem(v);
                return;
            }
            for (auto &e : g[v]) {
                if (e.to() == par[v] || e.to() == heavy_path[v]) continue;
                self(self, e.to());
                clear();
            }
            self(self, hp);
            for (int i = left[v]; i < left[hp]; ++i) query(query_order[i]);
            for (int i = right[hp]; i < right[v]; ++i) query(query_order[i]);
            rem(v);
        };
        dsu(dsu, 0);
    }

  private:
    const Graph<T> &g;
    int size, root;
    std::vector<int> par, sub, euler, left, right, heavy_path, query_order, query_size;

    void dfs_sz(int v) {
        int max_sub = 0;
        for (auto &e : g[v]) {
            int u = e.to();
            if (u == par[v]) continue;
            par[u] = v;
            dfs_sz(u);
            sub[v] += sub[u];
            if (chmax(max_sub, sub[u])) heavy_path[v] = u;
        }
    }

    void dfs_hld(int v, int &pos, int &len) {
        euler[pos++] = v;
        left[v] = len;
        right[v] = len + sub[v];
        len += query_size[v];
        int hp = heavy_path[v];
        if (hp == -1) {
            right[v] = len;
            return;
        }
        dfs_hld(hp, pos, len);
        for (auto &e : g[v]) {
            int u = e.to();
            if (u == par[v] || u == hp) continue;
            dfs_hld(u, pos, len);
        }
    }
};
