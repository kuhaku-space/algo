#pragma once
#include <cassert>
#include <limits>
#include <optional>
#include <vector>
#include "flow/max_flow.hpp"

/// @brief 流量下限付き最大流
/// @details 各辺に流量の下限と上限を持つ有向グラフで、下限・上限を満たす s-t フローのうち
/// 流量（s から出る正味の量で、負にもなりうる）が最大・最小のものを求める。条件を満たすフローが存在しなければ
/// `std::nullopt` を返す。 超頂点を加えた `MaxFlow` に帰着して解く。
/// @warning `max_flow` と `min_flow` は合わせて1インスタンスにつき1回だけ呼べる。
/// @tparam Cap 容量の型
template <class Cap>
struct MaxFlowLowerBound {
    /// @brief n頂点0辺のグラフを構築する
    /// @param _n 頂点数
    /// @complexity $O(n)$
    explicit MaxFlowLowerBound(int _n) : n(_n), graph(_n + 2), excess(_n) {}

    /// @brief 頂点数を返す
    /// @return 頂点数
    /// @complexity $O(1)$
    int size() const { return n; }

    /// @brief 流量が lower 以上 upper 以下の有向辺を追加する
    /// @param from 始点。$0\le from<n$
    /// @param to 終点。$0\le to<n$
    /// @param lower 流量の下限
    /// @param upper 流量の上限。$0\le lower\le upper$
    /// @return 追加した辺のID
    /// @complexity 償却 $O(1)$
    int add_edge(int from, int to, Cap lower, Cap upper) {
        assert(!solved);
        assert(0 <= from && from < n);
        assert(0 <= to && to < n);
        assert(0 <= lower && lower <= upper);
        int id = graph.add_edge(from, to, upper - lower);
        lowers.emplace_back(lower);
        excess[to] += lower;
        excess[from] -= lower;
        return id;
    }

    /// @brief 追加した辺の現在状態
    /// @complexity 各フィールドへのアクセスは $O(1)$
    struct Edge {
        /// @brief 辺の始点と終点
        /// @complexity $O(1)$ で参照可能
        int from, to;
        /// @brief 流量の下限・上限と現在の流量
        /// @complexity $O(1)$ で参照可能
        Cap lower, upper, flow;
    };

    /// @brief 指定した辺の現在状態を返す
    /// @param i `add_edge` が返した辺ID
    /// @return i番目に追加した辺の現在状態
    /// @complexity $O(1)$
    Edge get_edge(int i) const {
        assert(0 <= i && i < int(lowers.size()));
        auto e = graph.get_edge(i);
        return Edge{e.from, e.to, lowers[i], e.cap + lowers[i], e.flow + lowers[i]};
    }

    /// @brief 全辺の現在状態を追加順で返す
    /// @return 辺状態の列
    /// @complexity 辺数を $m$ として $O(m)$
    std::vector<Edge> edges() const {
        std::vector<Edge> result;
        result.reserve(lowers.size());
        for (int i = 0; i < int(lowers.size()); ++i) result.emplace_back(get_edge(i));
        return result;
    }

    /// @brief 条件を満たす s-t フローのうち流量最大のものを流し、その流量を返す
    /// @param s 始点
    /// @param t 終点。sとは異なる頂点
    /// @return 最大流量。条件を満たすフローがなければ `std::nullopt`
    /// @complexity 頂点数を $n$、辺数を $m$ として $O(n^2m)$
    std::optional<Cap> max_flow(int s, int t) {
        auto base = feasible_flow(s, t);
        if (!base) return std::nullopt;
        return *base + graph.flow(s, t);
    }

    /// @brief 条件を満たす s-t フローのうち流量最小のものを流し、その流量を返す
    /// @param s 始点
    /// @param t 終点。sとは異なる頂点
    /// @return 最小流量。条件を満たすフローがなければ `std::nullopt`
    /// @complexity 頂点数を $n$、辺数を $m$ として $O(n^2m)$
    std::optional<Cap> min_flow(int s, int t) {
        auto base = feasible_flow(s, t);
        if (!base) return std::nullopt;
        return *base - graph.flow(t, s);
    }

  private:
    int n;
    MaxFlow<Cap> graph;
    std::vector<Cap> lowers, excess;
    bool solved = false;

    // 下限を満たす s-t フローを1つ流し、その流量を返す。存在しなければ nullopt。
    // 戻ったとき、補助辺は s-t 間の増加路に使われない状態になっている。
    std::optional<Cap> feasible_flow(int s, int t) {
        assert(!solved);
        assert(0 <= s && s < n);
        assert(0 <= t && t < n);
        assert(s != t);
        solved = true;
        int super_s = n, super_t = n + 1;
        Cap required = 0;
        for (int v = 0; v < n; ++v) {
            if (excess[v] > 0) {
                graph.add_edge(super_s, v, excess[v]);
                required += excess[v];
            } else if (excess[v] < 0) {
                graph.add_edge(v, super_t, -excess[v]);
            }
        }
        // s-t 流量が負になりうるので、t→s と s→t の両方に容量無限の辺を張って循環流に帰着する。
        int back = graph.add_edge(t, s, std::numeric_limits<Cap>::max());
        int forward = graph.add_edge(s, t, std::numeric_limits<Cap>::max());
        if (graph.flow(super_s, super_t) != required) return std::nullopt;
        // super_s から出る辺・super_t に入る辺はすべて飽和しているので、以降の s-t 間の増加路は
        // 超頂点を通らない。補助辺を外すと、その正味の流量が現在の s-t 流量になる。
        Cap base = graph.get_edge(back).flow - graph.get_edge(forward).flow;
        graph.change_edge(back, 0, 0);
        graph.change_edge(forward, 0, 0);
        return base;
    }
};
