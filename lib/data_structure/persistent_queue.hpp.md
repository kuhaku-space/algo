---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/persistent_queue.test.cpp
    title: test/yosupo/data_structure/persistent_queue.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"lib/data_structure/persistent_queue.hpp\"\n#include <vector>\n\
    \ntemplate <class T>\nstruct persistent_queue {\n  private:\n    struct _node\
    \ {\n        using pointer = _node *;\n        T val;\n        std::vector<pointer>\
    \ prev;\n\n        _node(T _val) : val(_val), prev() {}\n    };\n\n  public:\n\
    \    using node_pointer = typename _node::pointer;\n\n    constexpr persistent_queue()\
    \ : _size(), root() {}\n    constexpr persistent_queue(int n, node_pointer _root)\
    \ : _size(n), root(_root) {}\n\n    constexpr int size() const { return _size;\
    \ }\n\n    T top() const {\n        node_pointer node = root;\n        int k =\
    \ 0;\n        while ((_size - 1) >> k) {\n            if ((_size - 1) >> k & 1)\
    \ { node = node->prev[k]; }\n            ++k;\n        }\n        return node->val;\n\
    \    }\n    T front() const { return top(); }\n\n    persistent_queue push(T val)\
    \ const {\n        node_pointer new_node = new _node(val);\n        node_pointer\
    \ node = root;\n        new_node->prev.emplace_back(node);\n        int k = 0;\n\
    \        while (node) {\n            if (node->prev.size() > k) node = node->prev[k++];\n\
    \            else node = nullptr;\n            new_node->prev.emplace_back(node);\n\
    \        }\n        return persistent_queue(_size + 1, new_node);\n    }\n   \
    \ persistent_queue emplace(T val) const { return push(val); }\n\n    persistent_queue\
    \ pop() const { return persistent_queue(_size - 1, root); }\n\n  private:\n  \
    \  int _size;\n    node_pointer root;\n};\n"
  code: "#pragma once\n#include <vector>\n\ntemplate <class T>\nstruct persistent_queue\
    \ {\n  private:\n    struct _node {\n        using pointer = _node *;\n      \
    \  T val;\n        std::vector<pointer> prev;\n\n        _node(T _val) : val(_val),\
    \ prev() {}\n    };\n\n  public:\n    using node_pointer = typename _node::pointer;\n\
    \n    constexpr persistent_queue() : _size(), root() {}\n    constexpr persistent_queue(int\
    \ n, node_pointer _root) : _size(n), root(_root) {}\n\n    constexpr int size()\
    \ const { return _size; }\n\n    T top() const {\n        node_pointer node =\
    \ root;\n        int k = 0;\n        while ((_size - 1) >> k) {\n            if\
    \ ((_size - 1) >> k & 1) { node = node->prev[k]; }\n            ++k;\n       \
    \ }\n        return node->val;\n    }\n    T front() const { return top(); }\n\
    \n    persistent_queue push(T val) const {\n        node_pointer new_node = new\
    \ _node(val);\n        node_pointer node = root;\n        new_node->prev.emplace_back(node);\n\
    \        int k = 0;\n        while (node) {\n            if (node->prev.size()\
    \ > k) node = node->prev[k++];\n            else node = nullptr;\n           \
    \ new_node->prev.emplace_back(node);\n        }\n        return persistent_queue(_size\
    \ + 1, new_node);\n    }\n    persistent_queue emplace(T val) const { return push(val);\
    \ }\n\n    persistent_queue pop() const { return persistent_queue(_size - 1, root);\
    \ }\n\n  private:\n    int _size;\n    node_pointer root;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/data_structure/persistent_queue.hpp
  requiredBy: []
  timestamp: '2024-05-03 19:27:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/persistent_queue.test.cpp
documentation_of: lib/data_structure/persistent_queue.hpp
layout: document
redirect_from:
- /library/lib/data_structure/persistent_queue.hpp
- /library/lib/data_structure/persistent_queue.hpp.html
title: lib/data_structure/persistent_queue.hpp
---
