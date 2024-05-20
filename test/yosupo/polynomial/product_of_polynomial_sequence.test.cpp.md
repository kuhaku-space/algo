---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: "\u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_fft.hpp
    title: lib/internal/internal_fft.hpp
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
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/product_of_polynomial_sequence
    links:
    - https://judge.yosupo.jp/problem/product_of_polynomial_sequence
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: fft/ntt.hpp: line\
    \ -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/product_of_polynomial_sequence\"\
    \n#include <iostream>\n#include <utility>\n#include <vector>\n\n#include \"fft/ntt.hpp\"\
    \n\nusing Mint = modint998;\n\nstd::vector<Mint> prod(const std::vector<std::vector<Mint>>\
    \ &a, int l, int r) {\n    if (l + 1 == r)\n        return a[l];\n    int m =\
    \ (l + r) / 2;\n    return convolution(prod(a, l, m), prod(a, m, r));\n}\n\nint\
    \ main(void) {\n    int n;\n    std::cin >> n;\n    std::vector<std::vector<Mint>>\
    \ a(n);\n    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,\
    \ int>>, std::greater<>>\n        p_que;\n    for (int i = 0; i < n; ++i) {\n\
    \        int d;\n        std::cin >> d;\n        p_que.emplace(d + 1, i);\n  \
    \      a[i].resize(d + 1);\n        for (int j = 0; j < d + 1; ++j) std::cin >>\
    \ a[i][j];\n    }\n\n    if (n == 0) {\n        std::cout << 1 << '\\n';\n   \
    \ } else {\n        auto ans = prod(a, 0, n);\n        for (int i = 0; i < (int)ans.size();\
    \ ++i)\n            std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\\n' :\
    \ ' ');\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/fft/ntt.hpp
  - lib/internal/internal_fft.hpp
  - lib/internal/internal_bit.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/polynomial/product_of_polynomial_sequence.test.cpp
  requiredBy: []
  timestamp: '2024-05-15 13:22:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/polynomial/product_of_polynomial_sequence.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/polynomial/product_of_polynomial_sequence.test.cpp
- /verify/test/yosupo/polynomial/product_of_polynomial_sequence.test.cpp.html
title: test/yosupo/polynomial/product_of_polynomial_sequence.test.cpp
---
