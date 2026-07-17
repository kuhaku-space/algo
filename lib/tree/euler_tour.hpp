#pragma once
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief オイラーツアー
struct euler_tour {
    template <graph_type G>
    euler_tour(const G &g, int r = 0) : euler_tour(g, g.size(), r) {}

    std::pair<int, int> operator[](int i) const { return std::make_pair(ls[i], rs[i]); }

    int size() const { return _size; }

    int left(int i) const { return ls[i]; }
    int right(int i) const { return rs[i]; }
    int order(int i) const { return ord[i]; }

    template <class F>
    void query(int v, const F &f) const {
        f(ls[v], rs[v]);
    }

  private:
    int _size;
    std::vector<int> ord, ls, rs;

    template <class G>
    euler_tour(const G &g, int n, int r) : _size(n), ord(n), ls(n, -1), rs(n) {
        int c = 0;
        std::vector<int> stk;
        stk.reserve(2 * n);
        stk.emplace_back(r);
        while (!stk.empty()) {
            auto x = stk.back();
            stk.pop_back();
            if (x < 0) {
                rs[~x] = c;
                continue;
            }
            ls[x] = c;
            ord[x] = c++;
            rs[x] = c;
            for (auto &e : g[x]) {
                int to = e.to();
                if (ls[to] != -1) continue;
                stk.emplace_back(~x);
                stk.emplace_back(to);
            }
        }
    }
};
