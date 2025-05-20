#pragma once
#include <array>
#include <cassert>
#include <concepts>
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

    T operator[](int k) const {
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
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    T kth_element(int k) const { return operator[](k); }

    constexpr bool empty() const { return nodes.front().count == 0; }
    constexpr int size() const { return nodes.front().count; }

    void insert(T val) {
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
    void erase(T val) {
        if (!count(val)) return;
        --nodes[0].count;
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            idx = nodes[idx].ch[f];
            --nodes[idx].count;
        }
    }

    T min_element(T bias = 0) const {
        assert(!empty());
        T res{};
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = bias >> b & 1;
            f ^= nodes[idx].ch[f] == -1 || nodes[nodes[idx].ch[f]].count == 0;
            res += T(f) << b;
            idx = nodes[idx].ch[f];
        }
        return res;
    }
    T max_element(T bias = 0) const { return min_element(~bias); }

    int count_less(T val) const {
        int res = 0, idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            if (f && nodes[idx].ch[0] != -1) res += nodes[nodes[idx].ch[0]].count;
            idx = nodes[idx].ch[val >> b & 1];
            if (idx == -1) break;
        }
        return res;
    }
    int count(T val) const {
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            idx = nodes[idx].ch[val >> b & 1];
            if (idx == -1) return 0;
        }
        return nodes[idx].count;
    }
    int count(T l, T r) const { return count_less(r) - count_less(l); }

  private:
    std::vector<node_t> nodes;
};
