---
title: Git・PR 運用
---

# Git・PR 運用

## ブランチ

- **`main` に直接コミットしない**（保護されており push が弾かれる）。`git switch -c <branch>` で作業する。
- **新ブランチは必ず最新 `main` から切る**。squash マージ済みブランチ上から切るとコンフリクトする。

  ```sh
  git switch main && git pull        # または git fetch origin main
  git switch -c <branch> origin/main
  ```

- **未 PR の作業ブランチを勝手に切り替えない**。`git switch` / `git stash` はユーザの明示指示があるときだけ。

## コミット

- **ひと区切りしたら指示を待たず自動コミット**する（意味のある単位で、`main` 以外のブランチ上で）。
- **PR を作成したブランチに、無関係な新規作業のコミットを足さない**（auto-merge でブランチごと削除される）。
  新しい作業は別ブランチで始める。
  - 例外: **その PR 自体の CI 失敗を直すコミットは同じブランチでよい**。この規則は
    「マージ待ちの PR に別件を混ぜない」ためのもの。

## PR・マージ（ユーザの明示指示時のみ）

- **PR 作成はユーザの明示指示時のみ**。それまでは push も auto-merge も実行しない。
- PR を作成したら必ず auto-merge を有効化する。

  ```sh
  gh pr create --fill && gh pr merge --auto --squash
  ```

  リポジトリ側の前提は整っている（`allow_auto_merge` ON、必須チェックは `docs-and-check`、
  `pr-auto-approve.yml` が bot 承認）。CI 通過 → 承認 → マージ → ブランチ削除まで全自動で進む。
