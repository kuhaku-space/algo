#pragma once
#include <cstring>
#include <vector>

/// @brief 永続配列
/// @see https://ei1333.github.io/luzhiled/snippets/structure/persistent-array.html
/// @see https://qiita.com/hotman78/items/9c643feae1de087e6fc5
/// @see https://37zigen.com/persistent-array/
template <class T, int B = 4>
struct persistent_array {
  private:
    static constexpr int MASK = (1 << B) - 1;

    struct _node {
        using pointer = _node *;
        T val;
        pointer ch[1 << B] = {};
    };
    using node_ptr = typename _node::pointer;

  public:
    constexpr persistent_array() : root() {}
    constexpr persistent_array(node_ptr _root) : root(_root) {}
    constexpr persistent_array(int n, T val) : root() {
        for (int i = 0; i < n; ++i) { root = set(i, val, root); }
    }
    template <class U>
    constexpr persistent_array(const std::vector<U> &v) : root() {
        for (int i = 0; i < (int)v.size(); ++i) { root = set(i, v[i], root); }
    }

    constexpr T operator[](int i) const noexcept {
        node_ptr node = root;
        while (node) {
            if (i == 0) return node->val;
            else --i, node = node->ch[i & MASK], i = i >> B;
        }
        return T();
    }
    constexpr T at(int k) const noexcept { return operator[](k); }
    constexpr T get(int k) const noexcept { return operator[](k); }

    persistent_array set(int k, T val) const noexcept {
        return persistent_array(set(k, val, root));
    }

  private:
    node_ptr root;

    node_ptr set(int k, T val, node_ptr node) const noexcept {
        node_ptr res = new _node();
        if (node) {
            res->val = node->val;
            std::memcpy(res->ch, node->ch, sizeof(node->ch));
        }
        if (k == 0) res->val = val;
        else --k, res->ch[k & MASK] = set(k >> B, val, res->ch[k & MASK]);
        return res;
    }
};
