#pragma once
#include <functional>
#include <utility>
#include <vector>

/// @brief leftist heap（融合可能ヒープ）
/// @see http://hos.ac/blog/#blog0001
/// @details ノードを `std::vector` のプールに置き `int` インデックスで連結する index-pool
///          実装で、`new`/`delete` を一切行わない（コピー・ムーブも自動で正しい）。
///          各ノードの rank（右脊柱の長さ）でバランスを保ち、`meld` は O(log N)。
///          `Comp = std::less<>` で最大ヒープ、`std::greater<>` で最小ヒープ。
/// @note `meld` は引数のヒープを空にして要素を取り込む破壊的操作。
template <class T, class Comp = std::less<>>
struct leftist_heap {
  private:
    struct _node {
        T val;
        int left, right;  // 子のプールインデックス（-1 で null）
        int rank;
    };
    static constexpr int nil = -1;

  public:
    using value_type = T;

    leftist_heap() : pool(), root(nil), _size(), comp() {}

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
    void meld(leftist_heap &rhs) {
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
        pool.push_back({std::move(val), nil, nil, 0});
        return (int)pool.size() - 1;
    }

    int rank(int x) const { return x == nil ? 0 : pool[x].rank; }

    int meld(int a, int b) {
        if (a == nil) return b;
        if (b == nil) return a;
        if (comp(pool[a].val, pool[b].val)) std::swap(a, b);
        pool[a].right = meld(pool[a].right, b);
        if (rank(pool[a].left) < rank(pool[a].right)) std::swap(pool[a].left, pool[a].right);
        pool[a].rank = rank(pool[a].right) + 1;
        return a;
    }
};
