#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include "segtree/segment_tree.hpp"

/// @brief Segment Tree on Tree
/// @complexity 構築は $O(n)$、点更新は $O(\log n)$、経路積は $O(\log^2 n)$
template <monoid M>
struct SegmentTreeOnTree {
  private:
    using T = typename M::value_type;
    int n, st_size;
    std::vector<std::vector<int>> g;
    std::vector<std::pair<int, int>> edges;
    std::vector<int> vid, nxt, head_par;
    std::vector<int> v_in, v_out, v_rev_in, v_rev_out;
    std::vector<int> up_left, up_rev_right;
    std::vector<int> edge_in, edge_rev_in;
    SegmentTree<M> st;
    SegmentTree<M> rev_st;

  public:
    /// @brief 空の構造を構築する
    /// @complexity $O(1)$
    SegmentTreeOnTree() : n(0), st_size(0) {}

    /// @brief n頂点の空の木を構築する
    /// @complexity $O(n)$
    explicit SegmentTreeOnTree(int _n) : n(_n), st_size(_n == 0 ? 0 : 2 * _n - 1), g(_n), vid(_n, -1), nxt(_n) {}

    /// @brief 無向辺u-vを追加する
    /// @complexity 償却 $O(1)$
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
        edges.emplace_back(u, v);
    }

    /// @brief 根rとしてHL分解とsegment treeを構築する
    /// @complexity $O(n)$
    void build(int r = 0) {
        if (n == 0) return;
        std::vector<int> heavy_path(n, -1), sub_size(n, 1), par(n, -1), dep(n, 0);
        std::vector<int> stk;
        stk.reserve(n);
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
        for (int i = n - 1; i >= 0; --i) {
            int v = vid[i];
            int max_sub = 0;
            for (int u : g[v]) {
                if (u == par[v]) continue;
                sub_size[v] += sub_size[u];
                if (max_sub < sub_size[u]) max_sub = sub_size[u], heavy_path[v] = u;
            }
        }
        nxt[r] = r;
        pos = 0;
        stk.emplace_back(r);
        while (!stk.empty()) {
            int v = stk.back();
            stk.pop_back();
            vid[v] = pos++;
            int hp = heavy_path[v];
            for (int u : g[v]) {
                if (u == par[v] || u == hp) continue;
                nxt[u] = u, stk.emplace_back(u);
            }
            if (hp != -1) nxt[hp] = nxt[v], stk.emplace_back(hp);
        }

        head_par.resize(n);
        v_in.resize(n);
        v_out.resize(n);
        v_rev_in.resize(n);
        v_rev_out.resize(n);
        up_left.resize(n);
        up_rev_right.resize(n);

        for (int i = 0; i < n; ++i) {
            v_in[i] = 2 * vid[i];
            v_out[i] = 2 * vid[i] + 1;
            v_rev_in[i] = st_size - v_out[i];
            v_rev_out[i] = st_size - v_in[i];
            up_left[i] = 2 * vid[nxt[i]] - 1;
            up_rev_right[i] = st_size - up_left[i];
            head_par[i] = par[nxt[i]];
        }

        edge_in.resize(edges.size());
        edge_rev_in.resize(edges.size());
        for (int i = 0; i < (int)edges.size(); ++i) {
            int u = edges[i].first;
            int v = edges[i].second;
            int w = (dep[u] > dep[v] ? u : v);
            edge_in[i] = 2 * vid[w] - 1;
            edge_rev_in[i] = st_size - 1 - edge_in[i];
        }

        st = SegmentTree<M>(st_size);
        rev_st = SegmentTree<M>(st_size);
    }

    /// @brief 頂点値と辺値を設定して構築する
    /// @complexity $O(n)$
    void build(const std::vector<T> &v_vals, const std::vector<T> &e_vals = {}, int r = 0) {
        build(r);
        if (n == 0) return;
        std::vector<T> a(st_size, M::id());
        for (int i = 0; i < n; ++i) {
            if (i < (int)v_vals.size()) a[v_in[i]] = v_vals[i];
        }
        for (int i = 0; i < (int)e_vals.size(); ++i) a[edge_in[i]] = e_vals[i];
        st = SegmentTree<M>(a);

        std::vector<T> rev_a(st_size);
        for (int i = 0; i < st_size; ++i) rev_a[st_size - 1 - i] = a[i];
        rev_st = SegmentTree<M>(rev_a);
    }

    /// @brief 頂点uの値を返す
    /// @complexity $O(1)$
    T get_vertex(int u) { return st.get(v_in[u]); }

    /// @brief 頂点uの値を変更する
    /// @complexity $O(\log n)$
    void set_vertex(int u, T val) {
        st.set(v_in[u], val);
        rev_st.set(v_rev_in[u], val);
    }

    /// @brief edge_idの辺値を変更する
    /// @complexity $O(\log n)$
    void set_edge(int edge_id, T val) {
        st.set(edge_in[edge_id], val);
        rev_st.set(edge_rev_in[edge_id], val);
    }

    /// @brief uからvへの経路積を順序付きで返す
    /// @param edge trueなら頂点値を除き辺値だけを集約する
    /// @complexity $O(\log^2 n)$
    T prod(int u, int v, bool edge = false) const {
        if (n == 0) return M::id();
        T l = M::id(), r = M::id();
        while (true) {
            if (vid[u] > vid[v]) {
                if (nxt[u] == nxt[v]) {
                    l = M::op(l, rev_st.prod(v_rev_in[u], v_rev_out[v] - edge));
                    break;
                }
                l = M::op(l, rev_st.prod(v_rev_in[u], up_rev_right[u]));
                u = head_par[u];
            } else {
                if (nxt[u] == nxt[v]) {
                    r = M::op(st.prod(v_in[u] + edge, v_out[v]), r);
                    break;
                }
                r = M::op(st.prod(up_left[v], v_out[v]), r);
                v = head_par[v];
            }
        }
        return M::op(l, r);
    }
};
