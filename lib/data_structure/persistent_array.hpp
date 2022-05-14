#include "template/template.hpp"

template <class T, int N = 20>
struct persistent_array {
    struct Node {
        using pointer = Node *;
        T val;
        pointer ch[N] = {};
    };
    using node_pointer = typename Node::pointer;

    constexpr persistent_array() : root() {}
    constexpr persistent_array(node_pointer _root) : root(_root) {}
    constexpr persistent_array(int n, T val) : root() {
        for (int i = 0; i < n; ++i) { this->root = this->set(i, val, this->root); }
    }
    template <class U>
    constexpr persistent_array(const vector<U> &v) : root() {
        for (int i = 0; i < (int)v.size(); ++i) { this->root = this->set(i, v[i], this->root); }
    }

    constexpr T operator[](int i) const noexcept {
        node_pointer node = root;
        while (node) {
            if (i == 0) {
                return node->val;
            } else {
                --i;
                node = node->ch[i % N], i = i / N;
            }
        }
        return T();
    }
    constexpr T at(int k) const noexcept { return this->operator[](k); }
    constexpr T get(int k) const noexcept { return this->operator[](k); }

    persistent_array set(int k, T val) const noexcept {
        return persistent_array(this->set(k, val, root));
    }

  private:
    node_pointer root;

    node_pointer set(int k, T val, node_pointer node) const noexcept {
        node_pointer res = new Node();
        if (node) {
            memcpy(res->ch, node->ch, sizeof(node->ch));
            res->val = node->val;
        }
        if (k == 0) {
            res->val = val;
        } else {
            --k;
            res->ch[k % N] = set(k / N, val, res->ch[k % N]);
        }
        return res;
    }
};
