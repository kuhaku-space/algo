#pragma once
#include <algorithm>
#include <utility>
#include <vector>

/// @brief Static Top Treeと点更新可能な全方位木DP
/// @details `static_top_tree` が木をrake/compressの二分木へ分解し、
/// `static_top_tree_dp` がTreeDPの演算で集約値を管理する。
/// @complexity 構築と全計算は $O(n\log n)$、点更新は $O(\log n)$、
/// 全体値の取得は $O(1)$
/// @see https://codeforces.com/blog/entry/103989
/// @see https://nyaannyaan.github.io/library/tree/static-top-tree-vertex-based.hpp
template <class Graph>
struct static_top_tree {
    /// @brief Top Tree ノードの種類
    /// @complexity 列挙型のため実行時コストなし
    enum Type { Vertex, Compress, Rake, AddEdge, AddVertex };

    /// @brief Top Tree の二分木ノード
    /// @complexity 各フィールドは $O(1)$ で参照可能
    struct Node {
        /// @brief 親・左子・右子のノード番号
        /// @complexity $O(1)$ で参照可能
        int p, l, r;
        /// @brief ノードが表す結合操作
        /// @complexity $O(1)$ で参照可能
        Type type;
    };

    /// @brief Top Tree の根ノード番号。空なら `-1`
    /// @complexity $O(1)$ で参照可能
    int root;
    /// @brief Top Tree の全ノード
    /// @complexity 1 ノードの参照は $O(1)$
    std::vector<Node> nodes;

    /// @brief 空の Static Top Tree を作る
    /// @complexity $O(1)$
    static_top_tree() : root(-1) {}

    /// @brief 木 `g` を `_root` から Static Top Tree へ分解する
    /// @complexity $O(n\log n)$
    static_top_tree(const Graph &g, int _root = 0) {
        int n = g.size();
        if (n == 0) {
            root = -1;
            return;
        }

        auto get_to = [](auto &&e) -> int {
            if constexpr (requires { e.to(); }) return e.to();
            else if constexpr (requires { e.to; }) return e.to;
            else return e;
        };

        nodes.assign(n, {-1, -1, -1, Vertex});
        std::vector<int> par(n, -1), sz(n, 1), heavy(n, -1);

        // 反復 DFS（再帰だと深い木でスタックオーバーフローしうる）。
        // 帰りがけに部分木サイズを集計し、最大の子を heavy に記録する。
        {
            std::vector<int> max_sub(n, 0);
            std::vector<std::pair<int, int>> stk;  // (頂点, 隣接走査位置)
            stk.reserve(n);
            par[_root] = -1;
            stk.emplace_back(_root, 0);
            while (!stk.empty()) {
                auto &[u, idx] = stk.back();
                if (idx < (int)g[u].size()) {
                    int v = get_to(g[u][idx++]);
                    if (v == par[u]) continue;
                    par[v] = u;
                    stk.emplace_back(v, 0);
                } else {
                    int p = par[u];
                    stk.pop_back();
                    if (p != -1) {
                        sz[p] += sz[u];
                        if (max_sub[p] < sz[u]) {
                            max_sub[p] = sz[u];
                            heavy[p] = u;
                        }
                    }
                }
            }
        }

        auto new_node = [&](int l, int r, Type type) -> int {
            int id = nodes.size();
            nodes.push_back({-1, l, r, type});
            if (l != -1) nodes[l].p = id;
            if (r != -1) nodes[r].p = id;
            return id;
        };

        auto merge = [&](auto self, const std::vector<std::pair<int, int>> &a, Type type) -> int {
            if (a.empty()) return -1;
            if (a.size() == 1) return a[0].first;
            int sum = 0;
            for (auto &p : a) sum += p.second;

            std::vector<std::pair<int, int>> b, c;
            int cur = 0;
            for (auto &p : a) {
                if (cur * 2 < sum) b.push_back(p);
                else c.push_back(p);
                cur += p.second;
            }
            if (b.empty()) {
                b.push_back(c.front());
                c.erase(c.begin());
            } else if (c.empty()) {
                c.push_back(b.back());
                b.pop_back();
            }
            int l = self(self, b, type);
            int r = self(self, c, type);
            return new_node(l, r, type);
        };

        auto build = [&](auto self, int u) -> int {
            std::vector<std::pair<int, int>> path;
            int curr = u;
            while (curr != -1) {
                std::vector<std::pair<int, int>> lights;
                for (auto &&e : g[curr]) {
                    int v = get_to(e);
                    if (v == par[curr] || v == heavy[curr]) continue;
                    int light_root = self(self, v);
                    int en = new_node(light_root, -1, AddEdge);
                    lights.push_back({en, sz[v]});
                }
                int rk = merge(merge, lights, Rake);
                int v_node = curr;
                if (rk != -1) { v_node = new_node(curr, rk, AddVertex); }
                path.push_back({v_node, sz[curr] - (heavy[curr] != -1 ? sz[heavy[curr]] : 0)});
                curr = heavy[curr];
            }
            return merge(merge, path, Compress);
        };
        root = build(build, _root);
    }
};

