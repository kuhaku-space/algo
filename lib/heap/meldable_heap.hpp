#pragma once
#include <deque>
#include <functional>
#include <memory>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

/// @brief 融合可能ヒープ（leftist heap / skew heap）
/// @see http://hos.ac/blog/#blog0001
/// @details ノードをポインタで連結し、`meld` は右脊柱を辿って融合する。
///          ノード実体は `std::deque` のプールが所有する（要素アドレスが安定し、
///          `new`/`delete` を一切行わずリークもしない）。`meld` で別ヒープの要素を
///          取り込む際は相手のプールを `shared_ptr` で延命するだけなので、プールを
///          コピーせず連結は O(log N) のまま。
///          `Comp = std::less<>` で最大ヒープ、`std::greater<>` で最小ヒープ。
/// @tparam Leftist true なら leftist heap（rank 比較で子を交換、最悪 O(log N)）、
///                 false なら skew heap（無条件に子を交換、ならし O(log N)）。
/// @note `meld` は引数のヒープを空にして要素を取り込む破壊的操作。
template <class T, class Comp = std::less<>, bool Leftist = true>
struct MeldableHeap {
  private:
    struct _node {
        T val;
        _node *left, *right;
        [[no_unique_address]] std::conditional_t<Leftist, int, std::monostate> rank;
    };

  public:
    /// @brief 格納値の型
    /// @complexity 型別名であり実行時計算量はない
    using value_type = T;

    /// @brief 空の融合可能ヒープを構築する
    /// @complexity $O(1)$
    MeldableHeap() : pool(std::make_shared<std::deque<_node>>()), root(nullptr), _size(), comp() {}

    /// @brief 空か返す
    /// @complexity $O(1)$
    constexpr bool empty() const { return root == nullptr; }

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return _size; }

    /// @brief 最上位の値を返す
    /// @complexity $O(1)$
    T top() const { return root->val; }

    /// @brief 値を追加する
    /// @complexity $O(\log n)$
    void push(const T &val) { root = meld(root, make_node(val)), ++_size; }

    /// @brief 値をムーブして追加する
    /// @complexity $O(\log n)$
    void push(T &&val) { root = meld(root, make_node(std::move(val))), ++_size; }

    /// @brief 値を直接構築して追加する
    /// @complexity $O(\log n)$
    template <class... Args>
    void emplace(Args &&...args) {
        root = meld(root, make_node(T(std::forward<Args>(args)...))), ++_size;
    }

    /// @brief 最上位の値を削除する
    /// @complexity $O(\log n)$
    void pop() { root = meld(root->left, root->right), --_size; }

    /// @brief rhsを空にして全要素を融合する
    /// @details rhsのノードプールはshared_ptrで延命される。
    /// @complexity $O(\log(n+m))$
    void meld(MeldableHeap &rhs) {
        if (this == &rhs || rhs.root == nullptr) return;
        if (rhs.pool != pool) extra_pools.push_back(rhs.pool);
        root = meld(root, rhs.root);
        _size += rhs._size;
        rhs.root = nullptr;
        rhs._size = 0;
    }

  private:
    std::shared_ptr<std::deque<_node>> pool;
    // meld で取り込んだ相手のプールを延命するための保持先。
    std::vector<std::shared_ptr<std::deque<_node>>> extra_pools;
    _node *root;
    int _size;
    Comp comp;

    _node *make_node(T val) {
        pool->push_back({std::move(val), nullptr, nullptr, {}});
        return &pool->back();
    }

    static int rank(const _node *x)
    requires Leftist
    {
        return x == nullptr ? 0 : x->rank;
    }

    _node *meld(_node *a, _node *b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (comp(a->val, b->val)) std::swap(a, b);
        a->right = meld(a->right, b);
        if constexpr (Leftist) {
            if (rank(a->left) < rank(a->right)) std::swap(a->left, a->right);
            a->rank = rank(a->right) + 1;
        } else {
            std::swap(a->left, a->right);
        }
        return a;
    }
};
