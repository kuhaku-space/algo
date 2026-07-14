#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

/// @brief 二部グラフの最大マッチング（push-relabel 方式、O(E√V)）
/// @details 未マッチの右頂点が「レベル最小の左隣接頂点」を奪い、押し出された右頂点が
///          再びキューに戻る。左頂点のレベル（自由左頂点までの交互道長の下界）は
///          奪われるたびに +2 され（relabel）、V 回のポップごとに BFS で全体を
///          張り直す（global relabel）。レベルが V 以上に達した頂点は増強不能。
///          Goldberg–Kennedy の解析により O(E√V)。実測でも増強路ベースの
///          Hopcroft-Karp より速い。
/// @see https://judge.yosupo.jp/submission/339108
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
        // 第 0 段: 木 BFS の貪欲増強フェーズを定数回だけ回す（計算量保証に影響しない）。
        // 増強路が短いうちに大半を安価にマッチさせ、ここで最大に達したら
        // 逆 CSR の構築も push-relabel も丸ごと省略できる。
        {
            std::vector<int> root(n), prev(n), qq(n);
            for (int phase = 0; phase < 3; ++phase) {
                int augmented = 0;
                std::fill(root.begin(), root.end(), -1);
                std::fill(prev.begin(), prev.end(), -1);
                int qi = 0, qj = 0;
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
                            ++augmented;
                            break;
                        }
                        if (prev[match_right[v]] == -1)
                            v = match_right[v], prev[v] = u, root[v] = root[u], qq[qj++] = v;
                    }
                }
                // 増強路が見つからなければ最大マッチング
                if (augmented == 0) return n - (int)std::count(match_left.begin(), match_left.end(), -1);
            }
        }
        // 第 1 段: push-relabel 本体（ここで初めて右→左の CSR が必要になる）
        if (!rbuilt) build_rcsr();
        const int total = n + m;
        std::vector<int> lvl_l(n), lvl_r(m), bq(n), q(m);
        // q は未マッチ右頂点のリングバッファ（各右頂点は同時に高々 1 回しか入らない）
        int qh = 0, qt = 0, qsz = 0;
        auto push_q = [&](int v) {
            q[qt] = v;
            if (++qt == m) qt = 0;
            ++qsz;
        };
        for (int j = 0; j < m; j++) {
            if (match_right[j] == -1) push_q(j);
        }
        // global relabel: 未マッチ左頂点を 0 として交互道 BFS でレベルを張り直す。
        // 未マッチ右頂点に到達できなければ増強路は存在しない（= 最大）ので false を返す。
        auto global_relabel = [&]() -> bool {
            std::fill(lvl_l.begin(), lvl_l.end(), total);
            std::fill(lvl_r.begin(), lvl_r.end(), total);
            int bj = 0;
            for (int i = 0; i < n; i++) {
                if (match_left[i] == -1) lvl_l[i] = 0, bq[bj++] = i;
            }
            bool augmentable = false;
            for (int bi = 0; bi < bj; bi++) {
                int u = bq[bi];
                for (int idx = start[u]; idx < start[u + 1]; idx++) {
                    int v = elist[idx];
                    if (lvl_r[v] > lvl_l[u] + 1) {
                        lvl_r[v] = lvl_l[u] + 1;
                        int w = match_right[v];
                        if (w != -1) lvl_l[w] = lvl_r[v] + 1, bq[bj++] = w;
                        else augmentable = true;
                    }
                }
            }
            return augmentable;
        };
        int till = 0;
        while (true) {
            if (till == 0) {
                if (!global_relabel()) break;
                till = total;
            }
            if (qsz == 0) break;
            int v = q[qh];
            if (++qh == m) qh = 0;
            --qsz, --till;
            int s = -1, t = total;
            for (int idx = rstart[v]; idx < rstart[v + 1]; idx++) {
                int u = relist[idx];
                if (lvl_l[u] < t) {
                    t = lvl_l[u], s = u;
                    // レベル 0（自由左頂点）より小さいレベルはないので打ち切ってよい
                    if (t == 0) break;
                }
            }
            // レベル total 以上しか残っていなければ v は増強不能（破棄）
            if (t == total) continue;
            int old = match_left[s];
            if (old != -1) match_right[old] = -1, push_q(old);
            match_left[s] = v, match_right[v] = s;
            lvl_l[s] += 2;
        }
        return n - (int)std::count(match_left.begin(), match_left.end(), -1);
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
    bool built, rbuilt = false;
    std::vector<std::pair<int, int>> buf;  // add_edge で蓄積した辺（CSR 構築前）
    std::vector<int> start, elist;         // 左→右の CSR（貪欲フェーズ・BFS 用）
    std::vector<int> rstart, relist;       // 右→左の CSR（奪取ステップ用、遅延構築）
    std::vector<int> match_left, match_right;

    // 蓄積した辺を左→右の CSR に詰める（matching() 先頭で必要時のみ実行）
    void build_csr() {
        start.assign(n + 1, 0);
        elist.resize(buf.size());
        for (auto [u, v] : buf) ++start[u + 1];
        for (int i = 0; i < n; i++) start[i + 1] += start[i];
        auto counter = start;
        for (auto [u, v] : buf) elist[counter[u]++] = v;
        built = true;
        rbuilt = false;
    }

    // 右→左の CSR（push-relabel 段に入るときだけ必要）
    void build_rcsr() {
        rstart.assign(m + 1, 0);
        relist.resize(buf.size());
        for (auto [u, v] : buf) ++rstart[v + 1];
        for (int j = 0; j < m; j++) rstart[j + 1] += rstart[j];
        auto rcounter = rstart;
        for (auto [u, v] : buf) relist[rcounter[v]++] = u;
        rbuilt = true;
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
