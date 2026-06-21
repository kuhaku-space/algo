#pragma once
#include <functional>
#include <utility>
#include <vector>

/// @brief skew heap（融合可能ヒープ）
/// @see http://hos.ac/blog/#blog0001
/// @details ノードを `std::vector` のプールに置き `int` インデックスで連結する index-pool
///          実装で、`new`/`delete` を一切行わない（コピー・ムーブも自動で正しい）。
///          `Comp = std::less<>` で最大ヒープ、`std::greater<>` で最小ヒープ。
/// @note `meld` は引数のヒープを空にして要素を取り込む破壊的操作。
template <class T, class Comp = std::less<>>
struct skew_heap {
  private:
    struct _node {
        T val;
        int left, right;  // 子のプールインデックス（-1 で null）
    };
    static constexpr int nil = -1;

  public:
    using value_type = T;

    skew_heap() : pool(), root(nil), _size(), comp() {}

    constexpr bool empty() const { return root == nil; }
    constexpr int size() const { return _size; }
    T top() const { return pool[root].val; }

    void push(const T &val) { root = meld(root, make_node(val)), ++_size; }
    void push(T &&val) { root = meld(root, make_node(std::move(val))), ++_size; }
    template <class... Args>
    void emplace(Args &&...args) {
        root = meld(root, make_node(T(std::forward<Args>(args)...))), ++_size;
    }

    void pop() { root = meld(pool[root].left, pool[root].right), --_size; }

    // rhs を空にして、その全要素を自分へ取り込む。
    void meld(skew_heap &rhs) {
        if (this == &rhs || rhs.root == nil) return;
        int offset = (int)pool.size();
        pool.insert(pool.end(), rhs.pool.begin(), rhs.pool.end());
        // 取り込んだ側のインデックスを offset 分ずらす。
        for (int i = offset; i < (int)pool.size(); ++i) {
            if (pool[i].left != nil) pool[i].left += offset;
            if (pool[i].right != nil) pool[i].right += offset;
        }
        root = meld(root, rhs.root + offset);
        _size += rhs._size;
        rhs.pool.clear();
        rhs.root = nil;
        rhs._size = 0;
    }

  private:
    std::vector<_node> pool;
    int root;
    int _size;
    Comp comp;

    int make_node(T val) {
        pool.push_back({std::move(val), nil, nil});
        return (int)pool.size() - 1;
    }

    int meld(int a, int b) {
        if (a == nil) return b;
        if (b == nil) return a;
        if (comp(pool[a].val, pool[b].val)) std::swap(a, b);
        pool[a].right = meld(pool[a].right, b);
        std::swap(pool[a].left, pool[a].right);
        return a;
    }
};
