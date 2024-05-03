#include <cassert>
#include "random/xorshift.hpp"

/**
 * @brief Treap
 *
 * @tparam T 要素の型
 * @tparam UniformRandomBitGenerator 疑似乱数生成器
 */
template <class T, class UniformRandomBitGenerator = Xorshift>
struct Treap {
  private:
    struct _node {
        using pointer = _node *;
        T val;
        typename UniformRandomBitGenerator::result_type priority;
        pointer left, right;

        _node(T _val, typename UniformRandomBitGenerator::result_type _priority)
            : val(_val), priority(_priority), left(nullptr), right(nullptr) {}
    };

  public:
    using node_ptr = typename _node::pointer;

    constexpr Treap() : root(nullptr) {}

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

  private:
    UniformRandomBitGenerator gen;
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
        return pivot;
    }

    constexpr node_ptr rotr(node_ptr node) {
        assert(node);
        node_ptr pivot = node->left;
        assert(pivot);
        node->left = pivot->right;
        pivot->right = node;
        return pivot;
    }

    constexpr node_ptr rotate(node_ptr node) {
        if (node->right && node->priority < node->right->priority) node = rotl(node);
        else if (node->left && node->priority < node->left->priority) node = rotr(node);
        return node;
    }

    constexpr node_ptr insert(node_ptr node, T val) {
        if (node == nullptr) return new _node(val, gen());
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
