---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/atcoder/convolution.hpp
    title: lib/atcoder/convolution.hpp
  - icon: ':warning:'
    path: lib/atcoder/lazysegtree.hpp
    title: lib/atcoder/lazysegtree.hpp
  - icon: ':warning:'
    path: lib/atcoder/segtree.hpp
    title: lib/atcoder/segtree.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/internal_bit.hpp\"\n\n\n\r\n#ifdef _MSC_VER\r\
    \n#include <intrin.h>\r\n#endif\r\n\r\nnamespace atcoder {\r\n\r\nnamespace internal\
    \ {\r\n\r\n// @param n `0 <= n`\r\n// @return minimum non-negative `x` s.t. `n\
    \ <= 2**x`\r\nint ceil_pow2(int n) {\r\n    int x = 0;\r\n    while ((1U << x)\
    \ < (unsigned int)(n)) x++;\r\n    return x;\r\n}\r\n\r\n// @param n `1 <= n`\r\
    \n// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`\r\nint bsf(unsigned\
    \ int n) {\r\n#ifdef _MSC_VER\r\n    unsigned long index;\r\n    _BitScanForward(&index,\
    \ n);\r\n    return index;\r\n#else\r\n    return __builtin_ctz(n);\r\n#endif\r\
    \n}\r\n\r\n}  // namespace internal\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_INTERNAL_BITOP_HPP\r\n#define ATCODER_INTERNAL_BITOP_HPP\
    \ 1\r\n\r\n#ifdef _MSC_VER\r\n#include <intrin.h>\r\n#endif\r\n\r\nnamespace atcoder\
    \ {\r\n\r\nnamespace internal {\r\n\r\n// @param n `0 <= n`\r\n// @return minimum\
    \ non-negative `x` s.t. `n <= 2**x`\r\nint ceil_pow2(int n) {\r\n    int x = 0;\r\
    \n    while ((1U << x) < (unsigned int)(n)) x++;\r\n    return x;\r\n}\r\n\r\n\
    // @param n `1 <= n`\r\n// @return minimum non-negative `x` s.t. `(n & (1 << x))\
    \ != 0`\r\nint bsf(unsigned int n) {\r\n#ifdef _MSC_VER\r\n    unsigned long index;\r\
    \n    _BitScanForward(&index, n);\r\n    return index;\r\n#else\r\n    return\
    \ __builtin_ctz(n);\r\n#endif\r\n}\r\n\r\n}  // namespace internal\r\n\r\n}  //\
    \ namespace atcoder\r\n\r\n#endif  // ATCODER_INTERNAL_BITOP_HPP\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/atcoder/internal_bit.hpp
  requiredBy:
  - lib/atcoder/lazysegtree.hpp
  - lib/atcoder/segtree.hpp
  - lib/atcoder/convolution.hpp
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/internal_bit.hpp
layout: document
redirect_from:
- /library/lib/atcoder/internal_bit.hpp
- /library/lib/atcoder/internal_bit.hpp.html
title: lib/atcoder/internal_bit.hpp
---
