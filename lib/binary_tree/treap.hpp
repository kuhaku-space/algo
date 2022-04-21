#include "random/xorshift.hpp"
#include "template/template.hpp"

/**
 * @brief Treap
 *
 * @tparam T 要素の型
 * @tparam UniformRandomBitGenerator 疑似乱数生成器
 */
template <class T, class UniformRandomBitGenerator = Xorshift>
struct Treap {
  private:
    struct Node {
        using pointer = Node *;
        T val;
        UniformRandomBitGenerator::result_type priority;
        pointer left, right;

        Node(T _val, UniformRandomBitGenerator::result_type _priority)
            : val(_val), priority(_priority), left(nullptr), right(nullptr) {}
    };

  public:
    using node_pointer = typename Node::pointer;

    constexpr Treap() : root(nullptr) {}

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

  private:
    UniformRandomBitGenerator gen;
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
        return pivot;
    }

    constexpr node_pointer rotr(node_pointer node) {
        assert(node);
        node_pointer pivot = node->left;
        assert(pivot);
        node->left = pivot->right;
        pivot->right = node;
        return pivot;
    }

    constexpr node_pointer rotate(node_pointer node) {
        if (node->right && node->priority < node->right->priority) {
            node = this->rotl(node);
        } else if (node->left && node->priority < node->left->priority) {
            node = this->rotr(node);
        }
        return node;
    }

    constexpr node_pointer insert(node_pointer node, T val) {
        if (node == nullptr) return new Node(val, this->gen());
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
