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
| `union_find() = default;` | 空の Union-Find を作る | $O(1)$ |
| `explicit union_find(int _n)` | `n` 個の単集合を作る | $O(n)$ |
| `const int &operator[](std::size_t x) const` | 頂点 `x` の内部表現を読み取り専用で返す | $O(1)$ |
| `int &operator[](std::size_t x)` | 頂点 `x` の内部表現を返す | $O(1)$ |
| `int root(int x)` | `x` の代表を返し、経路圧縮する | 償却 $O(\alpha(n))$ |
| `int get_root(int x)` | `root(x)` の別名 | 償却 $O(\alpha(n))$ |
| `bool is_root(int x) const` | `x` が集合の代表なら true を返す | $O(1)$ |
| `bool same(int x, int y)` | `x`, `y` が同じ集合なら true を返す | 償却 $O(\alpha(n))$ |
| `bool is_same(int x, int y)` | `same(x, y)` の別名 | 償却 $O(\alpha(n))$ |
| `int rank()` | 現在の連結成分数を返す | $O(1)$ |
| `int size(int x)` | `x` が属する集合の要素数を返す | 償却 $O(\alpha(n))$ |
| `int get_size(int x)` | `size(x)` の別名 | 償却 $O(\alpha(n))$ |
| `std::vector<int> leaders()` | 全ての集合の代表を返す | $O(n)$ |
| `bool unite(int x, int y)` | `x`, `y` の集合を併合する<br>**戻り値:** 新たに併合したなら true | 償却 $O(\alpha(n))$ |
| `template <class F> requires std::invocable<F, int, int, bool> bool unite(int x, int y, F f)` | `x`, `y` を併合し、代表と入れ替えの有無を `f(x, y, swapped)` に渡す<br>**戻り値:** 新たに併合したなら true | 償却 $O(\alpha(n))$（`f` の実行時間を除く） |
| `template <class F> requires std::invocable<F, int, int> bool unite(int x, int y, F f)` | `x`, `y` を併合し、併合後の代表を `f(x, y)` に渡す<br>**戻り値:** 新たに併合したなら true | 償却 $O(\alpha(n))$（`f` の実行時間を除く） |

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
