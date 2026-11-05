#pragma once
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
#include "internal/internal_csr.hpp"

/// @brief 最小費用流
/// @details 有向辺からなるグラフに対し、最小費用流と流量・最小費用の折れ線を逐次最短路法で計算する。
/// 負コストの辺も扱える（負閉路は不可）。`flow`・`slope` は何回でも呼べ、2回目以降は
/// その時点の流れを保ったまま追加で流した量と追加の費用を返す。
/// @note 残余グラフに負コストの辺があるとき（負コスト辺がある、または既に流している）は、
/// 呼び出しごとに初期ポテンシャルを Bellman-Ford 法で求めるため $O(nm)$ が加わる。
/// @tparam Cap 容量の型
/// @tparam Cost コストの型
template <class Cap, class Cost>
struct MinCostFlow {
    /// @brief 0頂点のグラフを構築する
    /// @complexity $O(1)$
    MinCostFlow() : n(0) {}

    /// @brief n頂点0辺のグラフを構築する
    /// @param n 頂点数
    /// @complexity $O(1)$
    explicit MinCostFlow(int _n) : n(_n) {}

    /// @brief 頂点数を返す
    /// @return 頂点数
    /// @complexity $O(1)$
    int size() const { return n; }

    /// @brief 容量と単位流量あたりのコストを持つ有向辺を追加する
    /// @param from 始点。$0\le from<n$
    /// @param to 終点。$0\le to<n$
    /// @param cap 非負の容量
    /// @param cost 単位コスト。負でもよいが、負閉路を作ってはならない
    /// @return 追加した辺のID
    /// @complexity 償却 $O(1)$
    int add_edge(int from, int to, Cap cap, Cost cost) {
        assert(0 <= from && from < n);
        assert(0 <= to && to < n);
        assert(0 <= cap);
        int m = int(_edges.size());
        _edges.emplace_back(from, to, cap, 0, cost);
        return m;
    }

    /// @brief 追加した辺の現在状態
    /// @details `from`、`to`、容量 `cap`、現在の流量 `flow`、
    /// 単位流量あたりのコスト `cost` を保持する。
    /// @complexity 構築・各フィールドへのアクセスは $O(1)$
    struct Edge {
        /// @brief 辺の始点と終点
        /// @complexity $O(1)$ で参照可能
        int from, to;
        /// @brief 辺の容量と現在の流量
        /// @complexity $O(1)$ で参照可能
        Cap cap, flow;
        /// @brief 単位流量あたりのコスト
        /// @complexity $O(1)$ で参照可能
        Cost cost;

        /// @brief 辺の状態を構築する
        /// @param _from 始点
        /// @param _to 終点
        /// @param _cap 容量
        /// @param _flow 現在の流量
        /// @param _cost 単位流量あたりのコスト
        /// @complexity $O(1)$
        constexpr Edge(int _from, int _to, Cap _cap, Cap _flow, Cost _cost)
            : from(_from), to(_to), cap(_cap), flow(_flow), cost(_cost) {}
    };

    /// @brief 指定した辺の現在状態を返す
    /// @param i `add_edge` が返した辺ID
    /// @return i番目に追加した辺の現在状態
    /// @complexity $O(1)$
    Edge get_edge(int i) const {
        int m = int(_edges.size());
        assert(0 <= i && i < m);
        return _edges[i];
    }

    /// @brief 全辺の現在状態を追加順で返す
    /// @return 辺状態の列
    /// @complexity 追加した辺数を $m$ として $O(m)$
    std::vector<Edge> edges() const { return _edges; }

