#pragma once
#include <cassert>
#include <iostream>
#include <optional>
#include <random>

/// @brief Treap
template <class T, class UniformRandomBitGenerator = std::mt19937>
struct treap {
  private:
    struct node_t {
        using pointer = node_t *;

        static int count(pointer t) { return t ? t->cnt : 0; }

        node_t(T _val, typename UniformRandomBitGenerator::result_type _priority)
            : val(_val), priority(_priority), cnt(1), left(nullptr), right(nullptr) {}

        T val;
        typename UniformRandomBitGenerator::result_type priority;
        int cnt;
        pointer left, right;
    };

  public:
    using node_ptr = typename node_t::pointer;

    constexpr treap() : root(nullptr) {}
    constexpr treap(node_ptr p) : root(p) {}

    constexpr bool empty() const { return root == nullptr; }
    constexpr int size() const { return node_t::count(root); }

    constexpr T top() { return root->val; }

    T get(int k) const {
        assert(0 <= k && k < size());
        node_ptr node = root;
        while (true) {
            int c = node_t::count(node->left);
            if (c == k) break;
            if (k < c) node = node->left;
            else node = node->right, k -= c + 1;
        }
        return node->val;
    }

    int lower_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            int c = node_t::count(node->left);
            if (node->val < val) node = node->right, res += c + 1;
            else node = node->left;
        }
        return res;
    }

    int upper_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            int c = node_t::count(node->left);
            if (!(val < node->val)) node = node->right, res += c + 1;
            else node = node->left;
        }
        return res;
    }

    std::optional<T> floor(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(val < node->val)) res = node->val;
            if (!(val < node->val)) node = node->right;
            else node = node->left;
        }
        return res;
    }

    std::optional<T> ceil(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(node->val < val)) res = node->val;
            if (!(node->val < val)) node = node->left;
            else node = node->right;
        }
        return res;
    }

    void insert(T val) {
        node_ptr t = new node_t(val, gen());
        root = merge(root, t);
    }

    void erase(T val) { root = erase(root, val); }

    bool contains(T val) const {
        node_ptr node = root;
        while (node && node->val != val) {
            if (val < node->val) node = node->left;
            else node = node->right;
        }
        return node != nullptr;
    }

    int count(T val) const { return count(root, val); }

    std::pair<treap, treap> split(T val) {
        auto [l, r] = split(root, val);
        return std::make_pair(treap(l), treap(r));
    }

    void merge(treap treap) { root = merge(root, treap.root); }

  private:
    static inline UniformRandomBitGenerator gen = UniformRandomBitGenerator();
    node_ptr root;

    node_ptr update(node_ptr t) {
        if (t == nullptr) return t;
        t->cnt = node_t::count(t->left) + node_t::count(t->right) + 1;
        return t;
    }

    node_ptr merge(node_ptr l, node_ptr r) {
        if (!l || !r) return !l ? r : l;
        if (l->priority < r->priority) std::swap(l, r);
        auto [p, q] = split(r, l->val);
        l->left = merge(l->left, p);
        l->right = merge(l->right, q);
        return update(l);
    }

    std::pair<node_ptr, node_ptr> split(node_ptr node, T val) {
        if (node == nullptr) return {nullptr, nullptr};
        if (node->val < val) {
            auto [l, r] = split(node->right, val);
            node->right = nullptr;
            update(node);
            return {merge(node, l), r};
        } else {
            auto [l, r] = split(node->left, val);
            node->left = nullptr;
            update(node);
            return {l, merge(r, node)};
        }
    }

    node_ptr erase(node_ptr node, T val) {
        if (node == nullptr) return nullptr;
        if (val == node->val) return merge(node->left, node->right);
        if (val < node->val) node->left = erase(node->left, val);
        else node->right = erase(node->right, val);
        return update(node);
    }

    int count(node_ptr node, T val) const {
        if (node == nullptr) return 0;
        int res = node->val == val;
        if (!(node->val < val)) res += count(node->left, val);
        if (!(val < node->val)) res += count(node->right, val);
        return res;
    }
};
