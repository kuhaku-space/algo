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
    PROBLEM: https://judge.yosupo.jp/problem/sort_points_by_argument
    links:
    - https://judge.yosupo.jp/problem/sort_points_by_argument
  bundledCode: "#line 1 \"test/yosupo/geometry/sort_points_by_argument.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\n\
    #include <algorithm>\n#include <cmath>\n#include <iostream>\n#include <tuple>\n\
    #include <vector>\n\nint main(void) {\n    int n;\n    std::cin >> n;\n    std::vector<std::tuple<int,\
    \ int, long double>> v;\n    for (int i = 0; i < n; ++i) {\n        int x, y;\n\
    \        std::cin >> x >> y;\n        v.emplace_back(x, y, std::atan2((long double)y,\
    \ x));\n    }\n    std::sort(v.begin(), v.end(), [&](auto x, auto y) { return\
    \ std::get<2>(x) < std::get<2>(y); });\n    for (auto &&[x, y, z] : v) std::cout\
    \ << x << ' ' << y << '\\n';\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sort_points_by_argument\"\
    \n#include <algorithm>\n#include <cmath>\n#include <iostream>\n#include <tuple>\n\
    #include <vector>\n\nint main(void) {\n    int n;\n    std::cin >> n;\n    std::vector<std::tuple<int,\
    \ int, long double>> v;\n    for (int i = 0; i < n; ++i) {\n        int x, y;\n\
    \        std::cin >> x >> y;\n        v.emplace_back(x, y, std::atan2((long double)y,\
    \ x));\n    }\n    std::sort(v.begin(), v.end(), [&](auto x, auto y) { return\
    \ std::get<2>(x) < std::get<2>(y); });\n    for (auto &&[x, y, z] : v) std::cout\
    \ << x << ' ' << y << '\\n';\n\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/yosupo/geometry/sort_points_by_argument.test.cpp
  requiredBy: []
  timestamp: '2023-11-16 01:03:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/geometry/sort_points_by_argument.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/geometry/sort_points_by_argument.test.cpp
- /verify/test/yosupo/geometry/sort_points_by_argument.test.cpp.html
title: test/yosupo/geometry/sort_points_by_argument.test.cpp
---
