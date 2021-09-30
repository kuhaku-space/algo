#include "template/template.hpp"

/**
 * @brief 2分パトリシア木(重複あり)
 * @ref https://kyokkounoite.hatenablog.jp/entry/2021/05/17/170000 "参考"
 *
 * @tparam T
 * @tparam B ビットサイズ
 */
template <class T, int B = 31>
struct multi_patricia_binary_trie {
    struct Node {
        T val;
        int len, count;
        Node* ch[2];
        Node(T _val, int _len, int _count = 0)
            : val(_val), len(_len), count(_count), ch{nullptr, nullptr} {}
    };

    Node* root;

    multi_patricia_binary_trie() : root(nullptr) {}

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
        int rest = node->len;
        for (int i = B - 1; i >= 0; i--) {
            if (!rest) {
                node = node->ch[val >> i & 1];
                rest += node->len;
            }
            if (!node || ((val ^ node->val) >> i & 1)) return 0;
            --rest;
        }
        return node->count;
    }

  private:
    Node* add(Node* node, T val, int b = B - 1) {
        if (!node) node = new Node(val, b + 1);
        ++node->count;
        if (b < 0) return node;
        int len = node->len;
        for (int i = 0; i < node->len; ++i) {
            if (((val ^ node->val) >> (b - i) & 1)) {
                len = i;
                break;
            }
        }
        if (len == b + 1) return node;
        b -= len;
        Node* itr = node;
        if (len != node->len) {
            itr = new Node(val, len, node->count);
            node->len -= len;
            --node->count;
            itr->ch[node->val >> b & 1] = node;
        }
        bool f = val >> b & 1;
        itr->ch[f] = this->add(itr->ch[f], val, b);
        return itr;
    }
    Node* sub(Node* node, T val, int b = B - 1) {
        assert(node);
        --node->count;
        if (!node->count) return nullptr;
        b -= node->len;
        if (b < 0) return node;
        bool f = val >> b & 1;
        node->ch[f] = this->sub(node->ch[f], val, b);
        return node;
    }
    T get_min(Node* node, T val, int b = B - 1) const {
        assert(node);
        b -= node->len;
        if (b < 0) return node->val;
        bool f = val >> b & 1;
        f ^= !node->ch[f];
        return this->get_min(node->ch[f], val, b);
    }
    T get(Node* node, int k, int b = B - 1) const {
        b -= node->len;
        if (b < 0) return node->val;
        int m = node->ch[0] ? node->ch[0]->count : 0;
        return k < m ? this->get(node->ch[0], k, b) : this->get(node->ch[1], k - m, b);
    }
    int count_lower(Node* node, T val, int b = B - 1) {
        if (!node || b < 0) return 0;
        b -= node->len;
        bool f = val >> b & 1;
        return (f && node->ch[0] ? node->ch[0]->count : 0) +
               this->count_lower(node->ch[f], val, b - 1);
    }
};
