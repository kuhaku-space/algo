#include "random/xorshift.hpp"
#include "template/template.hpp"

template <class T>
struct Treap {
    struct Node {
        T val;
        Xorshift::result_type priority;
        Node *left, *right;

        Node(T _val, Xorshift::result_type _priority)
            : val(_val), priority(_priority), left(nullptr), right(nullptr) {}
    };

    Treap() : root(nullptr) {}

    void insert(T val) { this->root = this->insert(this->root, val); }

    void erase(T val) { this->root = this->erase(this->root, val); }

    bool contains(T val) const {
        Node *node = this->root;
        while (node && node->val != val) {
            if (val < node->val)
                node = node->left;
            else
                node = node->right;
        }
        return node != nullptr;
    }

    int count(T val) const { return this->count(this->root, val); }

    void dump(T l, T r) const { return this->dump(this->root, l, r); }

  private:
    Xorshift xor128;
    Node *root;

    constexpr T get_min_val(Node *node) const {
        assert(node);
        while (node->left) { node = node->left; }
        return node->val;
    }

    constexpr Node *rotl(Node *node) {
        assert(node);
        Node *pivot = node->right;
        assert(pivot);
        node->right = pivot->left;
        pivot->left = node;
        return pivot;
    }

    constexpr Node *rotr(Node *node) {
        assert(node);
        Node *pivot = node->left;
        assert(pivot);
        node->left = pivot->right;
        pivot->right = node;
        return pivot;
    }

    constexpr Node *rotate(Node *node) {
        if (node->right && node->priority < node->right->priority) {
            node = this->rotl(node);
        } else if (node->left && node->priority < node->left->priority) {
            node = this->rotr(node);
        }
        return node;
    }

    constexpr Node *insert(Node *node, T val) {
        if (node == nullptr) return new Node(val, this->xor128());
        if (val < node->val)
            node->left = this->insert(node->left, val);
        else
            node->right = this->insert(node->right, val);

        return this->rotate(node);
    }

    constexpr Node *erase(Node *node, T val) {
        if (node == nullptr) return nullptr;
        if (val < node->val) {
            node->left = this->erase(node->left, val);
        } else if (node->val < val) {
            node->right = this->erase(node->right, val);
        } else {
            if (node->right == nullptr) {
                return node->left;
            } else {
                node->val = this->get_min_val(node->right);
                node->right = this->erase_min(node->right);
            }
        }
        return this->rotate(node);
    }

    constexpr Node *erase_min(Node *node) {
        if (node->left == nullptr) return node->right;
        node->left = this->erase_min(node->left);
        return this->rotate(node);
    }

    int count(Node *node, T val) const {
        if (node == nullptr) return 0;
        int res = node->val == val;
        if (!(node->val < val)) res += this->count(node->left, val);
        if (!(val < node->val)) res += this->count(node->right, val);
        return res;
    }

    void dump(Node *node, T l, T r) const {
        if (node == nullptr) return;
        if (!(node->val < l)) this->dump(node->left, l, r);
        if (!(node->val < l) && !(r < node->val)) cout << node->val << '\n';
        if (!(r < node->val)) this->dump(node->right, l, r);
    }
};
