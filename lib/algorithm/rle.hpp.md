---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/joi/rle.test.cpp
    title: test/aoj/joi/rle.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30E9\u30F3\u30EC\u30F3\u30B0\u30B9\u5727\u7E2E"
    links: []
  bundledCode: "#line 1 \"lib/algorithm/rle.hpp\"\n#include <utility>\n#include <vector>\n\
    \n/**\n * @brief \u30E9\u30F3\u30EC\u30F3\u30B0\u30B9\u5727\u7E2E\n *\n * @tparam\
    \ Container\n * @param v \u914D\u5217\n * @return auto\n */\ntemplate <class Container>\n\
    auto run_length_encoding(const Container &v) {\n    std::vector<std::pair<std::decay_t<decltype(v[0])>,\
    \ int>> res;\n    for (auto &&e : v) {\n        if (res.empty() || res.back().first\
    \ != e) res.emplace_back(e, 1);\n        else ++res.back().second;\n    }\n  \
    \  return res;\n}\n"
  code: "#include <utility>\n#include <vector>\n\n/**\n * @brief \u30E9\u30F3\u30EC\
    \u30F3\u30B0\u30B9\u5727\u7E2E\n *\n * @tparam Container\n * @param v \u914D\u5217\
    \n * @return auto\n */\ntemplate <class Container>\nauto run_length_encoding(const\
    \ Container &v) {\n    std::vector<std::pair<std::decay_t<decltype(v[0])>, int>>\
    \ res;\n    for (auto &&e : v) {\n        if (res.empty() || res.back().first\
    \ != e) res.emplace_back(e, 1);\n        else ++res.back().second;\n    }\n  \
    \  return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/algorithm/rle.hpp
  requiredBy: []
  timestamp: '2023-11-16 06:30:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/joi/rle.test.cpp
documentation_of: lib/algorithm/rle.hpp
layout: document
redirect_from:
- /library/lib/algorithm/rle.hpp
- /library/lib/algorithm/rle.hpp.html
title: "\u30E9\u30F3\u30EC\u30F3\u30B0\u30B9\u5727\u7E2E"
---
