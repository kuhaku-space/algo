#pragma once
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>
#include "random/xoroshiro128.hpp"
#include "tree/cartesian_tree.hpp"

/// @brief Treap
template <class T, class UniformRandomBitGenerator = xoroshiro128>
struct treap {
  private:
    struct node_t {
        using pointer = node_t *;

        T val;
        typename UniformRandomBitGenerator::result_type priority;
        int count;
        pointer left, right;

        constexpr node_t(T _val, typename UniformRandomBitGenerator::result_type _priority)
            : val(_val), priority(_priority), count(1), left(nullptr), right(nullptr) {}

        static constexpr int get_count(pointer t) { return t ? t->count : 0; }

        constexpr void update() { count = 1 + node_t::get_count(left) + node_t::get_count(right); }
    };

  public:
    using node_ptr = typename node_t::pointer;

    constexpr treap() : root(nullptr) {}
    constexpr treap(node_ptr p) : root(p) {}
    constexpr treap(const std::vector<T> &v) : root(nullptr) {
        if (v.empty()) return;
        int n = v.size();
        std::vector<typename UniformRandomBitGenerator::result_type> u(n);
        for (auto &e : u) e = gen();
        auto tree = cartesian_tree_fully(u);
        int rt = -1;
        for (int i = 0; i < n; ++i) {
            if (tree[i].parent == -1) rt = i;
        }
        auto build = [&v, &u, &tree](auto self, int x) -> node_ptr {
            if (x == -1) return nullptr;
            auto node = new node_t(v[x], u[x]);
            node->left = self(self, tree[x].left);
            node->right = self(self, tree[x].right);
            node->update();
            return node;
        };
        root = build(build, rt);
    }

    constexpr bool empty() const { return root == nullptr; }
    constexpr int size() const { return node_t::get_count(root); }

    void insert(T val) {
        node_ptr t = new node_t(val, gen());
        root = merge(root, t);
    }

    void erase(T val) { root = erase(root, val); }

    T front() {
        assert(root);
        node_ptr node = root;
        while (node->left) node = node->left;
        return node->val;
    }
    T back() {
        assert(root);
        node_ptr node = root;
        while (node->right) node = node->right;
        return node->val;
    }

    T get(int k) const {
        assert(0 <= k && k < size());
        node_ptr node = root;
        while (true) {
            int c = node_t::get_count(node->left);
            if (c == k) break;
            if (k < c) node = node->left;
            else node = node->right, k -= c + 1;
        }
        return node->val;
    }

    int count(T val) const { return upper_bound(val) - lower_bound(val); }

    bool contains(T val) const {
        node_ptr node = root;
        while (node && node->val != val) node = (val < node->val ? node->left : node->right);
        return node != nullptr;
    }

    int lower_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            int c = node_t::get_count(node->left);
            if (node->val < val) node = node->right, res += c + 1;
            else node = node->left;
        }
        return res;
    }

    int upper_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            int c = node_t::get_count(node->left);
            if (!(val < node->val)) node = node->right, res += c + 1;
            else node = node->left;
        }
        return res;
    }

    std::optional<T> floor(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(val < node->val)) res = node->val, node = node->right;
            else node = node->left;
        }
        return res;
    }

    std::optional<T> ceil(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(node->val < val)) res = node->val, node = node->left;
            else node = node->right;
        }
        return res;
    }

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
        t->count = node_t::get_count(t->left) + node_t::get_count(t->right) + 1;
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
};
