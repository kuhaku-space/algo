#pragma once
#include <cassert>
#include <utility>
#include <vector>

/// @brief 永続キュー
/// @tparam T
/// @complexity 追加・先頭取得は $O(\log n)$、削除・サイズ取得は $O(1)$
template <class T>
struct PersistentQueue {
  private:
    struct Node {
        using pointer = Node *;
        T val;
        std::vector<pointer> prev;

        constexpr Node(const T &_val) : val(_val), prev() {}
        constexpr Node(T &&_val) : val(std::move(_val)), prev() {}
        template <typename... Args>
        constexpr Node(Args &&...args) : val(std::forward<Args>(args)...), prev() {}
    };

  public:
    /// @brief 内部ノードへのpointer型
    /// @complexity 型エイリアスで実行時計算量はない
    using node_ptr = typename Node::pointer;

    /// @brief 空のqueueを構築する
    /// @complexity $O(1)$
    constexpr PersistentQueue() : _size(), root() {}

    /// @brief 既存の根からサイズnのversionを構築する
    /// @complexity $O(1)$
    constexpr PersistentQueue(int n, node_ptr _root) : _size(n), root(_root) {}

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return _size; }

    /// @brief 空か返す
    /// @complexity $O(1)$
    constexpr bool empty() const { return _size == 0; }

    /// @brief 先頭要素を返す
    /// @complexity $O(\log n)$
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

    /// @brief 先頭要素を返す
    /// @complexity $O(\log n)$
    constexpr T front() const { return top(); }

    /// @brief 末尾にvalを追加した新しいversionを返す
    /// @complexity $O(\log n)$
    PersistentQueue push(const T &val) const {
        node_ptr new_node = new Node(val);
        return push_node(new_node);
    }

    /// @brief 末尾にvalをmoveして追加した新しいversionを返す
    /// @complexity $O(\log n)$
    PersistentQueue push(T &&val) const {
        node_ptr new_node = new Node(std::move(val));
        return push_node(new_node);
    }

    /// @brief 末尾に要素を直接構築した新しいversionを返す
    /// @complexity $O(\log n)$
    template <typename... Args>
    PersistentQueue emplace(Args &&...args) const {
        node_ptr new_node = new Node(std::forward<Args>(args)...);
        return push_node(new_node);
    }

    /// @brief 先頭を削除した新しいversionを返す
    /// @complexity $O(1)$
    PersistentQueue pop() const {
        assert(!empty());
        return PersistentQueue(_size - 1, root);
    }

  private:
    int _size;
    node_ptr root;

    PersistentQueue push_node(node_ptr new_node) const {
        node_ptr node = root;
        new_node->prev.emplace_back(node);
        int k = 0;
        while (node) {
            if (k < (int)node->prev.size()) node = node->prev[k++];
            else node = nullptr;
            new_node->prev.emplace_back(node);
        }
        return PersistentQueue(_size + 1, new_node);
    }
};
