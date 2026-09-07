---
title: リファレンス生成の仕組み
---

# リファレンス生成の仕組み

`tools/` にある Python の設計。**何を書くか**は
[documentation.md](documentation.md) と [reference-style.md](reference-style.md)、
**コマンド**は [commands.md](../commands.md) を参照。

## 流れ

```
lib/**/*.hpp ──parse──> モデル ──render──> docs/generated/**.md ──render_reference_site──> _jekyll/
                          │
                          └──check──> 品質ゲート
```

| モジュール | 役割 |
| --- | --- |
| `tools/reference_docs.py` | ドライバ。`build` で生成、`check` で生成したうえで品質を検査する |
| `tools/reference/parse.py` | ヘッダの Doxygen コメントを読みモデルを組み立てる |
| `tools/reference/model.py` | 中間表現 |
| `tools/reference/render.py` | モデルから cpprefjp 風の Markdown を書き出す |
| `tools/reference/check.py` | 生成物ではなくヘッダ側の記述を検査する品質ゲート |
| `tools/render_reference_site.py` | 生成済みページから Jekyll のソースツリーを組み立てる |

## モデル

「ヘッダ 1 つ = `Header`、名前空間直下の型・関数 = `Entity`、クラスの中身 = `Entity.members`、
同名のオーバーロード = `Entity.overloads`」という素直な木構造にしてある。

`parse` が見るのは **`///` の行コメントだけ**（規約でブロックコメントは使わない）。
名前空間・クラスのスコープを追いながら走査し、コメント直後の宣言をそのコメントの対象とみなす。

## ページの粒度

`render` が書き出すページは 2 段。

- ヘッダページ `<category>/<stem>.md` — ヘッダの概要、インクルード、提供する型・関数の一覧。
- エンティティページ `<category>/<stem>/<name>.md` — クラス 1 つ・関数 1 つの詳細
  （オーバーロードは 1 ページにまとまる）。

実装詳細と提出用テンプレートのカテゴリは、リンク先としてページは作るが一覧では最後に置く。

本文は `render` が GitHub Pages の kramdown 向けに退避する。素通しにすると、地の文の `|` は
行ごと表と解釈され、`<T>` は HTML タグと見なされて消える。数式（`$…$`）は MathJax が原文を
読むのに、kramdown が `\_` のバックスラッシュを取り除いたり `'` をスマートクォートに変えたり
してしまうので、**kramdown がエスケープを解くと原文に戻る形**へ退避してから書き出す。
バッククォートの中は kramdown がそのまま通すので触らない。表のセルでは加えて改行を `<br>` に
する。退避の過不足は `mise run docs-check` が両方向で確かめる。

## 品質ゲート

ヘッダのコメントが唯一の情報源なので、`check` が見るのも**生成物の書式ではなくヘッダ側の記述**。
守るのは次の 3 点。

1. 説明のない公開 API を増やさない
2. 計算量の記述を減らさない
3. 例（`@code` … `@endcode`）が壊れていない（実際にコンパイル・実行する）

しきい値は `docs/reference.toml` にある。

加えて、**数式が `$…$` で囲われているか**を `lib/` の `///` コメントに対して検査する。
MathJax は `$` の外を組版しないので、地の文に置いた計算量や LaTeX コマンドはそのままの文字列として
ページに出てしまう。生の `O(...)` / `Θ(...)` / `Ω(...)`、`log`・`sqrt`・`sum_`・`prod_`、
`$` の外の LaTeX コマンドを拾う（`@code` ブロック内とコードスパン・URL は除外）。

## サイトの組み立て

`render_reference_site.py` がやるのは**サイトとしての体裁だけ**で、ページの中身は
`docs/generated/` にあるものをそのまま使う。

- カテゴリ → ヘッダ → 型/関数 のナビゲーション
- 依存関係・検証結果・実装全文（ヘッダページの下部）
- 検証プログラムのページ
- トップページと検索インデックス
- `docs/**/*.md` の手書きページ（この文書など。`docs/generated/` は除く）をそのまま載せる

`verify_files.json` / `result.json` が無いローカル環境でも見た目を確認できるよう、`--offline` では
`#include` を辿った簡易版を合成する。このとき bundle エラーは落とす。competitive-verifier の
bundler はリポジトリ直下からしか探さずコンパイラの include パスを見ないため、`lib/` 起点の include を
使う都合上、bundle エラーはリファレンスとして意味がないため。

**レンダリングはこのリポジトリの持ち物**であり、competitive-verifier は入力の解決・検証・マージと
最終的な合否チェックだけを担当する（[verify-workflow.md](verify-workflow.md)）。
