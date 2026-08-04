#pragma once
#include <algorithm>
#include <cassert>
#include <concepts>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief Static Top Tree（木を rake / compress の二分木へ分解する）
/// @details 木を HL 分解し、heavy path 上のクラスタを compress で連結、頂点にぶら下がる
///          軽辺部分木を重み二分の rake で束ねることで、高さ $O(\log n)$ の二分木を作る。
///          この形状に `StaticTopTreeDP` を載せると、頂点値の点更新を $O(\log n)$ で
///          反映しながら木 DP の値を保てる。
/// @details 分解結果はグラフ表現に依存しないので構築だけを `graph_type` でテンプレート化
///          している。ノード番号 $[0, n)$ は元の頂点番号（`Type::Vertex` のノード）と一致し、
///          子の番号は必ず親より小さい（番号の昇順がボトムアップ順になる）。
/// @note 非連結なグラフを渡した場合、根 `r` を含む連結成分だけが分解される。
/// @complexity 構築は $O(n)$、ノード参照は $O(1)$
/// @see https://codeforces.com/blog/entry/103989
/// @see https://nyaannyaan.github.io/library/tree/static-top-tree-vertex-based.hpp
struct StaticTopTree {
    /// @brief Top Tree ノードが表す結合操作の種類
    /// @complexity 列挙型のため実行時コストなし
    enum class Type {
        Vertex,     ///< 元の木の頂点そのもの（葉。ノード番号 = 頂点番号）
        Compress,   ///< 親側パス（左）と子側パス（右）を 1 本のパスへ連結する
        Rake,       ///< 2 つの軽辺クラスタ（左・右）を並列に合成する
        AddEdge,    ///< 子部分木のパス値（左）を軽辺クラスタへ変換する単項ノード
        AddVertex,  ///< 頂点（左）に軽辺クラスタ（右）を付加してパスにする
    };

    /// @brief Top Tree の二分木ノード
    /// @complexity 各フィールドの参照は $O(1)$
    struct Node {
        /// @brief 親・左子・右子のノード番号（存在しなければ `-1`）
        /// @complexity $O(1)$ で参照可能
        int p = -1, l = -1, r = -1;
        /// @brief このノードが表す結合操作
        /// @complexity $O(1)$ で参照可能
        Type type = Type::Vertex;
    };

    /// @brief Top Tree の根ノード番号。空の木では `-1`
    /// @complexity $O(1)$ で参照可能
    int root = -1;
    /// @brief Top Tree の全ノード。先頭 $n$ 個が頂点に対応する `Type::Vertex` ノード
    /// @complexity 1 ノードの参照は $O(1)$
    std::vector<Node> nodes;

    /// @brief 空のStatic Top Treeを構築する
    /// @complexity $O(1)$
    StaticTopTree() = default;

