---
title: ダブリング (doubling)
documentation_of: //lib/algorithm/doubling.hpp
compile_example: true
---

写像を繰り返し適用した遷移先を $O(\log k)$ で求める。各頂点から $2^i$ 回進んだ先を
前計算するため、関数グラフ上のジャンプや巨大な回数のシミュレーションに使える。

モノイドを指定すると、遷移先だけでなく通過した頂点に対応する値も同じ順序で集約できる。

## 使い方

```cpp
#include "algorithm/doubling.hpp"
#include "segtree/monoid.hpp"

std::vector<int> to = {1, 2, 0};

doubling<60> next(to);
int destination = next.jump(0, 5);  // 0 -> 1 -> 2 -> 0 -> 1 -> 2

std::vector<long long> cost = {10, 20, 30};
doubling<60, Add<long long>> with_sum(to, cost);
auto [vertex, total] = with_sum.solve(0, 5);  // vertex == 2, total == 90
```

`to[v] == -1` は遷移先が存在しないことを表す。以後のジャンプ先も `-1` になる。

## API

`doubling<L, M>` — `L` は前計算するビット数、`M` は集約用モノイド。既定の `M = void`
では遷移先だけを扱う。

| API | 内容 | 計算量 |
| --- | --- | --- |
| `doubling(to)` | `M = void` 用。遷移表を構築 | $O(nL)$ |
| `doubling(to, values)` | 各1ステップに対応する値と集約表を構築 | $O(nL)$ |
| `jump(from, k)` | `k` ステップ後を返す。モノイド指定時は `{遷移先, 集約値}` | $O(L)$ |
| `solve(from, k)` | `jump` と同じ | $O(L)$ |
| `max_step(from, init, check)` | `check(op(init, accumulated))` が真である最大ステップ数 | $O(L)$ |
| `max_step(from, check)` | `init = M::id()` とした上記の短縮形 | $O(L)$ |

空間計算量は、遷移先だけなら $O(nL)$、モノイド指定時は遷移表と集約表を合わせて
$O(nL)$。

## 補足

- `0 <= k < 2^L` を満たす必要がある。必要な最大ジャンプ数に合わせて `L` を指定する。
- 集約値 `values[v]` は、頂点 `v` から次の頂点へ進む1ステップに対応する。
- `M::op` は結合的で、`M::id()` が単位元でなければならない。非可換モノイドでも遷移順を
  保って集約する。
- `max_step` は `M` を指定した場合だけ使える。`check` は集約値に対して真から偽へ一度だけ
  変化する単調な述語であること。
- `from == -1` も許され、ジャンプ先は `-1` のままになる。

## 検証

- [AOJ 2320 Infinity Maze](https://onlinejudge.u-aizu.ac.jp/problems/2320)
- [yukicoder No.1013](https://yukicoder.me/problems/no/1013)
- [yukicoder No.1097](https://yukicoder.me/problems/no/1097)
- [yukicoder No.1242](https://yukicoder.me/problems/no/1242)
- [yukicoder No.1977](https://yukicoder.me/problems/no/1977)
