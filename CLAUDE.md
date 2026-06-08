# CLAUDE.md

競技プログラミング用の C++ ヘッダオンリーライブラリ。`lib/` に実装、`test/` に
[competitive-verifier](https://github.com/competitive-verifier/competitive-verifier) 用の検証ファイル。

- 言語: **C++23**（応答・コメントは日本語）
- include ルートは **`lib/`**。ヘッダ間は `lib/` からの相対パス（例: `#include "math/modint.hpp"`）

## ビルド・テスト

```sh
g++ -std=c++23 -I lib -Wall -Wextra -fsyntax-only <test_file>
```

正しさはランダムテストで naive 実装と突き合わせて確認する。

## コーディング規約

- 全ヘッダ先頭に **`#pragma once`**。
- **標準ヘッダは明示 include**（`<bits/stdc++.h>` や `template/template.hpp` に依存しない）。
- **`namespace` は snake_case**。
- C++20/23 機能を使う: SFINAE より **concept**、サイズは **`std::bit_ceil`**、円周率は **`std::numbers::pi`**。
- コメントは行コメントで統一し、**ブロックコメント（`/** */` や `/* */`）は使わない**。
  - **Doxygen ドキュメントコメントは `///`**（`@brief` などを付ける説明）。
  - **通常の実装コメントは `//`**。
- 浮動小数点→整数の丸めは **`std::llround`**（`T(x + 0.5)` は負値で誤る）。

## ライブラリ変更の方針

- 個人用ライブラリなので、**後方互換性のために妥協しない**。設計・命名・API をより良く
  できるなら、破壊的変更（リネーム・シグネチャ変更・削除・再構成）を積極的に行う。
- 破壊的変更の際は、リポジトリ全体（`lib/`・`test/`）から参照箇所を洗い出して
  **呼び出し側もすべて追随させる**。古い API を中途半端に残さない。

## 注意

- `template.hpp` への暗黙依存を外すと、それ経由で標準ヘッダを得ていたテストが壊れることがある
  → テスト側に明示 include を補う。
