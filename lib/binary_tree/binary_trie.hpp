#pragma once
#include <array>
#include <cassert>
#include <concepts>
#include <vector>

/// @brief 2分トライ木
/// @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654
template <std::integral T, int B = 31>
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
        return get(0, k);
    }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    T kth_element(int k) const { return operator[](k); }

    constexpr bool empty() const { return nodes.front().count == 0; }
    constexpr int size() const { return nodes.front().count; }

    void insert(T val) {
        if (count(val)) return;
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

    T max_element(T bias = 0) const {
        assert(!empty());
        return get_min(0, ~bias);
    }
    T min_element(T bias = 0) const {
        assert(!empty());
        return get_min(0, bias);
    }
    int lower_bound(T val) const { return count_lower(0, val); }
    int upper_bound(T val) const { return count_lower(0, val + 1); }
    int count(T val) const {
        int idx = 0;
        for (int b = B - 1; b >= 0; --b) {
            idx = nodes[idx].ch[val >> b & 1];
            if (idx == -1) return 0;
        }
        return nodes[idx].count;
    }

  private:
    std::vector<node_t> nodes;

    T get_min(int idx, T val) const {
        T res{};
        for (int b = B - 1; b >= 0; --b) {
            bool f = val >> b & 1;
            f ^= nodes[idx].ch[f] == -1 || nodes[nodes[idx].ch[f]].count == 0;
            res += T(f) << b;
            idx = nodes[idx].ch[f];
        }
        return res;
    }
    T get(int idx, int k) const {
        T res{};
        for (int b = B - 1; b >= 0; --b) {
            int m = nodes[idx].ch[0] != -1 ? nodes[nodes[idx].ch[0]].count : 0;
            if (k < m) {
                idx = nodes[idx].ch[0];
            } else {
                res += T(1) << b;
                idx = nodes[idx].ch[1];
            }
        }
        return res;
    }
    int count_lower(int idx, T val, int b = B - 1) const {
        if (idx == -1 || b < 0) return 0;
        bool f = val >> b & 1;
        return (f && nodes[idx].ch[0] != -1 ? nodes[nodes[idx].ch[0]].count : 0) +
               count_lower(nodes[idx].ch[f], val, b - 1);
    }
};

/// @brief 多重2分トライ木
/// @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654
template <std::integral T, int B = 31>
struct multi_binary_trie {
  private:
    struct node_t {
        using pointer = node_t *;
        int count;
        pointer ch[2];
        node_t() : count(), ch{nullptr, nullptr} {}
    };

  public:
    using node_ptr = typename node_t::pointer;

    multi_binary_trie() : root(nullptr) {}

    T operator[](int k) const {
        assert(0 <= k && k < size());
        return get(root, k);
    }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    T kth_element(int k) const { return operator[](k); }

    constexpr int size() const { return root ? root->count : 0; }
    constexpr bool empty() const { return !root; }

    void insert(T val) { root = insert(root, val); }
    void erase(T val) {
        if (count(val)) root = erase(root, val);
    }

    T max_element(T bias = 0) const { return get_min(root, ~bias); }
    T min_element(T bias = 0) const { return get_min(root, bias); }
    int lower_bound(T val) { return count_lower(root, val); }
    int upper_bound(T val) { return count_lower(root, val + 1); }
    int count(T val) const {
        if (!root) return 0;
        node_ptr idx = root;
        for (int i = B - 1; i >= 0; i--) {
            idx = idx->ch[val >> i & 1];
            if (!idx) return 0;
        }
        return idx->count;
    }

  private:
    node_ptr root;

    node_ptr insert(node_ptr idx, T val, int b = B - 1) {
        if (!idx) idx = new node_t();
        ++idx->count;
        if (b < 0) return idx;
        bool f = val >> b & 1;
        idx->ch[f] = insert(idx->ch[f], val, b - 1);
        return idx;
    }
    node_ptr erase(node_ptr idx, T val, int b = B - 1) {
        assert(idx);
        --idx->count;
        if (!idx->count) return nullptr;
        if (b < 0) return idx;
        bool f = val >> b & 1;
        idx->ch[f] = erase(idx->ch[f], val, b - 1);
        return idx;
    }
    T get_min(node_ptr idx, T val, int b = B - 1) const {
        assert(idx);
        if (b < 0) return 0;
        bool f = val >> b & 1;
        f ^= !idx->ch[f];
        return get_min(idx->ch[f], val, b - 1) | ((T)f << b);
    }
    T get(node_ptr idx, int k, int b = B - 1) const {
        if (b < 0) return 0;
        int m = idx->ch[0] ? idx->ch[0]->count : 0;
        return k < m ? get(idx->ch[0], k, b - 1) : get(idx->ch[1], k - m, b - 1) | ((T)1 << b);
    }
    int count_lower(node_ptr idx, T val, int b = B - 1) {
        if (!idx || b < 0) return 0;
        bool f = val >> b & 1;
        return (f && idx->ch[0] ? idx->ch[0]->count : 0) + count_lower(idx->ch[f], val, b - 1);
    }
};
