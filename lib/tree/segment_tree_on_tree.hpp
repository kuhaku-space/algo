#pragma once
#include <stack>
#include <vector>
#include <algorithm>
#include <utility>
#include "segtree/segment_tree.hpp"

/**
 * @brief Segment Tree on Tree
 */
template <class M>
struct segment_tree_on_tree {
  private:
    using T = typename M::value_type;
    int _n, _st_size;
    std::vector<std::vector<int>> g;
    std::vector<std::pair<int, int>> edges;
    std::vector<int> vid, nxt, head_par;
    std::vector<int> v_in, v_out, v_rev_in, v_rev_out;
    std::vector<int> up_L, up_rev_R;
    std::vector<int> edge_in, edge_rev_in;
    segment_tree<M> st;
    segment_tree<M> rev_st;

  public:
    segment_tree_on_tree() : _n(0), _st_size(0) {}

    explicit segment_tree_on_tree(int n)
        : _n(n), _st_size(n == 0 ? 0 : 2 * n - 1), g(n), vid(n, -1), nxt(n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
        edges.emplace_back(u, v);
    }

    void build(int r = 0) {
        if (_n == 0) return;
        std::vector<int> heavy_path(_n, -1), sub_size(_n, 1), par(_n, -1), dep(_n, 0);
        std::stack<int> s;
        s.emplace(r);
        int pos = 0;
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            vid[pos++] = v;
            for (int u : g[v]) {
                if (u == par[v]) continue;
                par[u] = v, dep[u] = dep[v] + 1, s.emplace(u);
            }
        }
        for (int i = _n - 1; i >= 0; --i) {
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
        s.emplace(r);
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            vid[v] = pos++;
            int hp = heavy_path[v];
            for (int u : g[v]) {
                if (u == par[v] || u == hp) continue;
                nxt[u] = u, s.emplace(u);
            }
            if (hp != -1) nxt[hp] = nxt[v], s.emplace(hp);
        }

        head_par.resize(_n);
        v_in.resize(_n);
        v_out.resize(_n);
        v_rev_in.resize(_n);
        v_rev_out.resize(_n);
        up_L.resize(_n);
        up_rev_R.resize(_n);

        for (int i = 0; i < _n; ++i) {
            v_in[i] = 2 * vid[i];
            v_out[i] = 2 * vid[i] + 1;
            v_rev_in[i] = _st_size - v_out[i];
            v_rev_out[i] = _st_size - v_in[i];
            up_L[i] = 2 * vid[nxt[i]] - 1;
            up_rev_R[i] = _st_size - up_L[i];
            head_par[i] = par[nxt[i]];
        }

        edge_in.resize(edges.size());
        edge_rev_in.resize(edges.size());
        for (int i = 0; i < (int)edges.size(); ++i) {
            int u = edges[i].first;
            int v = edges[i].second;
            int w = (dep[u] > dep[v] ? u : v);
            edge_in[i] = 2 * vid[w] - 1;
            edge_rev_in[i] = _st_size - 1 - edge_in[i];
        }

        st = segment_tree<M>(_st_size);
        rev_st = segment_tree<M>(_st_size);
    }

    void build(const std::vector<T> &v_vals, const std::vector<T> &e_vals = {}, int r = 0) {
        build(r);
        if (_n == 0) return;
        std::vector<T> a(_st_size, M::id());
        for (int i = 0; i < _n; ++i) {
            if (i < (int)v_vals.size()) a[v_in[i]] = v_vals[i];
        }
        for (int i = 0; i < (int)e_vals.size(); ++i) {
            a[edge_in[i]] = e_vals[i];
        }
        st = segment_tree<M>(a);

        std::vector<T> rev_a(_st_size);
        for (int i = 0; i < _st_size; ++i) rev_a[_st_size - 1 - i] = a[i];
        rev_st = segment_tree<M>(rev_a);
    }

    void set_vertex(int u, T val) {
        st.set(v_in[u], val);
        rev_st.set(v_rev_in[u], val);
    }

    void set_edge(int edge_id, T val) {
        st.set(edge_in[edge_id], val);
        rev_st.set(edge_rev_in[edge_id], val);
    }

    T prod(int u, int v, bool edge = false) const {
        if (_n == 0) return M::id();
        T l = M::id(), r = M::id();
        while (true) {
            if (vid[u] > vid[v]) {
                if (nxt[u] == nxt[v]) {
                    l = M::op(l, rev_st.prod(v_rev_in[u], v_rev_out[v] - edge));
                    break;
                }
                l = M::op(l, rev_st.prod(v_rev_in[u], up_rev_R[u]));
                u = head_par[u];
            } else {
                if (nxt[u] == nxt[v]) {
                    r = M::op(st.prod(v_in[u] + edge, v_out[v]), r);
                    break;
                }
                r = M::op(st.prod(up_L[v], v_out[v]), r);
                v = head_par[v];
            }
        }
        return M::op(l, r);
    }
};
