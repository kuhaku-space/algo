---
title: 汎用式パーサ (ExpressionParser)
documentation_of: //lib/parser/parser.hpp
compile_example: true
---

演算子優先順位法 (precedence climbing) による汎用の式パーサ。二項演算子・前置単項
演算子・アトム (最小単位) の読み取りを差し替えることで、任意の式文法を構築できる。

値型 `T` は各コールバックが返す「意味」を表す。`T` を数値型にすれば評価器、AST の
ノードポインタにすれば構文木ビルダーになる。`T` が算術演算を持てば標準の四則演算
パーサ `arithmetic_parser<T>()` がそのまま使えるので、`long long` はもちろん
`modint`・複素数・行列・多項式などでも動く。

## 使い方

```cpp
#include "parser/parser.hpp"

// 標準の四則演算 (+ - * / ・単項 ± ・括弧・非負整数)
long long v = eval_expr<long long>("1 + 2 * (3 - 4)");   // -1

// 自前の文法を組み立てる: 右結合のべき乗 ^ と剰余 % を足す
using P = ExpressionParser<long long>;
auto p = arithmetic_parser<long long>();
p.binary("%", 20, P::Assoc::Left, [](auto& a, auto& b) { return a % b; })
 .binary("^", 30, P::Assoc::Right, [](auto& a, auto& b) {
     long long result = 1;
     for (long long i = 0; i < b; ++i) result *= a;
     return result;
 });
p.parse("2 ^ 3 ^ 2");   // 512 (右結合)
```

`T` を差し替えると評価対象を変えられる。たとえば `ExpressionParser<Complex>` に
`+ - *` と虚数単位 `i` のアトムを登録すれば複素数式の評価器になる。

## API

`ExpressionParser<T>` — `T` は演算子・アトムが返す値型。

### 文法の登録 (fluent)

| メソッド | 内容 |
| --- | --- |
| `binary(op, prec, assoc, f)` | 二項演算子を登録。`prec` が大きいほど優先、`assoc` は `Assoc::Left` / `Assoc::Right` |
| `binary(op, prec, assoc, f, guard)` | ガード付き二項演算子。`guard(after)` が `false` の位置は演算子とみなさない |
| `prefix(op, f)` | 前置単項演算子を登録 (二項より強く結合) |
| `concat(prec, assoc, f, guard)` | 暗黙の連接 (記号なしで項が並ぶ) を登録。`guard` は必須 |
| `atom(f)` | 数値・変数・関数呼び出し等の最小単位を読むコールバックを設定 |
| `group(open, close)` | グループ化括弧を設定 (既定は `(` `)`) |
| `no_group()` | 組み込みの括弧処理を無効化 (`(` を atom 側で扱いたいとき) |

- `op` は多文字トークン可 (現在位置での最長一致で選ばれる)。
- 前置演算子はアトムに最も強く結合する (`-x*y` は `(-x)*y`、`-x` は `x` に束縛)。
- `binary_fn` = `T(const T&, const T&)`、`unary_fn` = `T(const T&)`、
  `guard_fn` = `bool(std::string_view)` (トークン直後の残り入力を受け取る)。

### 解析

| メソッド | 内容 |
| --- | --- |
| `parse(str)` | 式全体を解析して `T` を返す。末尾に余分な文字が残れば例外 |
| `parse_expression(min_prec = 0)` | 優先順位 `min_prec` 以上の部分式を解析 (アトムから再帰的に呼ぶ) |

### アトムから使う低レベル API

| メソッド | 内容 |
| --- | --- |
| `peek()` | 空白を飛ばした現在の文字 (末尾なら `'\0'`) |
| `rest()` | 残りの入力 (`std::string_view`) |
| `consume(tok)` | `tok` が現在位置に一致すれば消費して `true` |
| `advance(n = 1)` | 現在位置を `n` 文字進める |
| `read_uint()` | 非負整数を `long long` として読む (`T` に依らない。AST 構築等に) |
| `read_identifier()` | 英字からなる識別子を読む (先頭が英字でなければ空) |
| `integer_atom(p)` | 非負整数を読む既定アトム (静的関数。`T` が整数から構築可能なとき) |

### プリセット

| 関数 | 内容 |
| --- | --- |
| `arithmetic_parser<T>()` | `+ - * /`・単項 `±`・括弧・非負整数の標準四則演算パーサを構築 |
| `eval_expr<T>(s)` | 四則演算の式文字列を評価する (上記プリセットの薄いラッパ) |

## 補足

- **優先順位と結合性**: 左結合は右辺を `prec + 1` 以上、右結合は `prec` 以上で解析する
  precedence climbing。前置演算子はアトムに最も強く結合し、優先順位表には載らない。
- **ガードの用途**: 閉じ記号と演算子が文字レベルで衝突する文脈依存文法に使う。
  例として AOJ 2570 (Shipura) では `>>` (シフト) と `>` (`S<...>` の閉じ) が衝突するため、
  「`>>` の直後に項が続くときだけシフト」というガードを与える。
- **暗黙の連接 (`concat`)**: 空トークンの二項演算子として扱う。演算子記号を持たない
  文字列連接・関数適用などに使う。停止条件を表す `guard` が無いと無限ループになるため必須。
- **AST の構築**: `T` をノードポインタにし、各 `binary` / `prefix` のコールバックで
  ノードを生成すれば構文木が得られる。アトムでは `read_uint()` 等で `T` に依らず整数を読める。
- **括弧の自前処理**: `no_group()` で組み込みの括弧処理を切ると、`(` を atom 側で扱える。
  分子式 `(X)2` のように「閉じ括弧の直後に処理を続けたい」ケースで有用。
- **既定アトム未設定時**: `atom()` を設定せず括弧でもない位置に来ると例外を投げる。
  `arithmetic_parser` は `integer_atom` を既定で設定する。

## 検証

- [AOJ 0109 スマート計算機](https://onlinejudge.u-aizu.ac.jp/problems/0109) — 四則演算
- [AOJ 0264 有限体電卓](https://onlinejudge.u-aizu.ac.jp/problems/0264) — GF(p) 上の四則演算・0 除算検出
- [AOJ 1102 Calculation of Expressions](https://onlinejudge.u-aizu.ac.jp/problems/1102) — 複素数を値型に
- [AOJ 1244 Molecular Formula](https://onlinejudge.u-aizu.ac.jp/problems/1244) — 暗黙の連接・後置乗数・`no_group`
- [AOJ 2570 Shipura](https://onlinejudge.u-aizu.ac.jp/problems/2570) — 二項演算子ガード
- [AOJ 2584 Broken Cipher Generator](https://onlinejudge.u-aizu.ac.jp/problems/2584) — 文字列を値型に・暗黙の連接
- [AOJ 2613 Unordered Operators](https://onlinejudge.u-aizu.ac.jp/problems/2613) — 優先順位の全列挙
