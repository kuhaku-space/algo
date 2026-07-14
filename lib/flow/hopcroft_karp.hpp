#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>

/// @brief Hopcroft-Karp algorithm（O(E√V)）
/// @details 2 段構成。第 1 段は経路長制限のない木 BFS の貪欲増強フェーズで、
///          構造的なケース（閉路・パス等）を少フェーズで処理する。O(√V) 回で打ち切り、
///          残りは第 2 段の Hopcroft-Karp 本体（BFS でレベルグラフを作り、
///          current-arc 付き DFS で頂点素な最短増強路の極大集合を一括増強、
///          フェーズ数 O(√V) 保証）が仕上げる。全体で O(E√V)。
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
        // 第 1 段: 未マッチ左頂点を根とする交互道の森を BFS で同時に伸ばし、
        // 自由右頂点を見つけ次第 prev 鎖に沿って即増強する（増強した木は根チェックで無効化）。
        // 経路長を制限しないぶん 1 フェーズで拾える増強路が多いが、
        // フェーズ数の保証がないため O(√V) 回で打ち切って第 2 段に引き継ぐ。
        {
            std::vector<int> root(n), prev(n), qq(n);
            int cap = (int)std::sqrt((double)std::min(n, m)) + 2;
            for (int phase = 0; phase < cap; ++phase) {
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
                flow += augmented;
                // 増強路が見つからなければ最大マッチング
                if (augmented == 0) return flow;
            }
        }
        // 第 2 段: Hopcroft-Karp 本体
        std::vector<int> dist(n), it(n), q(n), path;
        // limit: 最短増強路の左頂点レベル（増強路長は 2*limit+1）
        int limit = -1;
        // 未マッチ左頂点からの交互道 BFS でレベルを付け、自由右頂点に届く最小レベルを求める
        auto bfs = [&]() -> bool {
            std::fill(dist.begin(), dist.end(), -1);
            int qj = 0;
            for (int i = 0; i < n; i++) {
                if (match_left[i] == -1) dist[i] = 0, q[qj++] = i;
            }
            limit = -1;
            for (int qi = 0; qi < qj; qi++) {
                int u = q[qi];
                // キューのレベルは非減少なので、自由右頂点が見つかったレベル以降は打ち切れる
                if (limit != -1 && dist[u] >= limit) break;
                for (int idx = start[u]; idx < start[u + 1]; idx++) {
                    int w = match_right[elist[idx]];
                    if (w == -1) {
                        limit = dist[u];
                        break;
                    }
                    if (dist[w] == -1) dist[w] = dist[u] + 1, q[qj++] = w;
                }
            }
            return limit != -1;
        };
        // レベルグラフ上の反復 DFS で s からの最短増強路を 1 本探し、あれば増強する。
        // it は current-arc（フェーズ内で各辺を高々 1 回しか走査しない）、
        // 行き止まり・増強路上の頂点は dist = -1 で無効化して頂点素性を保つ。
        auto try_augment = [&](int s) -> bool {
            path.clear();
            path.emplace_back(s);
            while (!path.empty()) {
                int u = path.back();
                bool advanced = false;
                while (it[u] < start[u + 1]) {
                    int v = elist[it[u]++];
                    int w = match_right[v];
                    if (w == -1) {
                        if (dist[u] < limit) continue;
                        // path 上の各左頂点を「消費した辺」（elist[it[x] - 1]）と結び直す
                        for (int k = (int)path.size() - 1; k >= 0; --k) {
                            int x = path[k], y = elist[it[x] - 1];
                            match_left[x] = y, match_right[y] = x;
                            dist[x] = -1;
                        }
                        return true;
                    }
                    if (dist[u] < limit && dist[w] == dist[u] + 1) {
                        path.emplace_back(w);
                        advanced = true;
                        break;
                    }
                }
                if (!advanced) {
                    dist[u] = -1;
                    path.pop_back();
                }
            }
            return false;
        };
        while (bfs()) {
            std::copy(start.begin(), start.begin() + n, it.begin());
            for (int i = 0; i < n; i++) {
                if (match_left[i] == -1 && try_augment(i)) flow++;
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
