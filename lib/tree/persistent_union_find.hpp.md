---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/persistent_array.hpp
    title: "\u6C38\u7D9A\u914D\u5217"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/persistent_union_find.test.cpp
    title: test/yosupo/data_structure/persistent_union_find.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6C38\u7D9AUnion-Find"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/persistent_array.hpp:\
    \ line -1: no such header\n"
  code: "#include \"data_structure/persistent_array.hpp\"\n#include \"template/template.hpp\"\
    \n\n/**\n * @brief \u6C38\u7D9AUnion-Find\n *\n */\nstruct persistent_union_find\
    \ {\n    constexpr persistent_union_find() : data() {}\n    persistent_union_find(const\
    \ persistent_array<int> &_data) : data(_data) {}\n    persistent_union_find(int\
    \ n) : data(n, -1) {}\n\n    int root(int x) const {\n        int y = this->data[x];\n\
    \        return y < 0 ? x : this->root(y);\n    }\n    int get_root(int x) const\
    \ { return this->root(x); }\n\n    bool is_root(int x) const { return this->data[x]\
    \ < 0; }\n\n    persistent_union_find unite(int x, int y) {\n        x = this->root(x),\
    \ y = this->root(y);\n        if (x == y) return *this;\n        int a = this->data[x],\
    \ b = this->data[y];\n        if (a > b) std::swap(x, y);\n        return persistent_union_find(this->data.set(x,\
    \ a + b).set(y, x));\n    }\n\n    int size(int x) const { return -(this->data[this->root(x)]);\
    \ }\n    int get_size(int x) const { return this->size(x); }\n\n    bool same(int\
    \ x, int y) const { return this->root(x) == this->root(y); }\n    bool is_same(int\
    \ x, int y) const { return this->same(x, y); }\n\n  private:\n    persistent_array<int>\
    \ data;\n};\n"
  dependsOn:
  - lib/data_structure/persistent_array.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/persistent_union_find.hpp
  requiredBy: []
  timestamp: '2023-05-22 20:02:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/persistent_union_find.test.cpp
documentation_of: lib/tree/persistent_union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/persistent_union_find.hpp
- /library/lib/tree/persistent_union_find.hpp.html
title: "\u6C38\u7D9AUnion-Find"
---
