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

    T operator[](int k) const {
        assert(0 <= k && k < size());
        return get(root, k);
    }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    T kth_element(int k) const { return operator[](k); }

    constexpr bool empty() const { return !root; }
    constexpr int size() const { return empty() ? 0 : root->count; }

    void insert(T val) {
        if (!count(val)) root = insert(root, val);
    }
    void erase(T val) {
        if (count(val)) root = erase(root, val);
    }

    T max_element(T bias = 0) const { return get_min(root, ~bias); }
    T min_element(T bias = 0) const { return get_min(root, bias); }
    int lower_bound(T val) const { return count_lower(root, val); }
    int upper_bound(T val) const { return count_lower(root, val + 1); }
    int count(T val) const {
        if (!root) return 0;
        node_ptr node = root;
        for (int i = B - 1; i >= 0; i--) {
            node = node->ch[val >> i & 1];
            if (!node) return 0;
        }
        return node->count;
    }

  private:
    node_ptr root;

    node_ptr insert(node_ptr node, T val, int b = B - 1) {
        if (!node) node = new _node();
        ++node->count;
        if (b < 0) return node;
        bool f = val >> b & (T)1;
        node->ch[f] = insert(node->ch[f], val, b - 1);
        return node;
    }
    node_ptr erase(node_ptr node, T val, int b = B - 1) {
        assert(node);
        --node->count;
        if (!node->count) return nullptr;
        if (b < 0) return node;
        bool f = val >> b & (T)1;
        node->ch[f] = erase(node->ch[f], val, b - 1);
        return node;
    }
    T get_min(node_ptr node, T val, int b = B - 1) const {
        assert(node);
        if (b < 0) return 0;
        bool f = val >> b & (T)1;
        f ^= !node->ch[f];
        return get_min(node->ch[f], val, b - 1) | ((T)f << (T)b);
    }
    T get(node_ptr node, int k, int b = B - 1) const {
        if (b < 0) return 0;
        int m = node->ch[0] ? node->ch[0]->count : 0;
        return k < m ? get(node->ch[0], k, b - 1) : get(node->ch[1], k - m, b - 1) | ((T)1 << b);
    }
    int count_lower(node_ptr node, T val, int b = B - 1) const {
        if (!node || b < 0) return 0;
        bool f = val >> b & 1;
        return (f && node->ch[0] ? node->ch[0]->count : 0) + count_lower(node->ch[f], val, b - 1);
    }
};

/**
 * @brief 多重2分トライ木
 * @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654
 *
 * @tparam T 要素の型
 * @tparam B ビットサイズ
 */
template <class T, int B = 31>
struct multi_binary_trie {
  private:
    struct _node {
        using pointer = _node *;
        int count;
        pointer ch[2];
        _node() : count(), ch{nullptr, nullptr} {}
    };

  public:
    using node_ptr = typename _node::pointer;

    multi_binary_trie() : root(nullptr) {}

    T operator[](int k) const {
        assert(0 <= k && k < size());
        return get(root, k);
    }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }
    T kth_element(int k) const { return operator[](k); }

    constexpr int size() const { return root ? root->count : 0; }
    constexpr bool empty() const { return !root; }

    void insert(T val) { root = insert(root, val); }
    void erase(T val) {
        if (count(val)) root = erase(root, val);
    }

    T max_element(T bias = 0) const { return get_min(root, ~bias); }
    T min_element(T bias = 0) const { return get_min(root, bias); }
    int lower_bound(T val) { return count_lower(root, val); }
    int upper_bound(T val) { return count_lower(root, val + 1); }
    int count(T val) const {
        if (!root) return 0;
        node_ptr node = root;
        for (int i = B - 1; i >= 0; i--) {
            node = node->ch[val >> i & (T)1];
            if (!node) return 0;
        }
        return node->count;
    }

  private:
    node_ptr root;

    node_ptr insert(node_ptr node, T val, int b = B - 1) {
        if (!node) node = new _node();
        ++node->count;
        if (b < 0) return node;
        bool f = val >> b & (T)1;
        node->ch[f] = insert(node->ch[f], val, b - 1);
        return node;
    }
    node_ptr erase(node_ptr node, T val, int b = B - 1) {
        assert(node);
        --node->count;
        if (!node->count) return nullptr;
        if (b < 0) return node;
        bool f = val >> b & (T)1;
        node->ch[f] = erase(node->ch[f], val, b - 1);
        return node;
    }
    T get_min(node_ptr node, T val, int b = B - 1) const {
        assert(node);
        if (b < 0) return 0;
        bool f = val >> b & (T)1;
        f ^= !node->ch[f];
        return get_min(node->ch[f], val, b - 1) | ((T)f << (T)b);
    }
    T get(node_ptr node, int k, int b = B - 1) const {
        if (b < 0) return 0;
        int m = node->ch[0] ? node->ch[0]->count : 0;
        return k < m ? get(node->ch[0], k, b - 1) : get(node->ch[1], k - m, b - 1) | ((T)1 << b);
    }
    int count_lower(node_ptr node, T val, int b = B - 1) {
        if (!node || b < 0) return 0;
        bool f = val >> b & (T)1;
        return (f && node->ch[0] ? node->ch[0]->count : 0) + count_lower(node->ch[f], val, b - 1);
    }
};
