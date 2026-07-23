---
title: セグメント木 (segment_tree)
documentation_of: //lib/segtree/segment_tree.hpp
compile_example: true
---

モノイドで表せる区間積と点更新を $O(\log n)$ で処理する。和・最小値・最大値に加え、
行列積や関数合成のような非可換演算にも利用できる。

`max_right` / `min_left` により、「区間積が条件を満たす境界」を二分探索なしで求められる。

## 使い方

```cpp
#include "segtree/segment_tree.hpp"

std::vector<long long> a = {2, 1, 4, 3};
segment_tree<Add<long long>> seg(a);

long long sum = seg.prod(1, 4);  // 1 + 4 + 3
seg.set(2, 10);
seg[0] = 5;                     // set(0, 5) と同じ

int r = seg.max_right(0, [](long long x) { return x <= 12; });
```

## API

`segment_tree<M>` — `M` は `value_type`、`id()`、`op(lhs, rhs)` を持つ `monoid`。
区間は半開区間 `[l, r)`。

| API | 内容 | 計算量 |
| --- | --- | --- |
| `segment_tree(n, initial)` | 長さ `n`、各要素 `initial` で構築 | $O(n)$ |
| `segment_tree(values)` | 初期列から構築 | $O(n)$ |
| `assign(n, initial)` | 確保済み領域を再利用して長さと値を設定 | $O(C)$ |
| `get(k)` / `at(k)` / `operator[](k)` | 点の値を取得 | $O(1)$ |
| `set(k, value)` | 点を更新 | $O(\log n)$ |
| `reset(k)` | 点を `M::id()` に戻す | $O(\log n)$ |
| `prod(l, r)` | `M::op(a[l], ..., a[r-1])` | $O(\log n)$ |
| `all_prod()` | 全区間の積 | $O(1)$ |
| `max_right(l, f)` | `f(prod(l, r))` が真である最大の `r` | $O(\log n)$ |
| `min_left(r, f)` | `f(prod(l, r))` が真である最小の `l` | $O(\log n)$ |

`assign` の $C$ は内部で確保済みの葉数。`n` はその容量以下でなければならない。

## 補足

- `M::op` は結合的で、`M::id()` は左右の単位元であること。可換性は不要。
- 空区間の `prod(l, l)` は `M::id()` を返す。
- `max_right` / `min_left` では `f(M::id()) == true` が必要。また、区間を伸ばしたとき
  `f` が真から偽へ一度だけ変わる単調性を仮定する。
- 非 `const` の `operator[]` は更新用プロキシを返す。読み取り時は値へ変換され、
  代入時は `set` と同じく祖先を更新する。

## 検証

- [Point Set Range Composite](https://judge.yosupo.jp/problem/point_set_range_composite)
- [Static RMQ / AOJ DSL_2_A](https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_A)
- [Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)
