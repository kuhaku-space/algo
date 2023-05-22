#include "template/template.hpp"

/**
 * @brief skew heap
 *
 * @tparam T 要素の型
 *
 * @see http://hos.ac/blog/#blog0001
 */
template <class T>
struct skew_heap {
  private:
    struct _node {
        using pointer = _node *;

        pointer _left, _right;
        T _val;

        constexpr _node() : _left(), _right(), _val() {}
        constexpr _node(T _val) : _left(), _right(), _val(_val) {}
    };

  public:
    using value_type = T;
    using node_ptr = typename _node::pointer;

    constexpr skew_heap() : _root() {}

    constexpr T top() const { return _root->_val; }
    constexpr bool empty() const { return _root == nullptr; }

    constexpr void emplace(T val) {
        auto node = new _node(val);
        _root = meld(_root, node);
    }
    constexpr void push(T val) { emplace(val); }

    constexpr void pop() { _root = meld(_root->_left, _root->_right); }

    constexpr node_ptr meld(node_ptr a, node_ptr b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a->_val < b->_val) std::swap(a, b);
        a->_right = meld(a->_right, b);
        std::swap(a->_left, a->_right);
        return a;
    }

  private:
    node_ptr _root;
};
