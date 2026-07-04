---
title: グラフ上の文脈自由到達可能性 (CykGraph)
documentation_of: //lib/parser/cfg_graph.hpp
---

辺ラベル付き有向グラフに CNF (チョムスキー標準形) の文脈自由文法を適用し、各記号 `X`
について「頂点 `u` から `v` へ、通った辺ラベル列が `X` から導出される歩道が存在する」
頂点対 `(u, v)` の集合を求める。CYK 法のグラフ版で、辺ラベル列が文法に合う経路の存在
判定 (AOJ 2704「Stamp Rally」など) に使う。

辺は繰り返し使え、向きは固定。記号は `0 .. num_sym-1` の整数 id で表す (非終端・終端
クラスを区別しない)。文法は「`A -> B C` (二項)」と「`A -> 終端`」に正規化して与える。

## 使い方

対応の取れた括弧列の文法を CNF 化して、辺ラベルが `(` `)` のグラフに適用する例。
`S -> ( ) | ( S ) | S S` を、補助記号 `T` (`-> S )`) を使い次のように書ける:

```cpp
#include "parser/cfg_graph.hpp"

// 記号 id: S(開始), T(補助 = S の後に ')'), 終端 L='(' , R=')'
enum { S, T, L, R, NUM_SYM };

CykGraph g(n, NUM_SYM);
for (/* 各辺 u -> v (ラベル c) */) {
    if (c == '(') g.add(L, u, v);
    if (c == ')') g.add(R, u, v);
}
g.add_rule(S, L, R);   // S -> ( )     空の一組
g.add_rule(S, L, T);   // S -> ( T
g.add_rule(T, S, R);   // T -> S )     … あわせて S -> ( S )
g.add_rule(S, S, S);   // S -> S S     連接
g.solve();
bool ok = g.get(S, s, t);   // s から t へ S を導出できるか
```

実問題 (四則演算の文法) での完全な CNF 化とグラフへの適用は
`test/aoj/challenge/2704.test.cpp` を参照。

## API

`CykGraph(n, num_sym)` — 頂点数 `n`、記号数 `num_sym`。

| メンバ | 内容 |
| --- | --- |
| `add(sym, u, v)` | 記号 `sym` の到達対に `(u, v)` を追加 (終端辺の登録) |
| `add_rule(A, B, C)` | 二項規則 `A -> B C` を追加 |
| `solve()` | 不動点まで反復し全到達対を確定する |
| `get(sym, u, v)` | `(u, v)` が `sym` から導出可能かを返す |

## 補足

- **アルゴリズム**: 各記号の到達対をビット行列 ($n$ 行 $\times$ $n$ 列) で持ち、規則
  $A \to BC$ について $\mathrm{reach}[A] \mathrel{|}= \mathrm{reach}[B] \circ \mathrm{reach}[C]$
  (関係の合成) を、どの記号にもビットが増えなくなるまで繰り返す。
- **計算量**: 1 反復あたり $O(\text{規則数} \cdot n^3 / 64)$。反復回数は追加されるビット数で
  上から抑えられる (最悪 $O(\text{記号数} \cdot n^2)$ 回だが、実際の文法・グラフでは速く収束する)。
- **CNF 化**: 元の文法の単位規則 ($E \to T$ など) や長さ 3 以上の規則は、補助非終端を
  導入して `A -> B C` / `A -> 終端` の形へ変換してから登録する。
- **終端クラス**: 終端も記号 id を割り当て、対応するラベルの辺を `add` で登録する。
  同じラベルが複数辺にあってもよい。
- **メモリ**: `num_sym` 個の $n \times \lceil n/64 \rceil$ ワードのビット行列を確保する。

## 検証

- [AOJ 2704 Stamp Rally](https://onlinejudge.u-aizu.ac.jp/problems/2704) — 辺ラベル列が数式になる歩道の存在判定
