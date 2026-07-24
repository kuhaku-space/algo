# CLAUDE.md

競技プログラミング用の C++ ヘッダオンリーライブラリ。`lib/` に実装、`test/` に
[competitive-verifier](https://github.com/competitive-verifier/competitive-verifier) 用の検証ファイル。

> **注意**: この CLAUDE.md に書かれている内容はすべて**このライブラリ自体の仕様・開発方針**であり、
> 競技プログラミングの**問題を解くときには参照しないこと**。

- 言語: **C++23**（応答・コメントは日本語）。
- include ルートは **`lib/`**。ヘッダ間は `lib/` からの相対パス（例: `#include "math/modint.hpp"`）。

## ビルド・テスト

```sh
g++ -std=c++23 -I lib -Wall -Wextra -fsyntax-only <test_file>
```

- 正しさはランダムテストで naive 実装と突き合わせる。
- verify 用問題は **Library Checker → yukicoder → AOJ** の順で探す。素直に対応する問題が
  なければ verify は保留（competitive-verifier の UNIT_TEST は使わない）。
- 公開 API の日本語リファレンスを変更したら `mise run docs-check` で自動生成ページを
  同期し、形式・使用例のコンパイル・網羅率を検査する。新規の手書きページは
  `python3 tools/reference_docs.py stub lib/<category>/<header>.hpp` で雛形を作る。Doxygen
  由来のページはGit管理外の `docs/generated/` に生成し、コミットしない。

### CI 調査・トークン節約

- **push/CI ログ取得より先にローカル `-fsyntax-only` で再現**（ヘッダ変更時の逆依存チェックにも
  verify 失敗の再現にも共通。失敗の大半はコンパイルエラーなのでこれで即再現できる）。
  `grep -rl <header_basename> lib test | grep '\.test\.cpp$' | xargs -I{} g++ -std=c++23 -I lib -fsyntax-only {}`。
  transitive 依存は `oj-bundle <test>` で展開して確認（ローカルに `oj-verify`/`oj-bundle`/`oj` あり）。
- どうしても CI を見る時は**狭く**: 状態は `gh ... --json … -q`、エラーは `--log-failed` で**1 ジョブのみ**、
  「どのテストが落ちたか」は merged check の `N file(s) still failing` 行で特定。`--log` の全シャードループは避ける。
- 巨大ログ・数十 KB を超える外部ファイル（ミニファイ JS 等）を精読せざるを得ない時は
  **サブエージェントに委譲**（生データは子のコンテキストに留め、結論だけ受け取る）。
- CI はポーリングせず auto-merge に任せる。
- **同一 URL への curl は結果を使い回し、再フェッチしない**（GitHub Pages のドキュメント確認等）。

## コーディング規約

- 全ヘッダ先頭に **`#pragma once`**。
- **標準ヘッダは明示 include**（`<bits/stdc++.h>` や `template/template.hpp` に依存しない）。
  暗黙依存を外してテストが壊れたら、テスト側に明示 include を補う。
- **命名: 型は PascalCase、それ以外は snake_case**（ケースで型/値を区別）。
  - 型（`struct`/`class`、データ構造・モノイド・値型）→ PascalCase（`SegmentTree`、`UnionFind`、
    `Add`/`Min`/`BitXor`、`Matrix` 等）。
  - `namespace`・`concept`（std 流の述語）・関数・メンバ型エイリアス（`value_type`）・変数 → snake_case。
  - テンプレート引数 → 短い大文字または PascalCase（`M`/`S`/`F`/`Comp` 等）。
  - 移行は段階的。一括改名はせず、**そのライブラリを変更するついでに型名を PascalCase 化し、
    `lib/`・`test/` の参照も同時に追随**させる（旧 `segment_tree` 等の名残あり）。
- C++20/23 を使う: SFINAE より **concept**、サイズは **`std::bit_ceil`**、円周率は **`std::numbers::pi`**。
- コメントは行コメントのみ（ブロックコメント禁止）。Doxygen は **`///`**、実装コメントは **`//`**。
- 浮動小数点→整数の丸めは **`std::llround`**（`T(x + 0.5)` は負値で誤る）。
- グラフは **`graph_type` / `weighted_graph_type` concept** で書き、`list_graph<T>`・`csr_graph<T>` 両対応。
- ヒープ（`lib/heap/`）規約: **`Key` が順序基準**（`Comp` 比較側・radix の整数キー）、**`Value` が付随データ**。
  `push(key, value)` / `top() -> pair<key, value>` / `update(handle, key)`。`shortest_path` では `Heap<距離, 頂点, Comp>`。
- 「付随データなし」の型引数 `void`: 本体は部分特殊化で分けず
  `std::conditional_t<is_void_v<V>, std::monostate, V>` に正規化して 1 本化（API は `if constexpr`、
  空メンバは `[[no_unique_address]]`）。例: `radix_heap`、`doubling`。ただし `void` で**別のデータ構造**を
  選ぶ場合（`matrix_graph<void>` の `vector<vector<bool>>` 等）は部分特殊化のまま。

## フォーマット

- **clang-format**（`.clang-format`、Google ベース、mise 管理）。`.githooks/pre-commit` が
  ステージ済み `.cpp`/`.hpp` を自動整形して再 stage（`mise run setup` で有効化済み）。
- `lib/template/{atcoder,library_checker}.hpp` は `template/template.hpp`（`<bits/stdc++.h>`）を
  先頭に置く。`.clang-format` の `IncludeCategories` が負 `Priority` で先頭固定するので `template/` も通常整形でよい。

## ライブラリ変更の方針

- 個人用ライブラリ。**後方互換性のために妥協しない**——設計・命名・API を良くできるなら
  破壊的変更（リネーム・シグネチャ変更・削除・再構成）を積極的に行う。
- 破壊的変更時は `lib/`・`test/` から参照を洗い出し**呼び出し側もすべて追随**。古い API を中途半端に残さない。
- **計算量を悪化させない**。リファクタ・バグ修正でも各操作の時間計算量を既存より悪くしない
  （可読性とトレードオフなら計算量優先。変える必要があれば妥当性を示して合意を取る）。
  空間計算量は実用範囲では問わないが、不要なコピー・確保は避ける。

## Git・PR 運用

### ブランチ
- **`main` に直接コミットしない**（保護で push が弾かれる）。`git switch -c <branch>` で作業。
- **新ブランチは必ず最新 `main` から切る**: `git switch main && git pull`（or `git fetch origin main`）→
  `git switch -c <branch> origin/main`。squash マージ済みブランチ上から切るとコンフリクトする。
- **未 PR の作業ブランチを勝手に切り替えない**。`git switch`/`git stash` はユーザの明示指示時のみ。

### コミット
- **ひと区切りしたら指示を待たず自動コミット**（意味のある単位で、`main` 以外のブランチ上で）。
- **PR を作成したブランチには追加コミットしない**（auto-merge で削除される）。新作業は別ブランチで。

### PR・マージ（ユーザの明示指示時のみ）
- **PR 作成はユーザの明示指示時のみ**。それまでは push / auto-merge を実行しない。
- PR を作成したら必ず auto-merge を有効化:

  ```sh
  gh pr create --fill && gh pr merge --auto --squash
  ```

  リポジトリは前提が整っており（`allow_auto_merge` ON、必須チェック `docs-and-check`、
  `pr-auto-approve.yml` が bot 承認）、CI 通過 → 承認 → マージ → ブランチ削除まで全自動。
