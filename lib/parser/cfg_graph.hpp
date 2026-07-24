#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

/// @brief 辺ラベル付き有向グラフ上の文脈自由到達可能性 (CYK のグラフ版)
/// @details CNF (@c A->BC または @c A->終端) の文法を、各辺が 1 記号を表す
///   有向グラフに適用する。各記号 @c X について「頂点 @c u から @c v へ、
///   通った辺ラベル列が @c X から導出される歩道が存在する」頂点対 @c (u,v)
///   の集合を不動点反復で求める。辺は繰り返し使え、向きは固定。
///   記号は 0..num_sym-1 の整数 id で表す (非終端・終端クラスを区別しない)。
///   ビット行列 (@c n 行 × @c n 列) の合成で @c A |= B∘C を計算するため、
///   1 反復あたり @c O(規則数 · n^3 / 64)。
/// @complexity 1反復 $O(Rn^3/64)$、最悪 $O(SRn^5/64)$（記号数$S$、規則数$R$）
struct CykGraph {
    /// @brief 頂点数・記号数・1 行あたりの 64 bit ワード数
    /// @complexity $O(1)$ で参照可能
    int n, num_sym, words;
    /// @brief 登録済みの二項規則 `{A, B, C}`
    /// @complexity 1 規則の参照は $O(1)$
    std::vector<std::array<int, 3>> rules;  // {A, B, C}: A -> B C
    /// @brief 各記号の到達可能性を表すビット行列
    /// @complexity 1 ワードの参照は $O(1)$
    std::vector<std::vector<uint64_t>> reach;  // reach[sym]: n 行 × words ワード

    /// @brief n頂点・num_sym記号の空の到達関係を構築する
    /// @complexity $O(Sn^2/64)$
    CykGraph(int n, int num_sym)
        : n(n), num_sym(num_sym), words((n + 63) / 64),
          reach(num_sym, std::vector<uint64_t>(static_cast<std::size_t>(n) * words, 0)) {}

    /// @brief 記号 @c sym の到達対に @c (u,v) を追加する (終端辺の登録に使う)
    /// @complexity $O(1)$
    void add(int sym, int u, int v) { reach[sym][static_cast<std::size_t>(u) * words + (v >> 6)] |= 1ULL << (v & 63); }
    /// @brief @c (u,v) が記号 @c sym から導出可能か
    /// @complexity $O(1)$
    bool get(int sym, int u, int v) const {
        return reach[sym][static_cast<std::size_t>(u) * words + (v >> 6)] >> (v & 63) & 1;
    }
    /// @brief 二項規則 @c A->BC を追加する
    /// @complexity 償却 $O(1)$
    void add_rule(int A, int B, int C) { rules.push_back({A, B, C}); }

    /// @brief 不動点まで反復して全到達対を確定する
    /// @complexity 1反復 $O(Rn^3/64)$、最悪 $O(SRn^5/64)$
    void solve() {
        for (bool updated = true; updated;) {
            updated = false;
            for (const auto &[A, B, C] : rules) {
                for (int u = 0; u < n; ++u) {
                    const uint64_t *brow = &reach[B][static_cast<std::size_t>(u) * words];
                    uint64_t *arow = &reach[A][static_cast<std::size_t>(u) * words];
                    for (int w = 0; w < words; ++w) {
                        for (uint64_t bits = brow[w]; bits; bits &= bits - 1) {
                            int v = w * 64 + __builtin_ctzll(bits);
                            const uint64_t *crow = &reach[C][static_cast<std::size_t>(v) * words];
                            for (int x = 0; x < words; ++x) {
                                uint64_t nv = arow[x] | crow[x];
                                if (nv != arow[x]) arow[x] = nv, updated = true;
                            }
                        }
                    }
                }
            }
        }
    }
};
