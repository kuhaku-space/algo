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

| API | 内容 | 計算量 |
| --- | --- | --- |
| `FenwickTree()` | 空のFenwick Treeを構築する | $O(1)$ |
| `FenwickTree(int n)` | 長さnの0列を構築する | $O(n)$ |
| `template <class U> FenwickTree(const std::vector<U> &v)` | 列からFenwick Treeを構築する | RangeAddがfalseなら $O(n)$、trueなら $O(n\log n)$ |
| `T operator[](int i) const` | i番目の値を返す | $O(\log n)$ |
| `T at(int k) const` | k番目の値を返す | $O(\log n)$ |
| `T get(int k) const` | k番目の値を返す | $O(\log n)$ |
| `template <class U> void build(const std::vector<U> &v)` | 列の値を構築する | RangeAddがfalseなら $O(n)$、trueなら $O(n\log n)$ |
| `void set(int k, T val)` | v[k] = val | $O(\log n)$ |
| `void add(int k, T val)` | v[k] += val | $O(\log n)$ |
| `void add(int a, int b, T val) requires RangeAdd` | v[a] ... v[b - 1] += val | $O(\log n)$ |
| `bool chmax(int k, T val)` | chmax(v[k], val) | $O(\log n)$ |
| `bool chmin(int k, T val)` | chmin(v[k], val) | $O(\log n)$ |
| `T all_prod() const` | v[0] + ... + v[n - 1] | $O(\log n)$ |
| `T prod(int k) const` | v[0] + ... + v[k - 1] | $O(\log n)$ |
| `T prod(int a, int b) const` | v[a] + ... + v[b - 1] | $O(\log n)$ |
| `T all_sum() const` | v[0] + ... + v[n - 1] | $O(\log n)$ |
| `T sum(int k) const` | v[0] + ... + v[k - 1] | $O(\log n)$ |
| `T sum(int a, int b) const` | v[a] + ... + v[b - 1] | $O(\log n)$ |
| `int lower_bound(T val) const requires(!RangeAdd)` | 接頭辞和がval以上となる最初の位置を返す | $O(\log n)$ |
| `int lower_bound(int k, T val) const requires(!RangeAdd)` | kからの区間和がval以上となる最初の位置を返す | $O(\log n)$ |
| `int upper_bound(T val) const requires(!RangeAdd)` | 接頭辞和がvalより大きくなる最初の位置を返す | $O(\log n)$ |
| `int upper_bound(int k, T val) const requires(!RangeAdd)` | kからの区間和がvalより大きくなる最初の位置を返す | $O(\log n)$ |

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
