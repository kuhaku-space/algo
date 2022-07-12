#include "template/template.hpp"

/**
 * @brief leftist heap
 *
 * @tparam T 要素の型
 */
template <class T>
struct leftist_heap {
  private:
    struct _node {
        using pointer = _node *;

        pointer left, right;
        int rank;
        T val;

        constexpr _node() : left(), right(), rank(), val() {}
        constexpr _node(T _val) : left(), right(), rank(), val(_val) {}
    };

  public:
    using value_type = T;
    using node_ptr = typename _node::pointer;

    leftist_heap() : root() {}

    constexpr T top() const { return this->root->val; }
    constexpr bool empty() const { return this->root == nullptr; }

    void push(T val) {
        auto node = new _node(val);
        this->meld(this->root, node);
    }

    void pop() { this->root = this->meld(this->root->left, this->root->right); }

    node_ptr meld(node_ptr a, node_ptr b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a.val > b.val) swap(a, b);
        a.right = this->meld(a.right, b);
        if (a.left == nullptr || a.left.rank < a.right.rank) swap(a.left, a.right);
        a.rank = ((a.right == nullptr) ? 0 : a.right.rank) + 1;
        return a;
    }

  private:
    node_ptr root;
};
