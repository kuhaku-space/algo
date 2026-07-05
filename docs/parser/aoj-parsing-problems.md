---
title: AOJ 構文解析問題の実装状況と必要ライブラリ
---

[構文解析まとめ (rsk0315)](https://rsk0315.github.io/StringParsing/matome.html) に挙げられている
AOJ の構文解析問題について、このリポジトリでの verify 状況と、未実装問題を解くために
必要なライブラリを整理する。方針は「既存ライブラリ (特に
[`lib/parser/`](https://kuhaku-space.github.io/algo/)) で解けるものは verify を追加し、
足りない機能は洗い出す」こと。

## 凡例

- **必要ライブラリ** 列はヘッダのパス。既存のものは `lib/…`、未整備のものは *(要追加)* と記す。
- 「構文解析ライブラリの対象外」は、演算子優先順位法 (`ExpressionParser`) や CYK
  (`CykGraph`) の枠組みに乗らず、問題ごとの再帰下降で書き下すのが素直なもの。

## 実装済み

いずれも `lib/parser/parser.hpp` の `ExpressionParser<T>` を中心に verify 済み。値型 `T` を
差し替えて多様な意味づけを与えている (下表右列)。

| 問題 | 値型 / 技法 |
| --- | --- |
| [0109](https://onlinejudge.u-aizu.ac.jp/problems/0109) Smart Calculator | `long long` 四則演算 |
| [0264](https://onlinejudge.u-aizu.ac.jp/problems/0264) Finite Field Calculator | `modint`・0 除算検出 |
| [1012](https://onlinejudge.u-aizu.ac.jp/problems/1012) Operations with Finite Sets | `std::set<int>`・前置補集合 |
| [1078](https://onlinejudge.u-aizu.ac.jp/problems/1078) SAT-EN-3 | DNF (割り当て集合)・`&` 直積 / `|` 連結 |
| [1087](https://onlinejudge.u-aizu.ac.jp/problems/1087) Dimensional Analysis | 次元ベクトル + エラー伝播 |
| [1102](https://onlinejudge.u-aizu.ac.jp/problems/1102) Calculation of Expressions | 複素数 |
| [1155](https://onlinejudge.u-aizu.ac.jp/problems/1155) How can I satisfy thee | 三値論理 |
| [1233](https://onlinejudge.u-aizu.ac.jp/problems/1233) Equals are Equals | `F_{2^61-1}` の K 点同時評価 (多変数多項式の等価判定) |
| [1244](https://onlinejudge.u-aizu.ac.jp/problems/1244) Molecular Formula | 元素数マップ・連接・後置乗数・`no_group` |
| [1293](https://onlinejudge.u-aizu.ac.jp/problems/1293) Common Polynomial | 有理数係数多項式・GCM |
| [1300](https://onlinejudge.u-aizu.ac.jp/problems/1300) Chemist's Math | 元素数ベクトル + 零空間 (係数決定) |
| [1346](https://onlinejudge.u-aizu.ac.jp/problems/1346) Miscalculation | 優先順位違いの 2 パーサ |
| [1620](https://onlinejudge.u-aizu.ac.jp/problems/1620) 論理式圧縮機 | 16bit 真理値表 + 最短式 DP |
| [2255](https://onlinejudge.u-aizu.ac.jp/problems/2255) 6/2(1+2) | `ambiguous_expr.hpp` (評価順序の全列挙) |
| [2401](https://onlinejudge.u-aizu.ac.jp/problems/2401) Equation | `bitset<2^11>` 真理値ベクトル (恒等式判定) |
| [2570](https://onlinejudge.u-aizu.ac.jp/problems/2570) Shipura | 二項演算子ガード (`>>` と `>`) |
| [2584](https://onlinejudge.u-aizu.ac.jp/problems/2584) Broken Cipher Generator | 文字列を値型に・連接 |
| [2596](https://onlinejudge.u-aizu.ac.jp/problems/2596) Points and Lines | 点/直線の直和・型で演算分岐 |
| [2613](https://onlinejudge.u-aizu.ac.jp/problems/2613) Unordered Operators | 優先順位の全列挙 |
| [2857](https://onlinejudge.u-aizu.ac.jp/problems/2857) Tournament Chart | トーナメント木 (`group '[' ']'`) + 実現可能性 DP |
| [3002](https://onlinejudge.u-aizu.ac.jp/problems/3002) Factorization | 多項式・整数根探索 |

## 未実装: 既存ライブラリで解ける (verify 追加のみ)

新しいライブラリは不要。テストを書けば済むもの。

| 問題 | 必要ライブラリ | 備考 |
| --- | --- | --- |
| [0350](https://onlinejudge.u-aizu.ac.jp/problems/0350) 実数既約分数化 | `lib/math/fraction.hpp` | 循環小数 → 既約分数 |
| [2435](https://onlinejudge.u-aizu.ac.jp/problems/2435) Zero division checker | (なし) | 逆ポーランド記法はスタック評価で十分。`ExpressionParser` 不要 |
| [2845](https://onlinejudge.u-aizu.ac.jp/problems/2845) Star in Parentheses | (なし) | `*` を囲む括弧の対の数 = 深さ。スタックで十分 |
| [2369](https://onlinejudge.u-aizu.ac.jp/problems/2369) CatChecker | `lib/parser/parser.hpp` | 「鳴き声」文法の認識。`ExpressionParser`(値型 `bool`) か手書き再帰下降 |
| [2428](https://onlinejudge.u-aizu.ac.jp/problems/2428) 失われし数 | `lib/parser/parser.hpp` + 全探索 | 隠れた文字を総当りし、各候補を `ExpressionParser` で評価 |
| [1022](https://onlinejudge.u-aizu.ac.jp/problems/1022) Indian Puzzle | `lib/parser/parser.hpp` + バックトラッキング | 升目を数字・演算子で埋め、行/列の等式を式評価で検証 |

## 未実装: ライブラリの拡張が必要

`ExpressionParser` / 既存ヘッダの機能では届かず、追加・拡張が要るもの。

| 問題 | 不足している機能 | 提案 |
| --- | --- | --- |
| [2348](https://onlinejudge.u-aizu.ac.jp/problems/2348) Testing Circuits | 最大 10^6 文字で深いネスト時に `parse_expression` の再帰がスタックを溢れさせる | **再帰安全な式解析** (明示スタック / shunting-yard モード)。値型は `(真になる割当数, 偽になる割当数)` を `modint` で |
| [1314](https://onlinejudge.u-aizu.ac.jp/problems/1314) Matrix Calculator | 行要素の区切りが空白 (`[1 2;3 4]`)。現状の `ExpressionParser` は空白を無条件に読み飛ばすため `1 -2` (2 要素) と `1-2` (減算) を区別できない。ブロック行列の連結も必要 | **空白を区切りとして扱えるモード** か行指向トークナイザ。値型は既存の `lib/linalg/matrix.hpp` (`Matrix<modint>`) がそのまま使える |
| [1322](https://onlinejudge.u-aizu.ac.jp/problems/1322) ASCII Expression | 分数を横線で複数行にまたいで表す **2 次元レイアウト**。1 次元の `ExpressionParser` では扱えない | **2 次元セルの再帰下降** *(要追加)*。値型は既存の `lib/math/fraction.hpp` (`Fraction`) |

## 未実装: 構文解析ライブラリの対象外

インデント・入れ子・グラフ構造の解析が主で、`ExpressionParser` / `CykGraph` の枠に乗らない。
問題ごとに再帰下降やシミュレーションを書き下すのが素直。主に必要なのは以下。

| 問題 | 主に必要なもの |
| --- | --- |
| [0105](https://onlinejudge.u-aizu.ac.jp/problems/0105) 本の索引 / [0151](https://onlinejudge.u-aizu.ac.jp/problems/0151) マス目 / [1602](https://onlinejudge.u-aizu.ac.jp/problems/1602) ICPC 計算機 | 単純な文字列処理・グリッド・字下げ (ライブラリ不要) |
| [2438](https://onlinejudge.u-aizu.ac.jp/problems/2438) YAML / [2523](https://onlinejudge.u-aizu.ac.jp/problems/2523) Time Complexity | インデント/行指向の再帰下降。2523 は多項式次数の管理も |
| [2643](https://onlinejudge.u-aizu.ac.jp/problems/2643) AI | 制御構文 (if/while) の再帰下降 + 盤面シミュレーション |
| [2067](https://onlinejudge.u-aizu.ac.jp/problems/2067) Reading Brackets in English | リスト文法の再帰下降 (演算子なし・S 式生成) |
| [1282](https://onlinejudge.u-aizu.ac.jp/problems/1282) Bug Hunt | 文の解析 + 配列境界検査 (添字式のみ `ExpressionParser` 可) |
| [1031](https://onlinejudge.u-aizu.ac.jp/problems/1031) Simple GUI / [2421](https://onlinejudge.u-aizu.ac.jp/problems/2421) Markup | 入れ子構造の再帰下降 + 幾何/整形 |
| [1001](https://onlinejudge.u-aizu.ac.jp/problems/1001) Binary Tree / [2740](https://onlinejudge.u-aizu.ac.jp/problems/2740) 根付き木 / [1188](https://onlinejudge.u-aizu.ac.jp/problems/1188) 階層民主主義 | 木・入れ子構造の再帰下降 + 木 DP |
| [1145](https://onlinejudge.u-aizu.ac.jp/problems/1145) 全宇宙生命ゲノム DB | トライ / ハッシュ (`lib/string/`, `lib/data_structure/`) |
| [2680](https://onlinejudge.u-aizu.ac.jp/problems/2680) LR | `?` を埋めて妥当な式にできるかの文法 DP (`CykGraph` の応用が近い) |
| [2437](https://onlinejudge.u-aizu.ac.jp/problems/2437) DNA | 塩基組成のカウンティング DP + `modint` (畳み込み)。CFG は DAG で CYK ではない |
| [2328](https://onlinejudge.u-aizu.ac.jp/problems/2328) Mobile Network | 多項式容量の最大流 (`lib/flow/max_flow.hpp` + 多項式) |
| [2710](https://onlinejudge.u-aizu.ac.jp/problems/2710) 坑道数式 | 括弧挿入の区間 DP |
| [0291](https://onlinejudge.u-aizu.ac.jp/problems/0291) 古代遺跡の謎 | 順列 (あみだくじ) の合成・冪 |
| [2731](https://onlinejudge.u-aizu.ac.jp/problems/2731) Shifting a Matrix | 行列シフトのデータ構造 |
| [0110](https://onlinejudge.u-aizu.ac.jp/problems/0110) 覆面算 / [1037](https://onlinejudge.u-aizu.ac.jp/problems/1037) Midnight Teatime / [2883](https://onlinejudge.u-aizu.ac.jp/problems/2883) 知識の証明 / [2512](https://onlinejudge.u-aizu.ac.jp/problems/2512) 編集合戦 / [2365](https://onlinejudge.u-aizu.ac.jp/problems/2365) メモリーリーク | 探索・全列挙・シミュレーション (構文解析はほぼ無関係) |

## 提案する追加・拡張 (まとめ)

構文解析ライブラリとして手を入れる価値があるのは次の 3 点。

1. **再帰安全な式解析** — 深いネスト (10^6 文字級) でスタックを溢れさせない明示スタック版、
   あるいは shunting-yard による評価モード。対象: 2348。
2. **空白が意味を持つ文法への対応** — 行/要素の区切りとしての空白を扱えるオプション。
   ブロック行列 (要素が行列) の連結も含む。対象: 1314 (値型は既存 `Matrix<T>`)。
3. **2 次元レイアウト解析** — 分数の横線など、複数行にまたがる式を解析する 2 次元セルの
   再帰下降ヘルパ。対象: 1322 (値型は既存 `Fraction`)。

いずれも値型側 (`Matrix`, `Fraction`, `modint`) は既に揃っているため、追加すべきは
**パーサ側の入力の扱い**に集中する。
