#include <template/template.hpp>

template <class T>
struct avl_tree {
    struct Node {
        T val;
        int height;
        Node *left, *right;

        constexpr Node(T _val) : val(_val), height(1), left(nullptr), right(nullptr) {}

        constexpr bool is_leaf() const { return this->left == nullptr && this->right == nullptr; }
    };

    constexpr avl_tree() : root(nullptr) {}

    int get_height() const { return this->root == nullptr ? 0 : this->root->height; }

    void insert(T val) { this->root = this->insert(this->root, val); }

    void erase(T val) { this->root = this->erase(root, val); }

    bool find(T val) const {
        Node *node = this->root;
        while (node && node->val != val) {
            if (val < node->val)
                node = node->left;
            else
                node = node->right;
        }
        return node != nullptr;
    }

  private:
    Node *root;

    constexpr int get_height(Node *node) const { return node == nullptr ? 0 : node->height; }
    constexpr int get_balance_factor(Node *node) const {
        return node == nullptr ? 0 : this->get_height(node->left) - this->get_height(node->right);
    }

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
        node->height = max(this->get_height(node->left), this->get_height(node->right)) + 1;
        pivot->height = max(this->get_height(pivot->left), this->get_height(pivot->right)) + 1;
        return pivot;
    }

    constexpr Node *rotr(Node *node) {
        assert(node);
        Node *pivot = node->left;
        assert(pivot);
        node->left = pivot->right;
        pivot->right = node;
        node->height = max(this->get_height(node->left), this->get_height(node->right)) + 1;
        pivot->height = max(this->get_height(pivot->left), this->get_height(pivot->right)) + 1;
        return pivot;
    }

    constexpr Node *rotlr(Node *node) {
        node->left = this->rotl(node->left);
        node = this->rotr(node);
        return node;
    }

    constexpr Node *rotrl(Node *node) {
        node->right = this->rotr(node->right);
        node = this->rotl(node);
        return node;
    }

    constexpr Node *rotate(Node *node) {
        int bf = this->get_balance_factor(node);
        if (bf < -1) {
            if (this->get_balance_factor(node->right) >= 1)
                node = this->rotrl(node);
            else
                node = this->rotl(node);
        } else if (bf > 1) {
            if (this->get_balance_factor(node->left) <= -1)
                node = this->rotlr(node);
            else
                node = this->rotr(node);
        } else {
            node->height = max(this->get_height(node->left), this->get_height(node->right)) + 1;
        }
        return node;
    }

    constexpr Node *insert(Node *node, T val) {
        if (node == nullptr) return new Node(val);
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
};
