---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u4E8C\u5206\u30D2\u30FC\u30D7"
    links: []
  bundledCode: "#line 1 \"lib/heap/binary_heap.hpp\"\n#include <functional>\n#include\
    \ <utility>\n#include <vector>\n\n/**\n * @brief \u4E8C\u5206\u30D2\u30FC\u30D7\
    \n *\n * @tparam Key \u30AD\u30FC\u306E\u578B\n * @tparam Value \u5024\u306E\u578B\
    \n * @tparam Comp \u6BD4\u8F03\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n */\ntemplate\
    \ <class Key, class Value, class Comp = std::less<>>\nstruct binary_heap {\n \
    \ private:\n    struct _node {\n        using pointer = _node *;\n\n        Key\
    \ key;\n        Value value;\n        int index;\n\n        constexpr _node(Key\
    \ _key, Value _value) : key(_key), value(_value), index() {}\n\n        constexpr\
    \ bool operator<(const _node &rhs) const { return value < rhs.value; }\n\n   \
    \     constexpr std::pair<Key, Value> get_pair() const { return std::make_pair(key,\
    \ value); }\n        constexpr int get_index() const { return index; }\n     \
    \   constexpr void set_index(int new_index) { index = new_index; }\n    };\n\n\
    \  public:\n    using node_pointer = typename _node::pointer;\n\n    binary_heap()\
    \ : _size(), nodes(1), comp() {}\n\n    std::pair<Key, Value> top() const { return\
    \ nodes[1]->get_pair(); }\n    constexpr int size() const { return _size; }\n\
    \    constexpr bool empty() const { return _size == 0; }\n\n    node_pointer push(Key\
    \ key, Value value) {\n        auto node = new _node(key, value);\n        nodes.emplace_back(node);\n\
    \n        int index = increment_size();\n        while (index > 1 && comp(nodes[index\
    \ >> 1]->value, nodes[index]->value)) {\n            std::swap(nodes[index], nodes[index\
    \ >> 1]);\n            nodes[index]->set_index(index);\n            index >>=\
    \ 1;\n        }\n        nodes[index]->set_index(index);\n\n        return node;\n\
    \    }\n    node_pointer emplace(Key key, Value value) { return push(key, value);\
    \ }\n\n    void pop() {\n        nodes[1] = nodes[decrement_size()];\n       \
    \ nodes.pop_back();\n\n        int index = 1 << 1;\n        while (index <= _size)\
    \ {\n            if (index < _size && comp(nodes[index]->value, nodes[index +\
    \ 1]->value)) ++index;\n            if (comp(nodes[index]->value, nodes[index\
    \ >> 1]->value)) break;\n            std::swap(nodes[index >> 1], nodes[index]);\n\
    \            nodes[index >> 1]->set_index(index >> 1);\n            index <<=\
    \ 1;\n        }\n        nodes[index >> 1]->set_index(index >> 1);\n    }\n\n\
    \    void update(node_pointer node, Value value) {\n        if (comp(node->value,\
    \ value)) node->value = value;\n        else return;\n        int index = node->get_index();\n\
    \        while (index > 1 && comp(nodes[index >> 1]->value, nodes[index]->value))\
    \ {\n            std::swap(nodes[index], nodes[index >> 1]);\n            nodes[index]->set_index(index);\n\
    \            index >>= 1;\n        }\n        nodes[index]->set_index(index);\n\
    \    }\n\n  private:\n    int _size;\n    std::vector<node_pointer> nodes;\n \
    \   Comp comp;\n\n    constexpr int increment_size() { return ++_size; }\n   \
    \ constexpr int decrement_size() { return _size--; }\n};\n"
  code: "#include <functional>\n#include <utility>\n#include <vector>\n\n/**\n * @brief\
    \ \u4E8C\u5206\u30D2\u30FC\u30D7\n *\n * @tparam Key \u30AD\u30FC\u306E\u578B\n\
    \ * @tparam Value \u5024\u306E\u578B\n * @tparam Comp \u6BD4\u8F03\u30AA\u30D6\
    \u30B8\u30A7\u30AF\u30C8\n */\ntemplate <class Key, class Value, class Comp =\
    \ std::less<>>\nstruct binary_heap {\n  private:\n    struct _node {\n       \
    \ using pointer = _node *;\n\n        Key key;\n        Value value;\n       \
    \ int index;\n\n        constexpr _node(Key _key, Value _value) : key(_key), value(_value),\
    \ index() {}\n\n        constexpr bool operator<(const _node &rhs) const { return\
    \ value < rhs.value; }\n\n        constexpr std::pair<Key, Value> get_pair() const\
    \ { return std::make_pair(key, value); }\n        constexpr int get_index() const\
    \ { return index; }\n        constexpr void set_index(int new_index) { index =\
    \ new_index; }\n    };\n\n  public:\n    using node_pointer = typename _node::pointer;\n\
    \n    binary_heap() : _size(), nodes(1), comp() {}\n\n    std::pair<Key, Value>\
    \ top() const { return nodes[1]->get_pair(); }\n    constexpr int size() const\
    \ { return _size; }\n    constexpr bool empty() const { return _size == 0; }\n\
    \n    node_pointer push(Key key, Value value) {\n        auto node = new _node(key,\
    \ value);\n        nodes.emplace_back(node);\n\n        int index = increment_size();\n\
    \        while (index > 1 && comp(nodes[index >> 1]->value, nodes[index]->value))\
    \ {\n            std::swap(nodes[index], nodes[index >> 1]);\n            nodes[index]->set_index(index);\n\
    \            index >>= 1;\n        }\n        nodes[index]->set_index(index);\n\
    \n        return node;\n    }\n    node_pointer emplace(Key key, Value value)\
    \ { return push(key, value); }\n\n    void pop() {\n        nodes[1] = nodes[decrement_size()];\n\
    \        nodes.pop_back();\n\n        int index = 1 << 1;\n        while (index\
    \ <= _size) {\n            if (index < _size && comp(nodes[index]->value, nodes[index\
    \ + 1]->value)) ++index;\n            if (comp(nodes[index]->value, nodes[index\
    \ >> 1]->value)) break;\n            std::swap(nodes[index >> 1], nodes[index]);\n\
    \            nodes[index >> 1]->set_index(index >> 1);\n            index <<=\
    \ 1;\n        }\n        nodes[index >> 1]->set_index(index >> 1);\n    }\n\n\
    \    void update(node_pointer node, Value value) {\n        if (comp(node->value,\
    \ value)) node->value = value;\n        else return;\n        int index = node->get_index();\n\
    \        while (index > 1 && comp(nodes[index >> 1]->value, nodes[index]->value))\
    \ {\n            std::swap(nodes[index], nodes[index >> 1]);\n            nodes[index]->set_index(index);\n\
    \            index >>= 1;\n        }\n        nodes[index]->set_index(index);\n\
    \    }\n\n  private:\n    int _size;\n    std::vector<node_pointer> nodes;\n \
    \   Comp comp;\n\n    constexpr int increment_size() { return ++_size; }\n   \
    \ constexpr int decrement_size() { return _size--; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/heap/binary_heap.hpp
  requiredBy: []
  timestamp: '2023-10-01 20:39:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/heap/binary_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/binary_heap.hpp
- /library/lib/heap/binary_heap.hpp.html
title: "\u4E8C\u5206\u30D2\u30FC\u30D7"
---
