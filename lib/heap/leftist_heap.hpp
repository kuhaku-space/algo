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

        pointer l, r;
        int s;
        T val;

        constexpr _node() : l(), r(), s(), val() {}
        constexpr _node(T _val) : l(), r(), s(), val(_val) {}
    };

  public:
    using node_type = typename _node::pointer;

    leftist_heap() : root() {}

    constexpr auto top() const { return this->root->val; }
    constexpr bool empty() const { return this->root == nullptr; }

    void push(T val) {
        auto node = new _node(val);
        this->meld(root, node);
    }

    void pop() { this->root = this->meld(this->root->l, this->root->r); }

    node_type meld(node_type a, node_type b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a.val > b.val) swap(a, b);
        a.r = this->meld(a.r, b);
        if (a.l is null || a.l.s < a.r.s) swap(a.l, a.r);
        a.s = ((a.r == nullptr) ? 0 : a.r.s) + 1;
        return a;
    }

  private:
    node_type root;
};
