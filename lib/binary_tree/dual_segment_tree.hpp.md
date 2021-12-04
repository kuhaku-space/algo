---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u53CC\u5BFE\u30BB\
    \u30B0\u30E1\u30F3\u30C8\u6728\r\n *\r\n * @details Usage: @n\r\n * dual_segment_tree\
    \ RAQ(n, INF, [](ll a, ll x){ return a + x; } ); @n\r\n * dual_segment_tree RUQ(n,\
    \ 0, [](ll a, ll x){ return x; } );\r\n *\r\n * @tparam T \u8981\u7D20\u306E\u578B\
    \r\n * @tparam F \u95A2\u6570\u306E\u578B\r\n */\r\ntemplate <class T, class F>\r\
    \nstruct dual_segment_tree {\r\n    int N;\r\n    T e;\r\n    F op;\r\n    vector<T>\
    \ data;\r\n\r\n    dual_segment_tree(int _n, T _e, const F &_op) : e(_e), op(_op)\
    \ { this->init(_n); }\r\n    dual_segment_tree(int _n, T _e, F &&_op) : e(_e),\
    \ op(_op) { this->init(_n); }\r\n\r\n    void init(int n) {\r\n        for (this->N\
    \ = 1; this->N < n; this->N <<= 1) {}\r\n        this->data.assign(this->N <<\
    \ 1, e);\r\n    }\r\n\r\n    template <class U>\r\n    void build(const vector<U>\
    \ &v) {\r\n        for (int i = 0; i < v.size(); ++i) this->data[this->N + i]\
    \ = v[i];\r\n        for (int i = N - 1; i >= 1; --i)\r\n            this->data[i]\
    \ = this->op(this->data[i * 2], this->data[i * 2 + 1]);\r\n    }\r\n\r\n    void\
    \ update(int a, T x) {\r\n        int k = 0;\r\n        while (a >> k > 1) ++k;\r\
    \n        for (; k > 0; --k) {\r\n            int t = a >> k;\r\n            if\
    \ (this->data[t] == e) continue;\r\n            this->data[t * 2] = this->op(this->data[t\
    \ * 2], this->data[t]);\r\n            this->data[t * 2 + 1] = this->op(this->data[t\
    \ * 2 + 1], this->data[t]);\r\n            this->data[t] = e;\r\n        }\r\n\
    \        this->data[a] = this->op(this->data[a], x);\r\n    }\r\n\r\n    void\
    \ query(int a, T x) { query(a, a + 1, x); }\r\n    void query(int a, int b, T\
    \ x) {\r\n        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {\r\n        \
    \    if (a & 1) update(a++, x);\r\n            if (b & 1) update(--b, x);\r\n\
    \        }\r\n    }\r\n\r\n    T at(int k) const {\r\n        T res = e;\r\n \
    \       for (k += N; k >= 1; k >>= 1) {\r\n            if (this->data[k] != e)\
    \ res = this->op(res, this->data[k]);\r\n        }\r\n        return res;\r\n\
    \    }\r\n    T get(int k) const { return this->at(k); }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2021-11-25 18:20:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/binary_tree/dual_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/dual_segment_tree.hpp
- /library/lib/binary_tree/dual_segment_tree.hpp.html
title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
