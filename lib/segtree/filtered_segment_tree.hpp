#pragma once
#include <algorithm>
#include <iterator>
#include <vector>
#include "algorithm/compress.hpp"
#include "segtree/segment_tree.hpp"

/// @brief 要素を特定のキー（条件）でフィルタリングして区間取得を行えるセグメント木
/// @tparam M モノイド
template <class K, class M>
struct filtered_segment_tree {
  private:
    using T = typename M::value_type;

  public:
    /// @brief 構築 O(N log N)
    /// @param keys 各要素が属するキー
    /// @param values 各要素の初期値
    filtered_segment_tree(const std::vector<K> &keys, const std::vector<T> &values)
        : n(keys.size()), values(values), leaf_indices(n) {
        unique_keys = coordinate_compression<K>(keys);
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
                init_vals[tree_offsets[i] + j] = this->values[key_positions[i][j]];
        }
        tree = segment_tree<M>(init_vals);
    }

    /// @brief k 番目の要素を new_val に更新する
    /// @param k 更新する要素の元のインデックス
    /// @param new_val 新しい値
    /// @complexity O(log N)
    void set(int k, T new_val) {
        values[k] = new_val;
        int key_idx = compressed_keys[k];
        int i = leaf_indices[k];
        tree.set(tree_offsets[key_idx] + i, new_val);
    }

    /// @brief 区間 [l, r) のうち、キーが key である要素の総積を取得する
    /// @param l 区間の左端 (含む)
    /// @param r 区間の右端 (含まない)
    /// @param key 対象とするキー
    /// @return 対象要素の総積。存在しない場合はモノイドの単位元
    /// @complexity O(log N)
    T prod(int l, int r, K key) const {
        if (!unique_keys.exists(key)) return M::id();
        int key_idx = unique_keys.get(key);

        const auto &positions = key_positions[key_idx];
        int pos_l = std::lower_bound(positions.begin(), positions.end(), l) - positions.begin();
        int pos_r = std::lower_bound(positions.begin(), positions.end(), r) - positions.begin();

        return tree.prod(tree_offsets[key_idx] + pos_l, tree_offsets[key_idx] + pos_r);
    }

    /// @brief 区間 [l, r) のうち、キーが key である要素の総積を取得する。ただし単位元の場合は default_value を返す
    /// @param l 区間の左端 (含む)
    /// @param r 区間の右端 (含まない)
    /// @param key 対象とするキー
    /// @param default_value 要素が存在しない/単位元の場合のデフォルト値
    /// @return 対象要素の総積、または default_value
    /// @complexity O(log N)
    T prod_or_default(int l, int r, K key, T default_value) const {
        auto res = prod(l, r, key);
        return res == M::id() ? default_value : res;
    }

  private:
    int n;
    std::vector<T> values;
    std::vector<int> compressed_keys;
    coordinate_compression<K> unique_keys;
    std::vector<int> leaf_indices;
    std::vector<std::vector<int>> key_positions;
    std::vector<int> tree_offsets;
    segment_tree<M> tree;
};
