#include "template/template.hpp"

/**
 * @brief 2分トライ木
 * @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654
 *
 * @tparam T 要素の型
 * @tparam B ビットサイズ
 */
template <class T, int B = 31>
struct binary_trie {
  private:
    struct _node {
        using pointer = _node *;
        int count;
        pointer ch[2];
        _node() : count(), ch{nullptr, nullptr} {}
    };

  public:
    using node_ptr = typename _node::pointer;

    constexpr binary_trie() : root(nullptr) {}

    T operator[](int i) const {
        assert(0 <= i && i < this->size());
        return this->get(this->root, i);
    }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }
    T kth_element(int k) const { return this->operator[](k); }

    constexpr bool empty() const { return !this->root; }

    constexpr int size() const { return this->empty() ? 0 : this->root->count; }

    void insert(T val) {
        if (!this->count(val)) this->root = this->add(this->root, val);
    }

    void erase(T val) {
        if (this->count(val)) this->root = this->sub(this->root, val);
    }

    T max_element(T bias = 0) const { return this->get_min(this->root, ~bias); }
    T min_element(T bias = 0) const { return this->get_min(this->root, bias); }
    int lower_bound(T val) const { return this->count_lower(this->root, val); }
    int upper_bound(T val) const { return this->count_lower(this->root, val + 1); }
    int count(T val) const {
        if (!this->root) return 0;
        node_ptr node = this->root;
        for (int i = B - 1; i >= 0; i--) {
            node = node->ch[val >> i & 1];
            if (!node) return 0;
        }
        return node->count;
    }

  private:
    node_ptr root;

    node_ptr add(node_ptr node, T val, int b = B - 1) {
        if (!node) node = new _node();
        ++node->count;
        if (b < 0) return node;
        bool f = val >> b & (T)1;
        node->ch[f] = this->add(node->ch[f], val, b - 1);
        return node;
    }
    node_ptr sub(node_ptr node, T val, int b = B - 1) {
        assert(node);
        --node->count;
        if (!node->count) return nullptr;
        if (b < 0) return node;
        bool f = val >> b & (T)1;
        node->ch[f] = this->sub(node->ch[f], val, b - 1);
        return node;
    }
    T get_min(node_ptr node, T val, int b = B - 1) const {
        assert(node);
        if (b < 0) return 0;
        bool f = val >> b & (T)1;
        f ^= !node->ch[f];
        return this->get_min(node->ch[f], val, b - 1) | ((T)f << (T)b);
    }
    T get(node_ptr node, int k, int b = B - 1) const {
        if (b < 0) return 0;
        int m = node->ch[0] ? node->ch[0]->count : 0;
        return k < m ? this->get(node->ch[0], k, b - 1)
                     : this->get(node->ch[1], k - m, b - 1) | ((T)1 << b);
    }
    int count_lower(node_ptr node, T val, int b = B - 1) const {
        if (!node || b < 0) return 0;
        bool f = val >> b & 1;
        return (f && node->ch[0] ? node->ch[0]->count : 0) +
               this->count_lower(node->ch[f], val, b - 1);
    }
};
