---
title: コマンド一覧
---

# コマンド一覧

変更したあとに走らせる検査をここにまとめる。

## 構文チェック

```sh
g++ -std=c++23 -I lib -Wall -Wextra -fsyntax-only <test_file>
```

include ルートは `lib/` なので `-I lib` を必ず付ける。

ヘッダを変更したときは、そのヘッダを使う test をまとめて確認する（逆依存チェック）。

```sh
grep -rl <header_basename> lib test | grep '\.test\.cpp$' \
  | xargs -I{} g++ -std=c++23 -I lib -fsyntax-only {}
```

transitive な依存の確認には `oj-bundle <test>` を使う。

## ドキュメント

```sh
mise run docs        # docs/generated/ にページを生成する
mise run docs-check  # 網羅率・例のコンパイルと実行・リンクを検査する
mise run docs-site   # 検証結果なしでサイトのソースを _jekyll/ に組み立てる
```

- 公開 API を変えたら `mise run docs-check`。
- 生成物 `docs/generated/` は Git 管理外。コミットしない。

## Lint

```sh
mise run lint        # tools/ の Python を ruff で検査する（設定は ruff.toml）
```

## セットアップ

```sh
mise run setup       # ツール・oj 系 CLI・pre-commit フック・shim を一括導入
```

導入するものとその選定理由は [current/toolchain.md](current/toolchain.md)。

`.githooks/pre-commit` がステージ済みの `.cpp`/`.hpp` を clang-format で自動整形して再 stage する。

## PR

```sh
gh pr create --fill && gh pr merge --auto --squash
```

ユーザの明示指示があるときだけ実行する（[current/git-workflow.md](current/git-workflow.md)）。

## そのほか

問題を解く作業用の `oj*` タスク（`ojn` / `ojd` / `ojb` / `ojt` / `ojs` など）は
`mise tasks` で一覧できる。これらは `workspace/` で動くものでライブラリ開発とは別系統。
