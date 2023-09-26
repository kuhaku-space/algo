#include "template/template.hpp"

/**
 * @brief フィボナッチヒープ
 *
 * @tparam Key キーの型
 * @tparam Value 値の型
 * @tparam Comp 関数オブジェクト
 */
template <class Key, class Value, class Comp = std::less<>>
struct fibonacci_heap {
  private:
    struct _node {
        using pointer = _node *;
        Key key;
        Value value;
        int order;
        pointer left, right;
        pointer parent, child;
        bool damaged;

        _node() : key(), value(), order(), left(this), right(this), parent(), child(), damaged() {}
        _node(Key _key, Value _value)
            : key(_key), value(_value), order(), left(this), right(this), parent(), child(),
              damaged() {}

        void add_child(pointer node) {
            node->parent = this;
            if (this->child) this->child->insert_left(node);
            else this->child = node;
            ++(this->order);
        }
        void insert_left(pointer node) {
            node->right = this;
            node->left = this->left;
            this->left->right = node;
            this->left = node;
        }
        void insert_right(pointer node) {
            node->left = this;
            node->right = this->right;
            this->right->left = node;
            this->right = node;
        }

        pointer erase() {
            this->parent = nullptr;
            if (this->left == this) return nullptr;
            this->left->right = this->right;
            this->right->left = this->left;
            auto res = this->left;
            this->left = this->right = this;
            return res;
        }

        constexpr auto get_pair() const { return std::make_pair(key, value); }
    };

  public:
    using node_ptr = typename _node::pointer;

    fibonacci_heap() : _root(nullptr), _size(), comp() {}

    bool empty() const { return this->_size == 0; }
    constexpr int size() const { return this->_size; }
    constexpr auto top() const { return this->_root->get_pair(); }

    auto push(Key key, Value value) {
        ++(this->_size);
        auto node = new _node(key, value);
        if (!this->_root) {
            this->_root = node;
        } else {
            this->_root->insert_left(node);
            if (comp(this->_root->value, value)) this->_root = this->_root->left;
        }
        return node;
    }
    auto emplace(Key key, Value value) { return this->push(key, value); }

    void pop() {
        --(this->_size);
        if (this->_root->child) {
            auto child = this->_root->child, left = child->left;
            this->_root->left->right = child;
            child->left->right = this->_root;
            child->left = this->_root->left;
            this->_root->left = left;
        }
        this->_root = this->_root->erase();
        if (!this->_root) return;

        node_ptr nodes[30] = {};
        while (this->_root) {
            auto node = this->_root;
            auto order = node->order;
            this->_root = this->_root->erase();
            while (nodes[order]) {
                if (comp(node->value, nodes[order]->value)) std::swap(node, nodes[order]);
                node->add_child(nodes[order]);
                nodes[order] = nullptr;
                ++order;
            }
            nodes[order] = node;
        }

        for (auto node : nodes) {
            if (node && (!this->_root || comp(this->_root->value, node->value))) this->_root = node;
        }
        for (auto node : nodes) {
            if (node && node != this->_root) this->_root->insert_left(node);
        }
    }

    void update(node_ptr node, Value value) {
        if (comp(node->value, value)) node->value = value;
        else return;
        if (!node->parent) {
            if (comp(this->_root->value, value)) this->_root = node;
            return;
        } else if (!comp(node->parent->value, node->value)) {
            return;
        }
        while (node->parent) {
            auto parent = node->parent;
            node->damaged = false;
            parent->child = node->erase();
            --(parent->order);
            this->_root->insert_left(node);
            if (comp(this->_root->value, this->_root->left->value)) this->_root = this->_root->left;
            if (!parent->damaged) {
                parent->damaged = true;
                break;
            }
            node = parent;
        }
    }

  private:
    node_ptr _root;
    int _size;
    Comp comp;
};
