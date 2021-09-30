#include "template/template.hpp"

/**
 * @brief 動的セグメント木
 *
 * @tparam T
 * @tparam F
 */
template <class T, class F>
struct dynamic_segment_tree {
    struct Node {
        Node *parent, *left, *right;
        T value;

        Node(Node *ptr) : parent(ptr), left(nullptr), right(nullptr), value() {}
    };

    Node *root;
    int64_t N;
    const T e;
    const F op;

    dynamic_segment_tree(int64_t _n, T _e, F &&_op) : e(_e), op(_op) { init(_n); }
    dynamic_segment_tree(int64_t _n, T _e, const F &_op) : e(_e), op(_op) { init(_n); }

    void init(int64_t n) {
        for (this->N = 1; N < n; this->N <<= 1) {}
        this->root = new Node(nullptr);
    }

    void update(int64_t k, T x) {
        assert(0 <= k && k < N);
        Node *node = this->root;
        int64_t l = 0, r = this->N;
        while (r - l > 1) {
            int64_t m = (l + r) >> 1;
            if (k < m) {
                if (!node->left) node->left = new Node(node);
                node = node->left;
                r = m;
            } else {
                if (!node->right) node->right = new Node(node);
                node = node->right;
                l = m;
            }
        }

        node->value = x;
        while (node->parent) {
            node = node->parent;
            node->value =
                op(node->left ? node->left->value : e, node->right ? node->right->value : e);
        }
    }

    T query() const { return this->root->value; }
    T query(int64_t a, int64_t b) const {
        assert(0 <= a && a <= N);
        assert(0 <= b && b <= N);
        return this->query(a, b, this->root, 0, this->N);
    }
    T query(int64_t a, int64_t b, Node *node, int64_t l, int64_t r) const {
        if (a <= l && r <= b) return node->value;
        if (r <= a || b <= l) return e;

        return op(node->left ? this->query(a, b, node->left, l, (l + r) >> 1) : e,
                  node->right ? this->query(a, b, node->right, (l + r) >> 1, r) : e);
    }
};
