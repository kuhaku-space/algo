#pragma once
#include <cassert>
#include <cmath>
#include <vector>

/// @brief スケープゴート木
/// @see https://kopricky.github.io/code/BinarySearchTree/scapegoat_tree.html
template <class T>
struct scapegoat_tree {
  private:
    struct node_t {
        using pointer = node_t *;

        T val;
        unsigned int size;
        pointer left, right;

        node_t(T _val) : val(_val), size(1), left(nullptr), right(nullptr) {}

        static constexpr int get_size(pointer node) { return node ? node->size : 0; }

        void eval() { size = 1 + node_t::get_size(left) + node_t::get_size(right); }
    };

  public:
    using node_ptr = typename node_t::pointer;

    scapegoat_tree(const double _alpha = 2.0 / 3.0)
        : root(nullptr), alpha(_alpha), log_val(-1.0 / std::log2(_alpha)), max_element_size(0) {}

    constexpr bool empty() const { return !(root); }

    constexpr int size() const { return empty() ? 0 : root->size; }

    constexpr bool contains(T val) const {
        node_ptr node = root;
        while (node) {
            if (node->val == val) return true;
            node = (val < node->val ? node->left : node->right);
        }
        return false;
    }

    constexpr T index(int k) const {
        assert(k < size());
        node_ptr node = root;
        while (node) {
            if (node_t::get_size(node->left) == k) break;
            else if (k < node_t::get_size(node->left)) node = node->left;
            else k -= node_t::get_size(node->left) + 1, node = node->right;
        }
        return node->val;
    }
    constexpr T kth_element(int k) const { return index(k); }

    void insert(T val) {
        max_element_size = std::max(max_element_size, size() + 1);
        bool balanced = true;
        root = insert(root, val, 0, balanced);
        assert(balanced);
    }

    void erase(T val) {
        root = erase(root, val);
        check();
    }

    int count(T val) {
        int res = 0;
        node_ptr node = root;
        while (node) {
            if (node->val < val) res += node_t::get_size(node->left) + 1;
            node = (val <= node->val ? node->left : node->right);
        }
        return res;
    }

  private:
    node_ptr root;
    double alpha, log_val;
    int max_element_size;

    void subtree_dfs(node_ptr node, std::vector<node_ptr> &nodes) const {
        if (node->left) subtree_dfs(node->left, nodes);
        nodes.emplace_back(node);
        if (node->right) subtree_dfs(node->right, nodes);
    }
    node_ptr build_pbbt_rec(int l, int r, const std::vector<node_ptr> &nodes) {
        if (r - l == 0) {
            return nullptr;
        } else if (r - l == 1) {
            node_ptr node = nodes[l];
            node->left = node->right = nullptr;
            node->eval();
            return node;
        }
        int mid = (l + r) >> 1;
        node_ptr node = nodes[mid];
        node->left = build_pbbt_rec(l, mid, nodes);
        node->right = build_pbbt_rec(mid + 1, r, nodes);
        node->eval();
        return node;
    }
    node_ptr build_pbbt(node_ptr node) {
        if (!node) return nullptr;
        std::vector<node_ptr> nodes;
        subtree_dfs(node, nodes);
        return build_pbbt_rec(0, nodes.size(), nodes);
    }

    node_ptr insert(node_ptr node, T val, int depth, bool &balanced) {
        if (!node) {
            balanced = (depth <= std::floor(log_val * std::log2(max_element_size)));
            return new node_t(val);
        } else if (val < node->val) {
            node->left = insert(node->left, val, depth + 1, balanced);
            node->eval();
            if (balanced || node->left->size <= alpha * node->size) return node;
        } else {
            node->right = insert(node->right, val, depth + 1, balanced);
            node->eval();
            if (balanced || node->right->size <= alpha * node->size) return node;
        }
        balanced = true;
        return build_pbbt(node);
    }

    node_ptr join(node_ptr left, node_ptr right) {
        if (!left || !right) {
            return left ? left : right;
        } else if (left->size < right->size) {
            right->left = join(left, right->left);
            right->eval();
            return right;
        } else {
            left->right = join(left->right, right);
            left->eval();
            return left;
        }
    }

    node_ptr erase(node_ptr node, T val) {
        if (!node) {
            return nullptr;
        } else if (node->val == val) {
            return join(node->left, node->right);
        } else if (val < node->val) {
            node->left = erase(node->left, val);
            node->eval();
            return node;
        } else {
            node->right = erase(node->right, val);
            node->eval();
            return node;
        }
    }

    void check() {
        if (size() >= alpha * max_element_size) return;
        root = build_pbbt(root);
        max_element_size = size();
    }
};
