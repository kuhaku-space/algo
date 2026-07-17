#pragma once
#include <cassert>
#include <concepts>

/// @brief 2分パトリシア木
/// @see https://kyokkounoite.hatenablog.jp/entry/2021/05/17/170000
template <std::integral T, int B = 31, bool Multi = false>
struct patricia_binary_trie {
  private:
    struct node_t {
        using pointer = node_t *;
        T val;
        int len, count;
        pointer ch[2];
        node_t(T _val, int _len, int _count = 0) : val(_val), len(_len), count(_count), ch{nullptr, nullptr} {}
    };

  public:
    using node_ptr = typename node_t::pointer;

    patricia_binary_trie() : root(nullptr) {}

    T operator[](int k) const {
        assert(0 <= k && k < size());
        return get(root, k);
    }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    T kth_element(int k) const { return operator[](k); }

    constexpr int size() const { return root ? root->count : 0; }
    constexpr bool empty() const { return !root; }

    void insert(T val) {
        if constexpr (Multi) {
            root = insert(root, val);
        } else {
            if (!count(val)) root = insert(root, val);
        }
    }
    void erase(T val) {
        if (count(val)) root = erase(root, val);
    }
    T max_element(T bias = 0) const { return get_min(root, ~bias); }
    T min_element(T bias = 0) const { return get_min(root, bias); }
    int lower_bound(T val) { return count_lower(root, val); }
    int upper_bound(T val) { return count_lower(root, val + 1); }
    int count(T val) const {
        if (!root) return 0;
        node_ptr node = root;
        int rest = node->len;
        for (int i = B - 1; i >= 0; --i) {
            if (!rest) {
                node = node->ch[val >> i & 1];
                if (!node) return 0;
                rest += node->len;
            }
            if ((val ^ node->val) >> i & 1) return 0;
            --rest;
        }
        return node->count;
    }

  private:
    node_ptr root;

    node_ptr insert(node_ptr node, T val, int b = B - 1) {
        if (!node) node = new node_t(val, b + 1);
        ++node->count;
        if (b < 0) return node;
        int len = node->len;
        for (int i = 0; i < node->len; ++i) {
            if (((val ^ node->val) >> (b - i) & 1)) {
                len = i;
                break;
            }
        }
        if (len == b + 1) return node;
        b -= len;
        node_ptr itr = node;
        if (len != node->len) {
            itr = new node_t(val, len, node->count);
            node->len -= len;
            --node->count;
            itr->ch[node->val >> b & 1] = node;
        }
        bool f = val >> b & 1;
        itr->ch[f] = insert(itr->ch[f], val, b);
        return itr;
    }
    node_ptr erase(node_ptr node, T val, int b = B - 1) {
        assert(node);
        --node->count;
        if (!node->count) return nullptr;
        b -= node->len;
        if (b < 0) return node;
        bool f = val >> b & 1;
        node->ch[f] = erase(node->ch[f], val, b);
        return node;
    }
    T get_min(node_ptr node, T val, int b = B - 1) const {
        assert(node);
        b -= node->len;
        if (b < 0) return node->val;
        bool f = val >> b & 1;
        f ^= !node->ch[f];
        return get_min(node->ch[f], val, b);
    }
    T get(node_ptr node, int k, int b = B - 1) const {
        b -= node->len;
        if (b < 0) return node->val;
        int m = node->ch[0] ? node->ch[0]->count : 0;
        return k < m ? get(node->ch[0], k, b) : get(node->ch[1], k - m, b);
    }
    int count_lower(node_ptr node, T val, int b = B - 1) {
        if (!node || b < 0) return 0;
        b -= node->len;
        bool f = val >> b & 1;
        return (f && node->ch[0] ? node->ch[0]->count : 0) + count_lower(node->ch[f], val, b - 1);
    }
};
