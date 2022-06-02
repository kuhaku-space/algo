---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/tree/persistent_union_find.hpp
    title: lib/tree/persistent_union_find.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/persistent_union_find.test.cpp
    title: test/yosupo/data_structure/persistent_union_find.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\ntemplate <class T, int N = 20>\nstruct\
    \ persistent_array {\n    struct Node {\n        using pointer = Node *;\n   \
    \     T val;\n        pointer ch[N] = {};\n    };\n    using node_pointer = typename\
    \ Node::pointer;\n\n    constexpr persistent_array() : root() {}\n    constexpr\
    \ persistent_array(node_pointer _root) : root(_root) {}\n    constexpr persistent_array(int\
    \ n, T val) : root() {\n        for (int i = 0; i < n; ++i) { this->root = this->set(i,\
    \ val, this->root); }\n    }\n    template <class U>\n    constexpr persistent_array(const\
    \ vector<U> &v) : root() {\n        for (int i = 0; i < (int)v.size(); ++i) {\
    \ this->root = this->set(i, v[i], this->root); }\n    }\n\n    constexpr T operator[](int\
    \ i) const noexcept {\n        node_pointer node = root;\n        while (node)\
    \ {\n            if (i == 0) {\n                return node->val;\n          \
    \  } else {\n                --i;\n                node = node->ch[i % N], i =\
    \ i / N;\n            }\n        }\n        return T();\n    }\n    constexpr\
    \ T at(int k) const noexcept { return this->operator[](k); }\n    constexpr T\
    \ get(int k) const noexcept { return this->operator[](k); }\n\n    persistent_array\
    \ set(int k, T val) const noexcept {\n        return persistent_array(this->set(k,\
    \ val, root));\n    }\n\n  private:\n    node_pointer root;\n\n    node_pointer\
    \ set(int k, T val, node_pointer node) const noexcept {\n        node_pointer\
    \ res = new Node();\n        if (node) {\n            memcpy(res->ch, node->ch,\
    \ sizeof(node->ch));\n            res->val = node->val;\n        }\n        if\
    \ (k == 0) {\n            res->val = val;\n        } else {\n            --k;\n\
    \            res->ch[k % N] = set(k / N, val, res->ch[k % N]);\n        }\n  \
    \      return res;\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/persistent_array.hpp
  requiredBy:
  - lib/tree/persistent_union_find.hpp
  timestamp: '2022-05-14 10:40:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/persistent_union_find.test.cpp
documentation_of: lib/data_structure/persistent_array.hpp
layout: document
redirect_from:
- /library/lib/data_structure/persistent_array.hpp
- /library/lib/data_structure/persistent_array.hpp.html
title: lib/data_structure/persistent_array.hpp
---
