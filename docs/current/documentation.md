---
title: リファレンスの方針
---

# リファレンスの方針

## 生成物と手書きの境界

- 公開リファレンス（cpprefjp 風）は**ヘッダの `///` コメントだけ**から生成する。
  `reference/` 配下に**手書きの Markdown ページは置かない**。文章を直すときはヘッダを編集する。
  理由は [decisions/0003-generated-reference-only.md](../decisions/0003-generated-reference-only.md)。
- この制約は API ページの話であり、`docs/` の開発ドキュメント（この文書や
  [reference_style.md](../reference_style.md)）は手書きでよい。これらもサイトにそのまま載る。
- 生成物は Git 管理外の `docs/generated/` に出る。**コミットしない**。

## 書くとき

- 公開 API を変えたら `mise run docs-check` で網羅率・例のコンパイルと実行・リンクを検査する。
- ヘッダ全体の説明が要るとき（主要な型が 1 つに定まらない、使用例や注意点を書きたい）は、
  include 群の直後に `/// @file` ブロックを置く。
- `@code` … `@endcode` の例は実際にコンパイル・実行され、標準出力がページの「出力」節になる。
- タグの一覧や書き方の詳細は [reference_style.md](../reference_style.md)。

## コマンド

[commands.md](../commands.md) を参照。生成ツールの設計は
[reference-pipeline.md](reference-pipeline.md)。
