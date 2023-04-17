---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\ntemplate <class T>\n\
    struct persistent_queue {\n  private:\n    struct Node {\n        using pointer\
    \ = Node *;\n        T val;\n        std::vector<pointer> prev;\n\n        Node(T\
    \ _val) : val(_val), prev() {}\n    };\n\n  public:\n    using node_pointer =\
    \ typename Node::pointer;\n\n    constexpr persistent_queue() : _size(), root()\
    \ {}\n    constexpr persistent_queue(int n, node_pointer _root) : _size(n), root(_root)\
    \ {}\n\n    constexpr int size() const { return this->_size; }\n\n    T top()\
    \ const {\n        node_pointer node = this->root;\n        int k = 0;\n     \
    \   while ((this->_size - 1) >> k) {\n            if ((this->_size - 1) >> k &\
    \ 1) { node = node->prev[k]; }\n            ++k;\n        }\n        return node->val;\n\
    \    }\n    T front() const { return this->top(); }\n\n    persistent_queue push(T\
    \ val) const {\n        node_pointer new_node = new Node(val);\n        node_pointer\
    \ node = root;\n        new_node->prev.emplace_back(node);\n        int k = 0;\n\
    \        while (node) {\n            if (node->prev.size() > k) node = node->prev[k++];\n\
    \            else node = nullptr;\n            new_node->prev.emplace_back(node);\n\
    \        }\n        return persistent_queue(_size + 1, new_node);\n    }\n   \
    \ persistent_queue emplace(T val) const { return this->push(val); }\n\n    persistent_queue\
    \ pop() const { return persistent_queue(this->_size - 1, root); }\n\n  private:\n\
    \    int _size;\n    node_pointer root;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/persistent_queue.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
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
