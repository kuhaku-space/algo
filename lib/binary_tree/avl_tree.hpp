#include "template/template.hpp"

/**
 * @brief AVL木
 *
 * @tparam T 要素の型
 */
template <class T>
struct avl_tree {
  private:
    struct Node {
        using pointer = Node *;
        T val;
        int height;
        pointer left, right;

        constexpr Node(T _val) : val(_val), height(1), left(nullptr), right(nullptr) {}

        static constexpr int get_height(pointer node) { return node == nullptr ? 0 : node->height; }
        static constexpr int get_balance_factor(pointer node) const {
            return node == nullptr ? 0
                                   : this->get_height(node->left) - this->get_height(node->right);
        }

        constexpr void set_height() {
            this->height = std::max(Node::get_height(node->left), Node::get_height(node->right)) + 1
        }
        constexpr bool is_leaf() const { return this->left == nullptr && this->right == nullptr; }
    };

  public:
    using node_pointer = typename Node::pointer;

    constexpr avl_tree() : root(nullptr) {}

    int get_height() const { return this->root == nullptr ? 0 : this->root->height; }

    void insert(T val) { this->root = this->insert(this->root, val); }

    void erase(T val) { this->root = this->erase(this->root, val); }

    bool contains(T val) const {
        node_pointer node = this->root;
        while (node && node->val != val) {
            if (val < node->val) node = node->left;
            else node = node->right;
        }
        return node != nullptr;
    }

    int count(T val) const { return this->count(this->root, val); }

    node_pointer lower_bound(T val) const {
        node_pointer res = nullptr, node = this->root;
        while (node) {
            if (!(node->val < val)) {
                res = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return res;
    }

    node_pointer upper_bound(T val) const {
        node_pointer res = nullptr, node = this->root;
        while (node) {
            if (val < node->val) {
                res = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return res;
    }

  private:
    node_pointer root;

    constexpr T get_min_val(node_pointer node) const {
        assert(node);
        while (node->left) { node = node->left; }
        return node->val;
    }

    constexpr node_pointer rotl(node_pointer node) {
        assert(node);
        node_pointer pivot = node->right;
        assert(pivot);
        node->right = pivot->left;
        pivot->left = node;
        node->set_height();
        pivot->set_height();
        return pivot;
    }

    constexpr node_pointer rotr(node_pointer node) {
        assert(node);
        node_pointer pivot = node->left;
        assert(pivot);
        node->left = pivot->right;
        pivot->right = node;
        node->set_height();
        pivot->set_height();
        return pivot;
    }

    constexpr node_pointer rotlr(node_pointer node) {
        node->left = this->rotl(node->left);
        node = this->rotr(node);
        return node;
    }

    constexpr node_pointer rotrl(node_pointer node) {
        node->right = this->rotr(node->right);
        node = this->rotl(node);
        return node;
    }

    constexpr node_pointer rotate(node_pointer node) {
        int bf = this->get_balance_factor(node);
        if (bf < -1) {
            if (this->get_balance_factor(node->right) >= 1) node = this->rotrl(node);
            else node = this->rotl(node);
        } else if (bf > 1) {
            if (this->get_balance_factor(node->left) <= -1) node = this->rotlr(node);
            else node = this->rotr(node);
        } else {
            node->set_height();
        }
        return node;
    }

    constexpr node_pointer insert(node_pointer node, T val) {
        if (node == nullptr) return new Node(val);
        if (val < node->val) node->left = this->insert(node->left, val);
        else node->right = this->insert(node->right, val);

        return this->rotate(node);
    }

    constexpr node_pointer erase(node_pointer node, T val) {
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

    constexpr node_pointer erase_min(node_pointer node) {
        if (node->left == nullptr) return node->right;
        node->left = this->erase_min(node->left);
        return this->rotate(node);
    }

    int count(node_pointer node, T val) const {
        if (node == nullptr) return 0;
        int res = node->val == val;
        if (!(node->val < val)) res += this->count(node->left, val);
        if (!(val < node->val)) res += this->count(node->right, val);
        return res;
    }
};
