---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/binary_tree/BIT.hpp
    title: lib/binary_tree/BIT.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"binary_tree/BIT.hpp\"\r\n\
    \r\ntemplate <class T>\r\nstruct BIT_RSQ {\r\n    BIT<T> p, q;\r\n\r\n    BIT_RSQ(int\
    \ n) : p(n), q(n) {}\r\n\r\n    void init(int n) {\r\n        p = BIT<T>(n);\r\
    \n        q = BIT<T>(n);\r\n    }\r\n\r\n    auto operator[](int i) const { return\
    \ this->at(i); }\r\n\r\n    // v[k]\r\n    auto at(int k) const { return this->sum(k\
    \ + 1) - this->sum(k); }\r\n\r\n    template <class U>\r\n    void build(const\
    \ vector<U> &v) {\r\n        int n = v.size();\r\n        for (int i = 0; i <\
    \ n; ++i) {\r\n            p.add(i, v[i]);\r\n            p.add(i + 1, -v[i]);\r\
    \n        }\r\n    }\r\n\r\n    void update(int k, T x) { this->add(k, k + 1,\
    \ x - this->at(k)); }\r\n\r\n    // v[k] += w\r\n    void add(int k, T w) { this->add(k,\
    \ k + 1, w); }\r\n    // v[a ... b - 1] += w\r\n    void add(int a, int b, T w)\
    \ {\r\n        p.add(a, -w * a);\r\n        p.add(b, w * b);\r\n        q.add(a,\
    \ w);\r\n        q.add(b, -w);\r\n    }\r\n\r\n    // v[0] + ... + v[k - 1]\r\n\
    \    auto sum(int k) const { return p.sum(k) + q.sum(k) * k; }\r\n\r\n    // v[a]\
    \ + ... + v[b - 1]\r\n    auto sum(int a, int b) const { return this->sum(b) -\
    \ this->sum(a); }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/binary_tree/BIT.hpp
  isVerificationFile: false
  path: lib/binary_tree/BIT_RSQ.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/binary_tree/BIT_RSQ.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/BIT_RSQ.hpp
- /library/lib/binary_tree/BIT_RSQ.hpp.html
title: lib/binary_tree/BIT_RSQ.hpp
---
