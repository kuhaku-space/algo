#pragma once
#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

/**
 * @brief 動的セグメント木
 *
 * @tparam M モノイド
 */
template <class M>
struct dynamic_segment_tree {
  private:
    using T = typename M::value_type;

    struct _node {
        using pointer = _node *;
        pointer left, right;
        T value;

        constexpr _node() : left(nullptr), right(nullptr), value(M::id) {}
    };

  public:
    using node_ptr = typename _node::pointer;

    dynamic_segment_tree(std::int64_t n) : root(), _size(n) { this->init(); }

    T operator[](int k) const {
        node_ptr node = this->root;
        std::int64_t l = 0, r = _size;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            if (k >= m) {
                if (!node->right) return M::id;
                l = m;
                node = node->right;
            } else {
                if (!node->left) return M::id;
                r = m;
                node = node->left;
            }
        }
        return node->value;
    }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void set(std::int64_t k, T x) {
        assert(0 <= k && k < this->_size);
        node_ptr node = this->root;
        std::vector<node_ptr> nodes;
        std::int64_t l = 0, r = _size;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            nodes.emplace_back(node);
            if (k >= m) {
                if (!node->right) node->right = new _node();
                l = m;
                node = node->right;
            } else {
                if (!node->left) node->left = new _node();
                r = m;
                node = node->left;
            }
        }
        node->value = x;

        std::reverse(begin(nodes), end(nodes));
        for (auto node : nodes) {
            node->value = M::op(node->left ? node->left->value : M::id,
                                node->right ? node->right->value : M::id);
        }
    }
    void reset(std::int64_t k) { this->set(k, M::id); }

    T all_prod() const { return this->root ? this->root->value : M::id; }
    T prod(std::int64_t a, std::int64_t b) const {
        assert(0 <= a && a <= this->_size);
        assert(0 <= b && b <= this->_size);
        return this->prod(a, b, this->root, 0, this->_size);
    }

    template <class F>
    std::int64_t max_right(F f) const {
        assert(f(M::id));
        if (this->root == nullptr || f(this->root->value)) return this->_size;
        node_ptr node = this->root;
        T sm = M::id;
        std::int64_t l = 0, r = this->_size;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            if (node->left == nullptr || f(M::op(sm, node->left->value))) {
                if (node->left != nullptr) sm = M::op(sm, node->left->value);
                l = m;
                node = node->right;
            } else {
                r = m;
                node = node->left;
            }
        }
        return f(M::op(sm, node->value)) ? r : l;
    }

    template <class F>
    std::int64_t min_left(F f) const {
        assert(f(M::id));
        if (this->root == nullptr || f(this->root->value)) return 0;
        node_ptr node = this->root;
        T sm = M::id;
        std::int64_t l = 0, r = this->_size;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            if (node->right == nullptr || f(M::op(node->right->value, sm))) {
                if (node->right != nullptr) sm = M::op(node->right->value, sm);
                r = m;
                node = node->left;
            } else {
                l = m;
                node = node->right;
            }
        }
        return f(M::op(node->value, sm)) ? l : r;
    }

  private:
    node_ptr root;
    std::int64_t _size;

    void init() { this->root = new _node(); }

    T prod(std::int64_t a, std::int64_t b, node_ptr node, std::int64_t l, std::int64_t r) const {
        if (a <= l && r <= b) return node->value;
        if (r <= a || b <= l) return M::id;

        return M::op(node->left ? this->prod(a, b, node->left, l, (l + r) >> 1) : M::id,
                     node->right ? this->prod(a, b, node->right, (l + r) >> 1, r) : M::id);
    }
};
