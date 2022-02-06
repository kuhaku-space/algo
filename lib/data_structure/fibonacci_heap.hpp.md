---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/graph/dijkstra_fibonacci.hpp
    title: lib/graph/dijkstra_fibonacci.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_fibonacci.test.cpp
    title: test/aoj/grl/dijkstra_fibonacci.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\ntemplate <class Key, class Value, class\
    \ Comp = std::less<>>\nstruct fibonacci_heap {\n  private:\n    struct _node {\n\
    \        using pointer = _node *;\n        Key key;\n        Value value;\n  \
    \      int order;\n        pointer left, right;\n        pointer parent, child;\n\
    \        bool dameged;\n\n        _node() : key(), value(), order(), left(this),\
    \ right(this), parent(), child(), dameged() {}\n        _node(Key _key, Value\
    \ _value)\n            : key(_key),\n              value(_value),\n          \
    \    order(),\n              left(this),\n              right(this),\n       \
    \       parent(),\n              child(),\n              dameged() {}\n\n    \
    \    void add_child(pointer node) {\n            node->parent = this;\n      \
    \      if (this->child)\n                this->child->insert_left(node);\n   \
    \         else\n                this->child = node;\n            ++(this->order);\n\
    \        }\n        void insert_left(pointer node) {\n            node->right\
    \ = this;\n            node->left = this->left;\n            this->left->right\
    \ = node;\n            this->left = node;\n        }\n        void insert_right(pointer\
    \ node) {\n            node->left = this;\n            node->right = this->right;\n\
    \            this->right->left = node;\n            this->right = node;\n    \
    \    }\n\n        pointer erase() {\n            this->parent = nullptr;\n   \
    \         if (this->left == this) return nullptr;\n            this->left->right\
    \ = this->right;\n            this->right->left = this->left;\n            auto\
    \ res = this->left;\n            this->left = this->right = this;\n          \
    \  return res;\n        }\n    };\n\n  public:\n    using node_pointer = typename\
    \ _node::pointer;\n    fibonacci_heap() : _root(nullptr), _size() {}\n\n    bool\
    \ empty() const { return this->_size == 0; }\n\n    pair<Key, Value> top() const\
    \ { return make_pair(this->_root->key, this->_root->value); }\n\n    auto push(Key\
    \ key, Value value) {\n        ++(this->_size);\n        auto node = new _node(key,\
    \ value);\n        if (!this->_root) {\n            this->_root = node;\n    \
    \    } else {\n            this->_root->insert_left(node);\n            if (Comp()(this->_root->value,\
    \ value)) this->_root = this->_root->left;\n        }\n        return node;\n\
    \    }\n\n    void pop() {\n        --(this->_size);\n        if (this->_root->child)\
    \ {\n            auto child = this->_root->child, left = child->left;\n      \
    \      this->_root->left->right = child;\n            child->left->right = this->_root;\n\
    \            child->left = this->_root->left;\n            this->_root->left =\
    \ left;\n        }\n        this->_root = this->_root->erase();\n        if (!this->_root)\
    \ return;\n\n        node_pointer nodes[30] = {};\n        while (this->_root)\
    \ {\n            auto node = this->_root;\n            auto order = node->order;\n\
    \            this->_root = this->_root->erase();\n            while (nodes[order])\
    \ {\n                if (Comp()(node->value, nodes[order]->value)) { swap(node,\
    \ nodes[order]); }\n                node->add_child(nodes[order]);\n         \
    \       nodes[order] = nullptr;\n                ++order;\n            }\n   \
    \         nodes[order] = node;\n        }\n\n        for (auto node : nodes) {\n\
    \            if (node && (!this->_root || Comp()(this->_root->value, node->value)))\n\
    \                this->_root = node;\n        }\n        for (auto node : nodes)\
    \ {\n            if (node && node != this->_root) { this->_root->insert_left(node);\
    \ }\n        }\n    }\n\n    void update(node_pointer node, Value value) {\n \
    \       if (Comp()(node->value, value))\n            node->value = value;\n  \
    \      else\n            return;\n        if (!node->parent) {\n            if\
    \ (Comp()(this->_root->value, value)) this->_root = node;\n            return;\n\
    \        } else if (!Comp()(node->parent->value, node->value)) {\n           \
    \ return;\n        }\n        while (node->parent) {\n            auto parent\
    \ = node->parent;\n            node->dameged = false;\n            parent->child\
    \ = node->erase();\n            --(parent->order);\n            this->_root->insert_left(node);\n\
    \            if (Comp()(this->_root->value, this->_root->left->value))\n     \
    \           this->_root = this->_root->left;\n            if (!parent->dameged)\
    \ {\n                parent->dameged = true;\n                break;\n       \
    \     }\n            node = parent;\n        }\n    }\n\n  private:\n    node_pointer\
    \ _root;\n    int _size;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/fibonacci_heap.hpp
  requiredBy:
  - lib/graph/dijkstra_fibonacci.hpp
  timestamp: '2022-02-06 19:58:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/dijkstra_fibonacci.test.cpp
documentation_of: lib/data_structure/fibonacci_heap.hpp
layout: document
redirect_from:
- /library/lib/data_structure/fibonacci_heap.hpp
- /library/lib/data_structure/fibonacci_heap.hpp.html
title: lib/data_structure/fibonacci_heap.hpp
---
