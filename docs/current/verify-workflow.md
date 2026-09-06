---
title: verify ワークフローの設計
---

# verify ワークフローの設計

`.github/workflows/verify.yml` と `.verify-helper/config.toml` の設計意図。
CI が落ちたときの**調べ方**は [ci.md](ci.md)。

## ジョブ構成

```
setup ──> verify (10 shard) ──> docs-and-check ──> deploy（main のみ）
```

| ジョブ | 役割 |
| --- | --- |
| `setup` | リファレンス生成・ツールのテスト・`docs-check`、`oj-resolve` で `verify_files.json` を作る |
| `verify` | 10 分割して検証を走らせ、shard ごとに `result.json` を上げる |
| `docs-and-check` | 結果をマージし、サイトを組み立て、最終的な合否を出す |
| `deploy` | `main` のときだけ GitHub Pages に公開する |

**必須チェックは `docs-and-check`**。`if: always()` で verify が失敗しても必ず走らせ、失敗を集約して
このジョブ自体の結論に伝播させることで、CI 失敗時のマージを確実にブロックする。

## 失敗を取りこぼさないための仕掛け

- **`fail-fast: false`** — 1 つの shard が失敗しても他をキャンセルしない。巻き添えキャンセルすると
  `result.json` が欠けたまま `docs-and-check` に渡り、不完全な結果で Check が緑になりうる。
- **欠損 shard のガード** — `needs.verify.result != 'success'` なら `docs-and-check` の先頭で即失敗させる。
  competitive-verifier の Check は欠損 shard を検知しないので、ジョブ結論への失敗伝播はこのガードに依存する。
- `SPLIT_SIZE` は **matrix の index 数と必ず一致**させる。

## キャッシュ

### 検証結果（`merged-result.json`）

キーはブランチ名 + SHA。`restore-keys` で「自分のブランチの最新 → `main` → 任意のブランチ」の順に
フォールバックする。ブランチ毎のキーにしてあるのは、失敗している PR が他ブランチの基準を汚さないため。

**常に保存する**（verify が失敗していても）。competitive-verifier は次回、`failure` のテストを
prev-result に関わらず再検証し、`success` のテストだけタイムスタンプで省略する。だから部分的な結果を
保存しても本物の失敗を隠すことはなく、通っている多数のテストの再検証を省ける。

### 問題（テストケース）

`.competitive-verifier/cache` にテストケースとコンパイル済みバイナリが入る。これが無いと重いテストの
再検証のたびにジャッジから再ダウンロードが走り、実行時間を支配する（yosupo の 1 テストで約 107 秒の
ダウンロードが観測された）。

- **shard ごとのキー**。分割ごとにダウンロードする問題が違うので、共有キーだと最後の shard の保存が
  他を上書きしてしまう。
- キーに `run_id` を入れて**毎回新しい不変エントリ**にする（キャッシュは上書きできない）。エントリは
  溜まっていくが、これは意図的で、GitHub のリポジトリ毎 10GB LRU による退避に任せている。
- verify が失敗しても `if: always()` で保存する。部分的なダウンロードキャッシュを次に持ち越すため。

### 週次実行

Actions のキャッシュは**アクセスが無いまま 7 日**で退避される（復元のたびにタイマーが戻る）。
週次の `schedule` は、push の無い週でもキャッシュを温存するための保険であり、同時に外部ジャッジ
（AOJ など）に対する定期的な再チェックでもある。

## AOJ の一時的なタイムアウトを skipped に読み替える

`Reclassify transient AOJ timeouts as skipped` ステップが、verify ジョブのログを読み、
タイムアウト由来のダウンロード失敗を `failure` から `skipped` に書き換える。

- 対象は **AOJ（`judgedat.u-aizu.ac.jp`）だけ**。read/connect timeout が実際に観測されたのはここだけで、
  観測していないパターンまで一般化すると、本物の失敗を黙って握り潰す危険がある。
- `Failed to download` の行はタイムアウト行の数行あとに続くので、タイムアウト行の後ろ 30 行だけを走査する。
- ログ取得は `gh api` で行う。verify のログは ANSI 色付きで、新しい `gh` は `--allow-escape-sequences`
  なしだとエスケープを含むレスポンスの出力を拒否する。古い `gh` にはこのフラグが無いので、
  **付きで試して失敗したら無しで再試行**する。
- 取得できないと一時的なタイムアウトを判別できず Check が落ちるので、失敗は握り潰さず
  `::warning::` で必ず可視化する。

書き換えた結果は各 shard の `result.json` にも反映してから Check に渡す。

## 参考情報として出すもの

合否のゲートは最後の `Check` ステップだけで、次の 2 つは**参考情報**。

- `Report merged result summary` — 落ちているファイルの一覧（`N file(s) still failing`）。
  「どのテストが落ちたか」はこの行で特定できる。
- `Report timing summary` — `tools/verify_timing_summary.py` の出力。基準は退避しておいた `main` の
  結果なので、PR では「main と比べてどう変わったか」になる（基準が無ければ差分なしで合計と上位のみ）。

### 実行時間サマリーの読み方

共有 runner の実行時間は同一内容でも 2 倍程度ぶれるので、**ゲートではなく桁違いの退行を見つけるための数字**。
退行として報告するのは相対にも絶対にも大きいものだけにしてある（ミリ秒のテストはノイズだけで +80% に達する）。

検証パイプラインの性質が出力の形を決めている。

- 前回の結果が有効なテストは省略され、計測値がそのまま引き継がれる。したがって基準との差分は
  **この実行で再実行されたテストの一覧**になる。
- `skipped` の検証は計測値を持たない（`elapsed` は帳簿上のオーバーヘッド、`slowest` は null）ので、
  すべての集計から除外する。
- `elapsed` はテストケースの実行時間の合計で、コンパイルとテストケースのダウンロードは含まない。
  `slowest` は最も遅い単一テストケース。

## oj-resolve の設定

`.verify-helper/config.toml`:

- `read_macros = false` — `test/` は全ファイルが special comments 済みで未使用。`lib/` のヘッダに対する
  無駄な `g++ -dM -E` 呼び出し（oj-resolve の主要コスト）を避ける。
- `CXXFLAGS` は
  [AtCoder の言語アップデート](https://img.atcoder.jp/file/language-update/2025-10/language-list.html)
  に合わせている。
