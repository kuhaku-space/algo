---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum
    links:
    - https://judge.yosupo.jp/problem/static_range_sum
  bundledCode: "#line 1 \"test/yosupo/data_structure/static_range_sum.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n#include\
    \ <cstdint>\n#include <iostream>\n#include <numeric>\n#include <vector>\n\nint\
    \ main(void) {\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::int64_t>\
    \ a(n);\n    for (auto &e : a) std::cin >> e;\n    a.emplace_back(0);\n    std::inclusive_scan(a.rbegin(),\
    \ a.rend(), a.rbegin());\n    while (q--) {\n        int l, r;\n        std::cin\
    \ >> l >> r;\n        std::cout << a[l] - a[r] << '\\n';\n    }\n\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n#include\
    \ <cstdint>\n#include <iostream>\n#include <numeric>\n#include <vector>\n\nint\
    \ main(void) {\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::int64_t>\
    \ a(n);\n    for (auto &e : a) std::cin >> e;\n    a.emplace_back(0);\n    std::inclusive_scan(a.rbegin(),\
    \ a.rend(), a.rbegin());\n    while (q--) {\n        int l, r;\n        std::cin\
    \ >> l >> r;\n        std::cout << a[l] - a[r] << '\\n';\n    }\n\n    return\
    \ 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/yosupo/data_structure/static_range_sum.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 06:42:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/static_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/static_range_sum.test.cpp
- /verify/test/yosupo/data_structure/static_range_sum.test.cpp.html
title: test/yosupo/data_structure/static_range_sum.test.cpp
---
