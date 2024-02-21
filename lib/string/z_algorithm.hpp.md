---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/string/zalgorithm.test.cpp
    title: test/yosupo/string/zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Z algorithm
    links:
    - https://snuke.hatenablog.com/entry/2014/12/03/214243
  bundledCode: "#line 1 \"lib/string/z_algorithm.hpp\"\n#include <vector>\r\n\r\n\
    /**\r\n * @brief Z algorithm\r\n * @details Z[i] := S[i:Z[i]] == S[0:Z[i]-i]\r\
    \n * @see https://snuke.hatenablog.com/entry/2014/12/03/214243\r\n *\r\n * @tparam\
    \ Container\r\n */\r\ntemplate <class Container>\r\nstd::vector<int> z_algorithm(const\
    \ Container &s) {\r\n    int n = s.size();\r\n    std::vector<int> res(n);\r\n\
    \    res[0] = n;\r\n    int i = 1, j = 0;\r\n    while (i < n) {\r\n        while\
    \ (i + j < n && s[j] == s[i + j]) ++j;\r\n        res[i] = j;\r\n        if (!j)\
    \ {\r\n            ++i;\r\n            continue;\r\n        }\r\n        int k\
    \ = 1;\r\n        while (i + k < n && k + res[k] < j) res[i + k] = res[k], ++k;\r\
    \n        i += k, j -= k;\r\n    }\r\n    return res;\r\n}\r\n"
  code: "#include <vector>\r\n\r\n/**\r\n * @brief Z algorithm\r\n * @details Z[i]\
    \ := S[i:Z[i]] == S[0:Z[i]-i]\r\n * @see https://snuke.hatenablog.com/entry/2014/12/03/214243\r\
    \n *\r\n * @tparam Container\r\n */\r\ntemplate <class Container>\r\nstd::vector<int>\
    \ z_algorithm(const Container &s) {\r\n    int n = s.size();\r\n    std::vector<int>\
    \ res(n);\r\n    res[0] = n;\r\n    int i = 1, j = 0;\r\n    while (i < n) {\r\
    \n        while (i + j < n && s[j] == s[i + j]) ++j;\r\n        res[i] = j;\r\n\
    \        if (!j) {\r\n            ++i;\r\n            continue;\r\n        }\r\
    \n        int k = 1;\r\n        while (i + k < n && k + res[k] < j) res[i + k]\
    \ = res[k], ++k;\r\n        i += k, j -= k;\r\n    }\r\n    return res;\r\n}\r\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: lib/string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2024-01-23 18:10:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/string/zalgorithm.test.cpp
documentation_of: lib/string/z_algorithm.hpp
layout: document
redirect_from:
- /library/lib/string/z_algorithm.hpp
- /library/lib/string/z_algorithm.hpp.html
title: Z algorithm
---
