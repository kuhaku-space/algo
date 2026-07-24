#pragma once
#include <algorithm>
#include <bit>
#include <cassert>
#include <map>
#include <utility>
#include "union_find/undo_union_find.hpp"

/// @brief 辺の追加・削除を先読みして処理するオフライン動的連結性
/// @details `add` / `erase` を時刻順に登録してから `build` と `solve` を呼ぶ。
/// @complexity 前処理はイベント数を $k$ として $O(k\log(k+q))$、
/// `solve` は $O((q+k\log q)\log n)$（コールバックの実行時間を除く）
struct offline_dynamic_connectivity {
    /// @brief `n` 頂点・`q` 時刻の問い合わせを処理するオブジェクトを作る
    /// @complexity $O(n+q)$
    offline_dynamic_connectivity(int n, int q) : _q(q), uf(n) {
        _size = std::bit_ceil<unsigned>(_q);
        _log = std::countr_zero<unsigned>(_size);
        seg = std::vector(_size << 1, std::vector<std::pair<int, int>>());
    }

    /// @brief 時刻 `t` に無向辺 `(u, v)` を追加するイベントを登録する
    /// @complexity $O(\log k)$
    void add(int t, int u, int v) {
        auto p = std::minmax(u, v);
        mp[p].emplace_back(t, 0);
    }

    /// @brief 時刻 `t` に無向辺 `(u, v)` を削除するイベントを登録する
    /// @complexity $O(\log k)$
    void erase(int t, int u, int v) {
        auto p = std::minmax(u, v);
        mp[p].emplace_back(t, 1);
    }

    /// @brief 登録したイベントから各辺が有効な時刻区間を構築する
    /// @complexity イベント数を $k$ として $O(k\log(k+q))$
    void build() {
        for (auto [p, v] : mp) {
            std::sort(v.begin(), v.end());
            int s = 0;
            int last = 0;
            for (auto q : v) {
                if (q.second == 0) {
                    if (s++ == 0) last = q.first;
                } else {
                    assert(s > 0);
                    if (--s == 0) apply(last, q.first, p);
                }
            }
            if (s) apply(last, _q, p);
        }
    }

    /// @brief 各時刻のグラフ状態を復元し、`query(t)` を呼ぶ
    /// @complexity $O((q+k\log q)\log n)$（`query` の実行時間を除く）
    template <class F>
    void solve(F &&query, int k = 1) {
        int state = uf.snapshot();
        for (auto [u, v] : seg[k]) uf.unite(u, v);
        if (k < _size) {
            solve(query, 2 * k);
            solve(query, 2 * k + 1);
        } else if (k < _size + _q) {
            query(k - _size);
        }
        uf.rollback(state);
    }

    /// @brief 現在復元中の時刻で `u`, `v` が連結なら true を返す
    /// @complexity $O(\log n)$
    bool same(int u, int v) const { return uf.same(u, v); }

  private:
    int _q, _size, _log;
    std::vector<std::vector<std::pair<int, int>>> seg;
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> mp;
    undo_union_find uf;

    void apply(int l, int r, std::pair<int, int> p) {
        assert(0 <= l && l <= _q);
        assert(0 <= r && r <= _q);
        l += _size, r += _size;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) seg[l++].emplace_back(p);
            if (r & 1) seg[--r].emplace_back(p);
        }
    }
};
