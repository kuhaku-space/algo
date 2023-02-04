#include "template/template.hpp"

/**
 * @brief スケープゴート木
 * @see https://kopricky.github.io/code/BinarySearchTree/scapegoat_tree.html
 *
 * @tparam T 要素の型
 */
template <class T>
struct scapegoat_tree {
  private:
    struct Node {
        using pointer = Node *;

        T val;
        unsigned int size;
        pointer left, right;

        Node(T _val) : val(_val), size(1), left(nullptr), right(nullptr) {}

        static constexpr int get_size(pointer node) { return node ? node->size : 0; }

        void eval() { this->size = 1 + Node::get_size(left) + Node::get_size(right); }
    };

  public:
    using node_ptr = typename Node::pointer;

    scapegoat_tree(const double _alpha = 2.0 / 3.0)
        : root(nullptr), alpha(_alpha), log_val(-1.0 / std::log2(_alpha)), max_element_size(0) {}

    constexpr bool empty() const { return !(this->root); }

    constexpr int size() const { return this->empty() ? 0 : this->root->size; }

    constexpr bool contains(T val) const {
        node_ptr node = this->root;
        while (node) {
            if (node->val == val) return true;
            node = (val < node->val ? node->left : node->right);
        }
        return false;
    }

    constexpr T index(int k) const {
        assert(k < this->size());
        node_ptr node = this->root;
        while (node) {
            if (Node::get_size(node->left) == k) {
                break;
            } else if (k < Node::get_size(node->left)) {
                node = node->left;
            } else {
                k -= Node::get_size(node->left) + 1;
                node = node->right;
            }
        }
        return node->val;
    }
    constexpr T kth_element(int k) const { return this->index(k); }

    void insert(T val) {
        this->max_element_size = std::max(this->max_element_size, this->size() + 1);
        bool balanced = true;
        this->root = this->insert(this->root, val, 0, balanced);
        assert(balanced);
    }

    void erase(T val) {
        this->root = this->erase(this->root, val);
        this->check();
    }

    int count(T val) {
        int res = 0;
        node_ptr node = this->root;
        while (node) {
            if (node->val < val) res += Node::get_size(node->left) + 1;
            node = (val <= node->val ? node->left : node->right);
        }
        return res;
    }

  private:
    node_ptr root;
    double alpha, log_val;
    int max_element_size;

    void subtree_dfs(node_ptr node, std::vector<node_ptr> &nodes) const {
        if (node->left) this->subtree_dfs(node->left, nodes);
        nodes.emplace_back(node);
        if (node->right) this->subtree_dfs(node->right, nodes);
    }
    node_ptr build_pbbt_rec(int l, int r, const std::vector<node_ptr> &nodes) {
        if (r - l == 0) {
            return nullptr;
        } else if (r - l == 1) {
            node_ptr node = nodes[l];
            node->left = node->right = nullptr;
            node->eval();
            return node;
        }
        int mid = (l + r) >> 1;
        node_ptr node = nodes[mid];
        node->left = this->build_pbbt_rec(l, mid, nodes);
        node->right = this->build_pbbt_rec(mid + 1, r, nodes);
        node->eval();
        return node;
    }
    node_ptr build_pbbt(node_ptr node) {
        if (!node) return nullptr;
        std::vector<node_ptr> nodes;
        this->subtree_dfs(node, nodes);
        return this->build_pbbt_rec(0, nodes.size(), nodes);
    }

    node_ptr insert(node_ptr node, T val, int depth, bool &balanced) {
        if (!node) {
            balanced = (depth <= std::floor(log_val * std::log2(max_element_size)));
            return new Node(val);
        } else if (val < node->val) {
            node->left = this->insert(node->left, val, depth + 1, balanced);
            node->eval();
            if (balanced || node->left->size <= alpha * node->size) return node;
        } else {
            node->right = this->insert(node->right, val, depth + 1, balanced);
            node->eval();
            if (balanced || node->right->size <= alpha * node->size) return node;
        }
        balanced = true;
        return this->build_pbbt(node);
    }

    node_ptr join(node_ptr left, node_ptr right) {
        if (!left || !right) {
            return left ? left : right;
        } else if (left->size < right->size) {
            right->left = this->join(left, right->left);
            right->eval();
            return right;
        } else {
            left->right = this->join(left->right, right);
            left->eval();
            return left;
        }
    }

    node_ptr erase(node_ptr node, T val) {
        if (!node) {
            return nullptr;
        } else if (node->val == val) {
            return this->join(node->left, node->right);
        } else if (val < node->val) {
            node->left = this->erase(node->left, val);
            node->eval();
            return node;
        } else {
            node->right = this->erase(node->right, val);
            node->eval();
            return node;
        }
    }

    void check() {
        if (this->size() >= alpha * max_element_size) return;
        this->root = this->build_pbbt(this->root);
        this->max_element_size = this->size();
    }
};
