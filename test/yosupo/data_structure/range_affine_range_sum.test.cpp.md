---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_math.hpp
    title: lib/internal/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_type_traits.hpp
    title: lib/internal/internal_type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/lazy_segment_tree.hpp
    title: "\u9045\u5EF6\u8A55\u4FA1\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n#include <iostream>\n#include <utility>\n#include <vector>\n#include \"math/modint.hpp\"\
    \n#include \"segment_tree/lazy_segment_tree.hpp\"\n\nusing Mint = modint998;\n\
    \nstruct M1 {\n    using T = std::pair<Mint, Mint>;\n    using value_type = T;\n\
    \    static constexpr T id = T(0, 0);\n    static constexpr T op(T lhs, T rhs)\
    \ { return {lhs.first + rhs.first, rhs.second + lhs.second}; }\n};\n\nstruct M2\
    \ {\n    using T = std::pair<Mint, Mint>;\n    using value_type = T;\n    static\
    \ constexpr T id = T(1, 0);\n    static constexpr T op(T lhs, T rhs) {\n     \
    \   return {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second};\n   \
    \ }\n    template <class U>\n    static constexpr U f(T lhs, U rhs) {\n      \
    \  return {lhs.first * rhs.first + lhs.second * rhs.second, rhs.second};\n   \
    \ }\n};\n\nint main(void) {\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<Mint>\
    \ a(n);\n    for (auto &e : a) std::cin >> e;\n    std::vector<std::pair<Mint,\
    \ Mint>> p(n);\n    for (int i = 0; i < n; ++i) p[i] = {a[i], 1};\n    lazy_segment_tree<M1,\
    \ M2> st(p);\n\n    while (q--) {\n        int c;\n        std::cin >> c;\n  \
    \      if (c == 0) {\n            int l, r, b, c;\n            std::cin >> l >>\
    \ r >> b >> c;\n            st.apply(l, r, {b, c});\n        } else {\n      \
    \      int l, r;\n            std::cin >> l >> r;\n            std::cout << st.prod(l,\
    \ r).first << '\\n';\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/segment_tree/lazy_segment_tree.hpp
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/range_affine_range_sum.test.cpp
  requiredBy: []
  timestamp: '2024-05-06 21:20:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/range_affine_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/range_affine_range_sum.test.cpp
- /verify/test/yosupo/data_structure/range_affine_range_sum.test.cpp.html
title: test/yosupo/data_structure/range_affine_range_sum.test.cpp
---
