---
title: ドキュメント索引
---

# ドキュメント索引

競技プログラミング用の C++23 ヘッダオンリーライブラリ。`lib/` に実装、`test/` に
[competitive-verifier](https://github.com/competitive-verifier/competitive-verifier)
用の検証ファイルを置く。

> **注意**: ここに並ぶ文書はすべて**このライブラリ自体の仕様・開発方針**であり、
> 競技プログラミングの**問題を解くときには参照しない**。

**必要な文書だけを読む。`docs/` 以下を再帰的に全部読まない。**

## タスク別の入口

| やること | 読む文書 |
| --- | --- |
| 検査コマンドを走らせる | [commands.md](commands.md) |
| 置き場所・全体像を知る | [current/overview.md](current/overview.md) |
| ヘッダを書く・直す | [current/coding-style.md](current/coding-style.md) |
| テストや verify を足す | [current/testing.md](current/testing.md) |
| 公開リファレンスの文章を直す | [current/documentation.md](current/documentation.md) → [current/reference-style.md](current/reference-style.md) |
| API を壊す変更をする | [current/change-policy.md](current/change-policy.md) |
| コミット・PR を作る | [current/git-workflow.md](current/git-workflow.md) |
| CI の失敗を追う | [current/ci.md](current/ci.md) |
| ツールの設定を触る（mise・clang-format・ruff・フック） | [current/toolchain.md](current/toolchain.md) |
| `tools/` のリファレンス生成を直す | [current/reference-pipeline.md](current/reference-pipeline.md) |
| `.github/workflows/verify.yml` を直す | [current/verify-workflow.md](current/verify-workflow.md) |

## docs/current/ — 現行の方針

| 文書 | 内容 |
| --- | --- |
| [overview.md](current/overview.md) | ディレクトリ構成、include ルール、データ構造の置き場所 |
| [coding-style.md](current/coding-style.md) | 命名（型は PascalCase）、C++20/23 の使い方、グラフ・ヒープ・`void` の規約、フォーマット |
| [testing.md](current/testing.md) | ランダムテストでの突き合わせ、verify 用問題の選び方、ヘッダ変更時の逆依存チェック |
| [documentation.md](current/documentation.md) | リファレンスをヘッダの `///` だけから生成する運用 |
| [reference-style.md](current/reference-style.md) | リファレンス執筆ガイド（タグ・書き方・ページ構成） |
| [change-policy.md](current/change-policy.md) | 破壊的変更の進め方、計算量を悪化させない制約 |
| [git-workflow.md](current/git-workflow.md) | ブランチ、自動コミット、PR と auto-merge |
| [ci.md](current/ci.md) | CI の失敗をローカルで再現する手順、ログを狭く取る方法 |
| [toolchain.md](current/toolchain.md) | `mise.toml`・`.clang-format`・`ruff.toml`・pre-commit フックの設定意図 |
| [reference-pipeline.md](current/reference-pipeline.md) | `tools/` のリファレンス生成・検査・サイト組み立ての設計 |
| [verify-workflow.md](current/verify-workflow.md) | `verify.yml` のジョブ構成・キャッシュ・AOJ タイムアウトの扱い |

## docs/decisions/ — 決定の記録

なぜそうしているかを残したもの。現行の規則そのものは `docs/current/` にある。

| 文書 | 決定 |
| --- | --- |
| [0001](decisions/0001-data-structure-directories.md) | データ構造のディレクトリを増やさない |
| [0002](decisions/0002-no-backward-compatibility.md) | 後方互換性のために妥協しない |
| [0003](decisions/0003-generated-reference-only.md) | リファレンスはヘッダコメントだけから生成する |
| [0004](decisions/0004-void-type-parameter.md) | 「付随データなし」の `void` を `monostate` に正規化する |

## そのほか

| パス | 内容 |
| --- | --- |
| [reference.toml](reference.toml) | リファレンス検査のしきい値設定（`tools/reference/check.py` が読む） |
| [parser/aoj-parsing-problems.md](parser/aoj-parsing-problems.md) | AOJ 構文解析問題の verify 状況と必要ライブラリの調査 |
| [archive/](archive/) | 役目を終えた文書。歴史的経緯が要るときだけ読む |
| `generated/` | `mise run docs` の生成物。Git 管理外。人が編集しない |

利用者向けの説明（ライブラリの一覧、使い方）は [README.md](../README.md) にある。
