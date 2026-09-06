---
title: テストと verify
---

# テストと verify

## 正しさの確かめ方

- 正しさは**ランダムテストで naive 実装と突き合わせる**。
- `test/` の `*.test.cpp` には先頭に検証用問題の URL を書き、competitive-verifier が
  ジャッジに対して実行する。

## verify 用問題の選び方

1. Library Checker
2. yukicoder
3. AOJ

この順で探す。素直に対応する問題がなければ **verify は保留**する
（competitive-verifier の UNIT_TEST は使わない）。

## ヘッダを変更したとき

まずローカルで構文チェックする。CI ログを取りに行くより速く、失敗の大半はここで再現できる。

```sh
g++ -std=c++23 -I lib -Wall -Wextra -fsyntax-only <test_file>
```

そのヘッダを使う test を洗い出してまとめて確認する（逆依存チェック）。

```sh
grep -rl <header_basename> lib test | grep '\.test\.cpp$' \
  | xargs -I{} g++ -std=c++23 -I lib -fsyntax-only {}
```

transitive な依存は `oj-bundle <test>` で展開して確認する。

標準ヘッダの暗黙依存を外してテストが壊れたら、テスト側に明示 include を補う
（[coding-style.md](coding-style.md)）。

## CI

CI の失敗を追う手順とトークンを使わない調べ方は [ci.md](ci.md)。
