---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/macro.hpp
    title: lib/template/macro.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/sonic.hpp
    title: lib/template/sonic.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/sort_points_by_argument
    links:
    - https://judge.yosupo.jp/problem/sort_points_by_argument
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/atcoder.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \n#include \"template/atcoder.hpp\"\n\nint main(void) {\n    int n;\n    std::cin\
    \ >> n;\n    std::vector<tuple<int, int, long double>> v;\n    rep (i, n) {\n\
    \        int x, y;\n        cin >> x >> y;\n        v.emplace_back(x, y, atan2l(y,\
    \ x));\n    }\n    std::sort(v.begin(), v.end(), [&](auto x, auto y) {\n     \
    \   return get<2>(x) < get<2>(y);\n    });\n    for (auto &&[x, y, z] : v) co(x,\
    \ y);\n\n    return 0;\n}\n"
  dependsOn:
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/template.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/geometry/sort_points_by_argument.test.cpp
  requiredBy: []
  timestamp: '2023-07-19 00:42:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/geometry/sort_points_by_argument.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/geometry/sort_points_by_argument.test.cpp
- /verify/test/yosupo/geometry/sort_points_by_argument.test.cpp.html
title: test/yosupo/geometry/sort_points_by_argument.test.cpp
---
