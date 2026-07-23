---
title: Sparse Table (sparse_table)
documentation_of: //lib/sparse_table/sparse_table.hpp
compile_example: true
---

更新のない列に対する冪等な区間演算を、$O(n\log n)$ の前計算後に $O(1)$ で求める。
Range Minimum Query、Range Maximum Query、GCD などに適する。

## 使い方

```cpp
#include "sparse_table/sparse_table.hpp"

std::vector<int> a = {5, 2, 7, 1, 3};
sparse_table<Min<int>> table(a);

int minimum = table.prod(1, 4);  // min(2, 7, 1) == 1
```

## API

`sparse_table<M>` — `M` はモノイドであり、さらに `M::op(x, x) == x` を満たす冪等演算。

| API | 内容 | 計算量 |
| --- | --- | --- |
| `sparse_table(values)` | 長さ $2^k$ の各区間の積を前計算 | $O(n\log n)$ |
| `prod(l, r)` | 半開区間 `[l, r)` の積 | $O(1)$ |

空間計算量は $O(n\log n)$。

## 補足

- クエリでは区間を同じ長さの2区間で重ねて覆う。このため最小値・最大値・GCDのように
  演算が冪等である必要がある。
- 和や積のような非冪等演算には
  `disjoint_sparse_table`、更新が必要なら `segment_tree` を使用する。
- 空区間 `prod(l, l)` は `M::id()` を返す。
- 構築後の要素更新はできない。

## 検証

- [Static RMQ](https://judge.yosupo.jp/problem/staticrmq)
