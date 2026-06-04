#pragma once
#include <algorithm>
#include <stack>
#include <vector>
#include "graph/graph.hpp"
#include "tree/euler_tour.hpp"
#include "tree/linear_lca.hpp"

/// @brief auxiliary tree（補助木 / virtual tree）
/// @details コンストラクタで LCA・Euler tour を前計算し、build(vs) で指定頂点集合に対する
///          圧縮木を何度でも構築できる。Σ|vs| が小さければ各 build は O(|vs| log N)。
struct auxiliary_tree {
    /// @brief build が返す圧縮木。元の木の頂点番号・親・指定頂点フラグを保持する。
    struct tree : public Graph<void> {
        tree(const std::vector<int> &_ord, const std::vector<int> &_par, const std::vector<bool> &_f)
            : Graph::Graph(_par.size()), ord(_ord), par(_par), f(_f) {
            int n = _par.size();
            for (int i = 0; i < n; ++i) {
                if (par[i] != -1) add_edges(par[i], i);
            }
        }

        /// @brief 補助木ノード x に対応する元の木の頂点番号
        int get_vertex(int x) const { return ord[x]; }
        /// @brief 補助木ノード x の親ノード番号。根は -1。
        int get_parent(int x) const { return par[x]; }
        /// @brief 補助木ノード x が指定頂点（LCA で補われた頂点でない）か
        bool is_specified(int x) const { return f[x]; }

      private:
        std::vector<int> ord, par;
        std::vector<bool> f;
    };

    template <class T>
    auxiliary_tree(const Graph<T> &g, int r = 0) : lca(g, r), et(g, r) {}

    /// @brief 指定頂点集合 v に対する圧縮木を構築する。
    tree build(std::vector<int> v) {
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
        return tree{ord, par, f};
    }

  private:
    linear_lca lca;
    euler_tour et;
};
