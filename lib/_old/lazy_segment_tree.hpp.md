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
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/*\r\n * \u518D\u5E30\u9045\u5EF6\
    \u30BB\u30B0\u30E1\u30F3\u30C8\u6728\r\n * Usage:\r\n * lazy_segment_tree RAQ_RmQ(n,\
    \ INF, [](ll a, ll b){ return min(a, b); });\r\n * lazy_segment_tree RAQ_RMQ(n,\
    \ 0, [](ll a, ll b){ return max(a, b); });\r\n */\r\ntemplate <class T, class\
    \ F>\r\nstruct lazy_segment_tree {\r\n    int N;\r\n    T e;\r\n    F f;\r\n \
    \   vector<T> data;\r\n    vector<T> lazy;\r\n\r\n    lazy_segment_tree(int _n,\
    \ T &&_e, F &&_f) : e(_e), f(_f) { init(_n); }\r\n\r\n    void init(int n) {\r\
    \n        for (N = 1; N < n; N <<= 1)\r\n            ;\r\n        data.assign(N\
    \ << 1, e);\r\n        lazy.assign(N << 1, 0);\r\n    }\r\n\r\n    template <class\
    \ U>\r\n    void build(const vector<U> &v) {\r\n        for (int i = 0; i < v.size();\
    \ ++i) data[N + i] = v[i];\r\n        for (int i = N - 1; i >= 1; --i)\r\n   \
    \         data[i] = f(data[i * 2], data[i * 2 + 1]);\r\n    }\r\n\r\n    void\
    \ eval(int k) {\r\n        if (lazy[k] == 0) return;\r\n        if (k < N) {\r\
    \n            lazy[k * 2] += lazy[k];\r\n            lazy[k * 2 + 1] += lazy[k];\r\
    \n        }\r\n        data[k] += lazy[k];\r\n        lazy[k] = 0;\r\n    }\r\n\
    \r\n    T add(int a, T x) { return add(a, a + 1, x, 1, 0, N); }\r\n    T add(int\
    \ a, int b, T x) { return add(a, b, x, 1, 0, N); }\r\n    T add(int a, int b,\
    \ T x, int k, int l, int r) {\r\n        eval(k);\r\n        if (r <= a || b <=\
    \ l) return data[k];\r\n        if (a <= l && r <= b) {\r\n            lazy[k]\
    \ += x;\r\n            return data[k] + lazy[k];\r\n        }\r\n        int m\
    \ = (l + r) / 2;\r\n        return data[k] =\r\n                   f(add(a, b,\
    \ x, k * 2, l, m), add(a, b, x, k * 2 + 1, m, r));\r\n    }\r\n\r\n    T query(int\
    \ a, int b) { return query(a, b, 1, 0, N); }\r\n    T query(int a, int b, int\
    \ k, int l, int r) {\r\n        eval(k);\r\n        if (r <= a || b <= l) return\
    \ e;\r\n        if (a <= l && r <= b) return data[k];\r\n        int m = (l +\
    \ r) >> 1;\r\n        return f(query(a, b, k * 2, l, m), query(a, b, k * 2 + 1,\
    \ m, r));\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_old/lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_old/lazy_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/_old/lazy_segment_tree.hpp
- /library/lib/_old/lazy_segment_tree.hpp.html
title: lib/_old/lazy_segment_tree.hpp
---
