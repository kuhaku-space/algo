#pragma once
#include <algorithm>
#include <limits>
#include <stack>
#include <utility>
#include <vector>
#include "data_structure/linear_sparse_table.hpp"
#include "graph/graph.hpp"
#include "internal/internal_csr.hpp"

struct linear_lca {
  private:
    struct S {
        int depth, index;

        constexpr bool operator<(const S &rhs) const { return depth < rhs.depth; }
        constexpr bool operator==(const S &rhs) const = default;
    };

    struct M {
        using value_type = S;
        static constexpr S id() { return S{std::numeric_limits<int>::max(), -1}; }
        static constexpr S op(const S &lhs, const S &rhs) { return std::min(lhs, rhs); }
    };

  public:
    template <class T>
    linear_lca(const Graph<T> &g, int r = 0) : ord(g.size(), -1), lst() {
        std::vector<S> v;
        std::stack<std::pair<int, int>> st;
        st.emplace(r, 0);
        while (!st.empty()) {
            auto [x, d] = st.top();
            st.pop();
            if (x < 0) {
                v.emplace_back(d, ~x);
                continue;
            }
            ord[x] = v.size();
            v.emplace_back(d, x);
            for (auto e : g[x]) {
                if (ord[e.to()] != -1) continue;
                st.emplace(~x, d);
                st.emplace(e.to(), d + 1);
            }
        }
        lst = linear_sparse_table<M>(v);
    }
    linear_lca(const internal::graph_csr &g, int r = 0) : ord(g.size(), -1), lst() {
        std::vector<S> v;
        std::stack<std::pair<int, int>> st;
        st.emplace(r, 0);
        while (!st.empty()) {
            auto [x, d] = st.top();
            st.pop();
            if (x < 0) {
                v.emplace_back(d, ~x);
                continue;
            }
            ord[x] = v.size();
            v.emplace_back(d, x);
            for (int y : g[x]) {
                if (ord[y] != -1) continue;
                st.emplace(~x, d);
                st.emplace(y, d + 1);
            }
        }
        lst = linear_sparse_table<M>(v);
    }

    int operator()(int u, int v) const { return lca(u, v); }

    int lca(int u, int v) const {
        auto [l, r] = std::minmax(ord[u], ord[v]);
        return lst.prod(l, r + 1).index;
    }

  private:
    std::vector<int> ord;
    linear_sparse_table<M> lst;
};
