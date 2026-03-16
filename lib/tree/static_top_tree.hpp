#pragma once
#include <algorithm>
#include <utility>
#include <vector>

/**
 * @brief Static Top Tree
 * @see https://codeforces.com/blog/entry/103989
 * @see https://nyaannyaan.github.io/library/tree/static-top-tree-vertex-based.hpp
 */
template <class Graph>
struct static_top_tree {
    enum Type { Vertex, Compress, Rake, AddEdge, AddVertex };

    struct Node {
        int p, l, r;
        Type type;
    };

    int root;
    std::vector<Node> nodes;

    static_top_tree() : root(-1) {}

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

        auto dfs_sz = [&](auto self, int u, int p) -> void {
            par[u] = p;
            int max_sub = 0;
            for (auto &&e : g[u]) {
                int v = get_to(e);
                if (v == p) continue;
                self(self, v, u);
                sz[u] += sz[v];
                if (max_sub < sz[v]) {
                    max_sub = sz[v];
                    heavy[u] = v;
                }
            }
        };
        dfs_sz(dfs_sz, _root, -1);

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

/**
 * @brief Static Top Tree 上でDPを行うテンプレート
 *
 * `TreeDP` クラスは以下を持つ必要があります：
 * ```cpp
 * struct DP {
 *     using Path = ...; // 重パス上のデータ型
 *     using Light = ...; // 軽辺部分木のデータ型
 *     Path vertex(int u); // 頂点uのPathデータ初期化
 *     Path add_vertex(Path d, Light l); // 頂点を含むパスに軽辺部分木を付加
 *     Light add_edge(Path d); // 部分木のPathデータを親に繋ぐ軽辺のデータに変換
 *     Light rake(Light l, Light r); // 複数の軽辺のデータをマージ
 *     Path compress(Path p, Path c); // 親側のパスpと子側のパスcをマージして1つのパスにする
 * };
 * ```
 */
template <class Graph, class TreeDP>
struct static_top_tree_dp {
    using Path = typename TreeDP::Path;
    using Light = typename TreeDP::Light;

    static_top_tree<Graph> stt;
    TreeDP dp;
    std::vector<Path> path_val;
    std::vector<Light> light_val;

    static_top_tree_dp() = default;

    static_top_tree_dp(const static_top_tree<Graph> &_stt, const TreeDP &_dp = TreeDP()) : stt(_stt), dp(_dp) {
        int m = stt.nodes.size();
        path_val.resize(m);
        light_val.resize(m);
        update_all();
    }

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

    void update(int u) {
        if (u < 0 || u >= (int)stt.nodes.size() || stt.nodes[u].type != static_top_tree<Graph>::Vertex) { return; }
        while (u != -1) {
            update_node(u);
            u = stt.nodes[u].p;
        }
    }

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
