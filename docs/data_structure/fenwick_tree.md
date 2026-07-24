---
title: Fenwick Tree (FenwickTree)
documentation_of: //lib/data_structure/fenwick_tree.hpp
compile_example: true
---

可換な加算に対する点更新・区間和を $O(\log n)$ で処理する。`RangeAdd = true` にすると
内部で2本の Fenwick Tree を使い、区間加算・区間和を同じ計算量で処理する。

セグメント木より扱える演算は限られるが、必要なメモリと定数倍が小さい。

## 使い方

```cpp
#include "data_structure/fenwick_tree.hpp"

std::vector<long long> a = {3, 1, 4, 1, 5};
FenwickTree<long long> ft(a);
ft.add(2, 10);              // a[2] += 10
long long x = ft.sum(1, 4); // a[1] + a[2] + a[3]

FenwickTree<long long, true> range_ft(5);
range_ft.add(1, 4, 7);      // a[1], a[2], a[3] に 7 を加算
long long y = range_ft.sum(0, 5);
```

## API

`FenwickTree<T, RangeAdd = false>` — `T` は加減算、ゼロ初期化、整数との乗算をサポートする
値型。区間はすべて半開区間 `[l, r)`。

| API | 内容 | 計算量 |
| --- | --- | --- |
| `FenwickTree(n)` | 長さ `n`、全要素0で構築 | $O(n)$ |
| `FenwickTree(values)` | 初期列から構築 | $O(n)$、`RangeAdd` 時は $O(n\log n)$ |
| `build(values)` | 現在の領域に初期列を構築 | 上記と同じ |
| `at(k)` / `get(k)` / `operator[](k)` | `a[k]` を返す | $O(\log n)$ |
| `set(k, value)` | `a[k] = value` | $O(\log n)$ |
| `add(k, value)` | `a[k] += value` | $O(\log n)$ |
| `add(l, r, value)` | `[l, r)` に加算。`RangeAdd = true` のみ | $O(\log n)$ |
| `sum(r)` / `prod(r)` | `[0, r)` の総和 | $O(\log n)$ |
| `sum(l, r)` / `prod(l, r)` | `[l, r)` の総和 | $O(\log n)$ |
| `all_sum()` / `all_prod()` | 全要素の総和 | $O(\log n)$ |
| `lower_bound(value)` | 累積和が `value` 以上になる最初の添字 | $O(\log n)$ |
| `upper_bound(value)` | 累積和が `value` より大きくなる最初の添字 | $O(\log n)$ |
| `chmax(k, value)` / `chmin(k, value)` | 点の値を必要な場合だけ更新し、更新したかを返す | $O(\log n)$ |

## 補足

- `lower_bound` / `upper_bound` は `RangeAdd = false` の場合だけ使える。各要素が非負で、
  累積和が単調であることが前提。条件を満たす位置がない場合は `n` を返す。
- `lower_bound(k, value)` と `upper_bound(k, value)` は探索基準に `sum(k)` を加え、
  添字 `k` 以降の累積増分を探索する。
- `T` には加算だけでなく、区間和を差し引くための減算が必要。
- 空区間 `sum(l, l)` は `T()` を返す。

## 検証

- [Point Add Range Sum](https://judge.yosupo.jp/problem/point_add_range_sum)
- [AOJ DSL_2_B Range Sum Query](https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_B)
- [AOJ DSL_2_G Range Add Query](https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_G)
- [Vertex Add Path Sum](https://judge.yosupo.jp/problem/vertex_add_path_sum)
- [Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)
