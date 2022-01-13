---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/segment_tree/segment_tree_virtual.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/segment_tree_virtual.hpp:\
    \ line -1: no such header\n"
  code: "#include \"segment_tree/segment_tree_virtual.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\ntemplate <class T>\r\nstruct RAMQ {\r\n    struct segment_tree_max : segment_tree<pair<T,\
    \ T>> {\r\n        segment_tree_max(int _n, pair<T, T> _e) : segment_tree<pair<T,\
    \ T>>(_n, _e) {}\r\n        pair<T, T> op(pair<T, T> a, pair<T, T> b) const {\r\
    \n            return make_pair(max(a.first, a.second + b.first), a.second + b.second);\r\
    \n        }\r\n        pair<T, T> f(pair<T, T> val, pair<T, T> x) {\r\n      \
    \      T y = val.second + x.second;\r\n            return make_pair(y, y);\r\n\
    \        }\r\n    };\r\n\r\n    segment_tree_max st;\r\n\r\n    RAMQ(int _n, T\
    \ _e) : st(_n + 1, make_pair(_e, T(0))) {}\r\n\r\n    void apply(int k, T val)\
    \ { this->apply(k, k + 1, val); }\r\n    void apply(int a, int b, T val) {\r\n\
    \        this->st.add(a, make_pair(val, val));\r\n        this->st.add(b, make_pair(-val,\
    \ -val));\r\n    }\r\n    void add(int k, T val) { this->apply(k, k + 1, val);\
    \ }\r\n    void add(int a, int b, T val) { this->apply(a, b, val); }\r\n\r\n \
    \   T prod(int a, int b) { return this->st.prod(0, a).second + this->st.prod(a,\
    \ b).first; }\r\n\r\n    T at(int k) { return this->st.prod(0, k).second; }\r\n\
    \    T get(int k) { return this->at(k); }\r\n};\r\n\r\ntemplate <class T>\r\n\
    struct RAmQ {\r\n    struct segment_tree_min : segment_tree<pair<T, T>> {\r\n\
    \        segment_tree_min(int _n, pair<T, T> _e) : segment_tree<pair<T, T>>(_n,\
    \ _e) {}\r\n        pair<T, T> op(pair<T, T> a, pair<T, T> b) const {\r\n    \
    \        return make_pair(min(a.first, a.second + b.first), a.second + b.second);\r\
    \n        }\r\n        pair<T, T> f(pair<T, T> val, pair<T, T> x) {\r\n      \
    \      T y = val.second + x.second;\r\n            return make_pair(y, y);\r\n\
    \        }\r\n    };\r\n    segment_tree_min st;\r\n\r\n    RAmQ(int _n, T _e)\
    \ : st(_n + 1, make_pair(_e, T(0))) {\r\n        this->st.init(_n + 1, make_pair(T(0),\
    \ T(0)));\r\n    }\r\n\r\n    void apply(int k, T val) { this->apply(k, k + 1,\
    \ val); }\r\n    void apply(int a, int b, T val) {\r\n        this->st.apply(a,\
    \ make_pair(val, val));\r\n        this->st.apply(b, make_pair(-val, -val));\r\
    \n    }\r\n    void add(int k, T val) { this->apply(k, k + 1, val); }\r\n    void\
    \ add(int a, int b, T val) { this->apply(a, b, val); }\r\n\r\n    T prod(int a,\
    \ int b) { return this->st.prod(0, a).second + this->st.prod(a, b).first; }\r\n\
    \r\n    T at(int k) { return this->st.prod(0, k + 1).second; }\r\n    T get(int\
    \ k) { return this->at(k); }\r\n};\r\n"
  dependsOn:
  - lib/segment_tree/segment_tree_virtual.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/RAQ.hpp
  requiredBy: []
  timestamp: '2021-12-28 06:14:56+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/segment_tree/RAQ.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/RAQ.hpp
- /library/lib/segment_tree/RAQ.hpp.html
title: lib/segment_tree/RAQ.hpp
---
