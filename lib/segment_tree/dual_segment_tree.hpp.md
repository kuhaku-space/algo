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
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/ruq.test.cpp
    title: test/aoj/dsl/ruq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/pow.hpp:\
    \ line -1: no such header\n"
  code: "#include \"math/pow.hpp\"\r\n#include \"segment_tree/monoid.hpp\"\r\n#include\
    \ \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u53CC\u5BFE\u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\r\n *\r\n * @tparam M\r\n */\r\ntemplate <class M>\r\nstruct\
    \ dual_segment_tree {\r\n    using T = typename M::value_type;\r\n\r\n    dual_segment_tree(int\
    \ _n, T _e = M::id) { this->init(_n, _e); }\r\n\r\n    void init(int n, T e) {\r\
    \n        this->_log = ceil_pow2(n);\r\n        this->_size = 1 << this->_log;\r\
    \n        this->data.assign(this->_size << 1, e);\r\n    }\r\n\r\n    T at(int\
    \ k) { return this->get(k); }\r\n    T get(int k) {\r\n        assert(0 <= k &&\
    \ k < this->_size);\r\n        k += this->_size;\r\n        for (int i = this->_log;\
    \ i >= 1; --i) this->push(k >> i);\r\n        return this->data[k];\r\n    }\r\
    \n\r\n    void apply(int a, T val) { this->apply(a, a + 1, val); }\r\n    void\
    \ apply(int a, int b, T val) {\r\n        assert(0 <= a && a <= this->_size);\r\
    \n        assert(0 <= b && b <= this->_size);\r\n        a += this->_size, b +=\
    \ this->_size;\r\n        for (int i = _log; i >= 1; --i) {\r\n            if\
    \ (((a >> i) << i) != a) this->push(a >> i);\r\n            if (((b >> i) << i)\
    \ != b) this->push((b - 1) >> i);\r\n        }\r\n\r\n        for (; a < b; a\
    \ >>= 1, b >>= 1) {\r\n            if (a & 1) this->all_apply(a++, val);\r\n \
    \           if (b & 1) this->all_apply(--b, val);\r\n        }\r\n    }\r\n\r\n\
    \  private:\r\n    int _size, _log;\r\n    vector<T> data;\r\n\r\n    void all_apply(int\
    \ k, T val) { this->data[k] = M::op(val, this->data[k]); }\r\n    void push(int\
    \ k) {\r\n        this->all_apply(2 * k, this->data[k]);\r\n        this->all_apply(2\
    \ * k + 1, this->data[k]);\r\n        this->data[k] = M::id;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/math/pow.hpp
  - lib/template/template.hpp
  - lib/segment_tree/monoid.hpp
  isVerificationFile: false
  path: lib/segment_tree/dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dsl/ruq.test.cpp
documentation_of: lib/segment_tree/dual_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/dual_segment_tree.hpp
- /library/lib/segment_tree/dual_segment_tree.hpp.html
title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
