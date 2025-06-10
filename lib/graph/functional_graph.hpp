#pragma once
#include <cstdint>
#include <utility>
#include <vector>
#include "internal/internal_csr.hpp"
#include "tree/hld.hpp"

/// @brief functional graph
struct functional_graph {
    functional_graph() = default;
    functional_graph(const std::vector<int> &_to) : functional_graph(_to.size(), _to) {
        for (int i = 0; i < _size; ++i) {
            int x = i;
            while (_root[x] == -1) {
                _root[x] = i;
                x = to[x];
            }
            int r = (_root[x] == i ? x : _root[x]);
            x = i;
            while (r != i && _root[x] == i) {
                _root[x] = r;
                x = to[x];
            }
        }
        for (int i = 0; i < _size; ++i) {
            if (_root[i] == i) g.add_edge(_size, i);
            else g.add_edge(to[i], i);
        }
        g.build();
        hld = heavy_light_decomposition(g, _size);
    }

    constexpr int size() const { return _size; }

    int jump(int v, std::uint64_t step) const {
        int d = hld.get_depth(v);
        if (step <= (std::uint64_t)d - 1) return hld.jump(v, _size, step);
        v = _root[v];
        step -= d - 1;
        int bottom = to[v];
        int c = hld.get_depth(bottom);
        step %= c;
        if (step == 0) return v;
        return hld.jump(bottom, _size, step - 1);
    }

    std::vector<int> jump_all(std::uint64_t step) const {
        std::vector<int> res(_size, -1);
        std::vector<std::pair<int, int>> query;
        internal::graph_csr csr(_size);
        for (int v = 0; v < _size; ++v) {
            int d = hld.get_depth(v);
            int r = _root[v];
            if ((std::uint64_t)d - 1 > step) {
                csr.add_edge(v, query.size());
                query.emplace_back(v, step);
            } else {
                std::int64_t k = step - (d - 1);
                int bottom = to[r];
                int c = hld.get_depth(bottom);
                k %= c;
                if (k == 0) {
                    res[v] = r;
                    continue;
                }
                csr.add_edge(bottom, query.size());
                query.emplace_back(v, k - 1);
            }
        }
        csr.build();

        std::vector<int> path;
        auto dfs = [&](auto self, int v) -> void {
            path.emplace_back(v);
            for (int id : csr[v]) res[query[id].first] = path[path.size() - 1 - query[id].second];
            for (int u : g[v]) self(self, u);
            path.pop_back();
        };
        for (int u : g[_size]) dfs(dfs, u);
        return res;
    }

    int dist(int u, int v) {
        if (_root[u] != _root[v]) return -1;
        if (u == v) return 0;
        int du = hld.get_depth(u);
        int dv = hld.get_depth(v);
        if (du > dv) return du - dv;
        int c = hld.get_depth(to[_root[u]]);
        return dv > c ? -1 : c - dv + du;
    }

    int cycle_length(int v) const {
        v = _root[v];
        return hld.get_depth(to[v]);
    }

    std::vector<std::vector<int>> get_cycles() const {
        std::vector<std::vector<int>> res;
        for (int v = 0; v < _size; ++v) {
            if (v == _root[v]) res.emplace_back(get_cycle(v));
        }
        return res;
    }

    int root(int v) const { return _root[v]; }
    int depth(int v) const { return hld.get_depth(v); }
    int in_cycle(int v) const { return hld.get_depth(v) <= cycle_length(v); }
    int lca(int u, int v) const { return hld.lca(u, v); }

  private:
    int _size;
    const std::vector<int> &to;
    std::vector<int> _root;
    internal::graph_csr g;
    heavy_light_decomposition hld;

    functional_graph(int n, const std::vector<int> &_to) : _size(n), to(_to), _root(n, -1), g(n + 1), hld() {}

    std::vector<int> get_cycle(int v) const {
        std::vector<int> res(1, v);
        int u = to[v];
        while (u != v) res.emplace_back(u), u = to[u];
        return res;
    }
};
