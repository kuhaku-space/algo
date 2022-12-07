---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/pow.hpp
    title: lib/math/pow.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/raq_rmq.test.cpp
    title: test/aoj/dsl/raq_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/segment_tree.hpp:\
    \ line -1: no such header\n"
  code: "#include \"segment_tree/segment_tree.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\ntemplate <class T>\r\nstruct segment_tree_range_add_range_max {\r\n  private:\r\
    \n    struct Monoid {\r\n        using value_type = std::pair<T, T>;\r\n     \
    \   static constexpr std::pair<T, T> id =\r\n            std::make_pair(std::numeric_limits<T>::lowest()\
    \ / 2, T(0));\r\n        static constexpr std::pair<T, T> op(const std::pair<T,\
    \ T> &lhs,\r\n                                            const std::pair<T, T>\
    \ &rhs) {\r\n            return std::make_pair(std::max(lhs.first, lhs.second\
    \ + rhs.first),\r\n                                  lhs.second + rhs.second);\r\
    \n        }\r\n    };\r\n\r\n  public:\r\n    segment_tree_range_add_range_max(int\
    \ _n, T _e) : st(_n + 1, std::make_pair(_e, T(0))) {}\r\n\r\n    void apply(int\
    \ k, T val) { this->apply(k, k + 1, val); }\r\n    void apply(int a, int b, T\
    \ val) {\r\n        auto x = this->st.get(a);\r\n        this->st.set(a, std::make_pair(x.second\
    \ + val, x.second + val));\r\n        auto y = this->st.get(b);\r\n        this->st.set(b,\
    \ std::make_pair(y.second - val, y.second - val));\r\n    }\r\n    void add(int\
    \ k, T val) { this->apply(k, k + 1, val); }\r\n    void add(int a, int b, T val)\
    \ { this->apply(a, b, val); }\r\n\r\n    T prod(int a, int b) { return this->st.prod(0,\
    \ a).second + this->st.prod(a, b).first; }\r\n\r\n    T at(int k) { return this->st.prod(0,\
    \ k).second; }\r\n    T get(int k) { return this->at(k); }\r\n\r\n  private:\r\
    \n    segment_tree<Monoid> st;\r\n};\r\n\r\ntemplate <class T>\r\nstruct segment_tree_range_add_range_min\
    \ {\r\n  private:\r\n    struct Monoid {\r\n        using value_type = std::pair<T,\
    \ T>;\r\n        static constexpr std::pair<T, T> id =\r\n            std::make_pair(std::numeric_limits<T>::max()\
    \ / 2, T(0));\r\n        static constexpr std::pair<T, T> op(const std::pair<T,\
    \ T> &lhs,\r\n                                            const std::pair<T, T>\
    \ &rhs) {\r\n            return std::make_pair(std::min(lhs.first, lhs.second\
    \ + rhs.first),\r\n                                  lhs.second + rhs.second);\r\
    \n        }\r\n    };\r\n\r\n  public:\r\n    segment_tree_range_add_range_min(int\
    \ _n, T _e) : st(_n + 1, std::make_pair(_e, T(0))) {}\r\n\r\n    void apply(int\
    \ k, T val) { this->apply(k, k + 1, val); }\r\n    void apply(int a, int b, T\
    \ val) {\r\n        auto x = this->st.get(a);\r\n        this->st.set(a, std::make_pair(x.second\
    \ + val, x.second + val));\r\n        auto y = this->st.get(b);\r\n        this->st.set(b,\
    \ std::make_pair(y.second - val, y.second - val));\r\n    }\r\n    void add(int\
    \ k, T val) { this->apply(k, k + 1, val); }\r\n    void add(int a, int b, T val)\
    \ { this->apply(a, b, val); }\r\n\r\n    T prod(int a, int b) { return this->st.prod(0,\
    \ a).second + this->st.prod(a, b).first; }\r\n\r\n    T at(int k) { return this->st.prod(0,\
    \ k).second; }\r\n    T get(int k) { return this->at(k); }\r\n\r\n  private:\r\
    \n    segment_tree<Monoid> st;\r\n};\r\n"
  dependsOn:
  - lib/segment_tree/segment_tree.hpp
  - lib/math/pow.hpp
  - lib/template/template.hpp
  - lib/segment_tree/monoid.hpp
  isVerificationFile: false
  path: lib/segment_tree/segment_tree_raq.hpp
  requiredBy: []
  timestamp: '2022-07-31 15:35:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dsl/raq_rmq.test.cpp
documentation_of: lib/segment_tree/segment_tree_raq.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/segment_tree_raq.hpp
- /library/lib/segment_tree/segment_tree_raq.hpp.html
title: lib/segment_tree/segment_tree_raq.hpp
---
