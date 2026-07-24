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

| API | 内容 | 計算量 |
| --- | --- | --- |
| `using node = std::pair<Key, Value>;` | ヒープに格納する順序基準と付随データの組 | 型エイリアスで実行時計算量はない |
| `std::priority_queue<node, std::vector<node>, std::greater<>> que;` | 要素を保持する優先度付きキュー | `top` は $O(1)$、更新は $O(\log n)$ |
| `bool empty() const` | 空か返す | $O(1)$ |
| `void push(Key key, Value value)` | keyとvalueを追加する | $O(\log n)$ |
| `std::pair<Key, Value> top() const` | 最小keyの要素を返す | $O(1)$ |
| `void pop()` | 最小keyの要素を削除する | $O(\log n)$ |
| `template <class Heap, class Key, class Value> concept decrease_key_heap = requires(Heap &h, Key key, Value value)` | decrease-key（`update`）を持つヒープか<br>`binary_heap` / `fibonacci_heap` は満たし、`dijkstra_priority_queue` は満たさない。 | コンパイル時制約で実行時計算量はない |
| `template <template <class...> class Heap = dijkstra_priority_queue, properly_weighted_graph_type G, class T = graph_weight_t<G>> std::vector<T> shortest_path(const G &g, int s = 0, T inf = std::numeric_limits<T>::max())` | 単一始点最短路（実重み付きグラフはダイクストラ法）<br>**テンプレート引数:** `Heap`: 使用するヒープ。既定は `std::priority_queue` ベースの最小ヒープ。 `binary_heap` / `fibonacci_heap` を渡すと decrease-key 方式に切り替わる。 いずれも `Heap<Key, Value, Comp>`（Key=順序基準, Value=付随データ）形式で `push(key, value)` / `top() -> pair<key, value>` / `pop` / `empty` を持つこと。、`G`: 実重み付きグラフ型（`list_graph<T>` / `csr_graph<T>`、T は非 void）<br>**備考:** 重みなしグラフ（`*_graph<void>`）は下の BFS 版が選ばれる。<br>**備考:** `update` を持つヒープでは頂点ごとにハンドルを保持して decrease-key し、 ヒープ内要素を高々 V 個に保つ。持たないヒープでは緩和のたびに push して 取り出し時に stale をスキップする lazy-deletion 方式になる。 | 二分ヒープでは $O((V+E)\log V)$ |
| `template <weighted_graph_type G, class T = graph_weight_t<G>> std::vector<T> shortest_path_negative(const G &g, int s = 0, T inf = std::numeric_limits<T>::max(), T ninf = std::numeric_limits<T>::lowest())` | 単一始点最短路（負辺ありはベルマンフォード法）<br>**テンプレート引数:** `G`: 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）<br>**備考:** 負閉路から到達できる頂点の距離は `ninf`（既定で `lowest()`）になる。 | $O(VE)$ |
| `template <weighted_graph_type G, class T = graph_weight_t<G>> std::vector<T> shortest_path_spfa(const G &g, int s = 0, T inf = std::numeric_limits<T>::max())` | 単一始点最短路（負辺ありは SPFA）<br>**テンプレート引数:** `G`: 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）<br>**備考:** 負閉路を検出した場合は空の `vector` を返す。<br>**参考:** [https://hogloid.hatenablog.com/entry/20120409/1333973448](https://hogloid.hatenablog.com/entry/20120409/1333973448)、[https://ei1333.github.io/luzhiled/snippets/graph/shortest-path-faster-algorithm.html](https://ei1333.github.io/luzhiled/snippets/graph/shortest-path-faster-algorithm.html) | 平均 $O(E)$、最悪 $O(VE)$ |
| `template <unweighted_graph_type G> std::vector<int> shortest_path(const G &g, int s = 0, int inf = std::numeric_limits<int>::max())` | 単一始点最短路（重みなしグラフは BFS で O(V+E)）<br>**テンプレート引数:** `G`: 重みなしグラフ型（`list_graph<void>` / `csr_graph<void>` のいずれでも可）<br>**備考:** 重みが 1 固定なので priority_queue 不要。`unweighted_graph_type` と `properly_weighted_graph_type` は排他なので、重みなしグラフではこちらが選ばれる。 | $O(V+E)$ |

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
