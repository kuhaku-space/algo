---
title: Union-Find (union_find)
documentation_of: //lib/union_find/union_find.hpp
compile_example: true
---

要素の集合を併合し、2要素が同じ連結成分に属するかを管理する素集合データ構造。
経路圧縮とサイズ併合により、各操作をならし $O(\alpha(n))$ で処理する。

## 使い方

```cpp
#include "union_find/union_find.hpp"

union_find uf(5);
uf.unite(0, 1);
uf.unite(1, 3);

bool connected = uf.same(0, 3);  // true
int component_size = uf.size(0); // 3
int components = uf.rank();      // 3
```

## API

| API | 内容 | 計算量 |
| --- | --- | --- |
| `union_find(n)` | `0` から `n-1` を独立した集合として構築 | $O(n)$ |
| `root(x)` / `get_root(x)` | `x` の代表元を返し、経路圧縮する | ならし $O(\alpha(n))$ |
| `same(x, y)` / `is_same(x, y)` | 同じ集合に属するか | ならし $O(\alpha(n))$ |
| `unite(x, y)` | 2集合を併合し、実際に併合したかを返す | ならし $O(\alpha(n))$ |
| `size(x)` / `get_size(x)` | `x` を含む集合の要素数 | ならし $O(\alpha(n))$ |
| `is_root(x)` | `x` が代表元か | $O(1)$ |
| `leaders()` | 全代表元を返す | $O(n)$ |
| `rank()` | 現在の連結成分数を返す | $O(1)$ |
| `unite(x, y, callback)` | 併合後の代表元をコールバックへ渡す | ならし $O(\alpha(n))$ |

3引数のコールバックには `(new_root, old_root)`、または
`(new_root, old_root, swapped)` が渡る。既に同じ集合の場合もコールバックは呼ばれる。

## 補足

- 代表元は併合順に依存するため、特定の添字になるとは限らない。
- `operator[]` は内部の親または負の集合サイズを直接参照する低レベルAPI。通常は
  `root`、`size`、`same` を使う。
- 現在の実装では、コールバック付き `unite` は `rank()` の連結成分数を更新しない。
  `rank()` を利用する場合はコールバックなしの `unite(x, y)` を使用する。
- 併合を巻き戻す必要がある場合は `undo_union_find.hpp` を使用する。

## 検証

- [Unionfind](https://judge.yosupo.jp/problem/unionfind)
- [AOJ DSL_1_A Disjoint Set](https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_A)
