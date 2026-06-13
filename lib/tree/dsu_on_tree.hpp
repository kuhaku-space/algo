#pragma once
#include <cassert>
#include <utility>
#include <vector>
#include "graph/graph.hpp"
#include "template/template.hpp"

/// @brief DSU on Tree
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
        if (size == 0) return;
        // 反復版（再帰だと深い木でスタックオーバーフローしうる）。
        // 各フレームは light 子を走査する idx と heavy 再帰済みフラグ heavy_done を持つ。
        // light 子から戻った直後に clear()、heavy 子から戻った後に query/rem を行い、
        // 元の再帰と同じ呼び出し順序を再現する。
        struct frame {
            int v, idx;
            bool heavy_done, pending_clear;
        };
        std::vector<frame> st;
        st.reserve(size);
        st.push_back({root, 0, false, false});
        while (!st.empty()) {
            frame &f = st.back();
            int v = f.v, hp = heavy_path[v];
            if (hp == -1) {
                for (int i = left[v]; i < right[v]; ++i) query(query_order[i]);
                rem(v);
                st.pop_back();
                continue;
            }
            // 直前に light 子から戻っていれば、その都度 clear する
            if (f.pending_clear) {
                clear();
                f.pending_clear = false;
            }
            // light 子を順に処理（戻ってきたら上の pending_clear で clear）
            bool descended = false;
            while (f.idx < (int)g[v].size()) {
                int u = g[v][f.idx++].to();
                if (u == par[v] || u == hp) continue;
                f.pending_clear = true;
                st.push_back({u, 0, false, false});
                descended = true;
                break;
            }
            if (descended) continue;  // light 子の dsu へ降りる
            if (!f.heavy_done) {
                f.heavy_done = true;
                st.push_back({hp, 0, false, false});
                continue;
            }
            // heavy 子の処理完了後: 残り区間を query して rem
            for (int i = left[v]; i < left[hp]; ++i) query(query_order[i]);
            for (int i = right[hp]; i < right[v]; ++i) query(query_order[i]);
            rem(v);
            st.pop_back();
        }
    }

  private:
    const Graph<T> &g;
    int size, root;
    std::vector<int> par, sub, euler, left, right, heavy_path, query_order, query_size;

    // 反復 DFS（再帰だと深い木でスタックオーバーフローしうる）。
    // 帰りがけに部分木サイズを集計し、最大の子を heavy_path に記録する。
    void dfs_sz(int v) {
        std::vector<std::pair<int, int>> st;  // (頂点, 隣接走査位置)
        st.reserve(size);
        std::vector<int> max_sub(size, 0);
        st.emplace_back(v, 0);
        while (!st.empty()) {
            auto &[u, idx] = st.back();
            if (idx < (int)g[u].size()) {
                int w = g[u][idx++].to();
                if (w == par[u]) continue;
                par[w] = u;
                st.emplace_back(w, 0);
            } else {
                int p = par[u];
                st.pop_back();
                if (p != -1) {
                    sub[p] += sub[u];
                    if (chmax(max_sub[p], sub[u])) heavy_path[p] = u;
                }
            }
        }
    }

    // 反復 DFS（行きがけ順を保つ）。各頂点で heavy 子を先に、続いて light 子を
    // 左から処理する。pos / len の更新は行きがけ時に行う。
    void dfs_hld(int v, int &pos, int &len) {
        struct frame {
            int v, idx;
            bool entered;
        };
        std::vector<frame> st;
        st.reserve(size);
        st.push_back({v, 0, false});
        while (!st.empty()) {
            frame &f = st.back();
            int u = f.v;
            if (!f.entered) {
                f.entered = true;
                euler[pos++] = u;
                left[u] = len;
                right[u] = len + sub[u];
                len += query_size[u];
                if (heavy_path[u] == -1) {
                    right[u] = len;
                    st.pop_back();
                    continue;
                }
                // heavy 子を最初に処理する
                st.push_back({heavy_path[u], 0, false});
                continue;
            }
            // heavy 子の処理が終わった後、light 子を左から順に処理する
            int hp = heavy_path[u];
            bool descended = false;
            while (f.idx < (int)g[u].size()) {
                int w = g[u][f.idx++].to();
                if (w == par[u] || w == hp) continue;
                st.push_back({w, 0, false});
                descended = true;
                break;
            }
            if (!descended) st.pop_back();
        }
    }
};
