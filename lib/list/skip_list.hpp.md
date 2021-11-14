---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/algorithm/xorshift.hpp
    title: lib/algorithm/xorshift.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n#include \"algorithm/xorshift.hpp\"\n\
    \ntemplate <class T, int B = 20>\nstruct skip_list {\n    struct Node {\n    \
    \    T val;\n        Node* itr[B];\n\n        Node(T _val = T()) : val(_val) {\n\
    \            for (int i = 0; i < B; ++i) itr[i] = nullptr;\n        }\n    };\n\
    \n    Node* head;\n    Xorshift xor128;\n\n    skip_list() : xor128() { head =\
    \ new Node(); }\n\n    void insert(T val) {\n        int height = 0;\n       \
    \ for (int i = 0; i < B - 1; ++i) {\n            if (xor128() & 1) break;\n  \
    \          ++height;\n        }\n\n        Node* new_node = new Node(val);\n \
    \       Node* node = head;\n        for (int i = B - 1; i >= 0; --i) {\n     \
    \       while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];\n\
    \n            if (i <= height) {\n                new_node->itr[i] = node->itr[i];\n\
    \                node->itr[i] = new_node;\n            }\n        }\n    }\n\n\
    \    void erase(T val) {\n        Node* node = head;\n        for (int i = B -\
    \ 1; i >= 0; --i) {\n            while (node->itr[i] && node->itr[i]->val < val)\
    \ node = node->itr[i];\n        }\n        Node* delete_node = node->itr[0]->val\
    \ == val ? node->itr[0] : nullptr;\n        if (!delete_node) return;\n      \
    \  for (int i = B - 1; i >= 0; --i) {\n            while (node->itr[i] && node->itr[i]->val\
    \ < val) node = node->itr[i];\n            if (node->itr[i] == delete_node) node->itr[i]\
    \ = node->itr[i]->itr[i];\n        }\n    }\n\n    int count(T val) {\n      \
    \  Node* node = head;\n        for (int i = B - 1; i >= 0; --i) {\n          \
    \  while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];\n    \
    \    }\n\n        int res = 0;\n        while (node->itr[0] && node->itr[0]->val\
    \ == val) {\n            ++res;\n            node = node->itr[0];\n        }\n\
    \        return res;\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/algorithm/xorshift.hpp
  isVerificationFile: false
  path: lib/list/skip_list.hpp
  requiredBy: []
  timestamp: '2021-10-10 14:29:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/list/skip_list.hpp
layout: document
redirect_from:
- /library/lib/list/skip_list.hpp
- /library/lib/list/skip_list.hpp.html
title: lib/list/skip_list.hpp
---
