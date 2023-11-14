---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/min_linear.test.cpp
    title: test/yosupo/math/min_linear.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/math/min_linear.hpp\"\n#include <cstdint>\n\nnamespace\
    \ internal {\n\nnamespace min_linear {\n\nstd::int64_t min_linear(std::int64_t\
    \ n, std::int64_t m, std::int64_t a, std::int64_t b, bool is_min,\n          \
    \              std::int64_t p, std::int64_t q) {\n    if (a == 0) return b;\n\
    \    if (is_min) {\n        if (b >= a) {\n            std::int64_t t = (m - b\
    \ + a - 1) / a;\n            std::int64_t c = (t - 1) * p + q;\n            if\
    \ (n <= c) return b;\n            n -= c;\n            b += a * t - m;\n     \
    \   }\n        b = a - 1 - b;\n    } else {\n        if (b < m - a) {\n      \
    \      std::int64_t t = (m - b - 1) / a;\n            std::int64_t c = t * p;\n\
    \            if (n <= c) return a * ((n - 1) / p) + b;\n            n -= c;\n\
    \            b += a * t;\n        }\n        b = m - 1 - b;\n    }\n    std::int64_t\
    \ d = m / a;\n    std::int64_t c = min_linear(n, a, m % a, b, !is_min, (d - 1)\
    \ * p + q, d * p + q);\n    return is_min ? a - 1 - c : m - 1 - c;\n}\n\n}  //\
    \ namespace min_linear\n\n}  // namespace internal\n\nstd::int64_t min_linear(std::int64_t\
    \ n, std::int64_t m, std::int64_t a, std::int64_t b) {\n    return internal::min_linear::min_linear(n,\
    \ m, a, b, true, 1, 1);\n}\n"
  code: "#include <cstdint>\n\nnamespace internal {\n\nnamespace min_linear {\n\n\
    std::int64_t min_linear(std::int64_t n, std::int64_t m, std::int64_t a, std::int64_t\
    \ b, bool is_min,\n                        std::int64_t p, std::int64_t q) {\n\
    \    if (a == 0) return b;\n    if (is_min) {\n        if (b >= a) {\n       \
    \     std::int64_t t = (m - b + a - 1) / a;\n            std::int64_t c = (t -\
    \ 1) * p + q;\n            if (n <= c) return b;\n            n -= c;\n      \
    \      b += a * t - m;\n        }\n        b = a - 1 - b;\n    } else {\n    \
    \    if (b < m - a) {\n            std::int64_t t = (m - b - 1) / a;\n       \
    \     std::int64_t c = t * p;\n            if (n <= c) return a * ((n - 1) / p)\
    \ + b;\n            n -= c;\n            b += a * t;\n        }\n        b = m\
    \ - 1 - b;\n    }\n    std::int64_t d = m / a;\n    std::int64_t c = min_linear(n,\
    \ a, m % a, b, !is_min, (d - 1) * p + q, d * p + q);\n    return is_min ? a -\
    \ 1 - c : m - 1 - c;\n}\n\n}  // namespace min_linear\n\n}  // namespace internal\n\
    \nstd::int64_t min_linear(std::int64_t n, std::int64_t m, std::int64_t a, std::int64_t\
    \ b) {\n    return internal::min_linear::min_linear(n, m, a, b, true, 1, 1);\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/math/min_linear.hpp
  requiredBy: []
  timestamp: '2023-10-12 07:01:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/math/min_linear.test.cpp
documentation_of: lib/math/min_linear.hpp
layout: document
redirect_from:
- /library/lib/math/min_linear.hpp
- /library/lib/math/min_linear.hpp.html
title: lib/math/min_linear.hpp
---
