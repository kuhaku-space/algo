#pragma once
#include <functional>
#include <utility>

/// @brief skew heap
/// @see http://hos.ac/blog/#blog0001
template <class T, class Comp = std::less<>>
struct skew_heap {
  private:
    struct _node {
        using pointer = _node *;

        pointer _left, _right;
        T _val;

        constexpr _node() : _left(), _right(), _val() {}
        constexpr _node(const T &val) : _left(), _right(), _val(val) {}
        constexpr _node(T &&val) : _left(), _right(), _val(std::move(val)) {}
        template <typename... Args>
        constexpr _node(Args &&...args) : _left(), _right(), _val(std::forward<Args>(args)...) {}
    };

  public:
    using value_type = T;
    using node_ptr = typename _node::pointer;

    constexpr skew_heap() : _root(), _comp() {}

    constexpr bool empty() const { return !_root; }
    constexpr T top() const { return _root->_val; }

    constexpr void push(const T &val) {
        auto node = new _node(val);
        _root = meld(_root, node);
    }
    constexpr void push(T &&val) {
        auto node = new _node(std::move(val));
        _root = meld(_root, node);
    }
    template <typename... Args>
    constexpr void emplace(Args &&...args) {
        auto node = new _node(std::forward<Args>(args)...);
        _root = meld(_root, node);
    }

    constexpr void pop() { _root = meld(_root->_left, _root->_right); }

    constexpr void meld(const skew_heap<T, Comp> &rhs) { _root = meld(_root, rhs._root); }

  private:
    node_ptr _root;
    Comp _comp;

    constexpr node_ptr meld(node_ptr a, node_ptr b) const {
        if (!a) return b;
        if (!b) return a;
        if (_comp(a->_val, b->_val)) std::swap(a, b);
        a->_right = meld(a->_right, b);
        std::swap(a->_left, a->_right);
        return a;
    }
};
