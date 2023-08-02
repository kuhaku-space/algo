---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u30D5\u30A3\u30DC\u30CA\
    \u30C3\u30C1\u30D2\u30FC\u30D7\n *\n * @tparam Key \u30AD\u30FC\u306E\u578B\n\
    \ * @tparam Value \u5024\u306E\u578B\n * @tparam Comp \u95A2\u6570\u30AA\u30D6\
    \u30B8\u30A7\u30AF\u30C8\n */\ntemplate <class Key, class Value, class Comp =\
    \ std::less<>>\nstruct fibonacci_heap {\n  private:\n    struct _node {\n    \
    \    using pointer = _node *;\n        Key key;\n        Value value;\n      \
    \  int order;\n        pointer left, right;\n        pointer parent, child;\n\
    \        bool dameged;\n\n        _node() : key(), value(), order(), left(this),\
    \ right(this), parent(), child(), dameged() {}\n        _node(Key _key, Value\
    \ _value)\n            : key(_key), value(_value), order(), left(this), right(this),\
    \ parent(), child(),\n              dameged() {}\n\n        void add_child(pointer\
    \ node) {\n            node->parent = this;\n            if (this->child) this->child->insert_left(node);\n\
    \            else this->child = node;\n            ++(this->order);\n        }\n\
    \        void insert_left(pointer node) {\n            node->right = this;\n \
    \           node->left = this->left;\n            this->left->right = node;\n\
    \            this->left = node;\n        }\n        void insert_right(pointer\
    \ node) {\n            node->left = this;\n            node->right = this->right;\n\
    \            this->right->left = node;\n            this->right = node;\n    \
    \    }\n\n        pointer erase() {\n            this->parent = nullptr;\n   \
    \         if (this->left == this) return nullptr;\n            this->left->right\
    \ = this->right;\n            this->right->left = this->left;\n            auto\
    \ res = this->left;\n            this->left = this->right = this;\n          \
    \  return res;\n        }\n\n        constexpr auto get_pair() const { return\
    \ std::make_pair(key, value); }\n    };\n\n  public:\n    using node_ptr = typename\
    \ _node::pointer;\n\n    fibonacci_heap() : _root(nullptr), _size(), comp() {}\n\
    \n    bool empty() const { return this->_size == 0; }\n    constexpr int size()\
    \ const { return this->_size; }\n    constexpr auto top() const { return this->_root->get_pair();\
    \ }\n\n    auto push(Key key, Value value) {\n        ++(this->_size);\n     \
    \   auto node = new _node(key, value);\n        if (!this->_root) {\n        \
    \    this->_root = node;\n        } else {\n            this->_root->insert_left(node);\n\
    \            if (comp(this->_root->value, value)) this->_root = this->_root->left;\n\
    \        }\n        return node;\n    }\n    auto emplace(Key key, Value value)\
    \ { return this->push(key, value); }\n\n    void pop() {\n        --(this->_size);\n\
    \        if (this->_root->child) {\n            auto child = this->_root->child,\
    \ left = child->left;\n            this->_root->left->right = child;\n       \
    \     child->left->right = this->_root;\n            child->left = this->_root->left;\n\
    \            this->_root->left = left;\n        }\n        this->_root = this->_root->erase();\n\
    \        if (!this->_root) return;\n\n        node_ptr nodes[30] = {};\n     \
    \   while (this->_root) {\n            auto node = this->_root;\n            auto\
    \ order = node->order;\n            this->_root = this->_root->erase();\n    \
    \        while (nodes[order]) {\n                if (comp(node->value, nodes[order]->value))\
    \ std::swap(node, nodes[order]);\n                node->add_child(nodes[order]);\n\
    \                nodes[order] = nullptr;\n                ++order;\n         \
    \   }\n            nodes[order] = node;\n        }\n\n        for (auto node :\
    \ nodes) {\n            if (node && (!this->_root || comp(this->_root->value,\
    \ node->value))) this->_root = node;\n        }\n        for (auto node : nodes)\
    \ {\n            if (node && node != this->_root) this->_root->insert_left(node);\n\
    \        }\n    }\n\n    void update(node_ptr node, Value value) {\n        if\
    \ (comp(node->value, value)) node->value = value;\n        else return;\n    \
    \    if (!node->parent) {\n            if (comp(this->_root->value, value)) this->_root\
    \ = node;\n            return;\n        } else if (!comp(node->parent->value,\
    \ node->value)) {\n            return;\n        }\n        while (node->parent)\
    \ {\n            auto parent = node->parent;\n            node->dameged = false;\n\
    \            parent->child = node->erase();\n            --(parent->order);\n\
    \            this->_root->insert_left(node);\n            if (comp(this->_root->value,\
    \ this->_root->left->value)) this->_root = this->_root->left;\n            if\
    \ (!parent->dameged) {\n                parent->dameged = true;\n            \
    \    break;\n            }\n            node = parent;\n        }\n    }\n\n \
    \ private:\n    node_ptr _root;\n    int _size;\n    Comp comp;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/heap/fibonacci_heap.hpp
  requiredBy: []
  timestamp: '2023-05-22 20:02:34+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/heap/fibonacci_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/fibonacci_heap.hpp
- /library/lib/heap/fibonacci_heap.hpp.html
title: "\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7"
---
