#pragma once
#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

namespace internal {

template <class T>
struct simple_queue {
    simple_queue() : payload(), pos() {}
    void reserve(int n) { payload.reserve(n); }
    int size() const { return int(payload.size()) - pos; }
    bool empty() const { return pos == int(payload.size()); }
    void push(const T &t) { payload.push_back(t); }
    void push(T &&t) { payload.push_back(std::move(t)); }
    T &front() { return payload[pos]; }
    void clear() { payload.clear(), pos = 0; }
    void pop() { ++pos; }

  private:
    std::vector<T> payload;
    int pos;
};

}  // namespace internal

/// @brief 最大流
template <class Cap>
struct mf_graph {
    /// @brief 0頂点のグラフを構築する
    /// @complexity $O(1)$
    mf_graph() : _n(0) {}

    /// @brief n頂点0辺のグラフを構築する
    /// @complexity $O(n)$
    explicit mf_graph(int n) : _n(n), g(n) {}

    /// @brief 頂点数を返す
    /// @complexity $O(1)$
    int size() const { return _n; }

    /// @brief 容量capの有向辺を追加して辺IDを返す
    /// @complexity 償却 $O(1)$
    int add_edge(int from, int to, Cap cap) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(0 <= cap);
        int m = int(pos.size());
        pos.emplace_back(from, int(g[from].size()));
        int from_id = int(g[from].size());
        int to_id = int(g[to].size());
        if (from == to) ++to_id;
        g[from].emplace_back(to, to_id, cap);
        g[to].emplace_back(from, from_id, 0);
        return m;
    }

    /// @brief 追加した辺の現在状態
    /// @complexity 各フィールドへのアクセスは $O(1)$
    struct edge {
        /// @brief 辺の始点と終点
        /// @complexity $O(1)$ で参照可能
        int from, to;
        /// @brief 辺の容量と現在の流量
        /// @complexity $O(1)$ で参照可能
        Cap cap, flow;
    };

    /// @brief 指定した辺の現在状態を返す
    /// @complexity $O(1)$
    edge get_edge(int i) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        auto _e = g[pos[i].first][pos[i].second];
        auto _re = g[_e.to][_e.rev];
        return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};
    }
    /// @brief 全辺の現在状態を追加順で返す
    /// @complexity 辺数を $E$ として $O(E)$
    std::vector<edge> edges() {
        int m = int(pos.size());
        std::vector<edge> result;
        for (int i = 0; i < m; ++i) result.emplace_back(get_edge(i));
        return result;
    }
    /// @brief 辺の容量と現在流量を変更する
    /// @complexity $O(1)$
    void change_edge(int i, Cap new_cap, Cap new_flow) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        assert(0 <= new_flow && new_flow <= new_cap);
        auto &_e = g[pos[i].first][pos[i].second];
        auto &_re = g[_e.to][_e.rev];
        _e.cap = new_cap - new_flow;
        _re.cap = new_flow;
    }

    /// @brief sからtへ流せるだけ流して追加流量を返す
    /// @complexity 頂点数を $V$、辺数を $E$ として $O(V^2E)$
    Cap flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max()); }

    /// @brief sからtへflow_limitまで流して追加流量を返す
    /// @complexity $O(V^2E)$
    Cap flow(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        std::vector<int> level(_n), iter(_n);
        internal::simple_queue<int> que;
        auto bfs = [&]() {
            std::fill(level.begin(), level.end(), -1);
            level[s] = 0;
            que.clear();
            que.push(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop();
                for (auto e : g[v]) {
                    if (e.cap == 0 || level[e.to] >= 0) continue;
                    level[e.to] = level[v] + 1;
                    if (e.to == t) return;
                    que.push(e.to);
                }
            }
        };
        auto dfs = [&](auto self, int v, Cap up) {
            if (v == s) return up;
            Cap res = 0;
            int level_v = level[v];
            for (int &i = iter[v]; i < int(g[v].size()); ++i) {
                _edge &e = g[v][i];
                if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;
                Cap d = self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));
                if (d <= 0) continue;
                g[v][i].cap += d;
                g[e.to][e.rev].cap -= d;
                res += d;
                if (res == up) return res;
            }
            level[v] = _n;
            return res;
        };

        Cap flow = 0;
        while (flow < flow_limit) {
            bfs();
            if (level[t] == -1) break;
            std::fill(iter.begin(), iter.end(), 0);
            Cap f = dfs(dfs, t, flow_limit - flow);
            if (!f) break;
            flow += f;
        }
        return flow;
    }

    /// @brief 残余グラフでsから到達可能な頂点集合を返す
    /// @complexity $O(V+E)$
    std::vector<bool> min_cut(int s) {
        std::vector<bool> visited(_n);
        internal::simple_queue<int> que;
        que.push(s);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            visited[p] = true;
            for (auto e : g[p]) {
                if (e.cap && !visited[e.to]) {
                    visited[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        return visited;
    }

  private:
    int _n;
    struct _edge {
        int to, rev;
        Cap cap;

        constexpr _edge(int _to, int _rev, Cap _cap) : to(_to), rev(_rev), cap(_cap) {}
    };
    std::vector<std::pair<int, int>> pos;
    std::vector<std::vector<_edge>> g;
};
