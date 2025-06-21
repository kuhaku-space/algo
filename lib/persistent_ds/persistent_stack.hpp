#pragma once
#include <cassert>
#include <utility>

/// @brief 永続スタック
template <class T>
struct persistent_stack {
  private:
    struct _node {
        using pointer = _node *;
        pointer prev;
        T val;

        constexpr _node(pointer p, const T &v) : prev(p), val(v) {}
        constexpr _node(pointer p, T &&v) : prev(p), val(std::move(v)) {}
        template <typename... Args>
        constexpr _node(pointer p, Args &&...args) : prev(p), val(std::forward<Args>(args)...) {}
    };

  public:
    using node_ptr = _node::pointer;

    constexpr persistent_stack() : _size(), root() {}
    constexpr persistent_stack(int n, node_ptr _root) : _size(n), root(_root) {}

    constexpr int size() const { return _size; }
    constexpr bool empty() const { return _size == 0; }

    constexpr T top() const {
        assert(!empty());
        return root->val;
    }
    constexpr T front() const { return top(); }

    persistent_stack push(const T &val) const { return persistent_stack(_size + 1, new _node(root, val)); }
    persistent_stack push(T &&val) const { return persistent_stack(_size + 1, new _node(root, std::move(val))); }
    template <typename... Args>
    persistent_stack emplace(Args &&...args) const {
        return persistent_stack(_size + 1, new _node(root, std::forward<Args>(args)...));
    }

    persistent_stack pop() const {
        assert(!empty());
        return persistent_stack(_size - 1, root->prev);
    }

  private:
    int _size;
    node_ptr root;
};
