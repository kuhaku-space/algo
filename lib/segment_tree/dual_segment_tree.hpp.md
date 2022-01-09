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
    document_title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u53CC\u5BFE\u30BB\
    \u30B0\u30E1\u30F3\u30C8\u6728\r\n *\r\n * @details Usage: @n\r\n * dual_segment_tree\
    \ RAQ(n, Inf, [](auto a, auto x){ return a + x; } ); @n\r\n * dual_segment_tree\
    \ RUQ(n, Inf, [](auto a, auto x){ return a; } );\r\n *\r\n * @tparam T \u8981\u7D20\
    \u306E\u578B\r\n * @tparam F \u95A2\u6570\u306E\u578B\r\n */\r\ntemplate <class\
    \ T, class F>\r\nstruct dual_segment_tree {\r\n    int N;\r\n    T e;\r\n    F\
    \ f;\r\n    vector<T> data;\r\n\r\n    dual_segment_tree(int _n, T _e, const F\
    \ &_f) : e(_e), f(_f) { this->init(_n); }\r\n    dual_segment_tree(int _n, T _e,\
    \ F &&_f) : e(_e), f(_f) { this->init(_n); }\r\n\r\n    void init(int n) {\r\n\
    \        for (this->N = 1; this->N < n; this->N <<= 1) {}\r\n        this->data.assign(this->N\
    \ << 1, e);\r\n    }\r\n\r\n    template <class U>\r\n    void build(const vector<U>\
    \ &v) {\r\n        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->N\
    \ + i] = v[i];\r\n    }\r\n\r\n    void update(int k, T x) {\r\n        int l\
    \ = 0;\r\n        while (k >> l > 1) ++l;\r\n        for (; l > 0; --l) {\r\n\
    \            int t = k >> l;\r\n            if (this->data[t] == e) continue;\r\
    \n            this->data[t * 2] = this->f(this->data[t], this->data[t * 2]);\r\
    \n            this->data[t * 2 + 1] = this->f(this->data[t], this->data[t * 2\
    \ + 1]);\r\n            this->data[t] = e;\r\n        }\r\n        this->data[k]\
    \ = this->f(x, this->data[k]);\r\n    }\r\n    void set(int k, T x) { this->update(k,\
    \ x); }\r\n\r\n    void apply(int k, T x) { this->apply(k, k + 1, x); }\r\n  \
    \  void apply(int a, int b, T x) {\r\n        assert(0 <= a && b <= this->N);\r\
    \n        for (a += this->N, b += this->N; a < b; a >>= 1, b >>= 1) {\r\n    \
    \        if (a & 1) this->update(a++, x);\r\n            if (b & 1) this->update(--b,\
    \ x);\r\n        }\r\n    }\r\n\r\n    T at(int k) const {\r\n        assert(0\
    \ <= k && k < this->N);\r\n        T res = e;\r\n        for (k += this->N; k\
    \ >= 1; k >>= 1) {\r\n            if (this->data[k] != e) res = this->f(this->data[k],\
    \ res);\r\n        }\r\n        return res;\r\n    }\r\n    T get(int k) const\
    \ { return this->at(k); }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2021-12-20 06:14:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/segment_tree/dual_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/dual_segment_tree.hpp
- /library/lib/segment_tree/dual_segment_tree.hpp.html
title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
