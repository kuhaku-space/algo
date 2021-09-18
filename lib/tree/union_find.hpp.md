---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/graph/kruskal.hpp
    title: lib/graph/kruskal.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/unionfind.test.cpp
    title: test/yosupo/data_structure/unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc214/tasks/abc214_d
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/*\r\n * verify :\r\n * https://atcoder.jp/contests/abc214/tasks/abc214_d\
    \ 21/08/15\r\n */\r\n\r\nstruct union_find {\r\n    vector<int> data;\r\n\r\n\
    \    union_find(int _n) : data(_n, -1) {}\r\n\r\n    int root(int x) { return\
    \ data[x] < 0 ? x : data[x] = this->root(data[x]); }\r\n\r\n    bool is_root(int\
    \ x) { return data[x] < 0; }\r\n\r\n    void unite(int x, int y) {\r\n       \
    \ x = this->root(x), y = this->root(y);\r\n        if (x != y) {\r\n         \
    \   if (data[x] > data[y]) swap(x, y);\r\n            data[x] += data[y];\r\n\
    \            data[y] = x;\r\n        }\r\n    }\r\n\r\n    int size(int x) { return\
    \ -data[this->root(x)]; }\r\n\r\n    bool same(int x, int y) { return this->root(x)\
    \ == this->root(y); }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/union_find.hpp
  requiredBy:
  - lib/graph/kruskal.hpp
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/unionfind.test.cpp
documentation_of: lib/tree/union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/union_find.hpp
- /library/lib/tree/union_find.hpp.html
title: lib/tree/union_find.hpp
---
