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
    PROBLEM: https://judge.yosupo.jp/problem/montmort_number_mod
    links:
    - https://judge.yosupo.jp/problem/montmort_number_mod
  bundledCode: "#line 1 \"test/yosupo/math/montmort_number.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/montmort_number_mod\"\n#include <cstdint>\n\
    #include <iostream>\n#include <vector>\n\nint main(void) {\n    int n, m;\n  \
    \  std::cin >> n >> m;\n    std::int64_t sum = 0;\n    std::vector<int> ans(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        ans[i] = sum;\n        sum *= i +\
    \ 2;\n        if (i & 1) sum += m - 1;\n        else ++sum;\n        sum %= m;\n\
    \    }\n    for (int i = 0; i < (int)ans.size(); ++i)\n        std::cout << ans[i]\
    \ << (i == (int)ans.size() - 1 ? '\\n' : ' ');\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/montmort_number_mod\"\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n\nint main(void) {\n\
    \    int n, m;\n    std::cin >> n >> m;\n    std::int64_t sum = 0;\n    std::vector<int>\
    \ ans(n);\n    for (int i = 0; i < n; ++i) {\n        ans[i] = sum;\n        sum\
    \ *= i + 2;\n        if (i & 1) sum += m - 1;\n        else ++sum;\n        sum\
    \ %= m;\n    }\n    for (int i = 0; i < (int)ans.size(); ++i)\n        std::cout\
    \ << ans[i] << (i == (int)ans.size() - 1 ? '\\n' : ' ');\n\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/yosupo/math/montmort_number.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 17:56:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/math/montmort_number.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/math/montmort_number.test.cpp
- /verify/test/yosupo/math/montmort_number.test.cpp.html
title: test/yosupo/math/montmort_number.test.cpp
---
