---
title: 単一始点最短路 (shortest_path)
documentation_of: //lib/graph/shortest_path.hpp
compile_example: true
---

グラフの重みに応じた単一始点最短路を提供する。非負重みには Dijkstra 法、負辺を含む場合は
Bellman–Ford 法または SPFA、重みなしグラフには BFS を使用する。

`list_graph<T>` と `csr_graph<T>` の両方に対応する。

## 使い方

```cpp
#include "graph/shortest_path.hpp"

list_graph<long long> graph(4);
graph.add_edge(0, 1, 2);
graph.add_edge(1, 2, 3);
graph.add_edge(0, 2, 10);

auto distance = shortest_path(graph, 0);
// distance[2] == 5
```

## API

| API | 対象 | 戻り値 | 計算量 |
| --- | --- | --- | --- |
| `shortest_path(graph, s, inf)` | 非負重み付きグラフ | 各頂点への距離 | 既定ヒープで $O((V+E)\log E)$ |
| `shortest_path<Heap>(...)` | 非負重み、ヒープ差し替え | 各頂点への距離 | ヒープに依存 |
| `shortest_path_negative(graph, s, inf, ninf)` | 負辺を含むグラフ | 距離。負閉路の影響下は `ninf` | $O(VE)$ |
| `shortest_path_spfa(graph, s, inf)` | 負辺を含むグラフ | 距離。負閉路検出時は空列 | 最悪 $O(VE)$ |
| `shortest_path(graph, s, inf)` | 重みなしグラフ | 辺数による距離 | $O(V+E)$ |

到達不能な頂点には `inf` が格納される。既定値は戻り値型の
`std::numeric_limits<T>::max()`。

## 補足

- Dijkstra 版では全辺の重みが非負でなければならない。この条件は実行時には検査しない。
- 距離の加算が型の範囲を超えないようにする。必要なら問題の上限より十分大きく、加算しても
  オーバーフローしない `inf` を渡す。
- `shortest_path_negative` は始点から到達可能な負閉路と、そこから到達できる頂点を
  `ninf` にする。到達不能な負閉路は結果に影響しない。
- `shortest_path_spfa` は実用上速い場合があるが、最悪計算量の保証は Bellman–Ford と同じ。
- `binary_heap` や `fibonacci_heap` のように `update` を持つヒープをテンプレート引数に
  渡すと decrease-key 方式を使用する。

## 検証

- [AOJ GRL_1_A Single Source Shortest Path](https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_A)
- [AOJ GRL_1_B Single Source Shortest Path (Negative Edges)](https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_B)
