#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

/**
 * @brief 永続セグメント木
 *
 * @tparam M モノイド
 */
template <class M>
struct persistent_segment_tree {
  private:
    using T = typename M::value_type;

    struct Node {
        using pointer = Node *;
        T val;
        pointer left, right;

        constexpr Node(T _val) : val(_val), left(), right() {}
        constexpr Node(T _val, pointer _left, pointer _right)
            : val(_val), left(_left), right(_right) {}
    };

  public:
    using node_pointer = typename Node::pointer;

    constexpr persistent_segment_tree() : _size(), root() {}
    constexpr persistent_segment_tree(int n, node_pointer _root) : _size(n), root(_root) {}
    persistent_segment_tree(int n, T e = M::id) : _size(n), root(this->build(0, n, e)) {}
    template <class U>
    persistent_segment_tree(const std::vector<U> &v)
        : _size(v.size()), root(this->build(0, v.size(), v)) {}

    T operator[](int i) const { return this->prod(i, i + 1); }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    persistent_segment_tree set(int k, T val) {
        assert(0 <= k && k < this->_size);
        return persistent_segment_tree(this->_size, this->set(0, this->_size, k, val, this->root));
    }
    persistent_segment_tree reset(int k) { return this->set(k, M::id); }

    T all_prod() const { return this->root->val; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->_size);
        return this->prod(0, this->_size, a, b, this->root);
    }

  private:
    int _size;
    node_pointer root;

    static node_pointer merge(node_pointer left, node_pointer right) {
        return new Node(M::op(left->val, right->val), left, right);
    }

    node_pointer build(int l, int r, T val) const {
        if (l + 1 == r) return new Node(val);
        int m = (l + r) >> 1;
        return this->merge(this->build(l, m, val), this->build(m, r, val));
    }
    template <class U>
    node_pointer build(int l, int r, const std::vector<U> &v) const {
        if (l + 1 == r) return new Node(v[l]);
        int m = (l + r) >> 1;
        return this->merge(this->build(l, m, v), this->build(m, r, v));
    }

    node_pointer set(int l, int r, int k, T val, node_pointer node) const {
        if (l + 1 == r) return new Node(val);
        int m = (l + r) >> 1;
        if (k < m) return this->merge(this->set(l, m, k, val, node->left), node->right);
        else return this->merge(node->left, this->set(m, r, k, val, node->right));
    }

    T prod(int l, int r, int a, int b, node_pointer node) const {
        if (a <= l && r <= b) return node->val;
        if (b <= l || r <= a) return M::id;
        int m = (l + r) >> 1;
        return M::op(this->prod(l, m, a, b, node->left), this->prod(m, r, a, b, node->right));
    }
};
