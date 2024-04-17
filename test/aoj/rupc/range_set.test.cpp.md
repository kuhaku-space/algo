---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/range_set.hpp
    title: lib/binary_tree/range_set.hpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2880
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2880
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/range_set.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2880\"\n#include\
    \ \"binary_tree/range_set.hpp\"\n#include <algorithm>\n#include <iostream>\n#include\
    \ <tuple>\n#include <vector>\n\nint main(void) {\n    int n, m, q;\n    std::cin\
    \ >> n >> m >> q;\n    std::vector<std::tuple<int, int, int, int, int>> queries;\n\
    \    for (int i = 0; i < m; ++i) {\n        int d, a, b;\n        std::cin >>\
    \ d >> a >> b;\n        queries.emplace_back(d, 1, i, a, b);\n    }\n    for (int\
    \ i = 0; i < q; ++i) {\n        int e, s, t;\n        std::cin >> e >> s >> t;\n\
    \        queries.emplace_back(e, 0, i, s, t - 1);\n    }\n\n    std::sort(queries.begin(),\
    \ queries.end());\n    std::vector<bool> ans(q);\n    range_set<int> rs;\n   \
    \ for (auto [a, b, c, d, e] : queries) {\n        if (b == 0) ans[c] = d > e ||\
    \ rs.same(d, e);\n        else rs.insert(d, e);\n    }\n    for (auto f : ans)\
    \ std::cout << (f ? \"Yes\" : \"No\") << std::endl;\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/range_set.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/rupc/range_set.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 01:56:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/rupc/range_set.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/rupc/range_set.test.cpp
- /verify/test/aoj/rupc/range_set.test.cpp.html
title: test/aoj/rupc/range_set.test.cpp
---
