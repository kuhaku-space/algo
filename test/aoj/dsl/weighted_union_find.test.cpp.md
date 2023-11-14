---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/weighted_union_find.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: tree/weighted_union_find.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DSL_1_B\"\n#include\
    \ \"tree/weighted_union_find.hpp\"\n#include <iostream>\n\nint main(void) {\n\
    \    int n, q;\n    std::cin >> n >> q;\n    weighted_union_find<int> uf(n);\n\
    \    while (q--) {\n        int com;\n        std::cin >> com;\n        if (com\
    \ == 0) {\n            int x, y, w;\n            std::cin >> x >> y >> w;\n  \
    \          uf.unite(x, y, w);\n        } else {\n            int x, y;\n     \
    \       std::cin >> x >> y;\n            if (uf.same(x, y)) std::cout << uf.diff(x,\
    \ y) << std::endl;\n            else std::cout << '?' << std::endl;\n        }\n\
    \    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/tree/weighted_union_find.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/dsl/weighted_union_find.test.cpp
  requiredBy: []
  timestamp: '2023-11-07 17:41:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/dsl/weighted_union_find.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/dsl/weighted_union_find.test.cpp
- /verify/test/aoj/dsl/weighted_union_find.test.cpp.html
title: test/aoj/dsl/weighted_union_find.test.cpp
---
