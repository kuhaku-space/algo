---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E"
    links: []
  bundledCode: "#line 1 \"lib/string/lcp.hpp\"\n#include <algorithm>\n#include <vector>\n\
    \n/**\n * @brief \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\n *\n * @tparam T\
    \ \u914D\u5217\u306E\u578B\n * @param a \u914D\u5217\n * @param b \u914D\u5217\
    \n * @return int \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u306E\u9577\u3055\n\
    \ */\ntemplate <class T>\nint longest_common_prefix(const std::vector<T> &a, const\
    \ std::vector<T> &b) {\n    int m = (int)std::min(a.size(), b.size());\n    for\
    \ (int i = 0; i < m; ++i) {\n        if (a[i] != b[i]) return i;\n    }\n    return\
    \ m;\n}\n\n/**\n * @brief \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\n *\n * @param\
    \ a \u6587\u5B57\u5217\n * @param b \u6587\u5B57\u5217\n * @return int \u6700\u9577\
    \u5171\u901A\u63A5\u982D\u8F9E\u306E\u9577\u3055\n */\nint longest_common_prefix(const\
    \ std::string &a, const std::string &b) {\n    int m = (int)std::min(a.size(),\
    \ b.size());\n    for (int i = 0; i < m; ++i) {\n        if (a[i] != b[i]) return\
    \ i;\n    }\n    return m;\n}\n"
  code: "#include <algorithm>\n#include <vector>\n\n/**\n * @brief \u6700\u9577\u5171\
    \u901A\u63A5\u982D\u8F9E\n *\n * @tparam T \u914D\u5217\u306E\u578B\n * @param\
    \ a \u914D\u5217\n * @param b \u914D\u5217\n * @return int \u6700\u9577\u5171\u901A\
    \u63A5\u982D\u8F9E\u306E\u9577\u3055\n */\ntemplate <class T>\nint longest_common_prefix(const\
    \ std::vector<T> &a, const std::vector<T> &b) {\n    int m = (int)std::min(a.size(),\
    \ b.size());\n    for (int i = 0; i < m; ++i) {\n        if (a[i] != b[i]) return\
    \ i;\n    }\n    return m;\n}\n\n/**\n * @brief \u6700\u9577\u5171\u901A\u63A5\
    \u982D\u8F9E\n *\n * @param a \u6587\u5B57\u5217\n * @param b \u6587\u5B57\u5217\
    \n * @return int \u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E\u306E\u9577\u3055\n\
    \ */\nint longest_common_prefix(const std::string &a, const std::string &b) {\n\
    \    int m = (int)std::min(a.size(), b.size());\n    for (int i = 0; i < m; ++i)\
    \ {\n        if (a[i] != b[i]) return i;\n    }\n    return m;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/string/lcp.hpp
  requiredBy: []
  timestamp: '2024-04-17 13:53:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/lcp.hpp
layout: document
redirect_from:
- /library/lib/string/lcp.hpp
- /library/lib/string/lcp.hpp.html
title: "\u6700\u9577\u5171\u901A\u63A5\u982D\u8F9E"
---
