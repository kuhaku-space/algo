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

| API | 内容 | 計算量 |
| --- | --- | --- |
| `segment_tree()` | 空の木を構築する | $O(1)$ |
| `explicit segment_tree(int n, T e = M::id())` | n要素をeで初期化する | $O(n)$ |
| `template <class U> explicit segment_tree(const std::vector<U> &v)` | 列vから構築する | $O(n)$ |
| `void assign(int n, T e = M::id())` | 確保済み領域を保ったままn要素をeで埋め直す | $O(n)$ |
| `const T &operator[](int k) const` | k番目の値をconst参照で返す | $O(1)$ |
| `_segment_tree_reference operator[](int k)` | k番目を参照・代入できるproxyを返す | 取得は $O(1)$、代入は $O(\log n)$ |
| `T at(int k) const` | k番目の値を返す | $O(1)$ |
| `T get(int k) const` | k番目の値を返す | $O(1)$ |
| `void set(int k, T val)` | k番目をvalへ変更する | $O(\log n)$ |
| `void reset(int k)` | k番目を単位元へ戻す | $O(\log n)$ |
| `T all_prod() const` | 全要素の積を返す | $O(1)$ |
| `T prod(int a, int b) const` | 半開区間[a,b)の積を返す | $O(\log n)$ |
| `template <class F> int max_right(F f) const` | 0から右へ述語fが真である最大境界を返す | $O(\log n)$ |
| `template <class F> int max_right(int l, F f) const` | lから右へ述語fが真である最大境界を返す | $O(\log n)$ |
| `template <class F> int min_left(F f) const` | nから左へ述語fが真である最小境界を返す | $O(\log n)$ |
| `template <class F> int min_left(int r, F f) const` | rから左へ述語fが真である最小境界を返す | $O(\log n)$ |

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
