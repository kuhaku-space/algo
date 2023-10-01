---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/tree/union_find.hpp
    title: "\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: tree/union_find.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n#include <iostream>\n\
    #include \"tree/union_find.hpp\"\n\nint main(void) {\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    union_find uf(n);\n    while (q--) {\n        int t, u, v;\n\
    \        std::cin >> t >> u >> v;\n        if (t == 0) uf.unite(u, v);\n     \
    \   else std::cout << uf.same(u, v) << std::endl;\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/tree/union_find.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/unionfind.test.cpp
  requiredBy: []
  timestamp: '2023-10-01 19:23:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/unionfind.test.cpp
- /verify/test/yosupo/data_structure/unionfind.test.cpp.html
title: test/yosupo/data_structure/unionfind.test.cpp
---
