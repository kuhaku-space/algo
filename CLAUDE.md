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
- コメントは **`///` 行コメント形式**で統一する。Doxygen も通常コメントも `///` を使い、
  **`/** */` や `/* */` などのブロックコメントは使わない**。
- 浮動小数点→整数の丸めは **`std::llround`**（`T(x + 0.5)` は負値で誤る）。

## 注意

- `template.hpp` への暗黙依存を外すと、それ経由で標準ヘッダを得ていたテストが壊れることがある
  → テスト側に明示 include を補う。
- 互換性を壊す変更（リネーム・削除）の前に、リポジトリ全体で参照ゼロを確認する。
