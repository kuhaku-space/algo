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
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n// verify : https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H\r\
    \n\r\n/*\r\n * \u975E\u518D\u5E30\u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\
    \r\n * Usage :\r\n * lazy_segment_tree RAQ_RmQ(n, INF, [](ll a, ll b){ return\
    \ min(a, b); });\r\n * lazy_segment_tree RAQ_RMQ(n, 0, [](ll a, ll b){ return\
    \ max(a, b); });\r\n */\r\ntemplate <class T, class F>\r\nstruct lazy_segment_tree\
    \ {\r\n    int N, logN;\r\n    T e;\r\n    F f;\r\n    vector<T> data;\r\n   \
    \ vector<T> lazy;\r\n\r\n    lazy_segment_tree(int _n, T _e, F _f) : f(_f), e(_e)\
    \ { init(_n); }\r\n\r\n    void init(int n) {\r\n        for (N = 1, logN = 0;\
    \ N < n; N <<= 1, ++logN)\r\n            ;\r\n        data.assign(N << 1, e);\r\
    \n        lazy.assign(N << 1, 0);\r\n    }\r\n\r\n    template <class U>\r\n \
    \   void build(const vector<U> &v) {\r\n        for (int i = 0; i < v.size();\
    \ ++i) data[N + i] = v[i];\r\n        for (int i = N - 1; i >= 1; --i)\r\n   \
    \         data[i] = f(data[i * 2], data[i * 2 + 1]);\r\n    }\r\n\r\n    void\
    \ update(int k, T x = T()) {\r\n        assert(k > 0 && k < N << 1);\r\n     \
    \   lazy[k] += x;\r\n\r\n        if ((k >>= 1) >= 1) {\r\n            data[k]\
    \ =\r\n                f(data[k * 2] + lazy[k * 2], data[k * 2 + 1] + lazy[k *\
    \ 2 + 1]);\r\n        }\r\n    }\r\n\r\n    T eval(int k) {\r\n        assert(k\
    \ > 0 && k < N << 1);\r\n        if (lazy[k] == 0) return data[k];\r\n       \
    \ if (k < N) {\r\n            lazy[k * 2] += lazy[k];\r\n            lazy[k *\
    \ 2 + 1] += lazy[k];\r\n        }\r\n        data[k] += lazy[k];\r\n        lazy[k]\
    \ = 0;\r\n        return data[k];\r\n    }\r\n\r\n    void add(int a, T x) { return\
    \ add(a, a + 1, x); }\r\n    void add(int a, int b, T x) {\r\n        assert(a\
    \ >= 0 && a <= N);\r\n        assert(b >= 0 && b <= N);\r\n        int l = a +\
    \ N, r = b + N - 1;\r\n        for (int i = logN; i >= 0; --i) eval(l >> i), eval(r\
    \ >> i);\r\n        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {\r\n      \
    \      if (a & 1) eval(a), update(a++, x);\r\n            if (b & 1) eval(--b),\
    \ update(b, x);\r\n        }\r\n        for (int i = 0; i <= logN; ++i) update(l\
    \ >> i), update(r >> i);\r\n    }\r\n\r\n    T query(int a, int b) {\r\n     \
    \   assert(a >= 0 && a <= N);\r\n        assert(b >= 0 && b <= N);\r\n       \
    \ a += N, b += N;\r\n        for (int i = logN; i >= 0; --i) eval(a >> i), eval((b\
    \ - 1) >> i);\r\n        T res = e;\r\n        for (; a < b; a >>= 1, b >>= 1)\
    \ {\r\n            if (a & 1) res = f(eval(a++), res);\r\n            if (b &\
    \ 1) res = f(res, eval(--b));\r\n        }\r\n        return res;\r\n    }\r\n\
    };\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_old/lazy_segment_tree_beta.hpp
  requiredBy: []
  timestamp: '2021-09-20 05:12:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_old/lazy_segment_tree_beta.hpp
layout: document
redirect_from:
- /library/lib/_old/lazy_segment_tree_beta.hpp
- /library/lib/_old/lazy_segment_tree_beta.hpp.html
title: lib/_old/lazy_segment_tree_beta.hpp
---
