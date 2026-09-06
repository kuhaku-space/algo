#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

/// @file
/// @brief グラフ上の文脈自由到達可能性 (CykGraph)
/// @details 辺ラベル付き有向グラフに CNF（チョムスキー標準形）の文脈自由文法を適用し、各記号 `X` について
///          「頂点 `u` から `v` へ、通った辺ラベル列が `X` から導出される歩道が存在する」頂点対 `(u, v)` の
///          集合を求める。CYK 法のグラフ版で、辺ラベル列が文法に合う経路の存在判定に使う。
/// @details 辺は繰り返し使え、向きは固定。記号は `0 .. num_sym-1` の整数 id で表す（非終端・終端クラスを
///          区別しない）。文法は「`A -> B C`（二項）」と「`A -> 終端`」に正規化して与える。
/// @note 各記号の到達対をビット行列で持ち、規則 $A \to BC$ について
///       $\mathrm{reach}[A] \mathrel{|}= \mathrm{reach}[B] \circ \mathrm{reach}[C]$ を、
///       どの記号にもビットが増えなくなるまで繰り返す。
/// @note 1 反復あたり $O(\text{規則数} \cdot n^3 / 64)$。反復回数は追加されるビット数で上から抑えられる。
/// @note 元の文法の単位規則や長さ 3 以上の規則は、補助非終端を導入して `A -> B C` / `A -> 終端` の形へ
///       変換してから登録する。
/// @note 終端も記号 id を割り当て、対応するラベルの辺を `add` で登録する。同じラベルが複数辺にあってもよい。
/// @note `num_sym` 個の $n \times \lceil n/64 \rceil$ ワードのビット行列を確保する。
/// @code
/// #include <iostream>
/// #include "parser/cfg_graph.hpp"
///
/// // 対応の取れた括弧列 S -> ( ) | ( S ) | S S を CNF 化して適用する。
/// // 記号 id: S(開始), T(補助 = S の後に ')'), 終端 L='(', R=')'
/// enum { S, T, L, R, NUM_SYM };
///
/// int main() {
///     CykGraph g(2, NUM_SYM);
///     g.add(L, 0, 1);       // 頂点 0 -> 1、ラベル '('
///     g.add(R, 1, 0);       // 頂点 1 -> 0、ラベル ')'
///     g.add_rule(S, L, R);  // S -> ( )
///     g.add_rule(S, L, T);  // S -> ( T
///     g.add_rule(T, S, R);  // T -> S )   あわせて S -> ( S )
///     g.add_rule(S, S, S);  // S -> S S
///     g.solve();
///     std::cout << g.get(S, 0, 0) << '\n';  // 0 から 0 へ S を導出できるか
/// }
/// @endcode

/// @brief 辺ラベル付き有向グラフ上の文脈自由到達可能性 (CYK のグラフ版)
/// @details CNF（`A->BC` または `A->終端`）の文法を、各辺が 1 記号を表す
///   有向グラフに適用する。各記号 $X$ について「頂点 $u$ から $v$ へ、
///   通った辺ラベル列が $X$ から導出される歩道が存在する」頂点対 $(u, v)$
///   の集合を不動点反復で求める。辺は繰り返し使え、向きは固定。
///   記号は $[0, num\_sym)$ の整数 id で表す（非終端・終端クラスを区別しない）。
///   ビット行列（$n$ 行 $\times$ $n$ 列）の合成で $A \mathrel{|}= B \circ C$ を計算するため、
///   1 反復あたり $O(R n^3 / 64)$（$R$ は規則数）。
/// @complexity 1 反復 $O(R n^3 / 64)$、最悪 $O(S R n^5 / 64)$（記号数 $S$、規則数 $R$）
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

    /// @brief 記号 `sym` の到達対に $(u, v)$ を追加する（終端辺の登録に使う）
    /// @complexity $O(1)$
    void add(int sym, int u, int v) { reach[sym][static_cast<std::size_t>(u) * words + (v >> 6)] |= 1ULL << (v & 63); }
    /// @brief $(u, v)$ が記号 `sym` から導出可能か
    /// @complexity $O(1)$
    bool get(int sym, int u, int v) const {
        return reach[sym][static_cast<std::size_t>(u) * words + (v >> 6)] >> (v & 63) & 1;
    }
    /// @brief 二項規則 `A->BC` を追加する
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
