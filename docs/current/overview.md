---
title: リポジトリの全体像
---

# リポジトリの全体像

競技プログラミング用の C++23 ヘッダオンリーライブラリ。`lib/` に実装、`test/` に
[competitive-verifier](https://github.com/competitive-verifier/competitive-verifier)
用の検証ファイルを置く。

> **注意**: `docs/` の文書はすべて**このライブラリ自体の仕様・開発方針**であり、
> 競技プログラミングの**問題を解くときには参照しない**。問題を解く作業は
> `workspace/` で行い、そこではこれらの方針は適用されない。

## ディレクトリ

| パス | 内容 |
| --- | --- |
| `lib/` | 実装。include ルート。カテゴリ別の内容は [README](../../README.md) の表を参照 |
| `test/` | competitive-verifier 用の `*.test.cpp`。先頭に検証用問題の URL を書く |
| `tools/` | リファレンスの生成・検査・CI 集計に使う Python（[reference-pipeline.md](reference-pipeline.md)） |
| `docs/` | 開発ドキュメント。`docs/generated/` は生成物で Git 管理外 |
| `workspace/` | 問題を解く作業用（ライブラリ開発とは別系統） |
| `.githooks/` | pre-commit（clang-format の自動整形） |

## 言語と include

- 言語は **C++23**。応答・コメントは日本語で書く。
- include ルートは **`lib/`**。ヘッダ間は `lib/` からの相対パスで参照する。

  ```cpp
  #include "number_theory/modint.hpp"
  ```

- コンパイル時は `-I lib` を付ける（[commands.md](../commands.md)）。

## 置き場所

- **データ構造は `lib/data_structure/` に置く**。ファミリ専用ディレクトリを新設しない。
- 既存の例外は `segtree/`・`heap/`・`persistent_ds/` の 3 つだけ
  （永続・部分永続版は名前に `persistent` が入るものすべて `persistent_ds/`）。
- 理由は [decisions/0001-data-structure-directories.md](../decisions/0001-data-structure-directories.md)。
