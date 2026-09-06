---
title: 決定 0004 「付随データなし」の void を monostate に正規化する
---

# 0004. 「付随データなし」の `void` を `monostate` に正規化する

## 決定

「付随データなし」を表す型引数 `void` は、部分特殊化で本体を分けず
`std::conditional_t<std::is_void_v<V>, std::monostate, V>` に正規化して実装を 1 本化する。
API の差は `if constexpr`、空メンバは `[[no_unique_address]]` で吸収する。例: `radix_heap`、`doubling`。

ただし `void` で**別のデータ構造**を選ぶ場合は部分特殊化のままにする
（`matrix_graph<void>` が `std::vector<std::vector<bool>>` を持つなど）。

## 理由

部分特殊化で分けると本体が二重になり、片方だけ直したバグや機能追加漏れが起きる。
`monostate` への正規化ならデータの持ち方が変わるだけで、アルゴリズムは 1 つで済む。
`[[no_unique_address]]` があるのでサイズ上の損もない。

一方、格納するデータ構造そのものが変わるケースでは共通化しても本体がほぼ分岐だらけになり、
1 本化の利点が消える。そこは特殊化のほうが素直。

## 影響

現行の規則は [current/coding-style.md](../current/coding-style.md) の「ドメイン別の規約」。
