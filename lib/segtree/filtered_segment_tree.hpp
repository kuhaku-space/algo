#pragma once
#include <algorithm>
#include <iterator>
#include <vector>
#include "algorithm/coordinate_compression.hpp"
#include "segtree/segment_tree.hpp"

/// @brief 要素を特定のキー（条件）でフィルタリングして区間取得を行えるセグメント木
/// @tparam K フィルタリングに用いるキーの型
/// @complexity 構築 $O(N \log N)$、更新・問合せ $O(\log N)$
template <class K, monoid M>
struct FilteredSegmentTree {
  private:
    using T = typename M::value_type;

  public:
    /// @brief 構築 $O(N \log N)$
    /// @param keys 各要素が属するキー
    /// @param _values 各要素の初期値
    /// @complexity $O(N \log N)$
    FilteredSegmentTree(const std::vector<K> &keys, const std::vector<T> &_values)
        : n(keys.size()), values(_values), leaf_indices(n) {
        unique_keys = CoordinateCompression<K>(keys);
        int num_keys = unique_keys.size();

        compressed_keys = unique_keys.compress(keys);
        key_positions.resize(num_keys);
        for (int i = 0; i < n; ++i) {
            int key_idx = compressed_keys[i];
            leaf_indices[i] = key_positions[key_idx].size();
            key_positions[key_idx].push_back(i);
        }

        tree_offsets.resize(num_keys + 1, 0);
        for (int i = 0; i < num_keys; ++i) tree_offsets[i + 1] = tree_offsets[i] + key_positions[i].size();

        std::vector<T> init_vals(n);
        for (int i = 0; i < num_keys; ++i) {
            for (int j = 0; j < (int)key_positions[i].size(); ++j)
                init_vals[tree_offsets[i] + j] = values[key_positions[i][j]];
        }
        tree = SegmentTree<M>(init_vals);
    }

    /// @brief `k` 番目の要素を `val` に更新する
    /// @param k 更新する要素の元のインデックス
    /// @param val 新しい値
    /// @complexity $O(\log N)$
    void set(int k, T val) {
        values[k] = val;
        int key_idx = compressed_keys[k];
        int i = leaf_indices[k];
        tree.set(tree_offsets[key_idx] + i, val);
    }

    /// @brief 区間 $[a, b)$ のうち、キーが `key` である要素の総積を取得する
    /// @param a 区間の左端 (含む)
    /// @param b 区間の右端 (含まない)
    /// @param key 対象とするキー
    /// @return 対象要素の総積。存在しない場合はモノイドの単位元
    /// @complexity $O(\log N)$
    T prod(int a, int b, K key) const {
        if (!unique_keys.contains(key)) return M::id();
        int key_idx = unique_keys.get(key);

        const auto &positions = key_positions[key_idx];
        int pos_a = std::lower_bound(positions.begin(), positions.end(), a) - positions.begin();
        int pos_b = std::lower_bound(positions.begin(), positions.end(), b) - positions.begin();

        return tree.prod(tree_offsets[key_idx] + pos_a, tree_offsets[key_idx] + pos_b);
    }

    /// @brief 区間 $[a, b)$ のうち、キーが `key` である要素の総積を取得する。ただし単位元の場合は `default_value`
    /// を返す
    /// @param a 区間の左端 (含む)
    /// @param b 区間の右端 (含まない)
    /// @param key 対象とするキー
    /// @param default_value 要素が存在しない/単位元の場合のデフォルト値
    /// @return 対象要素の総積、または `default_value`
    /// @complexity $O(\log N)$
    T prod_or_default(int a, int b, K key, T default_value) const {
        auto res = prod(a, b, key);
        return res == M::id() ? default_value : res;
    }

  private:
    int n;
    std::vector<T> values;
    std::vector<int> compressed_keys;
    CoordinateCompression<K> unique_keys;
    std::vector<int> leaf_indices;
    std::vector<std::vector<int>> key_positions;
    std::vector<int> tree_offsets;
    SegmentTree<M> tree;
};
