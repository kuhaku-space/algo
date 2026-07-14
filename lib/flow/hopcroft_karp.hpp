#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

/// @brief Hopcroft-Karp algorithm
/// @see https://judge.yosupo.jp/submission/99577
struct HopcroftKarp {
    HopcroftKarp(int _n, int _m) : n(_n), m(_m), built(false), match_left(_n, -1), match_right(_m, -1) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < m);
        buf.emplace_back(u, v);
        built = false;
    }

    /// @brief 最大マッチングのサイズ
    /// @note 冪等。既にマッチ済みの分も含めた総数を返すので、何度呼んでも同じ値になる。
    int matching() {
        if (!built) build_csr();
        int flow = n - (int)std::count(match_left.begin(), match_left.end(), -1);
        std::vector<int> root(n), prev(n), qq(n);
        for (bool updated = true; updated;) {
            updated = false;
            int qi = 0, qj = 0;
            std::fill(root.begin(), root.end(), -1);
            std::fill(prev.begin(), prev.end(), -1);
            for (int i = 0; i < n; i++) {
                if (match_left[i] == -1) qq[qj++] = i, root[i] = i, prev[i] = i;
            }
            while (qi < qj) {
                int u = qq[qi++];
                if (match_left[root[u]] != -1) continue;
                for (int idx = start[u]; idx < start[u + 1]; idx++) {
                    int v = elist[idx];
                    if (match_right[v] == -1) {
                        while (v != -1) match_right[v] = u, std::swap(match_left[u], v), u = prev[u];
                        updated = true, flow++;
                        break;
                    }

                    if (prev[match_right[v]] == -1) v = match_right[v], prev[v] = u, root[v] = root[u], qq[qj++] = v;
                }
            }
        }
        return flow;
    }

    std::vector<std::pair<int, int>> get_pairs() const {
        std::vector<std::pair<int, int>> res;
        for (int i = 0; i < n; i++) {
            if (~match_left[i]) res.emplace_back(i, match_left[i]);
        }
        return res;
    }

    /// @brief 最小頂点被覆（König の定理）
    /// @return (左側頂点集合, 右側頂点集合)
    std::pair<std::vector<int>, std::vector<int>> minimum_vertex_cover() {
        matching();
        auto [l_reach, r_reach] = alternating_reachable();
        std::vector<int> left, right;
        for (int i = 0; i < n; i++) {
            if (!l_reach[i]) left.emplace_back(i);
        }
        for (int j = 0; j < m; j++) {
            if (r_reach[j]) right.emplace_back(j);
        }
        return {left, right};
    }

    /// @brief 最大独立集合（最小頂点被覆の補集合）
    /// @return (左側頂点集合, 右側頂点集合)
    std::pair<std::vector<int>, std::vector<int>> maximum_independent_set() {
        matching();
        auto [l_reach, r_reach] = alternating_reachable();
        std::vector<int> left, right;
        for (int i = 0; i < n; i++) {
            if (l_reach[i]) left.emplace_back(i);
        }
        for (int j = 0; j < m; j++) {
            if (!r_reach[j]) right.emplace_back(j);
        }
        return {left, right};
    }

  private:
    const int n, m;
    bool built;
    std::vector<std::pair<int, int>> buf;  // add_edge で蓄積した辺（CSR 構築前）
    std::vector<int> start, elist;         // 左頂点ごとの隣接右頂点を詰めた CSR
    std::vector<int> match_left, match_right;

    // 蓄積した辺を CSR に詰める（matching() 先頭で必要時のみ実行）
    void build_csr() {
        start.assign(n + 1, 0);
        elist.resize(buf.size());
        for (auto [u, v] : buf) ++start[u + 1];
        for (int i = 0; i < n; i++) start[i + 1] += start[i];
        auto counter = start;
        for (auto [u, v] : buf) elist[counter[u]++] = v;
        built = true;
    }

    // 未マッチの左側頂点から交互道（左→右は非マッチング辺、右→左はマッチング辺）で到達可能な頂点
    std::pair<std::vector<bool>, std::vector<bool>> alternating_reachable() const {
        std::vector<bool> l_reach(n, false), r_reach(m, false);
        std::vector<int> st;
        for (int i = 0; i < n; i++) {
            if (match_left[i] == -1) l_reach[i] = true, st.emplace_back(i);
        }
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            for (int idx = start[u]; idx < start[u + 1]; idx++) {
                int v = elist[idx];
                if (v == match_left[u] || r_reach[v]) continue;
                r_reach[v] = true;
                int w = match_right[v];
                if (w != -1 && !l_reach[w]) l_reach[w] = true, st.emplace_back(w);
            }
        }
        return {l_reach, r_reach};
    }
};
