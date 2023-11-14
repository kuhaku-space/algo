---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/geometry/kdtree.hpp
    title: kd-tree
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: geometry/kdtree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C\"\n#include\
    \ <algorithm>\n#include <iostream>\n#include \"geometry/kdtree.hpp\"\n\nint main(void)\
    \ {\n    int n;\n    std::cin >> n;\n    kdtree kd;\n    while (n--) {\n     \
    \   int x, y;\n        std::cin >> x >> y;\n        kd.add(x, y);\n    }\n   \
    \ kd.build();\n\n    int q;\n    std::cin >> q;\n    while (q--) {\n        int\
    \ sx, tx, sy, ty;\n        std::cin >> sx >> tx >> sy >> ty;\n        auto v =\
    \ kd.find(sx, tx + 1, sy, ty + 1);\n        std::sort(v.begin(), v.end());\n \
    \       for (auto e : v) std::cout << e << std::endl;\n        std::cout << std::endl;\n\
    \    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/geometry/kdtree.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/dsl/range_search.test.cpp
  requiredBy: []
  timestamp: '2023-11-07 17:41:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/dsl/range_search.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/dsl/range_search.test.cpp
- /verify/test/aoj/dsl/range_search.test.cpp.html
title: test/aoj/dsl/range_search.test.cpp
---
