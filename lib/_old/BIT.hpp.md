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
  code: "#include \"template/template.hpp\"\r\n\r\n// \u4E00\u70B9\u52A0\u7B97\u3001\
    \u533A\u9593\u7DCF\u548C\r\ntemplate <class T>\r\nstruct BIT {\r\n    int N;\r\
    \n    vector<T> data;\r\n\r\n    BIT() {}\r\n    BIT(int n) { init(n); }\r\n \
    \   BIT(const vector<T> &v) { build(v); }\r\n\r\n    const T &operator[](int i)\
    \ const { return at(i); }\r\n\r\n    const T at(int k) const { return sum(k +\
    \ 1) - sum(k); }\r\n\r\n    void init() { data = vector<T>(N + 1); }\r\n\r\n \
    \   void init(int n) {\r\n        for (N = 1; N < n; N <<= 1)\r\n            ;\r\
    \n        data = vector<T>(N + 1);\r\n    }\r\n\r\n    template <class U>\r\n\
    \    void build(const vector<U> &v) {\r\n        int n = v.size();\r\n       \
    \ init(n);\r\n        for (int i = 0; i < n; ++i) add(i, v[i]);\r\n    }\r\n\r\
    \n    // v[k] += w\r\n    void add(int k, T w) {\r\n        for (++k; k <= N;\
    \ k += k & -k) data[k] += w;\r\n    }\r\n\r\n    // v[k] = x\r\n    void update(int\
    \ k, T x) { add(k, x - at(k)); }\r\n\r\n    // v[0] + ... + v[k - 1]\r\n    T\
    \ sum(int k) const {\r\n        T res = 0;\r\n        for (; k > 0; k -= k & -k)\
    \ res += data[k];\r\n        return res;\r\n    }\r\n\r\n    // v[a] + ... + v[b\
    \ - 1]\r\n    T sum(int a, int b) const { return sum(b) - sum(a); }\r\n\r\n  \
    \  int lower_bound(T x) const {\r\n        if (x <= 0) return 0;\r\n        int\
    \ res = 0;\r\n        for (int k = N; k > 0; k >>= 1) {\r\n            if (res\
    \ + k <= N && data[res + k] < x) x -= data[res += k];\r\n        }\r\n       \
    \ return res;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_old/BIT.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_old/BIT.hpp
layout: document
redirect_from:
- /library/lib/_old/BIT.hpp
- /library/lib/_old/BIT.hpp.html
title: lib/_old/BIT.hpp
---
