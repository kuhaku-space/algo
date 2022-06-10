#include "template/template.hpp"

/**
 * @brief AVL木
 * @see https://tjkendev.github.io/procon-library/cpp/binary_search_tree/avl-tree.html
 *
 * @tparam T 要素の型
 */
template <class T>
struct avl_tree {
  private:
    struct _node {
        using pointer = _node *;
        T val;
        int height;
        pointer left, right;

        constexpr _node(T _val) : val(_val), height(1), left(nullptr), right(nullptr) {}

        static constexpr int get_height(pointer node) { return node == nullptr ? 0 : node->height; }
        static constexpr int get_balance_factor(pointer node) const {
            return node == nullptr ? 0
                                   : this->get_height(node->left) - this->get_height(node->right);
        }

        constexpr void set_height() {
            this->height = std::max(_node::get_height(node->left), _node::get_height(node->right)) + 1
        }
        constexpr bool is_leaf() const { return this->left == nullptr && this->right == nullptr; }
    };

  public:
    using node_ptr = typename _node::pointer;

    constexpr avl_tree() : root(nullptr) {}

    int get_height() const { return this->root == nullptr ? 0 : this->root->height; }

    void insert(T val) { this->root = this->insert(this->root, val); }

    void erase(T val) { this->root = this->erase(this->root, val); }

    bool contains(T val) const {
        node_ptr node = this->root;
        while (node && node->val != val) {
            if (val < node->val) node = node->left;
            else node = node->right;
        }
        return node != nullptr;
    }

    int count(T val) const { return this->count(this->root, val); }

    node_ptr lower_bound(T val) const {
        node_ptr res = nullptr, node = this->root;
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

    node_ptr upper_bound(T val) const {
        node_ptr res = nullptr, node = this->root;
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
    node_ptr root;

    constexpr T get_min_val(node_ptr node) const {
        assert(node);
        while (node->left) { node = node->left; }
        return node->val;
    }

    constexpr node_ptr rotl(node_ptr node) {
        assert(node);
        node_ptr pivot = node->right;
        assert(pivot);
        node->right = pivot->left;
        pivot->left = node;
        node->set_height();
        pivot->set_height();
        return pivot;
    }

    constexpr node_ptr rotr(node_ptr node) {
        assert(node);
        node_ptr pivot = node->left;
        assert(pivot);
        node->left = pivot->right;
        pivot->right = node;
        node->set_height();
        pivot->set_height();
        return pivot;
    }

    constexpr node_ptr rotlr(node_ptr node) {
        node->left = this->rotl(node->left);
        node = this->rotr(node);
        return node;
    }

    constexpr node_ptr rotrl(node_ptr node) {
        node->right = this->rotr(node->right);
        node = this->rotl(node);
        return node;
    }

    constexpr node_ptr rotate(node_ptr node) {
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

    constexpr node_ptr insert(node_ptr node, T val) {
        if (node == nullptr) return new _node(val);
        if (val < node->val) node->left = this->insert(node->left, val);
        else node->right = this->insert(node->right, val);

        return this->rotate(node);
    }

    constexpr node_ptr erase(node_ptr node, T val) {
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

    constexpr node_ptr erase_min(node_ptr node) {
        if (node->left == nullptr) return node->right;
        node->left = this->erase_min(node->left);
        return this->rotate(node);
    }

    int count(node_ptr node, T val) const {
        if (node == nullptr) return 0;
        int res = node->val == val;
        if (!(node->val < val)) res += this->count(node->left, val);
        if (!(val < node->val)) res += this->count(node->right, val);
        return res;
    }
};
