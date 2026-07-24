#pragma once
#include <array>
#include <cassert>
#include <concepts>
#include <optional>
#include <vector>

/// @brief 2分トライ木
/// @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654
/// @complexity 要素数に依らず各操作 $O(B)$、`size` と `empty` は $O(1)$
template <std::integral T, int B = 31, bool Multi = false>
struct binary_trie {
  private:
    struct node_t {
        int count;
        std::array<int, 2> ch;
        node_t() : count(), ch{-1, -1} {}
    };

  public:
    /// @brief 空のtrieを構築する
    /// @complexity $O(1)$
    constexpr binary_trie() : nodes(1) {}

    /// @brief 0-indexedでk番目に小さい値を返す
    /// @complexity $O(B)$
    constexpr T operator[](int k) const {
        assert(0 <= k && k < size());
        T res{};
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            int m = nodes[idx].ch[0] != -1 ? nodes[nodes[idx].ch[0]].count : 0;
            if (k < m) {
                idx = nodes[idx].ch[0];
            } else {
                k -= m;
                res += T(1) << b;
                idx = nodes[idx].ch[1];
            }
        }
        return res;
    }

    /// @brief k番目に小さい値を返す
    /// @complexity $O(B)$
    constexpr T at(int k) const { return operator[](k); }

    /// @brief k番目に小さい値を返す
    /// @complexity $O(B)$
    constexpr T get(int k) const { return operator[](k); }

    /// @brief k番目に小さい値を返す
    /// @complexity $O(B)$
    constexpr T kth_element(int k) const { return operator[](k); }

    /// @brief 空か返す
    /// @complexity $O(1)$
    constexpr bool empty() const { return nodes.front().count == 0; }

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return nodes.front().count; }

    /// @brief valを挿入する
    /// @complexity $O(B)$
    constexpr void insert(T val) {
        if constexpr (!Multi) {
            if (count(val)) return;
        }
        ++nodes[0].count;
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            if (nodes[idx].ch[f] == -1) {
                nodes[idx].ch[f] = nodes.size();
                nodes.emplace_back();
            }
            idx = nodes[idx].ch[f];
            ++nodes[idx].count;
        }
    }

    /// @brief valを1個削除する
    /// @complexity $O(B)$
    constexpr void erase(T val) {
        if (!count(val)) return;
        --nodes[0].count;
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            idx = nodes[idx].ch[val >> b & 1];
            --nodes[idx].count;
        }
    }

    /// @brief val XOR biasを最小化するvalを返す
    /// @complexity $O(B)$
    constexpr T min_element(T bias = 0) const {
        assert(!empty());
        T res{};
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = bias >> b & 1;
            f ^= !get_count(nodes[idx].ch[f]);
            res += T(f) << b;
            idx = nodes[idx].ch[f];
        }
        return res;
    }

    /// @brief val XOR biasを最大化するvalを返す
    /// @complexity $O(B)$
    constexpr T max_element(T bias = 0) const { return min_element(~bias); }

    /// @brief valを含むか返す
    /// @complexity $O(B)$
    constexpr bool contains(T val) const { return count(val); }

    /// @brief val未満の要素数を返す
    /// @complexity $O(B)$
    constexpr int count_less(T val) const { return lower_bound(val); }

    /// @brief valの個数を返す
    /// @complexity $O(B)$
    constexpr int count(T val) const {
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            idx = nodes[idx].ch[val >> b & 1];
            if (idx == -1) return 0;
        }
        return nodes[idx].count;
    }

    /// @brief 半開区間[l,r)の要素数を返す
    /// @complexity $O(B)$
    constexpr int count(T l, T r) const { return count_less(r) - count_less(l); }

    /// @brief val未満の要素数を返す
    /// @complexity $O(B)$
    constexpr int lower_bound(T val) const {
        int res = 0, idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            if (f) res += get_count(nodes[idx].ch[0]);
            idx = nodes[idx].ch[f];
            if (idx == -1) break;
        }
        return res;
    }

    /// @brief val以下の要素数を返す
    /// @complexity $O(B)$
    constexpr int upper_bound(T val) const {
        int res = 0, idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            if (f) res += get_count(nodes[idx].ch[0]);
            idx = nodes[idx].ch[f];
            if (idx == -1) break;
        }
        return res + get_count(idx);
    }

    /// @brief val以下で最大の要素を返す
    /// @complexity $O(B)$
    constexpr std::optional<T> floor(T val) const {
        T res{}, last_res{};
        int idx = 0, last_idx = -1, last_b = -1;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            if (f && get_count(nodes[idx].ch[0])) last_res = res, last_idx = nodes[idx].ch[0], last_b = b;
            res += T(f) << b, idx = nodes[idx].ch[f];
            if (!get_count(idx)) break;
        }
        if (get_count(idx)) return res;
        if (last_idx == -1) return std::nullopt;
        res = last_res, idx = last_idx;
        for (int b = last_b - 1; b >= 0; --b) {
            if (nodes[idx].ch[1] != -1 && nodes[nodes[idx].ch[1]].count) res += T(1) << b, idx = nodes[idx].ch[1];
            else idx = nodes[idx].ch[0];
        }
        return res;
    }

    /// @brief val以上で最小の要素を返す
    /// @complexity $O(B)$
    constexpr std::optional<T> ceil(T val) const {
        T res{}, last_res{};
        int idx = 0, last_idx = -1, last_b = -1;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            if (!f && get_count(nodes[idx].ch[1]))
                last_res = res + (T(1) << b), last_idx = nodes[idx].ch[1], last_b = b;
            res += T(f) << b, idx = nodes[idx].ch[f];
            if (!get_count(idx)) break;
        }
        if (get_count(idx)) return res;
        if (last_idx == -1) return std::nullopt;
        res = last_res, idx = last_idx;
        for (int b = last_b - 1; b >= 0; --b) {
            if (get_count(nodes[idx].ch[0])) idx = nodes[idx].ch[0];
            else res += T(1) << b, idx = nodes[idx].ch[1];
        }
        return res;
    }

  private:
    std::vector<node_t> nodes;

    constexpr int get_count(int idx) const { return idx == -1 ? 0 : nodes[idx].count; }
};
