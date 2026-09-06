---
title: CI の調査とトークン節約
---

# CI の調査とトークン節約

CI ログは巨大になりやすい。**まずローカルで再現し、どうしても必要なときだけ狭く取りに行く**。
ワークフロー自体の設計は [verify-workflow.md](verify-workflow.md)。

## まずローカルで再現する

**push や CI ログ取得より先に `-fsyntax-only` で再現する**。ヘッダ変更時の逆依存チェックにも、
verify 失敗の再現にも同じ手が使える。失敗の大半はコンパイルエラーなのでこれで即再現できる。

```sh
grep -rl <header_basename> lib test | grep '\.test\.cpp$' \
  | xargs -I{} g++ -std=c++23 -I lib -fsyntax-only {}
```

transitive な依存は `oj-bundle <test>` で展開して確認する
（ローカルに `oj-verify` / `oj-bundle` / `oj` がある）。

## CI を見るときは狭く

- 状態の確認は `gh ... --json … -q` で必要なフィールドだけ取る。
- エラーログは `--log-failed` で**1 ジョブのみ**。`--log` で全シャードをループしない。
- 「どのテストが落ちたか」は merged check の `N file(s) still failing` 行で特定する。
- CI はポーリングせず auto-merge に任せる。
- **同一 URL への curl は結果を使い回し、再フェッチしない**（GitHub Pages のドキュメント確認など）。
- 巨大ログや数十 KB を超える外部ファイル（ミニファイ JS 等）を精読せざるを得ないときは
  **サブエージェントに委譲**する（生データは子のコンテキストに留め、結論だけ受け取る）。

## 実行時間

`docs-and-check` ジョブのサマリーで確認する。`tools/verify_timing_summary.py` が `main` の
結果キャッシュと比較して、合計・最悪ケース・再実行された test の差分を出力する。
共有 runner のばらつきが大きいので**参考値でありゲートではない**。
