---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/compress.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bit_vector.hpp
    title: "\u5B8C\u5099\u8F9E\u66F8"
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/wavelet_matrix_rectangle_sum.hpp
    title: lib/data_structure/wavelet_matrix_rectangle_sum.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/rectangle_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/compress.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n#include\
    \ <cstdint>\n#include <iostream>\n#include <tuple>\n#include <vector>\n#include\
    \ \"algorithm/compress.hpp\"\n#include \"data_structure/wavelet_matrix_rectangle_sum.hpp\"\
    \n\nint main(void) {\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::tuple<int,\
    \ int, int>> a(n);\n    for (auto &[x, y, z] : a) std::cin >> x >> y >> z;\n \
    \   std::sort(a.begin(), a.end());\n    std::vector<std::int64_t> x(n), y(n),\
    \ z(n);\n    for (int i = 0; i < n; ++i) std::tie(x[i], y[i], z[i]) = a[i];\n\n\
    \    wavelet_matrix_rectangle_sum<std::int64_t, std::int64_t, 30> wm(y, z);\n\n\
    \    while (q--) {\n        int l, d, r, u;\n        std::cin >> l >> d >> r >>\
    \ u;\n        int lx = std::lower_bound(x.begin(), x.end(), l) - x.begin();\n\
    \        int rx = std::lower_bound(x.begin(), x.end(), r) - x.begin();\n     \
    \   std::cout << wm.rect_sum(lx, rx, d, u) << '\\n';\n    }\n\n    return 0;\n\
    }\n"
  dependsOn:
  - lib/algorithm/compress.hpp
  - lib/data_structure/wavelet_matrix_rectangle_sum.hpp
  - lib/data_structure/bit_vector.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2024-02-04 15:23:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/rectangle_sum.test.cpp
- /verify/test/yosupo/data_structure/rectangle_sum.test.cpp.html
title: test/yosupo/data_structure/rectangle_sum.test.cpp
---
