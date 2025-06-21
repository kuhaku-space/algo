#pragma once
#include <cassert>
#include <utility>
#include <vector>

/// @brief 永続キュー
/// @tparam T
template <class T>
struct persistent_queue {
  private:
    struct _node {
        using pointer = _node *;
        T val;
        std::vector<pointer> prev;

        constexpr _node(const T &_val) : val(_val), prev() {}
        constexpr _node(T &&_val) : val(std::move(_val)), prev() {}
        template <typename... Args>
        constexpr _node(Args &&...args) : val(std::forward<Args>(args)...), prev() {}
    };

  public:
    using node_ptr = typename _node::pointer;

    constexpr persistent_queue() : _size(), root() {}
    constexpr persistent_queue(int n, node_ptr _root) : _size(n), root(_root) {}

    constexpr int size() const { return _size; }
    constexpr bool empty() const { return _size == 0; }

    constexpr T top() const {
        assert(!empty());
        node_ptr node = root;
        int k = 0;
        while ((_size - 1) >> k) {
            if ((_size - 1) >> k & 1) node = node->prev[k];
            ++k;
        }
        return node->val;
    }
    constexpr T front() const { return top(); }

    persistent_queue push(const T &val) const {
        node_ptr new_node = new _node(val);
        return push_node(new_node);
    }
    persistent_queue push(T &&val) const {
        node_ptr new_node = new _node(std::move(val));
        return push_node(new_node);
    }
    template <typename... Args>
    persistent_queue emplace(Args &&...args) const {
        node_ptr new_node = new _node(std::forward<Args>(args)...);
        return push_node(new_node);
    }

    persistent_queue pop() const {
        assert(!empty());
        return persistent_queue(_size - 1, root);
    }

  private:
    int _size;
    node_ptr root;

    persistent_queue push_node(node_ptr new_node) const {
        node_ptr node = root;
        new_node->prev.emplace_back(node);
        int k = 0;
        while (node) {
            if (k < (int)node->prev.size()) node = node->prev[k++];
            else node = nullptr;
            new_node->prev.emplace_back(node);
        }
        return persistent_queue(_size + 1, new_node);
    }
};
