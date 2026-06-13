#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief 有向グラフの閉路検出（閉路を構成する辺 ID 列を返す）
/// @return 閉路を構成する辺 ID の列（入力順で連結する）。閉路が無ければ空。
/// @note 各辺 ID は `list_graph::add_edge` の追加順（= 入力順）。多重辺・自己ループに対応。
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <graph_type G>
std::vector<int> cycle_detection_directed(const G &g) {
    int n = g.size();
    enum { unvisited, on_stack, done };
    std::vector<int> state(n, unvisited);
    // 現在の探索パス: vertices[i] へ入ってきた辺 ID が in_edge[i]（根は -1）
    std::vector<int> vertices, in_edge;
    std::vector<int> cycle;

    // 反復 DFS（再帰だと深いグラフでスタックオーバーフローしうる）
    for (int s = 0; s < n && cycle.empty(); ++s) {
        if (state[s] != unvisited) continue;
        std::vector<int> idx_stack;  // 各頂点の隣接リスト走査位置
        vertices.emplace_back(s);
        in_edge.emplace_back(-1);
        idx_stack.emplace_back(0);
        state[s] = on_stack;
        while (!vertices.empty()) {
            int v = vertices.back();
            if (idx_stack.back() < (int)g[v].size()) {
                auto e = g[v][idx_stack.back()++];
                int to = e.to();
                int eid = e.id();
                if (state[to] == unvisited) {
                    state[to] = on_stack;
                    vertices.emplace_back(to);
                    in_edge.emplace_back(eid);
                    idx_stack.emplace_back(0);
                } else if (state[to] == on_stack) {
                    // back edge 発見: パス上の to から現在の v までが閉路。
                    // vertices 上で to の位置を探し、そこから末尾までの in_edge と
                    // 今の辺 e を連結する。
                    int pos = (int)vertices.size() - 1;
                    while (vertices[pos] != to) --pos;
                    for (int i = pos + 1; i < (int)vertices.size(); ++i)
                        cycle.emplace_back(in_edge[i]);
                    cycle.emplace_back(eid);
                    break;
                }
                // state[to] == done なら無視
            } else {
                state[v] = done;
                vertices.pop_back();
                in_edge.pop_back();
                idx_stack.pop_back();
            }
        }
        if (cycle.empty()) {
            vertices.clear();
            in_edge.clear();
        }
    }
    return cycle;
}

/// @brief 無向グラフの閉路検出（閉路を構成する頂点列と辺 ID 列を返す）
/// @return {頂点列, 辺 ID 列}。閉路が無ければ両方空。
/// @note 無向辺は `list_graph::add_edges` で追加し、往復 2 本に同じ ID が振られていること。
///       自己ループは長さ 1、多重辺は長さ 2 の閉路として検出する。
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <graph_type G>
std::pair<std::vector<int>, std::vector<int>> cycle_detection_undirected(const G &g) {
    int n = g.size();
    // 自己ループは長さ 1 の閉路
    for (int v = 0; v < n; ++v) {
        for (auto &e : g[v]) {
            if (e.to() == v) return {{v}, {e.id()}};
        }
    }

    enum { unvisited, on_stack, done };
    std::vector<int> state(n, unvisited);
    // 探索パス: vertices[i] へ入ってきた辺 ID が in_edge[i]（根は -1）
    std::vector<int> vertices, in_edge;
    std::vector<int> cyc_v, cyc_e;

    for (int s = 0; s < n && cyc_v.empty(); ++s) {
        if (state[s] != unvisited) continue;
        std::vector<int> idx_stack;
        vertices.emplace_back(s);
        in_edge.emplace_back(-1);
        idx_stack.emplace_back(0);
        state[s] = on_stack;
        while (!vertices.empty()) {
            int v = vertices.back();
            if (idx_stack.back() < (int)g[v].size()) {
                auto e = g[v][idx_stack.back()++];
                int to = e.to();
                int eid = e.id();
                // 親へ戻る辺（来た辺そのもの）は無視。多重辺は ID が異なるので
                // ここでは弾かれず、下の back edge 検出で長さ 2 の閉路になる。
                if (eid == in_edge.back()) continue;
                if (state[to] == unvisited) {
                    state[to] = on_stack;
                    vertices.emplace_back(to);
                    in_edge.emplace_back(eid);
                    idx_stack.emplace_back(0);
                } else if (state[to] == on_stack) {
                    // back edge 発見: パス上の to から現在の v までが閉路。
                    int pos = (int)vertices.size() - 1;
                    while (vertices[pos] != to) --pos;
                    for (int i = pos; i < (int)vertices.size(); ++i) cyc_v.emplace_back(vertices[i]);
                    for (int i = pos + 1; i < (int)vertices.size(); ++i)
                        cyc_e.emplace_back(in_edge[i]);
                    cyc_e.emplace_back(eid);
                    break;
                }
            } else {
                state[v] = done;
                vertices.pop_back();
                in_edge.pop_back();
                idx_stack.pop_back();
            }
        }
        if (cyc_v.empty()) {
            vertices.clear();
            in_edge.clear();
        }
    }
    return {cyc_v, cyc_e};
}

/// @brief 閉路検出
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <graph_type G>
bool has_cycle(const G &g) {
    int n = g.size();
    std::vector<bool> seen(n), finished(n);
    bool res = false;

    // 反復 DFS（再帰だと深いグラフでスタックオーバーフローしうる）。
    // seen はパス上（灰）を、finished は探索完了（黒）を表し、
    // パス上の頂点へ戻る辺を見つけたら閉路あり。
    std::vector<std::pair<int, int>> stk;
    stk.reserve(n);
    for (int i = 0; i < n && !res; ++i) {
        if (finished[i] || seen[i]) continue;
        seen[i] = true;
        stk.emplace_back(i, 0);
        while (!stk.empty() && !res) {
            auto &[v, idx] = stk.back();
            if (idx < (int)g[v].size()) {
                int to = g[v][idx++].to();
                if (seen[to]) {
                    res = true;
                } else if (!finished[to]) {
                    seen[to] = true;
                    stk.emplace_back(to, 0);
                }
            } else {
                seen[v] = false;
                finished[v] = true;
                stk.pop_back();
            }
        }
        if (res) break;
    }
    return res;
}
