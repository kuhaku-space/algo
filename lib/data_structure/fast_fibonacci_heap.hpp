#include "template/template.hpp"

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

        _node() : key(), value(), order(), left(this), right(this), parent(), child() {}
        _node(Key _key, Value _value)
            : key(_key), value(_value), order(), left(this), right(this), parent(), child() {}

        void add_child(pointer node) {
            node->parent = this;
            if (this->child)
                this->child->insert_left(node);
            else
                this->child = node;
            ++(this->order);
        }
        void insert_left(pointer node) {
            node->right = this;
            node->left = this->left;
            this->left->right = node;
            this->left = node;
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
    };

  public:
    using node_pointer = typename _node::pointer;

    fibonacci_heap() : _root(nullptr), _size() {}

    bool empty() const { return this->_size == 0; }

    pair<Key, Value> top() const { return make_pair(this->_root->key, this->_root->value); }

    auto push(Key key, Value value) {
        ++(this->_size);
        auto node = new _node(key, value);
        if (!this->_root) {
            this->_root = node;
        } else {
            this->_root->insert_left(node);
            if (Comp()(this->_root->value, value)) this->_root = this->_root->left;
        }
        return node;
    }

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

        node_pointer nodes[30] = {};
        while (this->_root) {
            auto node = this->_root;
            auto order = node->order;
            this->_root = this->_root->erase();
            while (nodes[order]) {
                if (Comp()(node->value, nodes[order]->value)) { swap(node, nodes[order]); }
                node->add_child(nodes[order]);
                nodes[order] = nullptr;
                ++order;
            }
            nodes[order] = node;
        }

        for (auto node : nodes) {
            if (node && (!this->_root || Comp()(this->_root->value, node->value)))
                this->_root = node;
        }
        for (auto node : nodes) {
            if (node && node != this->_root) { this->_root->insert_left(node); }
        }
    }

    void update(node_pointer node, Value value) {
        if (Comp()(node->value, value))
            node->value = value;
        else
            return;
        if (!node->parent) {
            if (Comp()(this->_root->value, value)) this->_root = node;
            return;
        } else if (!Comp()(node->parent->value, node->value)) {
            return;
        }
        if (node->parent) {
            auto parent = node->parent;
            parent->child = node->erase();
            --(parent->order);
            this->_root->insert_left(node);
            if (Comp()(this->_root->value, this->_root->left->value))
                this->_root = this->_root->left;
        }
    }

  private:
    node_pointer _root;
    int _size;
};
