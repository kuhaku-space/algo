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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T, class U, class\
    \ F, class G, class H>\r\nstruct lazy_segment_tree {\r\n    int N, logN;\r\n \
    \   const T e;\r\n    const U id;\r\n    const F op;    // (T, T) -> T\r\n   \
    \ const G mapp;  // (U, T) -> T\r\n    const H comp;  // (U, U) -> U\r\n    vector<T>\
    \ data;\r\n    vector<U> lazy;\r\n\r\n    lazy_segment_tree(int _n, T _e, U _id,\
    \ F &&_op, G &&_mapp, H &&_comp)\r\n        : e(_e), id(_id), op(_op), mapp(_mapp),\
    \ comp(_comp) {\r\n        init(_n);\r\n    }\r\n    lazy_segment_tree(int _n,\
    \ T _e, U _id, const F &_op, const G &_mapp, const H &_comp)\r\n        : e(_e),\
    \ id(_id), op(_op), mapp(_mapp), comp(_comp) {\r\n        init(_n);\r\n    }\r\
    \n\r\n    void init(int n) {\r\n        for (N = 1, logN = 0; N < n; N <<= 1,\
    \ ++logN) {}\r\n        data.assign(N << 1, e);\r\n        lazy.assign(N << 1,\
    \ id);\r\n    }\r\n\r\n    template <class V>\r\n    void build(const vector<V>\
    \ &v) {\r\n        for (int i = 0; i < v.size(); ++i) data[N + i] = v[i];\r\n\
    \        for (int i = N - 1; i >= 1; --i) data[i] = op(data[i * 2], data[i * 2\
    \ + 1]);\r\n    }\r\n\r\n    void apply(int k, const U &x) {\r\n        assert(0\
    \ < k && k < N << 1);\r\n        lazy[k] = comp(x, lazy[k]);\r\n\r\n        if\
    \ ((k >>= 1) >= 1) {\r\n            data[k] = op(mapp(lazy[k * 2], data[k * 2]),\
    \ mapp(lazy[k * 2 + 1], data[k * 2 + 1]));\r\n        }\r\n    }\r\n\r\n    T\
    \ eval(int k) {\r\n        assert(0 < k && k < N << 1);\r\n        if (lazy[k]\
    \ == id) return data[k];\r\n        if (k < N) {\r\n            lazy[k * 2] =\
    \ comp(lazy[k], lazy[k * 2]);\r\n            lazy[k * 2 + 1] = comp(lazy[k], lazy[k\
    \ * 2 + 1]);\r\n        }\r\n        data[k] = mapp(lazy[k], data[k]);\r\n   \
    \     lazy[k] = id;\r\n        return data[k];\r\n    }\r\n\r\n    void update(int\
    \ a, const U &x) { return add(a, a + 1, x); }\r\n    void update(int a, int b,\
    \ const U &x) {\r\n        assert(0 <= a && a <= N);\r\n        assert(0 <= b\
    \ && b <= N);\r\n        int l = a + N, r = b + N - 1;\r\n        for (int i =\
    \ logN; i >= 0; --i) eval(l >> i), eval(r >> i);\r\n        for (a += N, b +=\
    \ N; a < b; a >>= 1, b >>= 1) {\r\n            if (a & 1) eval(a), apply(a++,\
    \ x);\r\n            if (b & 1) eval(--b), apply(b, x);\r\n        }\r\n     \
    \   for (int i = 0; i <= logN; ++i) apply(l >> i, id), apply(r >> i, id);\r\n\
    \    }\r\n\r\n    T query(int a, int b) {\r\n        assert(0 <= a && a <= N);\r\
    \n        assert(0 <= b && b <= N);\r\n        a += N, b += N;\r\n        for\
    \ (int i = logN; i >= 0; --i) eval(a >> i), eval((b - 1) >> i);\r\n        T l\
    \ = e, r = e;\r\n        for (; a < b; a >>= 1, b >>= 1) {\r\n            if (a\
    \ & 1) l = op(l, eval(a++));\r\n            if (b & 1) r = op(eval(--b), r);\r\
    \n        }\r\n        return op(l, r);\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2021-12-20 06:14:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/segment_tree/lazy_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/lazy_segment_tree.hpp
- /library/lib/segment_tree/lazy_segment_tree.hpp.html
title: lib/segment_tree/lazy_segment_tree.hpp
---
