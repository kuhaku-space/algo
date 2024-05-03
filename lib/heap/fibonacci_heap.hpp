#include <functional>
#include <utility>

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
            if (child) child->insert_left(node);
            else child = node;
            ++order;
        }
        void insert_left(pointer node) {
            node->right = this;
            node->left = left;
            left->right = node;
            left = node;
        }
        void insert_right(pointer node) {
            node->left = this;
            node->right = right;
            right->left = node;
            right = node;
        }

        pointer erase() {
            parent = nullptr;
            if (left == this) return nullptr;
            left->right = right;
            right->left = left;
            auto res = left;
            left = right = this;
            return res;
        }

        constexpr auto get_pair() const { return std::make_pair(key, value); }
    };

  public:
    using node_ptr = typename _node::pointer;

    fibonacci_heap() : _root(nullptr), _size(), comp() {}

    constexpr bool empty() const { return _size == 0; }
    constexpr int size() const { return _size; }
    constexpr auto top() const { return _root->get_pair(); }

    auto push(Key key, Value value) {
        ++_size;
        auto node = new _node(key, value);
        if (!_root) {
            _root = node;
        } else {
            _root->insert_left(node);
            if (comp(_root->value, value)) _root = _root->left;
        }
        return node;
    }
    auto emplace(Key key, Value value) { return push(key, value); }

    void pop() {
        --_size;
        if (_root->child) {
            auto child = _root->child, left = child->left;
            _root->left->right = child;
            child->left->right = _root;
            child->left = _root->left;
            _root->left = left;
        }
        _root = _root->erase();
        if (!_root) return;

        node_ptr nodes[30] = {};
        while (_root) {
            auto node = _root;
            auto order = node->order;
            _root = _root->erase();
            while (nodes[order]) {
                if (comp(node->value, nodes[order]->value)) std::swap(node, nodes[order]);
                node->add_child(nodes[order]);
                nodes[order] = nullptr;
                ++order;
            }
            nodes[order] = node;
        }

        for (auto node : nodes) {
            if (node && (!_root || comp(_root->value, node->value))) _root = node;
        }
        for (auto node : nodes) {
            if (node && node != _root) _root->insert_left(node);
        }
    }

    void update(node_ptr node, Value value) {
        if (comp(node->value, value)) node->value = value;
        else return;
        if (!node->parent) {
            if (comp(_root->value, value)) _root = node;
            return;
        } else if (!comp(node->parent->value, node->value)) {
            return;
        }
        while (node->parent) {
            auto parent = node->parent;
            node->damaged = false;
            parent->child = node->erase();
            --(parent->order);
            _root->insert_left(node);
            if (comp(_root->value, _root->left->value)) _root = _root->left;
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
