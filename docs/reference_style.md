---
title: リファレンス執筆ガイド
---

# リファレンス執筆ガイド

利用者がヘッダを選び、制約を確認し、最小コードをコピーして使える日本語リファレンスを
目標とする。実装の逐語的な説明ではなく、公開 API の契約を記述する。

## ページの作成

次のコマンドで、Doxygen の `@brief` と verify ファイルの問題 URL を使った雛形を作れる。

```sh
python3 tools/reference_docs.py stub lib/segtree/segment_tree.hpp
```

未作成の全公開ヘッダをまとめて追加する場合は `generate-missing`、ヘッダ内のDoxygen
コメントを自動生成ページへ反映する場合は `sync-generated` を使う。

```sh
python3 tools/reference_docs.py generate-missing
python3 tools/reference_docs.py sync-generated
```

自動生成ページの出力先は、Git管理外の `docs/generated/` である。CIは検査時と
サイト構築時に `sync-generated` を実行するため、このディレクトリをコミットしない。
手書きページと自動生成を置き換える場合だけ、通常の `docs/<category>/` に作成する。

生成された「執筆中」をすべて埋め、品質検査を実行する。

```sh
python3 tools/reference_docs.py check
```

## ページ構成

各公開ヘッダのページは次の順序で記述する。

1. 概要と、どのような問題に使うか
2. `## 使い方` — そのままコンパイルできる最小例
3. `## API` — 宣言、引数、戻り値、前提条件、計算量をMarkdown表で一覧化する
4. `## 補足` — 境界条件、選択基準、実装上重要な性質
5. `## 検証` — competitive-verifier で使っている問題

フロントマターでは、ドキュメントとヘッダを一対一に対応させる。

```yaml
---
title: セグメント木 (segment_tree)
documentation_of: //lib/segtree/segment_tree.hpp
compile_example: true
---
```

`compile_example: true` を付けると、最初の `cpp` コードブロックが `main` 関数内に
展開され、C++23 と `-I lib` でコンパイル検査される。完結した最小例にはこれを付ける。

API表は原則として「API」「内容」「計算量」の列を使用し、「API」にはテンプレート引数を
含む完全な宣言を記載する。型や用途に応じて「前提」「戻り値」などへ置き換えてもよいが、
公開APIを見出しと本文だけで列挙しない。

## 記述方針

- 区間は半開区間 `[l, r)` と明記する。
- 失敗を表す戻り値、`assert` される前提、空入力の挙動を書く。
- 時間計算量と、重要な場合は空間計算量を書く。
- テンプレート引数に要求される concept や演算を書く。
- コードから読み取れない保証を推測で追加しない。
- 内部実装より、利用者から観測できる挙動を優先する。

`lib/internal/` と `lib/template/` は公開リファレンスの網羅率には含めない。
