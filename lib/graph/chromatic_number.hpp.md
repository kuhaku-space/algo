---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/matrix_graph.hpp
    title: "\u96A3\u63A5\u884C\u5217"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/graph/chromatic_number.test.cpp
    title: test/yosupo/graph/chromatic_number.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5F69\u8272\u6570\u3092\u6C42\u3081\u308B"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/matrix_graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/matrix_graph.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\n/**\r\n * @brief \u5F69\u8272\u6570\u3092\u6C42\u3081\u308B\r\n * @details\
    \ $O(2^N)$\r\n *\r\n * @param G \u30B0\u30E9\u30D5\r\n * @return int \u5F69\u8272\
    \u6570\r\n */\r\nint chromatic_number(const matrix_graph<void> &G) {\r\n    constexpr\
    \ std::int64_t _MOD = (1LL << 31) - 1;\r\n    int n = G.size();\r\n    std::vector<int>\
    \ neighbor(n, 0);\r\n    for (int i = 0; i < n; ++i) {\r\n        int s = 1 <<\
    \ i;\r\n        for (int j = 0; j < n; ++j) {\r\n            if (G[i][j]) s |=\
    \ 1 << j;\r\n        }\r\n        neighbor[i] = s;\r\n    }\r\n\r\n    std::vector<int>\
    \ v(1 << n);\r\n    v[0] = 1;\r\n    for (int s = 1; s < 1 << n; ++s) {\r\n  \
    \      int c = __builtin_ctz(s);\r\n        v[s] = v[s & ~(1 << c)] + v[s & ~neighbor[c]];\r\
    \n    }\r\n\r\n    auto _mod = [](std::int64_t a) -> std::int64_t {\r\n      \
    \  a = (a & _MOD) + (a >> 31);\r\n        return a >= _MOD ? a - _MOD : a;\r\n\
    \    };\r\n    auto _pow = [](auto f, std::int64_t a, int n) {\r\n        std::int64_t\
    \ res = 1;\r\n        for (; n > 0; n >>= 1) {\r\n            if (n & 1) res =\
    \ f(res * a);\r\n            a = f(a * a);\r\n        }\r\n        return res;\r\
    \n    };\r\n\r\n    int low = 0, high = n;\r\n    while (high - low > 1) {\r\n\
    \        int mid = (low + high) >> 1;\r\n        std::int64_t g = 0;\r\n     \
    \   for (int s = 0; s < 1 << n; ++s) {\r\n            if ((n - __builtin_popcount(s))\
    \ & 1) g = _mod(g + _MOD - _pow(_mod, v[s], mid));\r\n            else g = _mod(g\
    \ + _pow(_mod, v[s], mid));\r\n        }\r\n        if (g != 0) high = mid;\r\n\
    \        else low = mid;\r\n    }\r\n    return high;\r\n}\r\n"
  dependsOn:
  - lib/graph/matrix_graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/chromatic_number.hpp
  requiredBy: []
  timestamp: '2022-07-17 07:17:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/graph/chromatic_number.test.cpp
documentation_of: lib/graph/chromatic_number.hpp
layout: document
redirect_from:
- /library/lib/graph/chromatic_number.hpp
- /library/lib/graph/chromatic_number.hpp.html
title: "\u5F69\u8272\u6570\u3092\u6C42\u3081\u308B"
---
