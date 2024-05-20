---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"lib/data_structure/persistent_stack.hpp\"\n#include <cassert>\n\
    \ntemplate <class T>\nstruct persistent_stack {\n  private:\n    struct _node\
    \ {\n        using pointer = _node *;\n        T val;\n        pointer prev;\n\
    \    };\n\n  public:\n    using node_pointer = _node::pointer;\n\n    constexpr\
    \ persistent_stack() : root(nullptr) {}\n    constexpr persistent_stack(node_pointer\
    \ _root) : root(_root) {}\n\n    T top() const {\n        assert(root);\n    \
    \    return root->val;\n    }\n\n    persistent_stack push(T val) const { return\
    \ persistent_stack(new _node{val, root}); }\n\n    persistent_stack pop() const\
    \ {\n        assert(root);\n        return persistent_stack(root->prev);\n   \
    \ }\n\n  private:\n    node_pointer root;\n};\n"
  code: "#pragma once\n#include <cassert>\n\ntemplate <class T>\nstruct persistent_stack\
    \ {\n  private:\n    struct _node {\n        using pointer = _node *;\n      \
    \  T val;\n        pointer prev;\n    };\n\n  public:\n    using node_pointer\
    \ = _node::pointer;\n\n    constexpr persistent_stack() : root(nullptr) {}\n \
    \   constexpr persistent_stack(node_pointer _root) : root(_root) {}\n\n    T top()\
    \ const {\n        assert(root);\n        return root->val;\n    }\n\n    persistent_stack\
    \ push(T val) const { return persistent_stack(new _node{val, root}); }\n\n   \
    \ persistent_stack pop() const {\n        assert(root);\n        return persistent_stack(root->prev);\n\
    \    }\n\n  private:\n    node_pointer root;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/data_structure/persistent_stack.hpp
  requiredBy: []
  timestamp: '2024-05-03 19:30:49+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/persistent_stack.hpp
layout: document
redirect_from:
- /library/lib/data_structure/persistent_stack.hpp
- /library/lib/data_structure/persistent_stack.hpp.html
title: lib/data_structure/persistent_stack.hpp
---