/// @brief Static Top Tree 上でDPを行うテンプレート
/// @details `TreeDP` クラスは以下を持つ必要があります：
/// ```cpp
/// struct DP {
///     using Path = ...; // 重パス上のデータ型
///     using Light = ...; // 軽辺部分木のデータ型
///     Path vertex(int u); // 頂点uのPathデータ初期化
///     Path add_vertex(Path d, Light l); // 頂点を含むパスに軽辺部分木を付加
///     Light add_edge(Path d); // 部分木のPathデータを親に繋ぐ軽辺のデータに変換
///     Light rake(Light l, Light r); // 複数の軽辺のデータをマージ
///     Path compress(Path p, Path c); // 親側のパスpと子側のパスcをマージして1つのパスにする
/// };
/// ```
/// @complexity 構築と全再計算は $O(n)$、点更新は $O(\log n)$、結果取得は $O(1)$
template <class Graph, class TreeDP>
struct static_top_tree_dp {
    /// @brief 重パス上の集約値型
    /// @complexity 型エイリアスのため実行時コストなし
    using Path = typename TreeDP::Path;
    /// @brief 軽辺部分木の集約値型
    /// @complexity 型エイリアスのため実行時コストなし
    using Light = typename TreeDP::Light;

    /// @brief DP の土台となる Static Top Tree
    /// @complexity 1 ノードの参照は $O(1)$
    static_top_tree<Graph> stt;
    /// @brief Tree DP の演算オブジェクト
    /// @complexity 参照は $O(1)$
    TreeDP dp;
    /// @brief 各 Top Tree ノードの `Path` 集約値
    /// @complexity 1 要素の参照は $O(1)$
    std::vector<Path> path_val;
    /// @brief 各 Top Tree ノードの `Light` 集約値
    /// @complexity 1 要素の参照は $O(1)$
    std::vector<Light> light_val;

    /// @brief 空の DP オブジェクトを作る
    /// @complexity $O(1)$
    static_top_tree_dp() = default;

    /// @brief Static Top Tree `_stt` 上で `_dp` を使い全 DP 値を計算する
    /// @complexity $O(n)$
    static_top_tree_dp(const static_top_tree<Graph> &_stt, const TreeDP &_dp = TreeDP()) : stt(_stt), dp(_dp) {
        int m = stt.nodes.size();
        path_val.resize(m);
        light_val.resize(m);
        update_all();
    }

    /// @brief 全ての Top Tree ノードの DP 値を再計算する
    /// @complexity $O(n)$
    void update_all() {
        if (stt.root == -1) return;
        auto dfs = [&](auto self, int u) -> void {
            auto &node = stt.nodes[u];
            if (node.l != -1) self(self, node.l);
            if (node.r != -1) self(self, node.r);
            update_node(u);
        };
        dfs(dfs, stt.root);
    }

    /// @brief 頂点 `u` の値を `dp.vertex(u)` から再取得し、根まで更新する
    /// @complexity $O(\log n)$
    void update(int u) {
        if (u < 0 || u >= (int)stt.nodes.size() || stt.nodes[u].type != static_top_tree<Graph>::Vertex) { return; }
        while (u != -1) {
            update_node(u);
            u = stt.nodes[u].p;
        }
    }

    /// @brief 木全体の集約値を返す
    /// @complexity $O(1)$
    Path get() const { return path_val[stt.root]; }

  private:
    void update_node(int u) {
        auto &node = stt.nodes[u];
        if (node.type == static_top_tree<Graph>::Vertex) {
            path_val[u] = dp.vertex(u);
        } else if (node.type == static_top_tree<Graph>::Compress) {
            path_val[u] = dp.compress(path_val[node.l], path_val[node.r]);
        } else if (node.type == static_top_tree<Graph>::Rake) {
            light_val[u] = dp.rake(light_val[node.l], light_val[node.r]);
        } else if (node.type == static_top_tree<Graph>::AddEdge) {
            light_val[u] = dp.add_edge(path_val[node.l]);
        } else if (node.type == static_top_tree<Graph>::AddVertex) {
            path_val[u] = dp.add_vertex(path_val[node.l], light_val[node.r]);
        }
    }
};
