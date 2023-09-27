---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_math.hpp
    title: lib/internal/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: floor sum
    links:
    - https://atcoder.github.io/ac-library/production/document_ja/math.html
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: internal/internal_math.hpp:\
    \ line -1: no such header\n"
  code: "#include \"internal/internal_math.hpp\"\n#include \"template/template.hpp\"\
    \n\n/**\n * @brief floor sum\n *\n * @param n\n * @param m\n * @param a\n * @param\
    \ b\n * @retval std::int64_t sum[0 <= i < n]floor((a * i + b) / m)\n *\n * @see\
    \ https://atcoder.github.io/ac-library/production/document_ja/math.html\n */\n\
    std::int64_t floor_sum(std::int64_t n, std::int64_t m, std::int64_t a, std::int64_t\
    \ b) {\n    assert(0 <= n && n < (1LL << 32));\n    assert(1 <= m && m < (1LL\
    \ << 32));\n    std::uint64_t ans = 0;\n    if (a < 0) {\n        std::uint64_t\
    \ a2 = internal::safe_mod(a, m);\n        ans -= 1ULL * n * (n - 1) / 2 * ((a2\
    \ - a) / m);\n        a = a2;\n    }\n    if (b < 0) {\n        std::uint64_t\
    \ b2 = internal::safe_mod(b, m);\n        ans -= 1ULL * n * ((b2 - b) / m);\n\
    \        b = b2;\n    }\n    return ans + internal::floor_sum_unsigned(n, m, a,\
    \ b);\n}\n"
  dependsOn:
  - lib/internal/internal_math.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/floor_sum.hpp
  requiredBy: []
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/floor_sum.hpp
layout: document
redirect_from:
- /library/lib/math/floor_sum.hpp
- /library/lib/math/floor_sum.hpp.html
title: floor sum
---
