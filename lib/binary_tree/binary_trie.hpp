#pragma once
#include <array>
#include <cassert>
#include <concepts>
#include <optional>
#include <vector>

/// @brief 2分トライ木
/// @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654
template <std::integral T, int B = 31, bool Multi = false>
struct binary_trie {
  private:
    struct node_t {
        int count;
        std::array<int, 2> ch;
        node_t() : count(), ch{-1, -1} {}
    };

  public:
    constexpr binary_trie() : nodes(1) {}

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
    constexpr T at(int k) const { return operator[](k); }
    constexpr T get(int k) const { return operator[](k); }
    constexpr T kth_element(int k) const { return operator[](k); }

    constexpr bool empty() const { return nodes.front().count == 0; }
    constexpr int size() const { return nodes.front().count; }

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
    constexpr void erase(T val) {
        if (!count(val)) return;
        --nodes[0].count;
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            idx = nodes[idx].ch[val >> b & 1];
            --nodes[idx].count;
        }
    }

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
    constexpr T max_element(T bias = 0) const { return min_element(~bias); }

    constexpr bool contains(T val) const { return count(val); }

    constexpr int count_less(T val) const { return lower_bound(val); }
    constexpr int count(T val) const {
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            idx = nodes[idx].ch[val >> b & 1];
            if (idx == -1) return 0;
        }
        return nodes[idx].count;
    }
    constexpr int count(T l, T r) const { return count_less(r) - count_less(l); }

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
