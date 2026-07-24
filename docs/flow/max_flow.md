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

| API | 内容 | 計算量 |
| --- | --- | --- |
| `mf_graph()` | 0頂点のグラフを構築する | $O(1)$ |
| `explicit mf_graph(int n)` | n頂点0辺のグラフを構築する | $O(n)$ |
| `int size() const` | 頂点数を返す | $O(1)$ |
| `int add_edge(int from, int to, Cap cap)` | 容量capの有向辺を追加して辺IDを返す | 償却 $O(1)$ |
| `struct edge` | 追加した辺の現在状態 | 各フィールドへのアクセスは $O(1)$ |
| `int from, to;` | 辺の始点と終点 | $O(1)$ で参照可能 |
| `Cap cap, flow;` | 辺の容量と現在の流量 | $O(1)$ で参照可能 |
| `edge get_edge(int i)` | 指定した辺の現在状態を返す | $O(1)$ |
| `std::vector<edge> edges()` | 全辺の現在状態を追加順で返す | 辺数を $E$ として $O(E)$ |
| `void change_edge(int i, Cap new_cap, Cap new_flow)` | 辺の容量と現在流量を変更する | $O(1)$ |
| `Cap flow(int s, int t)` | sからtへ流せるだけ流して追加流量を返す | 頂点数を $V$、辺数を $E$ として $O(V^2E)$ |
| `Cap flow(int s, int t, Cap flow_limit)` | sからtへflow_limitまで流して追加流量を返す | $O(V^2E)$ |
| `std::vector<bool> min_cut(int s)` | 残余グラフでsから到達可能な頂点集合を返す | $O(V+E)$ |

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
