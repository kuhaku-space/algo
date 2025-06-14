#pragma once
#include <algorithm>
#include <cassert>
#include <optional>

/// @brief AVL木
/// @see https://tjkendev.github.io/procon-library/cpp/binary_search_tree/avl-tree.html
template <class T>
struct avl_tree {
  private:
    struct node_t {
        using pointer = node_t *;
        T val;
        int height, count;
        pointer left, right;

        constexpr node_t(T _val) : val(_val), height(1), count(1), left(nullptr), right(nullptr) {}

        static constexpr int get_height(pointer node) { return node == nullptr ? 0 : node->height; }
        static constexpr int get_count(pointer node) { return node == nullptr ? 0 : node->count; }
        static constexpr int get_balance_factor(pointer node) {
            return node == nullptr ? 0 : node_t::get_height(node->left) - node_t::get_height(node->right);
        }

        constexpr void update() {
            height = std::max(node_t::get_height(left), node_t::get_height(right)) + 1;
            count = node_t::get_count(left) + node_t::get_count(right) + 1;
        }
        constexpr bool is_leaf() const { return left == nullptr && right == nullptr; }
    };

  public:
    using node_type = node_t;
    using node_ptr = typename node_t::pointer;

    constexpr avl_tree() : root(nullptr) {}

    constexpr bool empty() const { return root == nullptr; }
    constexpr int size() const { return node_t::get_count(root); }

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

    void insert(T val) { root = insert(root, val); }

    void erase(T val) { root = erase(root, val); }

    bool contains(T val) const {
        node_ptr node = root;
        while (node && node->val != val) {
            if (val < node->val) node = node->left;
            else node = node->right;
        }
        return node != nullptr;
    }

    int count(T val) const { return upper_bound(val) - lower_bound(val); }

    int lower_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            if (!(node->val < val)) node = node->left;
            else res += node_t::get_count(node->left) + 1, node = node->right;
        }
        return res;
    }

    int upper_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            if (val < node->val) node = node->left;
            else res += node_t::get_count(node->left) + 1, node = node->right;
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

  private:
    node_ptr root;

    constexpr T get_min_val(node_ptr node) const {
        assert(node);
        while (node->left) node = node->left;
        return node->val;
    }

    constexpr node_ptr rotl(node_ptr node) {
        assert(node);
        node_ptr pivot = node->right;
        assert(pivot);
        node->right = pivot->left;
        pivot->left = node;
        node->update();
        pivot->update();
        return pivot;
    }

    constexpr node_ptr rotr(node_ptr node) {
        assert(node);
        node_ptr pivot = node->left;
        assert(pivot);
        node->left = pivot->right;
        pivot->right = node;
        node->update();
        pivot->update();
        return pivot;
    }

    constexpr node_ptr rotlr(node_ptr node) {
        node->left = rotl(node->left);
        node = rotr(node);
        return node;
    }

    constexpr node_ptr rotrl(node_ptr node) {
        node->right = rotr(node->right);
        node = rotl(node);
        return node;
    }

    constexpr node_ptr rotate(node_ptr node) {
        int bf = node_type::get_balance_factor(node);
        if (bf < -1) {
            if (node_type::get_balance_factor(node->right) >= 1) node = rotrl(node);
            else node = rotl(node);
        } else if (bf > 1) {
            if (node_type::get_balance_factor(node->left) <= -1) node = rotlr(node);
            else node = rotr(node);
        } else {
            node->update();
        }
        return node;
    }

    constexpr node_ptr insert(node_ptr node, T val) {
        if (node == nullptr) return new node_t(val);
        if (val < node->val) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);
        return rotate(node);
    }

    constexpr node_ptr erase(node_ptr node, T val) {
        if (node == nullptr) return nullptr;
        if (val < node->val) {
            node->left = erase(node->left, val);
        } else if (node->val < val) {
            node->right = erase(node->right, val);
        } else {
            if (node->right == nullptr) {
                return node->left;
            } else {
                node->val = get_min_val(node->right);
                node->right = erase_min(node->right);
            }
        }
        return rotate(node);
    }

    constexpr node_ptr erase_min(node_ptr node) {
        if (node->left == nullptr) return node->right;
        node->left = erase_min(node->left);
        return rotate(node);
    }
};
