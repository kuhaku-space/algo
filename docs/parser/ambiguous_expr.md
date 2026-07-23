---
title: 曖昧式の全順序評価 (AmbiguousExpr)
documentation_of: //lib/parser/ambiguous_expr.hpp
compile_example: true
---

二項演算式を「あらゆる評価順序 (全 parenthesization)」で計算し、得られる値の集合を
区間 DP で求める。演算子の優先順位や結合性が定まっておらず、任意の順序で計算してよい
タイプの問題 (AOJ 2255「6/2(1+2)」など) に使う。`values(s).size()` で「あり得る結果の
通り数」が得られる。

入力中の括弧 `()` は固定のグループ化として扱い、その内側も再帰的に全順序を試す。
`op(c, f)` で二項演算子を登録し、`f` は無効な演算 (0 除算など) に対し `std::nullopt`
を返すとその評価経路を捨てる。

## 使い方

```cpp
#include "parser/ambiguous_expr.hpp"

using ll = long long;
AmbiguousExpr<ll> e;
e.op('+', [](ll a, ll b) { return std::optional<ll>(a + b); })
 .op('-', [](ll a, ll b) { return std::optional<ll>(a - b); })
 .op('*', [](ll a, ll b) { return std::optional<ll>(a * b); })
 .op('/', [](ll a, ll b) -> std::optional<ll> {
     if (b == 0) return std::nullopt;   // 0 除算の経路は捨てる
     return a / b;                      // C++ の / は 0 方向切り捨て
 });

e.values("1-1-1").size();   // 2 通り: (1-1)-1=-1, 1-(1-1)=1
```

## API

`AmbiguousExpr<T>` — `T` は値型。`combine_fn` = `std::optional<T>(const T&, const T&)`。

| メソッド | 内容 |
| --- | --- |
| `op(c, f)` | 二項演算子 `c` を登録 (fluent)。`f` が `std::nullopt` を返す経路は無効 |
| `values(s)` | 式 `s` を全評価順序で計算し、得られる値集合 `std::set<T>` を返す |

## 補足

- **区間 DP**: オペランド列 $x_0, x_1, \dots$ と間の演算子に対し、部分区間 $[i, j]$ から
  得られる値集合 `dp[i][j]` を、最後に計算する演算子の位置 $k$ で分割して求める。
  オペランド数を $k$、演算子数を $m = k - 1$ とすると部分区間は $O(k^2)$ 個。
- **計算量**: 各区間の結合は両側の値集合サイズの積に比例する。値の範囲や演算子数が
  小さい前提の問題向け (AOJ 2255 は演算子 10 個以下)。
- **括弧**: `()` は必ず先に評価されるグループとして扱い、内側の集合を求めてから外側の
  オペランドとして使う。括弧記号は固定 (`(` `)`)。
- **無効な演算**: `combine_fn` が `std::nullopt` を返した組み合わせは集合に加えない。
  0 除算のように「その順序では計算不能」を表現できる。
- **オペランド**: 非負整数リテラルを読む。負数や単項演算子は扱わない (必要なら演算子として
  表現する)。

## 検証

- [AOJ 2255 6/2(1+2)](https://onlinejudge.u-aizu.ac.jp/problems/2255) — 全評価順序での結果の通り数
