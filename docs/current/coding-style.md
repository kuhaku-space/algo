---
title: コーディング規約
---

# コーディング規約

## 基本

- 全ヘッダ先頭に **`#pragma once`**。
- **標準ヘッダは明示 include** する（`<bits/stdc++.h>` や `template/template.hpp` に依存しない）。
  暗黙依存を外してテストが壊れたら、テスト側に明示 include を補う。
- C++20/23 の機能を使う: SFINAE より **concept**、サイズは **`std::bit_ceil`**、
  円周率は **`std::numbers::pi`**。
- コメントは行コメントのみ（ブロックコメント禁止）。Doxygen は **`///`**、実装コメントは **`//`**。
- 浮動小数点 → 整数の丸めは **`std::llround`**（`T(x + 0.5)` は負値で誤る）。

## 命名

**型は PascalCase、それ以外は snake_case**（ケースで型と値を区別する）。

| 対象 | ケース | 例 |
| --- | --- | --- |
| 型（`struct`/`class`、データ構造・モノイド・値型） | PascalCase | `SegmentTree`、`UnionFind`、`Add`/`Min`/`BitXor`、`Matrix` |
| `namespace`・`concept`（std 流の述語）・関数・メンバ型エイリアス・変数 | snake_case | `value_type`、`graph_type`、`shortest_path` |
| テンプレート引数 | 短い大文字か PascalCase | `M`/`S`/`F`/`Comp` |

- 複数の実装が並立しうる構造は、**アルゴリズム名ではなく役割ベースの名前**を公開名にする
  （`OrderedSet`、`DynamicSequence` のように、内部が splay 木か AVL 木かは名前に出さない）。
- 移行は段階的に行う。一括改名はせず、**そのライブラリを変更するついでに型名を PascalCase 化し、
  `lib/`・`test/` の参照も同時に追随**させる（旧 `segment_tree` 等の名残がある）。

## ドメイン別の規約

### グラフ

**`graph_type` / `weighted_graph_type` concept** で書き、`list_graph<T>`・`csr_graph<T>` の
両方に対応させる。

### ヒープ（`lib/heap/`）

- **`Key` が順序基準**（`Comp` の比較側・radix の整数キー）、**`Value` が付随データ**。
- API は `push(key, value)` / `top() -> pair<key, value>` / `update(handle, key)`。
- `shortest_path` では `Heap<距離, 頂点, Comp>` として使う。

### 「付随データなし」の型引数 `void`

本体は部分特殊化で分けず `std::conditional_t<is_void_v<V>, std::monostate, V>` に正規化して
1 本化する（API は `if constexpr`、空メンバは `[[no_unique_address]]`）。例: `radix_heap`、`doubling`。

ただし `void` で**別のデータ構造**を選ぶ場合（`matrix_graph<void>` の `vector<vector<bool>>` 等）は
部分特殊化のままにする。理由は
[decisions/0004-void-type-parameter.md](../decisions/0004-void-type-parameter.md)。

## フォーマット

- **clang-format**（`.clang-format`、Google ベース、mise 管理）に従う。設定の意図は
  [toolchain.md](toolchain.md)。
- `.githooks/pre-commit` がステージ済みの `.cpp`/`.hpp` を自動整形して再 stage する
  （`mise run setup` で有効化済み）。
- `lib/template/{atcoder,library_checker}.hpp` は `template/template.hpp`（`<bits/stdc++.h>`）を
  先頭に置く。`.clang-format` の `IncludeCategories` が負の `Priority` で先頭固定するので、
  `template/` も通常整形でよい。
