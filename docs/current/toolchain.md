---
title: 開発ツールの構成
---

# 開発ツールの構成

設定は `mise.toml`・`ruff.toml`・`.clang-format`・`.githooks/pre-commit` にある。
ここにはその**設定意図**を書く。コマンドそのものは [commands.md](../commands.md)。

## mise が単一の入口

必要なツールは `mise.toml` の `[tools]` にまとめ、`mise run setup` で一括導入する。
setup がやることは 4 つ。

1. `mise install`（`[tools]` の宣言をすべて導入）
2. CLI でしか入らないシステムパッケージ（`xclip`・`g++-14`）を apt で導入
3. `git config core.hooksPath .githooks`（pre-commit フックの有効化。リポジトリ毎のローカル設定）
4. `mise run install-shims`

## Python CLI は pipx（実体は uv）で入れる

`oj` / `oj-bundle` / `oj-verify` / `daily` は**import するライブラリではなく CLI アプリ**なので、
`pip` ではなく pipx バックエンドでアプリごとの隔離 venv に入れ、entry point を PATH に通す。
`pip` は共有環境を汚すうえ、PEP 668 の環境では弾かれる。

| 宣言 | 入るコマンド |
| --- | --- |
| `pipx:online-judge-tools` | `oj` |
| `pipx:online-judge-verify-helper` | `oj-bundle`、`oj-verify` |
| `pipx:git+…/daily-problems-cli` | `daily`（stdlib のみで依存なし、git+ 直インストール） |

- `uv` を `[tools]` に置いてあるのは pipx バックエンドの実体だから。uv は隔離 venv 用の Python も
  自前で用意するので、`python` を別途宣言する必要はない（`uv tool install` / `uvx` が速い）。
- **`setuptools<81` のピン**: `oj` は `distutils` / `pkg_resources`（どちらも setuptools 提供）を
  実行時に import するが、Python 3.12+ では stdlib から外れたので各 venv に同梱する必要がある。
  さらに `setuptools>=81` は `pkg_resources` を同梱しなくなったため、上限を切っている
  （`oj-verify` が `pkg_resources` を import する）。
- `uvx_args`（`--with`）と `pipx_args`（`--preinstall`）を両方書いてあるのは、mise が uv の有無で
  経路を変えるため。使われない側は無視される。

## shim

`mise run install-shims` が `~/.local/bin` に `ojd` / `ojn` / `ojc` / `ojg` / `ojb` / `ojt` / `ojs` /
`ojtc` / `ojrc` を生成する。中身は `mise -C <repo> run <task>` を exec するだけの薄いラッパーで、
リポジトリのパス（`config_root`）を埋め込むので**どのディレクトリからでも実行できる**し、
クローン先が変わっても正しく動く。`~/.local/bin` が PATH に無ければ警告を出す。

## workspace/ のタスク設計

`workspace/` で問題を解くための `oj` 系タスクは、ライブラリ開発とは別系統のもの。

- **正名は動詞**（`download` / `new` / `build` / `test` / `submit` / `test-clip` / `random-check` /
  `clean` / `gen-tests`）。旧エイリアス互換の短縮名（`ojd` 等）は `alias` で併設し、shim は短縮名で作る。
- mise タスクはタスク定義位置ではなく **`dir` で指定したディレクトリ**で実行される。
  `oj` 系は `workspace/` で動かす前提なので、各タスクに `dir = "{{config_root}}/workspace"` を置く。
- bundle・compile は**各タスク内にヘルパ関数としてインライン定義**する。CWD をまたぐネストした
  `mise run` を避けるため（`random-check` は `checker/` 配下でも同じ処理を使う）。
- `new` は `a.cpp` を常にテンプレートで上書きする（新しい問題を始める前提）。テストだけ取り直したい
  ときは `download` を使う。URL の埋め込みは sed のメタ文字で壊れないよう awk で行い、
  サンプル取得に成功してから `test/` を差し替える。
- `test` / `random-check` は先頭で **`ulimit -s`** を上げる。システム既定（多くの Linux で 8MB）だと
  再帰の深い解法がローカルでだけ SIGSEGV しうるため。`ulimit` は子プロセスに継承されるので、
  `oj t` や checker が fork/exec するバイナリにも効く。
- `submit` は既定で提出前にローカルテストを走らせ、落ちたら止める（誤提出ガード）。`-f` で省略できる。
- `build -g` はデバッグビルド。最適化を落として ASan/UBSan と `_GLIBCXX_DEBUG` を足す。

## pre-commit フック

`.githooks/pre-commit` が、ステージ済みで追加・変更・コピー・リネームされた `.cpp`/`.hpp`
（`--diff-filter=ACMR`、削除は除外）を clang-format で整形し、**再 stage** する。
コミットには整形後の内容が入る。

clang-format は mise の `[tools]` 管理なので、PATH に shim が無い環境でも解決できるよう
`mise exec -- clang-format` 経由で呼ぶ。mise が無ければ素の `clang-format` にフォールバックし、
どちらも無ければエラーで止める。

## clang-format の設定

`.clang-format` は Google ベース。既定から外している主なものと理由は次のとおり。

| 設定 | 理由 |
| --- | --- |
| `ForEachMacros: [rep, repn, repr, repnr]` | `atcoder.hpp` のループマクロを範囲 for と同様に整形する（`rep (...) { ... }` の括弧前空白など） |
| `MainIncludeChar: AngleBracket` | 主ヘッダ判定を `<...>` 限定にし、basename が一致しただけの引用符ライブラリヘッダが先頭固定されないようにする。include 順は「標準 `<...>` 先頭」に統一 |
| `IncludeCategories`（`"template/template.hpp"` に `Priority: -1`） | `lib/template/{atcoder,library_checker}.hpp` は `<bits/stdc++.h>` を引く `template/template.hpp` を必ず先頭に置く必要がある。ソートを効かせたまま負の優先度で先頭固定する |
| `CommentPragmas: 'competitive-verifier:'` | competitive-verifier の特殊コメント行を折り返させない |

## ruff の設定

`ruff.toml` は `tools/` の Python（リファレンス生成・CI 集計スクリプト）用。実行は `mise run lint`。

- `line-length = 100` — 日本語コメントは**全角幅で数えられる**ので、実測の最長行に合わせた値。
- `select` — 既定（F・E4/E7/E9）に、import 順（I）、行長・空白（E5/W）、非推奨構文の置き換え（UP）、
  バグ検出（B）、簡約（SIM/C4/PIE/FURB）、ruff 固有（RUF）を足している。
- `ignore = ["RUF001", "RUF002", "RUF003"]` — 全角の括弧・記号は日本語のコメントやメッセージとして
  意図的に使っている。
