---
data:
  _extendedDependsOn:
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/*\r\n * \u53CC\u5BFE\u30BB\u30B0\
    \u30E1\u30F3\u30C8\u6728\r\n * Usage:\r\n * dual_segment_tree RAQ(n, INF, [](ll\
    \ a, ll x){ return a + x; }; );\r\n * dual_segment_tree RUQ(n, 0, [](ll a, ll\
    \ x){ return x; }; );\r\n */\r\ntemplate <class T, class F>\r\nstruct dual_segment_tree\
    \ {\r\n    int N;\r\n    T e;\r\n    F op;\r\n    vector<T> data;\r\n\r\n    dual_segment_tree(int\
    \ _n, T _e, F _op) : e(_e), op(_op) { init(_n); }\r\n\r\n    void init(int n)\
    \ {\r\n        for (N = 1; N < n; N <<= 1)\r\n            ;\r\n        data.assign(N\
    \ << 1, e);\r\n    }\r\n\r\n    template <class U>\r\n    void build(const vector<U>\
    \ &v) {\r\n        for (int i = 0; i < v.size(); ++i) data[N + i] = v[i];\r\n\
    \        for (int i = N - 1; i >= 1; --i)\r\n            data[i] = op(data[i *\
    \ 2], data[i * 2 + 1]);\r\n    }\r\n\r\n    void update(int a, T x) {\r\n    \
    \    int k = 0;\r\n        while (a >> k > 1) ++k;\r\n        for (; k > 0; --k)\
    \ {\r\n            int t = a >> k;\r\n            if (data[t] == e) continue;\r\
    \n            data[t * 2] = op(data[t * 2], data[t]);\r\n            data[t *\
    \ 2 + 1] = op(data[t * 2 + 1], data[t]);\r\n            data[t] = e;\r\n     \
    \   }\r\n        data[a] = op(data[a], x);\r\n    }\r\n\r\n    void query(int\
    \ a, T x) { query(a, a + 1, 1, 0, N, x); }\r\n    void query(int a, int b, T x)\
    \ {\r\n        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {\r\n           \
    \ if (a & 1) update(a++, x);\r\n            if (b & 1) update(--b, x);\r\n   \
    \     }\r\n    }\r\n\r\n    const T at(int k) const {\r\n        T res = e;\r\n\
    \        for (k += N; k >= 1; k >>= 1) {\r\n            if (data[k] != e) res\
    \ = op(res, data[k]);\r\n        }\r\n        return res;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/binary_tree/dual_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/dual_segment_tree.hpp
- /library/lib/binary_tree/dual_segment_tree.hpp.html
title: lib/binary_tree/dual_segment_tree.hpp
---
