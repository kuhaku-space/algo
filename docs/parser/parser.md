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

| API | 内容 | 計算量 |
| --- | --- | --- |
| `enum class Assoc` | 結合性 | 列挙型で実行時計算量はない |
| `using binary_fn = std::function<T(const T &, const T &)>;` | 二項演算callback型 | 型エイリアスで実行時計算量はない |
| `using unary_fn = std::function<T(const T &)>;` | 単項演算callback型 | 型エイリアスで実行時計算量はない |
| `using atom_fn = std::function<T(ExpressionParser &)>;` | アトム読取りcallback型 | 型エイリアスで実行時計算量はない |
| `using guard_fn = std::function<bool(std::string_view)>;` | 二項演算子ガード: トークン直後の残り入力を見て演算子として<br>適用してよいか判定する。閉じ記号と演算子が文字レベルで衝突する 文脈依存文法 (例: AOJ 2570 の @c ">>" と @c ">") に使う。 | 型エイリアスで実行時計算量はない |
| `ExpressionParser &binary(std::string op, int prec, Assoc assoc, binary_fn f)` | 二項演算子を登録する (fluent) | トークン長を $L$ として償却 $O(L)$ |
| `ExpressionParser &binary(std::string op, int prec, Assoc assoc, binary_fn f, guard_fn guard)` | ガード付き二項演算子を登録する (fluent)<br>`guard`(after) が `false` のときは、その位置の一致を演算子と みなさない (トークンは消費されず、閉じ記号等として残る)。<br>`@c` after はトークン直後の残り入力。 | トークン長を $L$ として償却 $O(L)$ |
| `ExpressionParser &concat(int prec, Assoc assoc, binary_fn f, guard_fn guard)` | 暗黙の連接 (演算子記号なしで項が並ぶ) を登録する (fluent)<br>空トークンの二項演算子として扱う。項が続くかどうかを表す<br>`@c` guard は必須 (無いと停止できず無限ループになる)。`guard`(rest) が `true` のときだけ次の項を連接する。文字列連接・関数適用など。 | 償却 $O(1)$ |
| `ExpressionParser &prefix(std::string op, unary_fn f)` | 前置単項演算子を登録する (fluent) | トークン長を $L$ として償却 $O(L)$ |
| `ExpressionParser &atom(atom_fn f)` | アトム読み取りコールバックを設定する (fluent) | $O(1)$ |
| `ExpressionParser &group(char open, char close)` | グループ化括弧を設定する (fluent) | $O(1)$ |
| `ExpressionParser &no_group()` | 組み込みのグループ化括弧を無効化する (fluent)<br>括弧を atom 側で自前処理したいとき (例: 分子式 @c "(X)2" の ように閉じ括弧の直後に処理を続けたいとき) に使う。 | $O(1)$ |
| `T parse(std::string_view str)` | 式全体を解析する (末尾に余分な文字が残ればエラー) | 入力長を $n$、登録演算子数を $A$ として $O(nA)$ |
| `T parse_expression(int min_prec = 0)` | 優先順位 `min_prec` 以上の部分式を解析する | 読み取る長さを $n$、登録演算子数を $A$ として $O(nA)$ |
| `char peek()` | 空白を読み飛ばした現在の文字 (末尾なら @c '\0') | 読み飛ばす空白数を $k$ として $O(k)$ |
| `char cur() const` | 空白を読み飛ばさない現在位置の文字 (末尾なら @c '\0')<br>番兵 (`std`::string 末尾の @c '\0') により末尾でも安全に<br>`@c` '\0' を返す。アトム側で `rest`().size() の範囲チェックをせず<br>`@c` cur() と `advance`() で1文字ずつ走査できる。 | $O(1)$ |
| `std::string_view rest() const` | 残りの入力 | $O(1)$ |
| `bool consume(std::string_view tok)` | トークン `tok` が現在位置に一致すれば消費して `true` | 読み飛ばす空白とトークン長を合わせて $O(k)$ |
| `void advance(std::size_t n = 1)` | 現在位置を `n` 文字進める | $O(1)$ |
| `long long read_uint()` | 非負整数を `long` `long` として読む (`T` に依らない。AST 構築等で有用) | 読み取る文字数を $k$ として $O(k)$ |
| `std::string_view read_identifier()` | 英字からなる識別子を読む (先頭が英字でなければ空文字列) | 読み取る文字数を $k$ として $O(k)$ |
| `static T integer_atom(ExpressionParser &p)` | 非負整数を読む既定アトム (`T` が整数から構築可能なとき利用可能) | 読み取る文字数を $k$ として $O(k)$ |
| `template <class T = long long> ExpressionParser<T> arithmetic_parser()` | 標準的な四則演算パーサを構築する<br>@c + @c - @c * @c / ・単項 @c ± ・括弧・非負整数リテラルに対応。 値型 `T` は算術演算を持てば何でもよい (`long` `long` ・`modint` 等)。 | $O(1)$ |
| `template <class T = long long> T eval_expr(std::string_view s)` | 四則演算の式文字列を評価する | 入力長を $n$ として $O(n)$ |

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
