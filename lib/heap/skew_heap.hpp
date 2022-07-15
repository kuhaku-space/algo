#include "template/template.hpp"

/**
 * @brief skew heap
 *
 * @tparam T 要素の型
 */
template <class T>
struct skew_heap {
  private:
    struct _node {
        using pointer = _node *;

        pointer left, right;
        T val;

        constexpr _node() : left(), right(), val() {}
        constexpr _node(T _val) : left(), right(), val(_val) {}
    };

  public:
    using value_type = T;
    using node_ptr = _node::pointer;

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
        swap(a.left, a.right);
        return a;
    }

  private:
    node_ptr root;
};
