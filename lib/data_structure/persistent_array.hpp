#include "template/template.hpp"

/**
 * @brief 永続配列
 * @see https://ei1333.github.io/luzhiled/snippets/structure/persistent-array.html
 * @see https://qiita.com/hotman78/items/9c643feae1de087e6fc5
 * @see https://37zigen.com/persistent-array/
 *
 * @tparam T 要素の型
 * @tparam B ビットサイズ
 */
template <class T, int B = 4>
struct persistent_array {
  private:
    static constexpr int MASK = (1 << B) - 1;

    struct Node {
        using pointer = Node *;
        T val;
        pointer ch[1 << B] = {};
    };
    using node_pointer = typename Node::pointer;

  public:
    constexpr persistent_array() : root() {}
    constexpr persistent_array(node_pointer _root) : root(_root) {}
    constexpr persistent_array(int n, T val) : root() {
        for (int i = 0; i < n; ++i) { this->root = this->set(i, val, this->root); }
    }
    template <class U>
    constexpr persistent_array(const std::vector<U> &v) : root() {
        for (int i = 0; i < (int)v.size(); ++i) { this->root = this->set(i, v[i], this->root); }
    }

    constexpr T operator[](int i) const noexcept {
        node_pointer node = this->root;
        while (node) {
            if (i == 0) {
                return node->val;
            } else {
                --i;
                node = node->ch[i & MASK], i = i >> B;
            }
        }
        return T();
    }
    constexpr T at(int k) const noexcept { return this->operator[](k); }
    constexpr T get(int k) const noexcept { return this->operator[](k); }

    persistent_array set(int k, T val) const noexcept {
        return persistent_array(this->set(k, val, this->root));
    }

  private:
    node_pointer root;

    node_pointer set(int k, T val, node_pointer node) const noexcept {
        node_pointer res = new Node();
        if (node) {
            memcpy(res->ch, node->ch, sizeof(node->ch));
            res->val = node->val;
        }
        if (k == 0) {
            res->val = val;
        } else {
            --k;
            res->ch[k & MASK] = set(k >> B, val, res->ch[k & MASK]);
        }
        return res;
    }
};
