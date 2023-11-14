---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/stern_brocot_tree.hpp
    title: "Stern-Brocot \u6728"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/1208
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/1208
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: tree/stern_brocot_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/1208\"\n#include\
    \ \"tree/stern_brocot_tree.hpp\"\n#include <cstdint>\n#include <iostream>\n\n\
    int main(void) {\n    while (true) {\n        int n, p;\n        std::cin >> p\
    \ >> n;\n        if (n == 0 && p == 0) break;\n        int u, v, x, y;\n     \
    \   auto f = [&](std::int64_t a, std::int64_t b) -> bool {\n            bool f\
    \ = a * a < b * b * p;\n            if (f) u = a, v = b;\n            else x =\
    \ a, y = b;\n            return f;\n        };\n        stern_brocot_tree sbt;\n\
    \        while (true) {\n            auto [s, t] = sbt.get();\n            if\
    \ (s > n || t > n) break;\n            if (f(s, t)) sbt = sbt.get_right();\n \
    \           else sbt = sbt.get_left();\n        }\n\n        std::cout << x <<\
    \ \"/\" << y << \" \" << u << \"/\" << v << std::endl;\n    }\n\n    return 0;\n\
    }\n"
  dependsOn:
  - lib/tree/stern_brocot_tree.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/icpc/stern_brocot_tree.test.cpp
  requiredBy: []
  timestamp: '2023-11-14 23:28:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/icpc/stern_brocot_tree.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/icpc/stern_brocot_tree.test.cpp
- /verify/test/aoj/icpc/stern_brocot_tree.test.cpp.html
title: test/aoj/icpc/stern_brocot_tree.test.cpp
---
