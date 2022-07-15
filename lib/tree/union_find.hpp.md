---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/graph/kruskal.hpp
    title: "\u30AF\u30E9\u30B9\u30AB\u30EB\u6CD5"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/union_find.test.cpp
    title: test/aoj/dsl/union_find.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/kruskal.test.cpp
    title: test/aoj/grl/kruskal.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/unionfind.test.cpp
    title: test/yosupo/data_structure/unionfind.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
    links:
    - https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u7D20\u96C6\u5408\
    \u30C7\u30FC\u30BF\u69CB\u9020\r\n * @details Implement (union by size) + (path\
    \ compression)\r\n * @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp\r\
    \n */\r\nstruct union_find {\r\n    union_find() : data() {}\r\n    union_find(int\
    \ _n) : data(_n, -1) {}\r\n\r\n    int root(int x) { return this->data[x] < 0\
    \ ? x : this->data[x] = this->root(this->data[x]); }\r\n    int get_root(int x)\
    \ { return this->root(x); }\r\n\r\n    bool is_root(int x) const { return this->data[x]\
    \ < 0; }\r\n\r\n    bool same(int x, int y) { return this->root(x) == this->root(y);\
    \ }\r\n    bool is_same(int x, int y) { return this->same(x, y); }\r\n\r\n   \
    \ int size(int x) { return -(this->data[this->root(x)]); }\r\n    int get_size(int\
    \ x) { return this->size(x); }\r\n\r\n    bool unite(int x, int y) {\r\n     \
    \   x = this->root(x), y = this->root(y);\r\n        if (x == y) return false;\r\
    \n        if (this->data[x] > this->data[y]) swap(x, y);\r\n        this->data[x]\
    \ += this->data[y];\r\n        this->data[y] = x;\r\n        return true;\r\n\
    \    }\r\n\r\n    template <class F>\r\n    bool unite(int x, int y, F f) {\r\n\
    \        x = this->root(x), y = this->root(y);\r\n        if (x != y) {\r\n  \
    \          if (this->data[x] > this->data[y]) swap(x, y);\r\n            this->data[x]\
    \ += this->data[y];\r\n            this->data[y] = x;\r\n        }\r\n       \
    \ f(x, y);\r\n        return x != y;\r\n    }\r\n\r\n  private:\r\n    std::vector<int>\
    \ data;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/union_find.hpp
  requiredBy:
  - lib/graph/kruskal.hpp
  timestamp: '2022-06-15 02:23:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/kruskal.test.cpp
  - test/aoj/dsl/union_find.test.cpp
  - test/yosupo/data_structure/unionfind.test.cpp
documentation_of: lib/tree/union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/union_find.hpp
- /library/lib/tree/union_find.hpp.html
title: "\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
---