    /// @brief 木gを根rからStatic Top Treeへ分解する
    /// @complexity $O(n)$
    template <graph_type G>
    explicit StaticTopTree(const G &g, int r = 0) : _size(g.size()) {
        if (_size == 0) return;
        assert(0 <= r && r < _size);

        // HL 分解: 行きがけ順を作り、その逆順で部分木サイズと heavy child を確定させる。
        std::vector<int> par(_size, -1), sub(_size, 1), heavy(_size, -1), ord;
        ord.reserve(_size);
        ord.emplace_back(r);
        for (int i = 0; i < (int)ord.size(); ++i) {
            int v = ord[i];
            for (auto &&e : g[v]) {
                int u = e.to();
                if (u == par[v]) continue;
                par[u] = v;
                ord.emplace_back(u);
            }
        }
        for (int i = (int)ord.size() - 1; i >= 1; --i) {
            int v = ord[i], p = par[v];
            sub[p] += sub[v];
            if (heavy[p] == -1 || sub[heavy[p]] < sub[v]) heavy[p] = v;
        }

        // ノード数は 2n + (heavy path 数) - 2 で、n 頂点なら 3n 以下に収まる。
        nodes.reserve(3 * _size);
        nodes.resize(_size);
        auto new_node = [&](int left, int right, Type type) -> int {
            int id = nodes.size();
            nodes.push_back({-1, left, right, type});
            if (left != -1) nodes[left].p = id;
            if (right != -1) nodes[right].p = id;
            return id;
        };

        // マージ対象のクラスタ列と、その重みの累積和。再帰しないので使い回せる。
        std::vector<int> item, pre;

        // 重み二分マージ: item[lo, hi) を左右の重み和がほぼ等しくなる位置で再帰的に分割し、
        // type ノードの二分木にする。分割位置の探索を累積和への両端からの指数探索にすると
        // 1 回のコストが短い側の長さの $\log$ で収まり、列全体で $O(hi - lo)$ になる。
        auto merge = [&](auto self, int lo, int hi, Type type) -> int {
            if (hi - lo == 1) return item[lo];
            int target = pre[lo] + pre[hi];  // 2 * pre[m] >= target となる最小の m で分割する
            int lft = lo, rgt = hi;          // 不変条件: 2 * pre[lft] < target <= 2 * pre[rgt]
            for (int step = 1; rgt - lft > 1; step *= 2) {
                int a = lft + step, b = rgt - step;
                if (a >= rgt) break;  // 残り幅が step 以下になったので二分探索に切り替える
                if (2 * pre[a] >= target) {
                    rgt = a;
                    break;
                }
                if (2 * pre[b] < target) {
                    lft = b;
                    break;
                }
                lft = a, rgt = b;
            }
            while (rgt - lft > 1) {
                int mid = lft + (rgt - lft) / 2;
                if (2 * pre[mid] >= target) rgt = mid;
                else lft = mid;
            }
            int mid = std::min(rgt, hi - 1);  // 右が空にならないよう末尾の要素は必ず右へ回す
            int left = self(self, lo, mid, type);
            int right = self(self, mid, hi, type);
            return new_node(left, right, type);
        };

        // 行きがけ順の逆順に走査する。頂点 v を処理する時点で子の結果は揃っているので、
        // 再帰なしで下から組み上げられる（vertex_node は頂点単体、path_root は heavy path
        // 全体を表すノード）。
        std::vector<int> vertex_node(_size, -1), path_root(_size, -1);
        for (int i = (int)ord.size() - 1; i >= 0; --i) {
            int v = ord[i];
            item.clear();
            pre.assign(1, 0);
            for (auto &&e : g[v]) {
                int u = e.to();
                if (u == par[v] || u == heavy[v]) continue;
                item.emplace_back(new_node(path_root[u], -1, Type::AddEdge));
                pre.emplace_back(pre.back() + sub[u]);
            }
            vertex_node[v] = v;
            if (!item.empty()) {
                int rake = merge(merge, 0, item.size(), Type::Rake);
                vertex_node[v] = new_node(v, rake, Type::AddVertex);
            }
            if (par[v] != -1 && heavy[par[v]] == v) continue;
            // v は heavy path の先頭なので、パス全体を compress でまとめる。
            item.clear();
            pre.assign(1, 0);
            for (int u = v; u != -1; u = heavy[u]) {
                item.emplace_back(vertex_node[u]);
                pre.emplace_back(pre.back() + sub[u] - (heavy[u] == -1 ? 0 : sub[heavy[u]]));
            }
            path_root[v] = merge(merge, 0, item.size(), Type::Compress);
        }
        root = path_root[r];
    }

    /// @brief 元の木の頂点数を返す（Top Tree のノード数は `nodes.size()`）
    /// @complexity $O(1)$
    int size() const { return _size; }

  private:
    int _size = 0;
};

/// @brief Static Top Tree に載せる木DPの要件
/// @details 重パス上の集約型 `Path` と軽辺クラスタの集約型 `Light` に対し、頂点の初期値
///          `vertex`、パスへの軽辺クラスタの付加 `add_vertex`、部分木から軽辺クラスタへの
///          変換 `add_edge`、軽辺クラスタ同士の合成 `rake`、パス同士の連結 `compress` を
///          持つこと。`compress(p, c)` の `p` は親側、`c` は子側で、非可換でよい。
///          `DynamicTopTree` も同じ要件のクラスを受け取る。
/// @tparam D 判定対象の木DP
/// @complexity コンパイル時の型制約のため実行時コストなし
template <class D>
concept tree_dp = requires(D &d, const typename D::Path &p, const typename D::Light &l, int u) {
    { d.vertex(u) } -> std::convertible_to<typename D::Path>;
    { d.add_vertex(p, l) } -> std::convertible_to<typename D::Path>;
    { d.add_edge(p) } -> std::convertible_to<typename D::Light>;
    { d.rake(l, l) } -> std::convertible_to<typename D::Light>;
    { d.compress(p, p) } -> std::convertible_to<typename D::Path>;
};

