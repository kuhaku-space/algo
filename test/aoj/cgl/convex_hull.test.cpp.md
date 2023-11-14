---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/geometry/convex_hull.hpp
    title: "\u70B9"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: geometry/convex_hull.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_A\"\n#include\
    \ \"geometry/convex_hull.hpp\"\n#include <algorithm>\n#include <iostream>\n#include\
    \ <iterator>\n#include <vector>\n\nint main(void) {\n    int n;\n    std::cin\
    \ >> n;\n    std::vector<Point<int>> ps(n);\n    std::copy_n(std::istream_iterator<Point<int>>(std::cin),\
    \ n, std::begin(ps));\n    auto v = convex_hull(ps);\n    std::cout << std::size(v)\
    \ << '\\n';\n\n    int t = 0;\n    for (int i = 0; i < n; ++i) {\n        if (v[i].y\
    \ < v[t].y || (v[i].y == v[t].y && v[i].x < v[i].y)) t = i;\n    }\n\n    std::rotate(std::begin(v),\
    \ std::begin(v) + t, std::end(v));\n    for (auto &[x, y] : v) std::cout << x\
    \ << ' ' << y << '\\n';\n\n    return 0;\n}\n"
  dependsOn:
  - lib/geometry/convex_hull.hpp
  isVerificationFile: true
  path: test/aoj/cgl/convex_hull.test.cpp
  requiredBy: []
  timestamp: '2023-10-12 07:19:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/cgl/convex_hull.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/cgl/convex_hull.test.cpp
- /verify/test/aoj/cgl/convex_hull.test.cpp.html
title: test/aoj/cgl/convex_hull.test.cpp
---
