---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7"
    links: []
  bundledCode: "#line 1 \"lib/heap/fibonacci_heap.hpp\"\n#include <functional>\n#include\
    \ <utility>\n\n/**\n * @brief \u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\
    \u30D7\n *\n * @tparam Key \u30AD\u30FC\u306E\u578B\n * @tparam Value \u5024\u306E\
    \u578B\n * @tparam Comp \u95A2\u6570\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n */\n\
    template <class Key, class Value, class Comp = std::less<>>\nstruct fibonacci_heap\
    \ {\n  private:\n    struct _node {\n        using pointer = _node *;\n      \
    \  Key key;\n        Value value;\n        int order;\n        pointer left, right;\n\
    \        pointer parent, child;\n        bool damaged;\n\n        _node() : key(),\
    \ value(), order(), left(this), right(this), parent(), child(), damaged() {}\n\
    \        _node(Key _key, Value _value)\n            : key(_key), value(_value),\
    \ order(), left(this), right(this), parent(), child(),\n              damaged()\
    \ {}\n\n        void add_child(pointer node) {\n            node->parent = this;\n\
    \            if (child) child->insert_left(node);\n            else child = node;\n\
    \            ++order;\n        }\n        void insert_left(pointer node) {\n \
    \           node->right = this;\n            node->left = left;\n            left->right\
    \ = node;\n            left = node;\n        }\n        void insert_right(pointer\
    \ node) {\n            node->left = this;\n            node->right = right;\n\
    \            right->left = node;\n            right = node;\n        }\n\n   \
    \     pointer erase() {\n            parent = nullptr;\n            if (left ==\
    \ this) return nullptr;\n            left->right = right;\n            right->left\
    \ = left;\n            auto res = left;\n            left = right = this;\n  \
    \          return res;\n        }\n\n        constexpr auto get_pair() const {\
    \ return std::make_pair(key, value); }\n    };\n\n  public:\n    using node_ptr\
    \ = typename _node::pointer;\n\n    fibonacci_heap() : _root(nullptr), _size(),\
    \ comp() {}\n\n    constexpr bool empty() const { return _size == 0; }\n    constexpr\
    \ int size() const { return _size; }\n    constexpr auto top() const { return\
    \ _root->get_pair(); }\n\n    auto push(Key key, Value value) {\n        ++_size;\n\
    \        auto node = new _node(key, value);\n        if (!_root) {\n         \
    \   _root = node;\n        } else {\n            _root->insert_left(node);\n \
    \           if (comp(_root->value, value)) _root = _root->left;\n        }\n \
    \       return node;\n    }\n    auto emplace(Key key, Value value) { return push(key,\
    \ value); }\n\n    void pop() {\n        --_size;\n        if (_root->child) {\n\
    \            auto child = _root->child, left = child->left;\n            _root->left->right\
    \ = child;\n            child->left->right = _root;\n            child->left =\
    \ _root->left;\n            _root->left = left;\n        }\n        _root = _root->erase();\n\
    \        if (!_root) return;\n\n        node_ptr nodes[30] = {};\n        while\
    \ (_root) {\n            auto node = _root;\n            auto order = node->order;\n\
    \            _root = _root->erase();\n            while (nodes[order]) {\n   \
    \             if (comp(node->value, nodes[order]->value)) std::swap(node, nodes[order]);\n\
    \                node->add_child(nodes[order]);\n                nodes[order]\
    \ = nullptr;\n                ++order;\n            }\n            nodes[order]\
    \ = node;\n        }\n\n        for (auto node : nodes) {\n            if (node\
    \ && (!_root || comp(_root->value, node->value))) _root = node;\n        }\n \
    \       for (auto node : nodes) {\n            if (node && node != _root) _root->insert_left(node);\n\
    \        }\n    }\n\n    void update(node_ptr node, Value value) {\n        if\
    \ (comp(node->value, value)) node->value = value;\n        else return;\n    \
    \    if (!node->parent) {\n            if (comp(_root->value, value)) _root =\
    \ node;\n            return;\n        } else if (!comp(node->parent->value, node->value))\
    \ {\n            return;\n        }\n        while (node->parent) {\n        \
    \    auto parent = node->parent;\n            node->damaged = false;\n       \
    \     parent->child = node->erase();\n            --(parent->order);\n       \
    \     _root->insert_left(node);\n            if (comp(_root->value, _root->left->value))\
    \ _root = _root->left;\n            if (!parent->damaged) {\n                parent->damaged\
    \ = true;\n                break;\n            }\n            node = parent;\n\
    \        }\n    }\n\n  private:\n    node_ptr _root;\n    int _size;\n    Comp\
    \ comp;\n};\n"
  code: "#include <functional>\n#include <utility>\n\n/**\n * @brief \u30D5\u30A3\u30DC\
    \u30CA\u30C3\u30C1\u30D2\u30FC\u30D7\n *\n * @tparam Key \u30AD\u30FC\u306E\u578B\
    \n * @tparam Value \u5024\u306E\u578B\n * @tparam Comp \u95A2\u6570\u30AA\u30D6\
    \u30B8\u30A7\u30AF\u30C8\n */\ntemplate <class Key, class Value, class Comp =\
    \ std::less<>>\nstruct fibonacci_heap {\n  private:\n    struct _node {\n    \
    \    using pointer = _node *;\n        Key key;\n        Value value;\n      \
    \  int order;\n        pointer left, right;\n        pointer parent, child;\n\
    \        bool damaged;\n\n        _node() : key(), value(), order(), left(this),\
    \ right(this), parent(), child(), damaged() {}\n        _node(Key _key, Value\
    \ _value)\n            : key(_key), value(_value), order(), left(this), right(this),\
    \ parent(), child(),\n              damaged() {}\n\n        void add_child(pointer\
    \ node) {\n            node->parent = this;\n            if (child) child->insert_left(node);\n\
    \            else child = node;\n            ++order;\n        }\n        void\
    \ insert_left(pointer node) {\n            node->right = this;\n            node->left\
    \ = left;\n            left->right = node;\n            left = node;\n       \
    \ }\n        void insert_right(pointer node) {\n            node->left = this;\n\
    \            node->right = right;\n            right->left = node;\n         \
    \   right = node;\n        }\n\n        pointer erase() {\n            parent\
    \ = nullptr;\n            if (left == this) return nullptr;\n            left->right\
    \ = right;\n            right->left = left;\n            auto res = left;\n  \
    \          left = right = this;\n            return res;\n        }\n\n      \
    \  constexpr auto get_pair() const { return std::make_pair(key, value); }\n  \
    \  };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n    fibonacci_heap()\
    \ : _root(nullptr), _size(), comp() {}\n\n    constexpr bool empty() const { return\
    \ _size == 0; }\n    constexpr int size() const { return _size; }\n    constexpr\
    \ auto top() const { return _root->get_pair(); }\n\n    auto push(Key key, Value\
    \ value) {\n        ++_size;\n        auto node = new _node(key, value);\n   \
    \     if (!_root) {\n            _root = node;\n        } else {\n           \
    \ _root->insert_left(node);\n            if (comp(_root->value, value)) _root\
    \ = _root->left;\n        }\n        return node;\n    }\n    auto emplace(Key\
    \ key, Value value) { return push(key, value); }\n\n    void pop() {\n       \
    \ --_size;\n        if (_root->child) {\n            auto child = _root->child,\
    \ left = child->left;\n            _root->left->right = child;\n            child->left->right\
    \ = _root;\n            child->left = _root->left;\n            _root->left =\
    \ left;\n        }\n        _root = _root->erase();\n        if (!_root) return;\n\
    \n        node_ptr nodes[30] = {};\n        while (_root) {\n            auto\
    \ node = _root;\n            auto order = node->order;\n            _root = _root->erase();\n\
    \            while (nodes[order]) {\n                if (comp(node->value, nodes[order]->value))\
    \ std::swap(node, nodes[order]);\n                node->add_child(nodes[order]);\n\
    \                nodes[order] = nullptr;\n                ++order;\n         \
    \   }\n            nodes[order] = node;\n        }\n\n        for (auto node :\
    \ nodes) {\n            if (node && (!_root || comp(_root->value, node->value)))\
    \ _root = node;\n        }\n        for (auto node : nodes) {\n            if\
    \ (node && node != _root) _root->insert_left(node);\n        }\n    }\n\n    void\
    \ update(node_ptr node, Value value) {\n        if (comp(node->value, value))\
    \ node->value = value;\n        else return;\n        if (!node->parent) {\n \
    \           if (comp(_root->value, value)) _root = node;\n            return;\n\
    \        } else if (!comp(node->parent->value, node->value)) {\n            return;\n\
    \        }\n        while (node->parent) {\n            auto parent = node->parent;\n\
    \            node->damaged = false;\n            parent->child = node->erase();\n\
    \            --(parent->order);\n            _root->insert_left(node);\n     \
    \       if (comp(_root->value, _root->left->value)) _root = _root->left;\n   \
    \         if (!parent->damaged) {\n                parent->damaged = true;\n \
    \               break;\n            }\n            node = parent;\n        }\n\
    \    }\n\n  private:\n    node_ptr _root;\n    int _size;\n    Comp comp;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/heap/fibonacci_heap.hpp
  requiredBy: []
  timestamp: '2024-05-03 20:45:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/heap/fibonacci_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/fibonacci_heap.hpp
- /library/lib/heap/fibonacci_heap.hpp.html
title: "\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7"
---
