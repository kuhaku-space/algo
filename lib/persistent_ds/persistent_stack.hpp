#pragma once
#include <cassert>
#include <utility>

/// @brief 永続スタック
/// @complexity すべての操作が $O(1)$
template <class T>
struct PersistentStack {
  private:
    struct Node {
        using pointer = Node *;
        pointer prev;
        T val;

        constexpr Node(pointer p, const T &v) : prev(p), val(v) {}
        constexpr Node(pointer p, T &&v) : prev(p), val(std::move(v)) {}
        template <typename... Args>
        constexpr Node(pointer p, Args &&...args) : prev(p), val(std::forward<Args>(args)...) {}
    };

  public:
    /// @brief 内部ノードへのpointer型
    /// @complexity 型エイリアスで実行時計算量はない
    using node_ptr = Node::pointer;

    /// @brief 空のstackを構築する
    /// @complexity $O(1)$
    constexpr PersistentStack() : _size(), root() {}

    /// @brief 既存の根からサイズnのversionを構築する
    /// @complexity $O(1)$
    constexpr PersistentStack(int n, node_ptr _root) : _size(n), root(_root) {}

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
    PersistentStack push(const T &val) const { return PersistentStack(_size + 1, new Node(root, val)); }

    /// @brief 先頭にvalをmoveして追加した新しいversionを返す
    /// @complexity $O(1)$
    PersistentStack push(T &&val) const { return PersistentStack(_size + 1, new Node(root, std::move(val))); }

    /// @brief 先頭に要素を直接構築した新しいversionを返す
    /// @complexity $O(1)$
    template <typename... Args>
    PersistentStack emplace(Args &&...args) const {
        return PersistentStack(_size + 1, new Node(root, std::forward<Args>(args)...));
    }

    /// @brief 先頭を削除した新しいversionを返す
    /// @complexity $O(1)$
    PersistentStack pop() const {
        assert(!empty());
        return PersistentStack(_size - 1, root->prev);
    }

  private:
    int _size;
    node_ptr root;
};
