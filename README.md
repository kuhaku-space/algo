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
| [`lib/data_structure/`](lib/data_structure/) | Union-Find・Sparse Table・Wavelet Matrix・Li Chao Tree・多倍長整数・SWAG など             |
| [`lib/segtree/`](lib/segtree/)               | セグメント木・遅延セグメント木・双対セグメント木・動的セグメント木・モノイド定義          |
| [`lib/binary_tree/`](lib/binary_tree/)       | Fenwick Tree・平衡二分探索木（AVL / Treap / Splay / Scapegoat）・Binary Trie              |
| [`lib/persistent_ds/`](lib/persistent_ds/)   | 永続配列・永続セグメント木・永続 Union-Find・永続スタック/キュー                          |
| [`lib/heap/`](lib/heap/)                     | Binary / Fibonacci / Leftist / Skew / Radix / Interval ヒープ                             |
| [`lib/math/`](lib/math/)                     | modint・組合せ・素数判定/列挙・行列・floor sum・きたまさ法・Slope Trick など              |
| [`lib/fft/`](lib/fft/)                       | FFT・NTT・形式的冪級数・subset convolution・Garner                                        |
| [`lib/graph/`](lib/graph/)                   | Dijkstra・Bellman-Ford・SCC・2-SAT・最小全域木・functional graph・トポロジカルソート など |
| [`lib/flow/`](lib/flow/)                     | 最大流・最小費用流・Hopcroft-Karp                                                         |
| [`lib/tree/`](lib/tree/)                     | HLD・LCA・重心分解・Euler Tour・Link-Cut Tree・全方位木 DP・Static Top Tree など          |
| [`lib/string/`](lib/string/)                 | Suffix Array・Z-algorithm・KMP・Aho-Corasick・Rolling Hash・Manacher・回文木 など         |
| [`lib/geometry/`](lib/geometry/)             | 2D / 3D 幾何・凸包・Convex Hull Trick・kd-tree                                            |
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