    /// @brief sからtへ流せるだけ流し、流量と最小費用を返す
    /// @param s 始点
    /// @param t 終点。sとは異なる頂点
    /// @return 追加で流した量と追加の最小費用の組
    /// @complexity 流量を $F$、頂点数を $n$、辺数を $m$ として
    /// $O(F(n+m)\log(n+m))$。残余グラフに負コストの辺があれば $O(nm)$ が加わる
    std::pair<Cap, Cost> flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max()); }

    /// @brief sからtへ上限まで流し、流量と最小費用を返す
    /// @param s 始点
    /// @param t 終点。sとは異なる頂点
    /// @param flow_limit 流量の上限
    /// @return 追加で流した量と追加の最小費用の組
    /// @complexity 実際の流量を $F$、頂点数を $n$、辺数を $m$ として
    /// $O(F(n+m)\log(n+m))$。残余グラフに負コストの辺があれば $O(nm)$ が加わる
    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) { return slope(s, t, flow_limit).back(); }

    /// @brief 流量と最小費用の関係を表す折れ線を返す
    /// @details 最初の要素は $(0,0)$。連続する3点が同一直線上にならないよう圧縮される。
    /// 最後の要素は最大流量とその最小費用である。流量・費用はこの呼び出しで追加した分を表す。
    /// @param s 始点
    /// @param t 終点。sとは異なる頂点
    /// @return 折れ線の頂点を流量・最小費用の組で並べた列
    /// @complexity 最大流量を $F$、頂点数を $n$、辺数を $m$ として
    /// $O(F(n+m)\log(n+m))$。残余グラフに負コストの辺があれば $O(nm)$ が加わる
    std::vector<std::pair<Cap, Cost>> slope(int s, int t) { return slope(s, t, std::numeric_limits<Cap>::max()); }

    /// @brief 流量上限までの流量と最小費用の関係を表す折れ線を返す
    /// @details 最初の要素は $(0,0)$。連続する3点が同一直線上にならないよう圧縮される。
    /// 最後の要素は最大流量とflow_limitの小さい方に対する最小費用である。
    /// 流量・費用はこの呼び出しで追加した分を表す。
    /// @param s 始点
    /// @param t 終点。sとは異なる頂点
    /// @param flow_limit 流量の上限
    /// @return 折れ線の頂点を流量・最小費用の組で並べた列
    /// @complexity 実際の流量を $F$、頂点数を $n$、辺数を $m$ として
    /// $O(F(n+m)\log(n+m))$。残余グラフに負コストの辺があれば $O(nm)$ が加わる
    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < n);
        assert(0 <= t && t < n);
        assert(s != t);

        int m = int(_edges.size());
        std::vector<int> edge_idx(m);

        auto g = [&]() {
            std::vector<int> degree(n), redge_idx(m);
            std::vector<std::pair<int, InternalEdge>> elist;
            elist.reserve(2 * m);
            for (int i = 0; i < m; ++i) {
                auto e = _edges[i];
                edge_idx[i] = degree[e.from]++;
                redge_idx[i] = degree[e.to]++;
                elist.emplace_back(e.from, InternalEdge(e.to, -1, e.cap - e.flow, e.cost));
                elist.emplace_back(e.to, InternalEdge(e.from, -1, e.flow, -e.cost));
            }
            auto _g = internal::Csr<InternalEdge>(n, elist);
            for (int i = 0; i < m; ++i) {
                auto e = _edges[i];
                edge_idx[i] += _g.start[e.from];
                redge_idx[i] += _g.start[e.to];
                _g.elist[edge_idx[i]].rev = redge_idx[i];
                _g.elist[redge_idx[i]].rev = edge_idx[i];
            }
            return _g;
        }();

        auto result = slope(g, s, t, flow_limit);

        for (int i = 0; i < m; i++) {
            auto e = g.elist[edge_idx[i]];
            _edges[i].flow = _edges[i].cap - e.cap;
        }

        return result;
    }

  private:
    int n;
    std::vector<Edge> _edges;

    struct InternalEdge {
        int to, rev;
        Cap cap;
        Cost cost;

        constexpr InternalEdge() : to(), rev(), cap(), cost() {}
        constexpr InternalEdge(int _to, int _rev, Cap _cap, Cost _cost) : to(_to), rev(_rev), cap(_cap), cost(_cost) {}
    };

    // 残余グラフに負コストの辺があれば、s からの最短距離で双対変数を初期化する。
    // 双対変数は dual[t] = 0 となるよう正規化する。t に到達できなければ false を返す。
    bool init_dual(const internal::Csr<InternalEdge> &g, int s, int t, std::vector<std::pair<Cost, Cost>> &dual_dist) {
        if (std::none_of(g.elist.begin(), g.elist.end(), [](const InternalEdge &e) { return e.cap && e.cost < 0; }))
            return true;
        constexpr Cost inf = std::numeric_limits<Cost>::max();
        std::vector<Cost> dist(n, inf);
        std::vector<int> depth(n);
        std::vector<bool> in_queue(n);
        std::queue<int> que;
        dist[s] = 0;
        que.push(s);
        in_queue[s] = true;
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            in_queue[v] = false;
            for (int i = g.start[v]; i < g.start[v + 1]; ++i) {
                const auto &e = g.elist[i];
                if (!e.cap || dist[v] + e.cost >= dist[e.to]) continue;
                dist[e.to] = dist[v] + e.cost;
                depth[e.to] = depth[v] + 1;
                assert(depth[e.to] < n && "negative cycle");
                if (!in_queue[e.to]) {
                    in_queue[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        if (dist[t] == inf) return false;
        for (int v = 0; v < n; ++v) dual_dist[v].first = dist[v] == inf ? Cost(0) : dist[v] - dist[t];
        return true;
    }

    std::vector<std::pair<Cap, Cost>> slope(internal::Csr<InternalEdge> &g, int s, int t, Cap flow_limit) {
        std::vector<std::pair<Cost, Cost>> dual_dist(n);
        std::vector<int> prev_e(n);
        std::vector<bool> vis(n);
        struct Q {
            Cost key;
            int to;
            constexpr Q(Cost _key, int _to) : key(_key), to(_to) {}
            constexpr bool operator<(Q r) const { return key > r.key; }
        };
        std::vector<int> que_min;
        std::vector<Q> que;
        if (!init_dual(g, s, t, dual_dist)) return {{Cap(0), Cost(0)}};
        auto dual_ref = [&]() {
            for (int i = 0; i < n; ++i) dual_dist[i].second = std::numeric_limits<Cost>::max();
            std::fill(vis.begin(), vis.end(), false);
            que_min.clear();
            que.clear();

            size_t heap_r = 0;

            dual_dist[s].second = 0;
            que_min.emplace_back(s);
            while (!que_min.empty() || !que.empty()) {
                int v;
                if (!que_min.empty()) {
                    v = que_min.back();
                    que_min.pop_back();
                } else {
                    while (heap_r < que.size()) {
                        ++heap_r;
                        std::push_heap(que.begin(), que.begin() + heap_r);
                    }
                    v = que.front().to;
                    std::pop_heap(que.begin(), que.end());
                    que.pop_back();
                    --heap_r;
                }
                if (vis[v]) continue;
                vis[v] = true;
                if (v == t) break;
                Cost dual_v = dual_dist[v].first, dist_v = dual_dist[v].second;
                for (int i = g.start[v]; i < g.start[v + 1]; ++i) {
                    auto e = g.elist[i];
                    if (!e.cap) continue;
                    Cost cost = e.cost - dual_dist[e.to].first + dual_v;
                    if (dual_dist[e.to].second - dist_v > cost) {
                        Cost dist_to = dist_v + cost;
                        dual_dist[e.to].second = dist_to;
                        prev_e[e.to] = e.rev;
                        if (dist_to == dist_v) que_min.emplace_back(e.to);
                        else que.emplace_back(dist_to, e.to);
                    }
                }
            }
            if (!vis[t]) return false;

            for (int v = 0; v < n; ++v) {
                if (!vis[v]) continue;
                dual_dist[v].first -= dual_dist[t].second - dual_dist[v].second;
            }
            return true;
        };
        Cap flow = 0;
        Cost cost = 0, prev_cost_per_flow = 0;
        bool first = true;
        std::vector<std::pair<Cap, Cost>> result = {{Cap(0), Cost(0)}};
        while (flow < flow_limit) {
            if (!dual_ref()) break;
            Cap c = flow_limit - flow;
            for (int v = t; v != s; v = g.elist[prev_e[v]].to) c = std::min(c, g.elist[g.elist[prev_e[v]].rev].cap);
            for (int v = t; v != s; v = g.elist[prev_e[v]].to) {
                auto &e = g.elist[prev_e[v]];
                e.cap += c;
                g.elist[e.rev].cap -= c;
            }
            Cost d = -dual_dist[s].first;
            flow += c;
            cost += c * d;
            if (!first && prev_cost_per_flow == d) result.pop_back();
            result.emplace_back(flow, cost);
            prev_cost_per_flow = d;
            first = false;
        }
        return result;
    }
};
