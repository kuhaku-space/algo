# algo

[![Actions Status](https://github.com/kuhaku-space/algo/workflows/verify/badge.svg)](https://github.com/kuhaku-space/algo/actions)
[![GitHub Pages](https://img.shields.io/static/v1?label=GitHub+Pages&message=+&color=brightgreen&logo=github)](https://kuhaku-space.github.io/algo/)
![GitHub](https://img.shields.io/github/license/kuhaku-space/algo)
![C++](https://img.shields.io/badge/C++-23-green)

[![kuhaku](https://img.shields.io/endpoint?url=https%3A%2F%2Fatcoder-badges.vercel.app%2Fapi%2Fatcoder%2Fjson%2Fkuhaku)](https://atcoder.jp/users/kuhaku)
[![ku-haku](https://img.shields.io/endpoint?url=https%3A%2F%2Fatcoder-badges.vercel.app%2Fapi%2Fcodeforces%2Fjson%2Fku-haku)](https://codeforces.com/profile/ku-haku)
[![kuhqku](https://img.shields.io/endpoint?url=https%3A%2F%2Fcodechef-badges.vercel.app%2Fapi%2Fcodechef%2Fkuhqku)](https://www.codechef.com/users/kuhqku)

競技プログラミング用の C++23 ヘッダオンリーライブラリです。

すべての実装は [`lib/`](lib/) 以下にあり、その正しさは
[competitive-verifier](https://github.com/competitive-verifier/competitive-verifier)
を用いて [`test/`](test/) のジャッジ（AtCoder / Library Checker / yukicoder / AOJ）で
継続的に検証されています。ドキュメントは [GitHub Pages](https://kuhaku-space.github.io/algo/) で公開しています。

## 使い方

include ルートは `lib/` です。各ヘッダは `lib/` からの相対パスで参照します。

```cpp
#include "segtree/segment_tree.hpp"
#include "math/modint.hpp"
```

コンパイル時に `-I lib` を指定してください。

```sh
g++ -std=c++23 -I lib your_solution.cpp
```

## ライブラリ構成

| ディレクトリ                                 | 内容                                                                                      |
| -------------------------------------------- | ----------------------------------------------------------------------------------------- |
| [`lib/algorithm/`](lib/algorithm/)           | 二分探索・座標圧縮・累積和・ダブリング・Mo's algorithm・LIS・転倒数 など                  |
| [`lib/data_structure/`](lib/data_structure/) | SWAG・Merge Sort Tree・領域木・区間 set・flip set・undo deque など                        |
| [`lib/segtree/`](lib/segtree/)               | セグメント木・遅延セグメント木・双対セグメント木・動的セグメント木・モノイド定義          |
| [`lib/fenwick/`](lib/fenwick/)               | Fenwick Tree（点更新区間和・区間加算区間和）                                              |
| [`lib/sparse_table/`](lib/sparse_table/)     | Sparse Table・Disjoint Sparse Table・線形 Sparse Table                                    |
| [`lib/wavelet/`](lib/wavelet/)               | Wavelet Matrix（圧縮版・動的版・矩形和）                                                  |
| [`lib/ordered_set/`](lib/ordered_set/)       | 順序集合・多重集合（AVL 木）・Binary Trie・Patricia Binary Trie・64 分木                  |
| [`lib/union_find/`](lib/union_find/)         | Union-Find（重み付き・undo・動的・永続・offline dynamic connectivity）                    |
| [`lib/heap/`](lib/heap/)                     | Binary / Fibonacci / Leftist / Skew / Radix / Interval ヒープ・削除可能 PQ・k 番目和      |
| [`lib/persistent_ds/`](lib/persistent_ds/)   | 永続配列・永続セグメント木・永続スタック/キュー                                           |
| [`lib/dp/`](lib/dp/)                         | Convex Hull Trick・Li Chao Tree・Slope Trick・monotone minima                             |
| [`lib/math/`](lib/math/)                     | modint・多倍長整数・分数・ハッシュ用整数（数の型・基盤演算）                              |
| [`lib/number_theory/`](lib/number_theory/)   | 素数判定/列挙・篩・素因数分解・CRT・floor sum・mod 平方根・Stern-Brocot 木 など           |
| [`lib/combinatorics/`](lib/combinatorics/)   | 二項係数・スターリング数等の列挙・ベル数・分割数・offline binomial sum                    |
| [`lib/linalg/`](lib/linalg/)                 | 行列・Berlekamp-Massey・きたまさ法（線形漸化式）                                          |
| [`lib/convolution/`](lib/convolution/)       | FFT・NTT・形式的冪級数・subset convolution・Garner                                        |
| [`lib/graph/`](lib/graph/)                   | Dijkstra・Bellman-Ford・SCC・2-SAT・最小全域木・functional graph・トポロジカルソート など |
| [`lib/flow/`](lib/flow/)                     | 最大流・最小費用流・Hopcroft-Karp                                                         |
| [`lib/tree/`](lib/tree/)                     | HLD・LCA・重心分解・Euler Tour・Link-Cut Tree・全方位木 DP・Static Top Tree など          |
| [`lib/string/`](lib/string/)                 | Suffix Array・Z-algorithm・KMP・Aho-Corasick・Rolling Hash・Manacher・回文木・Trie など   |
| [`lib/geometry/`](lib/geometry/)             | 2D / 3D 幾何・凸包・kd-tree                                                               |
| [`lib/random/`](lib/random/)                 | xorshift・xoroshiro128・xoshiro128・SplitMix64                                            |
| [`lib/internal/`](lib/internal/)             | 他ヘッダから利用する内部ユーティリティ（bit vector・CSR・型特性 など）                    |
| [`lib/template/`](lib/template/)             | 提出用テンプレート（マクロ・高速入出力 など）                                             |

## ビルド・テスト

構文チェックは次のコマンドで行えます。

```sh
g++ -std=c++23 -I lib -Wall -Wextra -fsyntax-only <test_file>
```

正しさは、ランダム入力に対する naive 実装との突き合わせで確認しています。
[`test/`](test/) 以下の `*.test.cpp` には先頭に検証用問題の URL を記述し、
competitive-verifier がジャッジに対して実行します。

verify で使用するコンパイラオプションは
[AtCoder の言語アップデート](https://img.atcoder.jp/file/language-update/2025-10/language-list.html)
を参考にしています。

## ドキュメント

公開 API の日本語リファレンスは [`docs/`](docs/) にあり、ヘッダの Doxygen コメント、
依存関係、検証結果と合わせてリポジトリ内のドキュメントActionが GitHub Pages 用の
Jekyllソースを自動生成します。`competitive-verifier`は検証データの作成までを担当し、
ページの構造とテンプレートはこのリポジトリで管理します。

新しい詳細ページの雛形生成と、既存ページの形式・使用例・網羅率の検査は次のコマンドで
行えます。

```sh
python3 tools/reference_docs.py stub lib/segtree/segment_tree.hpp
python3 tools/reference_docs.py sync-generated
python3 tools/reference_docs.py check
```

自動生成ページは `docs/generated/` に作られ、Git管理には含めません。CIでも検査と
サイト構築の前に同じページを生成するため、pushするのは手書きページと生成ロジックだけです。

ページの構成と記述方針は
[`docs/reference_style.md`](docs/reference_style.md) を参照してください。

## コーディング規約

- 言語は **C++23**。
- 全ヘッダ先頭に `#pragma once`。
- 標準ヘッダは明示的に include する（`<bits/stdc++.h>` に依存しない）。
- `namespace` は snake_case。
- SFINAE より concept、サイズ計算は `std::bit_ceil`、円周率は `std::numbers::pi` など
  C++20/23 の機能を優先する。
- Doxygen ドキュメントコメントは `///`、通常の実装コメントは `//`。ブロックコメントは使わない。

## ライセンス

This project is licensed under the [MIT License](https://github.com/kuhaku-space/algo/blob/main/LICENSE).
