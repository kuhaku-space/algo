#pragma once
#include <cassert>
#include <utility>

/// @brief 永続スタック
/// @complexity すべての操作が $O(1)$
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
    /// @brief 内部ノードへのpointer型
    /// @complexity 型エイリアスで実行時計算量はない
    using node_ptr = _node::pointer;

    /// @brief 空のstackを構築する
    /// @complexity $O(1)$
    constexpr persistent_stack() : _size(), root() {}

    /// @brief 既存の根からサイズnのversionを構築する
    /// @complexity $O(1)$
    constexpr persistent_stack(int n, node_ptr _root) : _size(n), root(_root) {}

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return _size; }

    /// @brief 空か返す
    /// @complexity $O(1)$
    constexpr bool empty() const { return _size == 0; }

    /// @brief 先頭要素を返す
    /// @complexity $O(1)$
    constexpr T top() const {
        assert(!empty());
        return root->val;
    }

    /// @brief 先頭要素を返す
    /// @complexity $O(1)$
    constexpr T front() const { return top(); }

    /// @brief 先頭にvalを追加した新しいversionを返す
    /// @complexity $O(1)$
    persistent_stack push(const T &val) const { return persistent_stack(_size + 1, new _node(root, val)); }

    /// @brief 先頭にvalをmoveして追加した新しいversionを返す
    /// @complexity $O(1)$
    persistent_stack push(T &&val) const { return persistent_stack(_size + 1, new _node(root, std::move(val))); }

    /// @brief 先頭に要素を直接構築した新しいversionを返す
    /// @complexity $O(1)$
    template <typename... Args>
    persistent_stack emplace(Args &&...args) const {
        return persistent_stack(_size + 1, new _node(root, std::forward<Args>(args)...));
    }

    /// @brief 先頭を削除した新しいversionを返す
    /// @complexity $O(1)$
    persistent_stack pop() const {
        assert(!empty());
        return persistent_stack(_size - 1, root->prev);
    }

  private:
    int _size;
    node_ptr root;
};
