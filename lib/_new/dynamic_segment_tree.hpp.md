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
  code: "#include \"template/template.hpp\"\r\n\r\n/*\r\n * \u52D5\u7684\u30BB\u30B0\
    \u30E1\u30F3\u30C8\u6728\r\n * Usage:\r\n * segment_tree st(n, Inf, [](auto a,\
    \ auto b) { return min(a, b); });\r\n * segment_tree st(n, 0, [](auto a, auto\
    \ b) { return max(a, b); });\r\n */\r\ntemplate <class T, class U, class F>\r\n\
    struct dynamic_segment_tree {\r\n    int N;\r\n    const T e;\r\n    const U id;\r\
    \n    const F op;\r\n    map<int64_t, U> data;\r\n\r\n    dynamic_segment_tree(int\
    \ _n, const T &_e, const U &_id const F &_op)\r\n        : e(_e), id(_id), op(_op)\
    \ {\r\n        init(_n);\r\n    }\r\n\r\n    const T &operator[](int i) const\
    \ { return at(i); }\r\n\r\n    T at(int k) const {}\r\n\r\n    void init(int n)\
    \ {\r\n        for (N = 1; N < n; N <<= 1)\r\n            ;\r\n        data.assign(N\
    \ << 1, e);\r\n    }\r\n\r\n    template <class U>\r\n    void build(const vector<U>\
    \ &v) {\r\n        for (int i = 0; i < v.size(); ++i) data[N + i] = T(v[i]);\r\
    \n        for (int i = N - 1; i >= 1; --i)\r\n            data[i] = op(data[i\
    \ * 2], data[i * 2 + 1]);\r\n    }\r\n\r\n    void update(int k, const T &x) {\r\
    \n        assert(k >= 0 && k < N);\r\n        data[k += N] = x;\r\n        while\
    \ ((k >>= 1) >= 1) data[k] = op(data[k * 2], data[k * 2 + 1]);\r\n    }\r\n\r\n\
    \    void add(int k, const T &x) {\r\n        assert(k >= 0 && k < N);\r\n   \
    \     data[k += N] += x;\r\n        while ((k >>= 1) >= 1) data[k] = op(data[k\
    \ * 2], data[k * 2 + 1]);\r\n    }\r\n\r\n    T query(int a, int b) {\r\n    \
    \    assert(a >= 0 && a <= N);\r\n        assert(b >= 0 && b <= N);\r\n      \
    \  T l = e, r = e;\r\n        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {\r\
    \n            if (a & 1) l = op(l, data[a++]);\r\n            if (b & 1) r = op(data[--b],\
    \ r);\r\n        }\r\n        return op(l, r);\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/dynamic_segment_tree.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/dynamic_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/_new/dynamic_segment_tree.hpp
- /library/lib/_new/dynamic_segment_tree.hpp.html
title: lib/_new/dynamic_segment_tree.hpp
---
