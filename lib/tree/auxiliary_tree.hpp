#pragma once
#include <algorithm>
#include <stack>
#include <vector>
#include "graph/graph.hpp"
#include "tree/euler_tour.hpp"
#include "tree/linear_lca.hpp"

struct auxiliary_tree : public Graph<void> {
    auxiliary_tree(const std::vector<int> &_ord, const std::vector<int> &_par,
                   const std::vector<bool> &_f)
        : Graph::Graph(_par.size()), ord(_ord), f(_f) {
        int n = _par.size();
        for (int i = 0; i < n; ++i) {
            if (_par[i] != -1) add_edges(_par[i], i);
        }
    }

    int vertex(int x) const { return ord[x]; }
    bool contains(int x) const { return f[x]; }

  private:
    std::vector<int> ord;
    std::vector<bool> f;
};

struct auxiliary_tree_builder {
    template <class T>
    auxiliary_tree_builder(const Graph<T> &g, int r = 0) : lca(g, r), et(g, r) {}

    auxiliary_tree build(std::vector<int> v) {
        std::sort(v.begin(), v.end(), [&](int x, int y) { return et.order(x) < et.order(y); });
        v.erase(std::unique(v.begin(), v.end()), v.end());
        std::vector<int> ord = v;
        int k = ord.size();
        for (int i = 0; i < k - 1; ++i) ord.emplace_back(lca(ord[i], ord[i + 1]));
        std::sort(ord.begin(), ord.end(), [&](int x, int y) { return et.order(x) < et.order(y); });
        ord.erase(std::unique(ord.begin(), ord.end()), ord.end());

        int m = ord.size();
        std::vector<int> par(m);
        std::stack<int> st;
        for (int i = 0; i < m; ++i) {
            while (!st.empty() && et.right(ord[st.top()]) <= et.left(ord[i])) st.pop();
            par[i] = (st.empty() ? -1 : st.top());
            st.emplace(i);
        }
        std::vector<bool> f(m);
        int x = 0;
        for (int i = 0; i < m; ++i) {
            if (x < k && ord[i] == v[x]) {
                f[i] = true;
                ++x;
            }
        }
        return auxiliary_tree{ord, par, f};
    }

  private:
    linear_lca lca;
    euler_tour et;
};
