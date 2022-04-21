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

        pointer l, r;
        T val;

        constexpr _node() : l(), r(), val() {}
        constexpr _node(T _val) : l(), r(), val(_val) {}
    };

  public:
    using node_pointer = _node::pointer;

    constexpr auto top() const { return this->root->val; }
    constexpr bool empty() const { return this->root == nullptr; }

    void push(T val) {
        auto node = new _node(val);
        this->meld(this->root, node);
    }

    void pop() { this->root = this->meld(this->root->l, this->root->r); }

    node_pointer meld(node_pointer a, node_pointer b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a.val > b.val) swap(a, b);
        a.r = this->meld(a.r, b);
        swap(a.l, a.r);
        return a;
    }

  private:
    node_pointer root;
};
