---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\ntemplate <class T>\n\
    struct persistent_stack {\n  private:\n    struct Node {\n        using pointer\
    \ = Node *;\n        T val;\n        pointer prev;\n    };\n\n  public:\n    using\
    \ node_pointer = Node::pointer;\n\n    constexpr persistent_stack() : root(nullptr)\
    \ {}\n    constexpr persistent_stack(node_pointer _root) : root(_root) {}\n\n\
    \    T top() const {\n        assert(this->root);\n        return this->root->val;\n\
    \    }\n\n    persistent_stack push(T val) const { return persistent_stack(new\
    \ Node{val, this->root}); }\n\n    persistent_stack pop() const {\n        assert(this->root);\n\
    \        return persistent_stack(this->root->prev);\n    }\n\n  private:\n   \
    \ node_pointer root;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/persistent_stack.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/persistent_stack.hpp
layout: document
redirect_from:
- /library/lib/data_structure/persistent_stack.hpp
- /library/lib/data_structure/persistent_stack.hpp.html
title: lib/data_structure/persistent_stack.hpp
---
