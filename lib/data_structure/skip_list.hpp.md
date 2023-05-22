---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/random/split_mix_64.hpp
    title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 SplitMix64"
  - icon: ':heavy_check_mark:'
    path: lib/random/xorshift.hpp
    title: "\u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: random/xorshift.hpp:\
    \ line -1: no such header\n"
  code: "#include \"random/xorshift.hpp\"\n#include \"template/template.hpp\"\n\n\
    template <class T, int B = 20, class UniformRandomBitGenerator = Xorshift>\nstruct\
    \ skip_list {\n  private:\n    struct _node {\n        using pointer = _node *;\n\
    \        T val;\n        pointer itr[B];\n\n        _node() : _node(T()) {}\n\
    \        _node(T _val) : val(_val), itr{} {}\n    };\n\n  public:\n    using node_ptr\
    \ = typename _node::pointer;\n\n    skip_list() : head(), gen() { this->head =\
    \ new _node(); }\n\n    void emplace(T val) { this->insert(val); }\n    void insert(T\
    \ val) {\n        int height = 0;\n        for (int i = 0; i < B - 1; ++i) {\n\
    \            if (this->gen() & 1) break;\n            ++height;\n        }\n\n\
    \        node_ptr new_node = new _node(val);\n        node_ptr node = this->head;\n\
    \        for (int i = B - 1; i >= 0; --i) {\n            while (node->itr[i] &&\
    \ node->itr[i]->val < val) node = node->itr[i];\n\n            if (i <= height)\
    \ {\n                new_node->itr[i] = node->itr[i];\n                node->itr[i]\
    \ = new_node;\n            }\n        }\n    }\n\n    void erase(T val) {\n  \
    \      node_ptr node = this->head;\n        for (int i = B - 1; i >= 0; --i) {\n\
    \            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];\n\
    \        }\n        node_ptr delete_node = node->itr[0]->val == val ? node->itr[0]\
    \ : nullptr;\n        if (!delete_node) return;\n        for (int i = B - 1; i\
    \ >= 0; --i) {\n            while (node->itr[i] && node->itr[i]->val < val) node\
    \ = node->itr[i];\n            if (node->itr[i] == delete_node) node->itr[i] =\
    \ node->itr[i]->itr[i];\n        }\n    }\n\n    bool contains(T val) {\n    \
    \    node_ptr node = this->head;\n        for (int i = B - 1; i >= 0; --i) {\n\
    \            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];\n\
    \            if (node->itr[i] && node->itr[i]->val == val) return true;\n    \
    \    }\n        return false;\n    }\n\n    int count(T val) {\n        node_ptr\
    \ node = this->head;\n        for (int i = B - 1; i >= 0; --i) {\n           \
    \ while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];\n     \
    \   }\n\n        int res = 0;\n        while (node->itr[0] && node->itr[0]->val\
    \ == val) {\n            ++res;\n            node = node->itr[0];\n        }\n\
    \        return res;\n    }\n\n  private:\n    node_ptr head;\n    UniformRandomBitGenerator\
    \ gen;\n};\n"
  dependsOn:
  - lib/random/xorshift.hpp
  - lib/random/split_mix_64.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/skip_list.hpp
  requiredBy: []
  timestamp: '2023-05-22 19:46:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/skip_list.hpp
layout: document
redirect_from:
- /library/lib/data_structure/skip_list.hpp
- /library/lib/data_structure/skip_list.hpp.html
title: lib/data_structure/skip_list.hpp
---
