#include "template/template.hpp"

template <class T>
struct persistent_array {
  private:
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

    constexpr persistent_array() : _size(), root() {}
    constexpr persistent_array(int n, node_pointer _root) : _size(n), root(_root) {}
    persistent_array(int n, T e = T()) : _size(n), root(this->build(0, n, e)) {}
    template <class U>
    persistent_array(const vector<U> &v) : _size(v.size()), root(this->build(0, v.size(), v)) {}

    constexpr T operator[](int i) const { return this->get(0, this->_size, i, this->root); }
    constexpr T at(int k) const { return this->operator[](k); }
    constexpr T get(int k) const { return this->operator[](k); }

    persistent_array set(int k, T val) {
        return persistent_array(this->_size, this->set(0, this->_size, k, val, this->root));
    }

  private:
    int _size;
    node_pointer root;

    node_pointer update(node_pointer left, node_pointer right) const {
        return new Node(T(), left, right);
    }

    node_pointer build(int l, int r, T val) const {
        if (l + 1 == r) return new Node(val);
        int m = (l + r) >> 1;
        return this->update(this->build(l, m, val), this->build(m, r, val));
    }
    template <class U>
    node_pointer build(int l, int r, const vector<U> &v) const {
        if (l + 1 == r) return new Node(v[l]);
        int m = (l + r) >> 1;
        return this->update(this->build(l, m, v), this->build(m, r, v));
    }

    node_pointer set(int l, int r, int k, T val, node_pointer node) const {
        if (l + 1 == r) return new Node(val);
        int m = (l + r) >> 1;
        if (k < m) return this->update(this->set(l, m, k, val, node->left), node->right);
        else return this->update(node->left, this->set(m, r, k, val, node->right));
    }

    constexpr T get(int l, int r, int k, node_pointer node) const {
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (k < m) {
                node = node->left;
                r = m;
            } else {
                node = node->right;
                l = m;
            }
        }
        return node->val;
    }
};
