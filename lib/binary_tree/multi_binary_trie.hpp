#include "template/template.hpp"

/**
 * @brief 2分トライ木(重複あり)
 * @ref https://kazuma8128.hatenablog.com/entry/2018/05/06/022654 "参考"
 *
 * @tparam T
 * @tparam B
 */
template <class T, int B = 31>
struct multi_binary_trie {
    struct Node {
        int count;
        Node* ch[2];
        Node() : count(), ch{nullptr, nullptr} {}
    };

    Node* root;

    multi_binary_trie() : root(nullptr) {}

    T operator[](int k) const {
        assert(0 <= k && k < this->size());
        return this->get(root, k);
    }

    int size() const { return this->root ? this->root->count : 0; }
    bool empty() const { return !this->root; }
    void insert(T val) { this->root = this->add(this->root, val); }
    void erase(T val) {
        if (this->count(val)) this->root = this->sub(this->root, val);
    }
    T kth_element(int k) const {
        assert(0 <= k && k < this->size());
        return this->get(this->root, k);
    }
    T max_element(T bias = 0) const { return this->get_min(this->root, ~bias); }
    T min_element(T bias = 0) const { return this->get_min(this->root, bias); }
    int lower_bound(T val) { return this->count_lower(this->root, val); }
    int upper_bound(T val) { return this->count_lower(this->root, val + 1); }
    int count(T val) const {
        if (!this->root) return 0;
        Node* node = this->root;
        for (int i = B - 1; i >= 0; i--) {
            node = node->ch[val >> i & (T)1];
            if (!node) return 0;
        }
        return node->count;
    }

  private:
    Node* add(Node* node, T val, int b = B - 1) {
        if (!node) node = new Node();
        ++node->count;
        if (b < 0) return node;
        bool f = val >> b & (T)1;
        node->ch[f] = this->add(node->ch[f], val, b - 1);
        return node;
    }
    Node* sub(Node* node, T val, int b = B - 1) {
        assert(node);
        --node->count;
        if (!node->count) return nullptr;
        if (b < 0) return node;
        bool f = val >> b & (T)1;
        node->ch[f] = this->sub(node->ch[f], val, b - 1);
        return node;
    }
    T get_min(Node* node, T val, int b = B - 1) const {
        assert(node);
        if (b < 0) return 0;
        bool f = val >> b & (T)1;
        f ^= !node->ch[f];
        return this->get_min(node->ch[f], val, b - 1) | ((T)f << (T)b);
    }
    T get(Node* node, int k, int b = B - 1) const {
        if (b < 0) return 0;
        int m = node->ch[0] ? node->ch[0]->count : 0;
        return k < m ? this->get(node->ch[0], k, b - 1)
                     : this->get(node->ch[1], k - m, b - 1) | ((T)1 << b);
    }
    int count_lower(Node* node, T val, int b = B - 1) {
        if (!node || b < 0) return 0;
        bool f = val >> b & (T)1;
        return (f && node->ch[0] ? node->ch[0]->count : 0) +
               this->count_lower(node->ch[f], val, b - 1);
    }
};