/// @brief Static Top Tree 上の木DP（頂点値の点更新に対応）
/// @details 木 DP の演算を `StaticTopTree` の各ノードで評価し、根の値として木全体の集約値を
///          保つ。頂点 $u$ の値を変えたら `dp` を書き換えて `update(u)` を呼ぶと、$u$ から
///          根までの $O(\log n)$ 個のノードだけが再計算される。
/// @details 使い方は `StaticTopTreeDP<DP> d(g, root, DP{...});` で構築し、頂点 $u$ の値を
///          変えるときは `d.dp` の頂点データを書き換えて `d.update(u)` を呼び、`d.get()` で
///          木全体の集約値を読む。同じ形状で別の DP を走らせたいときは `StaticTopTree` を
///          先に作って共有できる。
/// @tparam TreeDP 木DPの演算（`tree_dp` を満たすこと）
/// @complexity 構築と全再計算は $O(n)$、点更新は $O(\log n)$、集約値の取得は $O(1)$
template <tree_dp TreeDP>
struct StaticTopTreeDP {
    /// @brief 重パス上の集約値型
    /// @complexity 型エイリアスのため実行時コストなし
    using Path = typename TreeDP::Path;
    /// @brief 軽辺クラスタの集約値型
    /// @complexity 型エイリアスのため実行時コストなし
    using Light = typename TreeDP::Light;

    /// @brief DPの土台となるStatic Top Tree
    /// @complexity 1 ノードの参照は $O(1)$
    StaticTopTree stt;
    /// @brief 木DPの演算オブジェクト。頂点値の変更はこれを書き換えて `update` を呼ぶ
    /// @complexity 参照は $O(1)$
    TreeDP dp;

    /// @brief 空のDPオブジェクトを構築する
    /// @complexity $O(1)$
    StaticTopTreeDP() = default;

    /// @brief 木gを根rで分解し、全ノードのDP値を計算する
    /// @complexity $O(n)$
    template <graph_type G>
    explicit StaticTopTreeDP(const G &g, int r = 0, const TreeDP &_dp = TreeDP())
        : StaticTopTreeDP(StaticTopTree(g, r), _dp) {}

    /// @brief 構築済みのStatic Top Tree上で全DP値を計算する
    /// @complexity $O(n)$
    explicit StaticTopTreeDP(StaticTopTree _stt, const TreeDP &_dp = TreeDP())
        : stt(std::move(_stt)), dp(_dp), path_val(stt.nodes.size()), light_val(stt.nodes.size()) {
        update_all();
    }

    /// @brief 全ノードのDP値を再計算する
    /// @complexity $O(n)$
    void update_all() {
        // 子のノード番号は必ず親より小さいので、番号の昇順がボトムアップ順になる。
        for (int i = 0; i < (int)stt.nodes.size(); ++i) update_node(i);
    }

    /// @brief 頂点uの値を `dp.vertex(u)` から取り直し、根までのノードを更新する
    /// @complexity $O(\log n)$
    void update(int u) {
        assert(0 <= u && u < stt.size());
        for (int i = u; i != -1; i = stt.nodes[i].p) update_node(i);
    }

    /// @brief 木全体の集約値を返す
    /// @complexity $O(1)$
    const Path &get() const {
        assert(stt.root != -1);
        return path_val[stt.root];
    }

  private:
    std::vector<Path> path_val;    // Vertex / Compress / AddVertex ノードの集約値
    std::vector<Light> light_val;  // Rake / AddEdge ノードの集約値

    void update_node(int i) {
        const auto &node = stt.nodes[i];
        switch (node.type) {
            case StaticTopTree::Type::Vertex: path_val[i] = dp.vertex(i); break;
            case StaticTopTree::Type::Compress: path_val[i] = dp.compress(path_val[node.l], path_val[node.r]); break;
            case StaticTopTree::Type::Rake: light_val[i] = dp.rake(light_val[node.l], light_val[node.r]); break;
            case StaticTopTree::Type::AddEdge: light_val[i] = dp.add_edge(path_val[node.l]); break;
            case StaticTopTree::Type::AddVertex:
                path_val[i] = dp.add_vertex(path_val[node.l], light_val[node.r]);
                break;
        }
    }
};
