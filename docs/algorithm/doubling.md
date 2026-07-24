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

| API | 内容 | 計算量 |
| --- | --- | --- |
| `template <class M> concept doubling_monoid = std::is_void_v<M> \|\| monoid<M>;` | ダブリングで `M` が取れる型か（void または monoid）<br>`void` は集約なし（遷移先のみ）、`monoid` は遷移に沿った値の集約を表す。 | コンパイル時制約であり実行時計算量はない |
| `explicit doubling(const std::vector<int> &to) requires(!has_monoid)` | 遷移先のみを前計算する<br>**引数:** `to`: 各頂点から1ステップ後の遷移先 | 頂点数を $n$ として $O(Ln)$ |
| `template <class U> requires has_monoid doubling(const std::vector<int> &to, const std::vector<U> &v)` | 遷移先と各ステップの集約値を前計算する<br>**引数:** `to`: 各頂点から1ステップ後の遷移先、`v`: 各頂点から進む1ステップに対応する値 | 頂点数を $n$ として $O(Ln)$ |
| `auto jump(int f, std::uint64_t k)` | fからkステップ後の遷移先と必要なら集約値を返す | $O(L)=O(\log k)$ |
| `auto solve(int f, std::uint64_t k)` | fからkステップ後の遷移先と必要なら集約値を返す | $O(L)=O(\log k)$ |
| `template <class F> requires has_monoid std::uint64_t max_step(int f, T init, F check)` | check(M::op(init, accumulated)) が真である最大ステップ数を返す<br>check は単調 (真→偽に一度だけ変化) を仮定する | $O(L)$ |
| `template <class F> requires has_monoid std::uint64_t max_step(int f, F check)` | 単位元から開始してcheckが真である最大ステップ数を返す<br>check は単調 (真→偽に一度だけ変化) を仮定する | $O(L)$ |

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
