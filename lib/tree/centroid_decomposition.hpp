#pragma once
#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>
#include "graph/graph.hpp"

/// @brief 重心分解
/// @details 木を重心で再帰的に分解する。重心分解木の親配列を保持し、`run` で
///          各重心ごとの集計コールバックを呼べる。
///          - 重心分解木の再帰は深さ O(log n) なので再帰で実装する。
///          - 連結成分の走査・部分木サイズ計算・距離計算は深さ n になりうるため
///            すべて BFS 反復で行い、鎖状の木でもスタックオーバーフローしない。
/// @tparam T 辺の重みの型（`void` で重みなし。距離は辺数で数える）
template <class T>
struct centroid_decomposition {
    /// @brief ある重心 `c` の回で渡される連結成分の情報。
    /// @details いずれの配列も頂点番号で添字付けされる。`order` に現れない頂点
    ///          （別成分や `used` 済み）の成分は未定義なので参照しないこと。
    struct component {
        int centroid;                   ///< この回の重心
        const std::vector<int> &order;  ///< 重心を根とする連結成分の頂点列（BFS 行きがけ順、先頭は重心）
        const std::vector<int> &par;    ///< 連結成分内で重心を根とした親（重心は -1）
        const std::vector<int> &dep;    ///< 重心からの距離（辺数。重心は 0）
        const std::vector<int> &top;    ///< 重心直下の子部分木 ID（その頂点が属する重心直下の子。重心は -1）
        const std::vector<int> &sub;    ///< 連結成分内での部分木サイズ
    };

    /// @brief 重心分解を実行する。
    /// @param g 木（無向辺で構築されていること）
    explicit centroid_decomposition(const Graph<T> &g)
        : g_(g), n_(g.size()), par_(n_, -1), used_(n_, false), comp_par_(n_), comp_dep_(n_), comp_top_(n_),
          comp_sub_(n_) {
        order_.reserve(n_);
        if (n_ > 0) build(0, -1);
    }

    /// @brief 重心分解木における各頂点の親（根は -1）。
    const std::vector<int> &par() const { return par_; }

    /// @brief 各重心ごとに集計コールバックを呼ぶ。
    /// @details 分解木の根（全体の重心）から順に、各重心 `c` について
    ///          `f(component)` を 1 回ずつ呼ぶ。`component` 内の配列は呼び出しごとに
    ///          使い回されるので、必要なら呼び出し中にコピーすること。
    /// @param f `void(const component &)` 互換の呼び出し可能オブジェクト
    template <class F>
    void run(F f) {
        std::fill(used_.begin(), used_.end(), false);
        if (n_ > 0) run_dfs(0, std::ref(f));
    }

  private:
    const Graph<T> &g_;
    int n_;
    std::vector<int> par_;
    std::vector<bool> used_;
    std::vector<int> order_;                                      // 連結成分の BFS 行きがけ順（作業領域）
    std::vector<int> comp_par_, comp_dep_, comp_top_, comp_sub_;  // component 用作業領域

    /// @brief root を含む連結成分（used を除く）を BFS 順に order_ へ並べ、par/dep を記録する。
    /// @param root 走査の起点（この回はこれを根とみなす）
    /// @return 連結成分のサイズ
    int traverse(int root) {
        order_.clear();
        comp_par_[root] = -1;
        comp_dep_[root] = 0;
        order_.push_back(root);
        for (std::size_t i = 0; i < order_.size(); ++i) {
            int x = order_[i];
            for (auto e : g_[x]) {
                if (used_[e.to()] || e.to() == comp_par_[x]) continue;
                comp_par_[e.to()] = x;
                comp_dep_[e.to()] = comp_dep_[x] + 1;
                order_.push_back(e.to());
            }
        }
        return int(order_.size());
    }

    /// @brief order_（traverse 済み）から重心を求め、used に登録する。
    /// @details BFS 逆順に部分木サイズを comp_sub_ へ集計し（子は親より後ろにいるので 1 パス）、
    ///          起点から「過半数を占める子」へ降り続けて重心へ着く。降下経路は重心への一本道
    ///          だけを辿るので全頂点は見ない。降下中は comp_sub_/comp_par_ を現在地基準に書き換える。
    /// @param total 連結成分のサイズ
    /// @return 重心の頂点番号
    int find_centroid(int total) {
        for (auto it = order_.rbegin(); it != order_.rend(); ++it) {
            int x = *it;
            comp_sub_[x] = 1;
            for (auto e : g_[x]) {
                if (used_[e.to()] || e.to() == comp_par_[x]) continue;
                comp_sub_[x] += comp_sub_[e.to()];
            }
        }
        int c = order_[0];
        while (true) {
            int next = -1;
            for (auto e : g_[c]) {
                if (used_[e.to()] || e.to() == comp_par_[c]) continue;
                if (comp_sub_[e.to()] * 2 > total) {
                    next = e.to();
                    break;
                }
            }
            if (next == -1) break;
            comp_sub_[c] = total - comp_sub_[next];  // 反対側のサイズに更新してから降りる
            comp_par_[next] = c;
            c = next;
        }
        used_[c] = true;
        return c;
    }

    /// @brief 重心分解木を構築する（par_ を埋める）。重心の再帰のみ再帰。
    /// @details 親配列だけ必要なので連結成分のスキャンは traverse + find_centroid の 1 回で済む。
    void build(int root, int p) {
        int total = traverse(root);
        int c = find_centroid(total);
        par_[c] = p;
        for (auto e : g_[c]) {
            if (used_[e.to()]) continue;
            build(e.to(), c);
        }
    }

    /// @brief 各重心で component を組み立てて f を呼びながら再帰する。重心の再帰のみ再帰。
    /// @details component には c を根とした dep/top/sub が要るので、重心 c を見つけた後に
    ///          c を根として traverse + find_centroid をやり直す（連結成分を計 2 回スキャン）。
    template <class F>
    void run_dfs(int root, F f) {
        int total = traverse(root);
        int c = find_centroid(total);

        // 重心 c を根に取り直して BFS し、c からの距離（comp_dep_）と部分木サイズを確定する。
        traverse(c);
        find_centroid(total);  // comp_sub_ を c 基準で埋め直す（戻り値の重心は c に一致、再 used は無害）

        // top[x] = x が属する c 直下の子。BFS 順なので親から伝播できる。
        comp_top_[c] = -1;
        for (int x : order_) {
            if (x == c) continue;
            comp_top_[x] = (comp_par_[x] == c) ? x : comp_top_[comp_par_[x]];
        }

        component info{c, order_, comp_par_, comp_dep_, comp_top_, comp_sub_};
        f(info);

        for (auto e : g_[c]) {
            if (used_[e.to()]) continue;
            run_dfs(e.to(), f);
        }
    }
};

/// @brief 重心分解木の親配列だけを返す簡易版。
/// @param g 木
/// @return std::vector<int> 重心分解木における各頂点の親（根は -1）
template <class T>
std::vector<int> centroid_decomposition_par(const Graph<T> &g) {
    return centroid_decomposition<T>(g).par();
}
