#pragma once
#include <deque>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

/// @brief leftist heap（融合可能ヒープ）
/// @see http://hos.ac/blog/#blog0001
/// @details ノードをポインタで連結し、`meld` は右脊柱を辿って O(log N) で融合する。
///          ノード実体は `std::deque` のプールが所有する（要素アドレスが安定し、
///          `new`/`delete` を一切行わずリークもしない）。`meld` で別ヒープの要素を
///          取り込む際は相手のプールを `shared_ptr` で延命するだけなので、プールを
///          コピーせず連結は O(log N) のまま。
///          `Comp = std::less<>` で最大ヒープ、`std::greater<>` で最小ヒープ。
/// @note `meld` は引数のヒープを空にして要素を取り込む破壊的操作。
template <class T, class Comp = std::less<>>
struct leftist_heap {
  private:
    struct _node {
        T val;
        _node *left, *right;
        int rank;
    };

  public:
    using value_type = T;

    leftist_heap() : pool(std::make_shared<std::deque<_node>>()), root(nullptr), _size(), comp() {}

    constexpr bool empty() const { return root == nullptr; }
    constexpr int size() const { return _size; }
    T top() const { return root->val; }

    void push(const T &val) { root = meld(root, make_node(val)), ++_size; }
    void push(T &&val) { root = meld(root, make_node(std::move(val))), ++_size; }
    template <class... Args>
    void emplace(Args &&...args) {
        root = meld(root, make_node(T(std::forward<Args>(args)...))), ++_size;
    }

    void pop() { root = meld(root->left, root->right), --_size; }

    // rhs を空にして、その全要素を自分へ取り込む。rhs のノードは rhs のプールが
    // 所有しているので、そのプールを shared_ptr で延命して以後も参照できるようにする。
    void meld(leftist_heap &rhs) {
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
        pool->push_back({std::move(val), nullptr, nullptr, 0});
        return &pool->back();
    }

    static int rank(const _node *x) { return x == nullptr ? 0 : x->rank; }

    _node *meld(_node *a, _node *b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (comp(a->val, b->val)) std::swap(a, b);
        a->right = meld(a->right, b);
        if (rank(a->left) < rank(a->right)) std::swap(a->left, a->right);
        a->rank = rank(a->right) + 1;
        return a;
    }
};
