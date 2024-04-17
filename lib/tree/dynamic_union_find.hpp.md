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
    document_title: "\u52D5\u7684Union-Find"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u52D5\u7684Union-Find\n\
    \ *\n */\nstruct dynamic_union_find {\n    dynamic_union_find() : data() {}\n\n\
    \    int root(int x) {\n        if (!this->data.count(x)) this->data[x] = -1;\n\
    \        return this->data[x] < 0 ? x : this->data[x] = this->root(this->data[x]);\n\
    \    }\n    int get_root(int x) { return this->root(x); }\n\n    bool is_root(int\
    \ x) { return this->data.count(x) && this->data[x] < 0; }\n\n    bool same(int\
    \ x, int y) { return this->root(x) == this->root(y); }\n    bool is_same(int x,\
    \ int y) { return this->same(x, y); }\n\n    int size(int x) { return -(this->data[this->root(x)]);\
    \ }\n    int get_size(int x) { return this->size(x); }\n\n    bool unite(int x,\
    \ int y) {\n        x = this->root(x), y = this->root(y);\n        if (x == y)\
    \ return false;\n        if (this->data[x] > this->data[y]) std::swap(x, y);\n\
    \        this->data[x] += this->data[y];\n        this->data[y] = x;\n       \
    \ return true;\n    }\n\n    template <class F>\n    bool unite(int x, int y,\
    \ F f) {\n        x = this->root(x), y = this->root(y);\n        if (x != y) {\n\
    \            if (this->data[x] > this->data[y]) std::swap(x, y);\n           \
    \ this->data[x] += this->data[y];\n            this->data[y] = x;\n        }\n\
    \        f(x, y);\n        return x != y;\n    }\n\n  private:\n    std::unordered_map<int,\
    \ int> data;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/dynamic_union_find.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/dynamic_union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/dynamic_union_find.hpp
- /library/lib/tree/dynamic_union_find.hpp.html
title: "\u52D5\u7684Union-Find"
---
