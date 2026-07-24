#pragma once
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief shortest_path の既定ヒープ（std::priority_queue ベースの最小ヒープ）
/// @details 順序基準 `Key`（距離）・付随データ `Value`（頂点）を受け取り、`Key` 最小を
///          ルートにする。`binary_heap` / `fibonacci_heap` と同じ template-template 形式
///          （`Heap<Key, Value, Comp>`）で渡せるよう薄く包む。decrease-key は持たない。
/// @complexity 各更新は $O(\log n)$、`empty` と `top` は $O(1)$
template <class Key, class Value, class Comp = std::less<>>
struct dijkstra_priority_queue {
    /// @brief ヒープに格納する順序基準と付随データの組
    /// @complexity 型エイリアスで実行時計算量はない
    using node = std::pair<Key, Value>;
    /// @brief 要素を保持する優先度付きキュー
    /// @complexity `top` は $O(1)$、更新は $O(\log n)$
    std::priority_queue<node, std::vector<node>, std::greater<>> que;

    /// @brief 空か返す
    /// @complexity $O(1)$
    bool empty() const { return que.empty(); }

    /// @brief keyとvalueを追加する
    /// @complexity $O(\log n)$
    void push(Key key, Value value) { que.emplace(key, value); }

    /// @brief 最小keyの要素を返す
    /// @complexity $O(1)$
    std::pair<Key, Value> top() const { return que.top(); }

    /// @brief 最小keyの要素を削除する
    /// @complexity $O(\log n)$
    void pop() { que.pop(); }
};

/// @brief decrease-key（`update`）を持つヒープか
/// @details `binary_heap` / `fibonacci_heap` は満たし、`dijkstra_priority_queue` は満たさない。
/// @complexity コンパイル時制約で実行時計算量はない
template <class Heap, class Key, class Value>
concept decrease_key_heap = requires(Heap &h, Key key, Value value) {
    requires requires(decltype(h.push(key, value)) handle) { h.update(handle, key); };
};

/// @brief 単一始点最短路（実重み付きグラフはダイクストラ法）
/// @tparam Heap 使用するヒープ。既定は `std::priority_queue` ベースの最小ヒープ。
///         `binary_heap` / `fibonacci_heap` を渡すと decrease-key 方式に切り替わる。
///         いずれも `Heap<Key, Value, Comp>`（Key=順序基準, Value=付随データ）形式で
///         `push(key, value)` / `top() -> pair<key, value>` / `pop` / `empty` を持つこと。
/// @tparam G 実重み付きグラフ型（`list_graph<T>` / `csr_graph<T>`、T は非 void）
/// @note 重みなしグラフ（`*_graph<void>`）は下の BFS 版が選ばれる。
/// @note `update` を持つヒープでは頂点ごとにハンドルを保持して decrease-key し、
///       ヒープ内要素を高々 V 個に保つ。持たないヒープでは緩和のたびに push して
///       取り出し時に stale をスキップする lazy-deletion 方式になる。
/// @complexity 二分ヒープでは $O((V+E)\log V)$
template <template <class...> class Heap = dijkstra_priority_queue, properly_weighted_graph_type G,
          class T = graph_weight_t<G>>
std::vector<T> shortest_path(const G &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    int n = g.size();
    // key = 距離（順序基準）、value = 頂点（付随データ）。greater<> で距離最小をルートにする。
    using heap_type = Heap<T, int, std::greater<>>;
    std::vector<T> dists(n, inf);
    heap_type heap;
    dists[s] = T();

    if constexpr (decrease_key_heap<heap_type, T, int>) {
        // decrease-key 方式: 頂点ごとにハンドルを保持する。
        using node_ptr = decltype(heap.push(T(), 0));
        std::vector<node_ptr> handle(n, node_ptr{});
        handle[s] = heap.push(T(), s);
        while (!heap.empty()) {
            auto [d, v] = heap.top();
            heap.pop();
            handle[v] = node_ptr{};  // 確定済みの印（再度ヒープに入れない）
            for (auto &e : g[v]) {
                int to = e.to();
                if (dists[to] <= d + e.weight()) continue;
                dists[to] = d + e.weight();
                if (handle[to]) heap.update(handle[to], dists[to]);
                else handle[to] = heap.push(dists[to], to);
            }
        }
    } else {
        // lazy-deletion 方式: 緩和のたびに push し、取り出し時に stale をスキップする。
        heap.push(T(), s);
        while (!heap.empty()) {
            auto [d, v] = heap.top();
            heap.pop();
            if (dists[v] < d) continue;
            for (auto &e : g[v]) {
                int to = e.to();
                if (d + e.weight() < dists[to]) {
                    dists[to] = d + e.weight();
                    heap.push(dists[to], to);
                }
            }
        }
    }
    return dists;
}

