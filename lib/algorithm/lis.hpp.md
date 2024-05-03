---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/longest_increasing_subsequense.test.cpp
    title: test/aoj/dpl/longest_increasing_subsequense.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/longest_increasing_subsequence.test.cpp
    title: test/yosupo/math/longest_increasing_subsequence.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
    links: []
  bundledCode: "#line 1 \"lib/algorithm/lis.hpp\"\n#include <algorithm>\n#include\
    \ <iterator>\n#include <vector>\n\n/**\n * @brief \u6700\u9577\u5897\u52A0\u90E8\
    \u5206\u5217\n *\n * @tparam T \u914D\u5217\u306E\u578B\n * @param v \u914D\u5217\
    \n * @retval int \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u9577\u3055\n\
    \ */\ntemplate <class T>\nint longest_increasing_subsequence(const std::vector<T>\
    \ &v) {\n    int n = v.size();\n    std::vector<T> dp;\n    for (auto x : v) {\n\
    \        auto it = std::lower_bound(std::begin(dp), std::end(dp), x);\n      \
    \  if (it == std::end(dp)) dp.emplace_back(x);\n        else *it = x;\n    }\n\
    \    return dp.size();\n}\n\n/**\n * @brief \u6700\u9577\u5897\u52A0\u90E8\u5206\
    \u5217\n *\n * @tparam T \u914D\u5217\u306E\u578B\n * @param v \u914D\u5217\n\
    \ * @retval std::vector<int> \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u30A4\
    \u30F3\u30C7\u30C3\u30AF\u30B9\n */\ntemplate <class T>\nstd::vector<int> make_lis(const\
    \ std::vector<T> &v) {\n    int n = v.size();\n    std::vector<T> dp;\n    std::vector<int>\
    \ pos;\n    pos.reserve(n);\n    for (auto x : v) {\n        auto it = std::lower_bound(std::begin(dp),\
    \ std::end(dp), x);\n        pos.emplace_back(std::distance(std::begin(dp), it));\n\
    \        if (it == std::end(dp)) dp.emplace_back(x);\n        else *it = x;\n\
    \    }\n\n    int x = dp.size();\n    std::vector<int> res(x--);\n    for (int\
    \ i = n - 1; i >= 0; --i) {\n        if (pos[i] == x) res[x] = i, --x;\n    }\n\
    \    return res;\n}\n"
  code: "#include <algorithm>\n#include <iterator>\n#include <vector>\n\n/**\n * @brief\
    \ \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\n *\n * @tparam T \u914D\u5217\u306E\
    \u578B\n * @param v \u914D\u5217\n * @retval int \u6700\u9577\u5897\u52A0\u90E8\
    \u5206\u5217\u306E\u9577\u3055\n */\ntemplate <class T>\nint longest_increasing_subsequence(const\
    \ std::vector<T> &v) {\n    int n = v.size();\n    std::vector<T> dp;\n    for\
    \ (auto x : v) {\n        auto it = std::lower_bound(std::begin(dp), std::end(dp),\
    \ x);\n        if (it == std::end(dp)) dp.emplace_back(x);\n        else *it =\
    \ x;\n    }\n    return dp.size();\n}\n\n/**\n * @brief \u6700\u9577\u5897\u52A0\
    \u90E8\u5206\u5217\n *\n * @tparam T \u914D\u5217\u306E\u578B\n * @param v \u914D\
    \u5217\n * @retval std::vector<int> \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\
    \u306E\u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n */\ntemplate <class T>\nstd::vector<int>\
    \ make_lis(const std::vector<T> &v) {\n    int n = v.size();\n    std::vector<T>\
    \ dp;\n    std::vector<int> pos;\n    pos.reserve(n);\n    for (auto x : v) {\n\
    \        auto it = std::lower_bound(std::begin(dp), std::end(dp), x);\n      \
    \  pos.emplace_back(std::distance(std::begin(dp), it));\n        if (it == std::end(dp))\
    \ dp.emplace_back(x);\n        else *it = x;\n    }\n\n    int x = dp.size();\n\
    \    std::vector<int> res(x--);\n    for (int i = n - 1; i >= 0; --i) {\n    \
    \    if (pos[i] == x) res[x] = i, --x;\n    }\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/algorithm/lis.hpp
  requiredBy: []
  timestamp: '2023-11-16 01:25:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/math/longest_increasing_subsequence.test.cpp
  - test/aoj/dpl/longest_increasing_subsequense.test.cpp
documentation_of: lib/algorithm/lis.hpp
layout: document
redirect_from:
- /library/lib/algorithm/lis.hpp
- /library/lib/algorithm/lis.hpp.html
title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
---
