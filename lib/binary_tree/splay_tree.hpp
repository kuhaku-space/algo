#pragma once
#include <cassert>
#include <optional>

template <class T>
struct splay_tree {
  private:
    struct node_t {
        using pointer = node_t *;

        T val;
        int count;
        pointer left, right, parent;

        constexpr node_t(T _val) : val(_val), count(1), left(nullptr), right(nullptr), parent(nullptr) {}

        static constexpr int get_count(pointer node) { return node == nullptr ? 0 : node->count; }

        constexpr void update() { count = node_t::get_count(left) + node_t::get_count(right) + 1; }
        constexpr bool is_root() const { return parent == nullptr; }
        constexpr bool is_leaf() const { return left == nullptr && right == nullptr; }
        constexpr bool is_left_child() const { return parent->left == this; }
        constexpr bool is_right_child() const { return parent->right == this; }
    };
    using node_ptr = node_t::pointer;

  public:
    constexpr splay_tree() : root(nullptr) {}

    constexpr bool empty() const { return root == nullptr; }
    constexpr int size() const { return node_t::get_count(root); }

    T get(int k) {
        assert(0 <= k && k < size());
        auto node = get_node(k);
        splay(node);
        root = node;
        return root->val;
    }

    void insert(T val) {
        if (!root) {
            root = new node_t(val);
            return;
        }
        auto node = lower_bound_node(val);
        auto cur_node = new node_t(val);
        if (node) {
            splay(node);
            if (node->left) node->left->parent = cur_node;
            cur_node->left = node->left;
            cur_node->right = node;
            node->parent = cur_node;
            node->left = nullptr;
            node->update();
            cur_node->update();
        } else {
            root->parent = cur_node;
            cur_node->left = root;
            cur_node->update();
        }
        root = cur_node;
    }

    void erase(T val) {
        auto node = lower_bound_node(val);
        if (!node) return;
        splay(node);
        root = node;
        if (root->val != val) return;
        if (!root->left && !root->right) {
            root = nullptr;
            return;
        }
        if (!root->left) {
            root = root->right;
            root->parent = nullptr;
            return;
        }
        if (!root->right) {
            root = root->left;
            root->parent = nullptr;
            return;
        }
        root->right->parent = nullptr;
        auto l_node = lowest_node(root->right);
        splay(l_node);
        l_node->left = root->left;
        root->left->parent = l_node;
        l_node->update();
        root = l_node;
    }

    bool contains(T val) {
        auto node = lower_bound_node(val);
        if (!node) return false;
        splay(node);
        root = node;
        return root->val == val;
    }

    int lower_bound(T val) {
        auto node = lower_bound_node(val);
        if (!node) return size();
        splay(node);
        root = node;
        return node_t::get_count(root->left);
    }

    int upper_bound(T val) {
        auto node = upper_bound_node(val);
        if (!node) return size();
        splay(node);
        root = node;
        return node_t::get_count(root->left);
    }

    std::optional<T> floor(T val) {
        auto node = floor_node(val);
        if (!node) return std::nullopt;
        splay(node);
        root = node;
        return node->val;
    }

    std::optional<T> ceil(T val) {
        auto node = ceil_node(val);
        if (!node) return std::nullopt;
        splay(node);
        root = node;
        return node->val;
    }

  private:
    node_ptr root;

    node_ptr get_node(int k) const {
        node_ptr node = root;
        while (node) {
            int c = node_t::get_count(node->left);
            if (c == k) break;
            if (k < c) node = node->left;
            else k -= c + 1, node = node->right;
        }
        return node;
    }

    node_ptr lower_bound_node(T val) {
        node_ptr node = root, prev = nullptr, res = nullptr;
        while (node) {
            prev = node;
            if (!(node->val < val)) res = node, node = node->left;
            else node = node->right;
        }
        if (!res && prev) splay(prev), root = prev;
        return res;
    }

    node_ptr upper_bound_node(T val) {
        node_ptr node = root, prev = nullptr, res = nullptr;
        while (node) {
            prev = node;
            if (val < node->val) res = node, node = node->left;
            else node = node->right;
        }
        if (!res && prev) splay(prev), root = prev;
        return res;
    }

    node_ptr floor_node(T val) {
        node_ptr node = root, prev = nullptr, res = nullptr;
        while (node) {
            prev = node;
            if (!(val < node->val)) res = node, node = node->right;
            else node = node->left;
        }
        if (!res && prev) splay(prev), root = prev;
        return res;
    }

    node_ptr ceil_node(T val) { return lower_bound_node(val); }

    node_ptr lowest_node(node_ptr node) const {
        while (node->left) node = node->left;
        return node;
    }

    void splay(node_ptr node) {
        while (!node->is_root()) {
            auto p_node = node->parent;
            if (!p_node->is_root()) {
                if (node->is_left_child() == p_node->is_left_child()) rotate(p_node);
                else rotate(node);
            }
            rotate(node);
        }
    }

    void rotate(node_ptr node) {
        auto p_node = node->parent;
        bool f = node->is_right_child();
        auto ch_node = (f ? node->left : node->right);

        if (!p_node->is_root()) {
            if (p_node->is_left_child()) p_node->parent->left = node;
            else p_node->parent->right = node;
        }
        node->parent = p_node->parent;

        (f ? node->left : node->right) = p_node;
        p_node->parent = node;
        (!f ? p_node->left : p_node->right) = ch_node;
        if (ch_node) ch_node->parent = p_node;

        p_node->update();
        node->update();
    }
};
