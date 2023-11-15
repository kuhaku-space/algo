#include <algorithm>
#include <cassert>

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
        static constexpr int get_balance_factor(pointer node) {
            return node == nullptr ? 0
                                   : _node::get_height(node->left) - _node::get_height(node->right);
        }

        constexpr void set_height() {
            height = std::max(_node::get_height(left), _node::get_height(right)) + 1;
        }
        constexpr bool is_leaf() const { return left == nullptr && right == nullptr; }
    };

  public:
    using node_type = _node;
    using node_ptr = typename _node::pointer;

    constexpr avl_tree() : root(nullptr) {}

    void insert(T val) { root = insert(root, val); }

    void erase(T val) { root = erase(root, val); }

    bool contains(T val) const {
        node_ptr node = root;
        while (node && node->val != val) {
            if (val < node->val) node = node->left;
            else node = node->right;
        }
        return node != nullptr;
    }

    int count(T val) const { return count(root, val); }

    node_ptr lower_bound(T val) const {
        node_ptr res = nullptr, node = root;
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
        node_ptr res = nullptr, node = root;
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
        node->left = rotl(node->left);
        node = rotr(node);
        return node;
    }

    constexpr node_ptr rotrl(node_ptr node) {
        node->right = rotr(node->right);
        node = rotl(node);
        return node;
    }

    constexpr node_ptr rotate(node_ptr node) {
        int bf = node_type::get_balance_factor(node);
        if (bf < -1) {
            if (node_type::get_balance_factor(node->right) >= 1) node = rotrl(node);
            else node = rotl(node);
        } else if (bf > 1) {
            if (node_type::get_balance_factor(node->left) <= -1) node = rotlr(node);
            else node = rotr(node);
        } else {
            node->set_height();
        }
        return node;
    }

    constexpr node_ptr insert(node_ptr node, T val) {
        if (node == nullptr) return new _node(val);
        if (val < node->val) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);

        return rotate(node);
    }

    constexpr node_ptr erase(node_ptr node, T val) {
        if (node == nullptr) return nullptr;
        if (val < node->val) {
            node->left = erase(node->left, val);
        } else if (node->val < val) {
            node->right = erase(node->right, val);
        } else {
            if (node->right == nullptr) {
                return node->left;
            } else {
                node->val = get_min_val(node->right);
                node->right = erase_min(node->right);
            }
        }
        return rotate(node);
    }

    constexpr node_ptr erase_min(node_ptr node) {
        if (node->left == nullptr) return node->right;
        node->left = erase_min(node->left);
        return rotate(node);
    }

    int count(node_ptr node, T val) const {
        if (node == nullptr) return 0;
        int res = node->val == val;
        if (!(node->val < val)) res += count(node->left, val);
        if (!(val < node->val)) res += count(node->right, val);
        return res;
    }
};
