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

### verify 用問題を探す優先順位

ライブラリの verify 用問題は次の優先順位で探す:

1. **Library Checker**（<https://judge.yosupo.jp/>）
2. **yukicoder**（<https://yukicoder.me/>）
3. **AOJ**（Aizu Online Judge）

どのジャッジにも素直に対応する問題がなければ verify は保留する
（competitive-verifier の UNIT_TEST は使わない）。

## コーディング規約

- 全ヘッダ先頭に **`#pragma once`**。
- **標準ヘッダは明示 include**（`<bits/stdc++.h>` や `template/template.hpp` に依存しない）。
- **`namespace` は snake_case**。
- C++20/23 機能を使う: SFINAE より **concept**、サイズは **`std::bit_ceil`**、円周率は **`std::numbers::pi`**。
- コメントは行コメントで統一し、**ブロックコメント（`/** */` や `/* */`）は使わない**。
  - **Doxygen ドキュメントコメントは `///`**（`@brief` などを付ける説明）。
  - **通常の実装コメントは `//`**。
- 浮動小数点→整数の丸めは **`std::llround`**（`T(x + 0.5)` は負値で誤る）。
- グラフアルゴリズムは具体型に依存せず **`graph_type` / `weighted_graph_type` concept** で書き、
  `list_graph<T>`・`csr_graph<T>` の両方に対応させる。
- ヒープ（`lib/heap/`）の `Key`/`Value` 規約: **`Key` が順序基準**（`Comp` で比較する側・
  radix の整数キー）、**`Value` が付随データ**。`push(key, value)` / `top() -> pair<key, value>` /
  `update(handle, key)`。`shortest_path` では `Heap<距離, 頂点, Comp>` として使う。

## フォーマット

- 整形は **clang-format**（`.clang-format`、Google ベース）。clang-format は **mise 管理**
  （`mise install` で導入）。
- コミット時に **`.githooks/pre-commit`** がステージ済みの `.cpp`/`.hpp` を自動整形して
  再 stage する。有効化は `git config core.hooksPath .githooks`（`mise run setup` に組込み済み）。
- `lib/template/{atcoder,library_checker}.hpp` は `template/template.hpp`
  （`<bits/stdc++.h>` を引く）を先頭に置く必要がある。`.clang-format` の `IncludeCategories`
  で `template/template.hpp` に最優先（負 `Priority`）を与え、ソートを効かせたまま先頭固定して
  いるので、`template/` も通常どおり整形してよい。

## ライブラリ変更の方針

- 個人用ライブラリなので、**後方互換性のために妥協しない**。設計・命名・API をより良く
  できるなら、破壊的変更（リネーム・シグネチャ変更・削除・再構成）を積極的に行う。
- 破壊的変更の際は、リポジトリ全体（`lib/`・`test/`）から参照箇所を洗い出して
  **呼び出し側もすべて追随させる**。古い API を中途半端に残さない。

## PR 運用

- **`main` には直接コミットしない**。ブランチ保護で `main` への push は弾かれるため、
  作業は必ず新しいブランチを切ってそこにコミットする（`git switch -c <branch>`）。

- **PR を作成したブランチには新しくコミットしない**。PR 作成後は auto-merge で
  「CI 通過 → bot 承認 → 自動マージ → ブランチ削除」まで自動進行するため、追加変更を
  そのブランチに積むとマージ対象がずれたり削除済みブランチを掘り起こしたりする。
  新しい作業は別のブランチを切って行う。

- **PR を作成していない作業ブランチを勝手に切り替えない**。コミット済みでも未 PR の
  ブランチは作業中扱いとし、そのブランチ上で作業を続ける。`git switch` で別ブランチへ
  移ったり `git stash` で退避したりするのは、ユーザが明示的に指示したとき
  （ブランチ統合など）だけにする。

- **作業がひと区切りしたらコミットまでは自動で行う**。指示を待たずに、意味のある
  単位でコミットメッセージを付けてコミットする（`main` 以外のブランチ上で）。
  ただし **PR の作成はユーザが明示的に指示したときのみ**。指示があるまで作業は
  コミットまでで止め、`gh pr create` / push / auto-merge は実行しない。
  （以下は PR を作成する場合の手順であって、PR 作成自体を自動で行う指示ではない）

- PR を作成したら必ず auto-merge を有効化する

  ```sh
  gh pr create --fill && gh pr merge --auto --squash
  ```

- リポジトリ側は auto-merge の前提が整っている（`allow_auto_merge` ON、必須チェック
  `docs-and-check`、`pr-auto-approve.yml` が bot で自動承認）。これで「CI 通過 → bot 承認
  → 自動マージ → ブランチ削除」まで全自動で完結する。

## 注意

- `template.hpp` への暗黙依存を外すと、それ経由で標準ヘッダを得ていたテストが壊れることがある
  → テスト側に明示 include を補う。