/// @brief 単一始点最短路（負辺ありはベルマンフォード法）
/// @note 負閉路から到達できる頂点の距離は `ninf`（既定で `lowest()`）になる。
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity $O(VE)$
template <weighted_graph_type G, class T = graph_weight_t<G>>
std::vector<T> shortest_path_negative(const G &g, int s = 0, T inf = std::numeric_limits<T>::max(),
                                      T ninf = std::numeric_limits<T>::lowest()) {
    int n = g.size();
    std::vector<T> dists(n, inf);
    dists[s] = T();
    // 前半 n-1 回で最短距離を確定、後半 n-1 回で負閉路の影響を ninf として伝播する。
    bool updated = true;
    for (int count = 0; updated && count < 2 * n - 1; ++count) {
        updated = false;
        for (int i = 0; i < n; ++i) {
            if (dists[i] == inf) continue;
            for (auto &e : g[i]) {
                if (dists[i] == ninf || dists[i] + e.weight() < dists[e.to()]) {
                    if (dists[e.to()] == ninf) continue;
                    updated = true;
                    // n 回目以降の更新は負閉路に由来するので ninf にする。
                    if (count >= n - 1) dists[e.to()] = ninf;
                    else dists[e.to()] = dists[i] + e.weight();
                }
            }
        }
    }
    return dists;
}

/// @brief 単一始点最短路（負辺ありは SPFA）
/// @note 負閉路を検出した場合は空の `vector` を返す。
/// @see https://hogloid.hatenablog.com/entry/20120409/1333973448
/// @see https://ei1333.github.io/luzhiled/snippets/graph/shortest-path-faster-algorithm.html
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity 平均 $O(E)$、最悪 $O(VE)$
template <weighted_graph_type G, class T = graph_weight_t<G>>
std::vector<T> shortest_path_spfa(const G &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    int n = g.size();
    std::vector<T> dists(n, inf);
    std::vector<bool> pending(n, false);
    std::vector<int> times(n, 0);
    std::queue<int> que;
    dists[s] = T();
    pending[s] = true;
    ++times[s];
    que.emplace(s);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        pending[p] = false;
        for (auto &e : g[p]) {
            if (!(dists[p] + e.weight() < dists[e.to()])) continue;
            dists[e.to()] = dists[p] + e.weight();
            if (!pending[e.to()]) {
                if (++times[e.to()] >= n) return std::vector<T>();
                pending[e.to()] = true;
                que.emplace(e.to());
            }
        }
    }
    return dists;
}

/// @brief 単一始点最短路（重みなしグラフは BFS で O(V+E)）
/// @tparam G 重みなしグラフ型（`list_graph<void>` / `csr_graph<void>` のいずれでも可）
/// @note 重みが 1 固定なので priority_queue 不要。`unweighted_graph_type` と
///       `properly_weighted_graph_type` は排他なので、重みなしグラフではこちらが選ばれる。
/// @complexity $O(V+E)$
template <unweighted_graph_type G>
std::vector<int> shortest_path(const G &g, int s = 0, int inf = std::numeric_limits<int>::max()) {
    std::vector<int> dists(g.size(), inf);
    std::queue<int> que;
    dists[s] = 0;
    que.emplace(s);
    while (!que.empty()) {
        auto v = que.front();
        que.pop();
        for (auto &e : g[v]) {
            if (dists[v] + 1 < dists[e.to()]) {
                dists[e.to()] = dists[v] + 1;
                que.emplace(e.to());
            }
        }
    }
    return dists;
}
