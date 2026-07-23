---
title: 最大流 (mf_graph)
documentation_of: //lib/flow/max_flow.hpp
compile_example: true
---

Dinic 法で有向グラフの最大流を求める。辺追加時に返る ID から容量・現在流量を取得または
変更でき、最大流計算後の残余グラフから最小カットも復元できる。

## 使い方

```cpp
#include "flow/max_flow.hpp"

mf_graph<long long> graph(4);
graph.add_edge(0, 1, 3);
graph.add_edge(0, 2, 2);
graph.add_edge(1, 3, 2);
graph.add_edge(2, 3, 4);

long long maximum = graph.flow(0, 3); // 4
std::vector<bool> source_side = graph.min_cut(0);
```

## API

`mf_graph<Cap>` — `Cap` は容量と流量を表す数値型。

| API | 内容 | 計算量 |
| --- | --- | --- |
| `mf_graph(n)` | `n` 頂点の残余グラフを構築 | $O(V)$ |
| `add_edge(from, to, cap)` | 容量 `cap` の有向辺を追加し ID を返す | ならし $O(1)$ |
| `flow(s, t)` | 現在の残余グラフに最大流を追加して流量を返す | 一般に $O(V^2E)$ |
| `flow(s, t, limit)` | 追加する流量を `limit` までに制限 | 一般に $O(V^2E)$ |
| `get_edge(id)` | `{from, to, cap, flow}` を返す | $O(1)$ |
| `edges()` | 追加順に全辺を返す | $O(E)$ |
| `change_edge(id, cap, flow)` | 辺の容量と現在流量を変更 | $O(1)$ |
| `min_cut(s)` | 残余辺で `s` から到達可能な頂点集合 | $O(V+E)$ |
| `size()` | 頂点数 | $O(1)$ |

## 補足

- 容量は非負、`change_edge` では `0 <= flow <= cap` が必要。
- `flow` は残余グラフを更新する。複数回呼ぶと、その時点から追加で流せた量を返す。
- 最大流計算後の `min_cut(s)` が返す `true` 側が始点側の最小カットになる。
- 自己ループと多重辺を追加できる。
- 無向容量辺が必要な場合は、両方向の辺を別々に追加する。

## 検証

- [AOJ GRL_6_A Maximum Flow](https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_A)
- [AOJ GRL_7_A Bipartite Matching](https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A)
- [Bipartite Matching](https://judge.yosupo.jp/problem/bipartitematching)
