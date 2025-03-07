#pragma once
#include <stack>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief オイラーツアー
struct euler_tour {
    template <class T>
    euler_tour(const Graph<T> &g, int r = 0) : euler_tour(g, g.size(), r) {}

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

    template <class T>
    euler_tour(const Graph<T> &g, int n, int r) : _size(n), ord(n, -1), ls(n), rs(n) {
        int c = 0;
        std::stack<int> st;
        st.emplace(r);
        while (!st.empty()) {
            auto x = st.top();
            st.pop();
            if (x < 0) {
                rs[~x] = c;
                continue;
            }
            ls[x] = c;
            ord[c++] = x;
            rs[x] = c;
            for (auto e : g[x]) {
                if (ord[e.to()] != -1) continue;
                st.emplace(~x);
                st.emplace(e.to());
            }
        }
    }
};
