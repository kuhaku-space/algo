#pragma once
#include <functional>
#include <utility>

/// @brief フィボナッチヒープ
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
            : key(_key), value(_value), order(), left(this), right(this), parent(), child(), damaged() {}

        // node を子リストへ追加する。parent と order を更新する
        void add_child(pointer node) {
            node->parent = this;
            if (child) child->insert_left(node);
            else child = node;
            ++order;
        }
        // node を自分の左隣（前）へ挿入する
        void insert_left(pointer node) {
            node->right = this;
            node->left = left;
            left->right = node;
            left = node;
        }
        // 自分を兄弟リストから外す（parent は触らない）。
        // 外したあと参照できる兄弟（なければ nullptr）を返す
        pointer unlink() {
            if (left == this) {
                left = right = this;
                return nullptr;
            }
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
            if (comp(_root->value, value)) _root = node;
        }
        return node;
    }
    auto emplace(Key key, Value value) { return push(key, value); }

    void pop() {
        --_size;
        // _root の子をすべてルートリストへ昇格する（parent を nullptr に戻す）
        if (_root->child) {
            auto child = _root->child;
            do {
                child->parent = nullptr;
                child = child->right;
            } while (child != _root->child);
            // _root と child の双方向リストを連結する
            auto left = child->left;
            _root->left->right = child;
            child->left->right = _root;
            child->left = _root->left;
            _root->left = left;
            _root->child = nullptr;
        }
        _root = _root->unlink();
        if (!_root) return;

        // 同じ order の木を併合する（consolidate）
        node_ptr nodes[64] = {};
        while (_root) {
            auto node = _root;
            _root = _root->unlink();
            node->damaged = false;
            int order = node->order;
            while (nodes[order]) {
                if (comp(node->value, nodes[order]->value)) std::swap(node, nodes[order]);
                node->add_child(nodes[order]);
                nodes[order] = nullptr;
                ++order;
            }
            nodes[order] = node;
        }

        // 併合後の木をルートリストへ繋ぎ直し、最大を _root にする
        for (auto node : nodes) {
            if (!node) continue;
            if (!_root) {
                _root = node;
            } else {
                _root->insert_left(node);
                if (comp(_root->value, node->value)) _root = node;
            }
        }
    }

    // node の値を value に更新する（max-heap なので増加方向のみ反映）
    void update(node_ptr node, Value value) {
        if (comp(node->value, value)) node->value = value;
        else return;
        auto parent = node->parent;
        // ルート上のノードなら最大判定のみ
        if (!parent) {
            if (comp(_root->value, node->value)) _root = node;
            return;
        }
        // ヒープ条件を満たしているなら何もしない
        if (!comp(parent->value, node->value)) return;
        // node を切り離し、親へカスケードカットを伝播させる
        cut(node, parent);
        cascading_cut(parent);
        if (comp(_root->value, node->value)) _root = node;
    }

  private:
    node_ptr _root;
    int _size;
    Comp comp;

    // node を親 parent から切り離してルートリストへ移す
    void cut(node_ptr node, node_ptr parent) {
        auto sibling = node->unlink();
        if (parent->child == node) parent->child = sibling;
        --(parent->order);
        node->parent = nullptr;
        node->damaged = false;
        _root->insert_left(node);
    }

    // 親方向へカスケードカットを伝播させる
    void cascading_cut(node_ptr node) {
        while (auto parent = node->parent) {
            if (!node->damaged) {
                node->damaged = true;
                break;
            }
            cut(node, parent);
            node = parent;
        }
    }
};
