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
  code: "#include \"template/template.hpp\"\r\n\r\n/*\r\n * a * x + b * y = gcd(a,\
    \ b) \u306E\u7B54\u3048\u3092\u4E00\u3064\u6C42\u3081\u308B\r\n * \u623B\u308A\
    \u5024\u306F gcd(a, b)\r\n */\r\nint64_t extGCD(const int64_t a, const int64_t\
    \ b, int64_t &x, int64_t &y) {\r\n    if (b == 0) {\r\n        x = 1, y = 0;\r\
    \n        return a;\r\n    }\r\n\r\n    int64_t d = extGCD(b, a % b, y, x);\r\n\
    \    y -= a / b * x;\r\n    return d;\r\n}\r\n\r\n/*\r\n * \u4EFB\u610F\u306E\
    \ i \u306B\u304A\u3044\u3066\u3001x % b_i = m_i \u3068\u306A\u308B x \u3092\u6C42\
    \u3081\u308B\r\n * x = r + M * k (k in N) \u3068\u8868\u3059\u3053\u3068\u304C\
    \u3067\u304D\u308B\r\n */\r\ntemplate <class T, class U>\r\npair<int64_t, int64_t>\
    \ chinese_rem(const vector<T> &b, const vector<U> &m) {\r\n    int64_t r = 0,\
    \ M = 1;\r\n    int64_t n = b.size();\r\n    for (int64_t i = 0; i < n; ++i) {\r\
    \n        int64_t p, q;\r\n        int64_t d = extGCD(M, m[i], p, q);\r\n    \
    \    if ((b[i] - r) % d != 0) return {0, -1};\r\n        int64_t tmp = (b[i] -\
    \ r) / d * p % (m[i] / d);\r\n        r += M * tmp;\r\n        M *= m[i] / d;\r\
    \n    }\r\n    return {r >= 0 ? r % M : M - 1 - (-r - 1) % M, M};\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/chinese_rem.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/chinese_rem.hpp
layout: document
redirect_from:
- /library/lib/math/chinese_rem.hpp
- /library/lib/math/chinese_rem.hpp.html
title: lib/math/chinese_rem.hpp
---
