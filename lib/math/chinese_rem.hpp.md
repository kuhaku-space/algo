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
    document_title: "a * x + b * y = gcd(a, b) \u306E\u7B54\u3048\u3092\u4E00\u3064\
      \u6C42\u3081\u308B"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief a * x + b * y\
    \ = gcd(a, b) \u306E\u7B54\u3048\u3092\u4E00\u3064\u6C42\u3081\u308B\r\n *\r\n\
    \ * @param a\r\n * @param b\r\n * @param x\r\n * @param y\r\n * @return std::int64_t\
    \ gcd(a, b)\r\n */\r\nstd::int64_t extGCD(const std::int64_t a, const std::int64_t\
    \ b, std::int64_t &x, std::int64_t &y) {\r\n    if (b == 0) {\r\n        x = 1,\
    \ y = 0;\r\n        return a;\r\n    }\r\n\r\n    std::int64_t d = extGCD(b, a\
    \ % b, y, x);\r\n    y -= a / b * x;\r\n    return d;\r\n}\r\n\r\n/**\r\n * @brief\
    \ \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\r\n * @details \u4EFB\u610F\u306E i \u306B\
    \u304A\u3044\u3066\u3001$x % m_i = b_i$ \u3068\u306A\u308B x \u3092\u6C42\u3081\
    \u308B\r\n *\r\n * @tparam T \u914D\u5217b\u306E\u578B\r\n * @tparam U \u914D\u5217\
    m\u306E\u578B\r\n * @param b \u4F59\u308A\u306E\u914D\u5217\r\n * @param m mod\u306E\
    \u914D\u5217\r\n * @return std::pair<std::int64_t, std::int64_t> (r, M) ($x =\
    \ r + M * k$ (k\u306F\u6574\u6570))\r\n */\r\ntemplate <class T, class U>\r\n\
    std::pair<std::int64_t, std::int64_t> chinese_rem(const std::vector<T> &b,\r\n\
    \                                                  const std::vector<U> &m) {\r\
    \n    std::int64_t r = 0, M = 1;\r\n    int n = b.size();\r\n    for (int i =\
    \ 0; i < n; ++i) {\r\n        std::int64_t p, q;\r\n        std::int64_t d = extGCD(M,\
    \ m[i], p, q);\r\n        if ((b[i] - r) % d != 0) return {0, -1};\r\n       \
    \ std::int64_t tmp = (b[i] - r) / d * p % (m[i] / d);\r\n        r += M * tmp;\r\
    \n        M *= m[i] / d;\r\n    }\r\n    return {r >= 0 ? r % M : M - 1 - (-r\
    \ - 1) % M, M};\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/chinese_rem.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/chinese_rem.hpp
layout: document
redirect_from:
- /library/lib/math/chinese_rem.hpp
- /library/lib/math/chinese_rem.hpp.html
title: "a * x + b * y = gcd(a, b) \u306E\u7B54\u3048\u3092\u4E00\u3064\u6C42\u3081\
  \u308B"
---
