---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/kitamasa.test.cpp
    title: test/aoj/alds1/kitamasa.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u304D\u305F\u307E\u3055\u6CD5"
    links: []
  bundledCode: "#line 1 \"lib/math/kitamasa.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <iterator>\n#include <utility>\n#include <vector>\n\n/**\n\
    \ * @brief \u304D\u305F\u307E\u3055\u6CD5\n *\n * @tparam T\n * @param a\n * @param\
    \ d\n * @param n\n * @return T\n */\ntemplate <class T>\nT kitamasa(const std::vector<T>\
    \ &a, const std::vector<T> &d, std::int64_t n) {\n    assert(a.size() == d.size());\n\
    \    const int k = d.size();\n    if (n < k) return a[n];\n    std::vector<int>\
    \ bits;\n    while (n > k * 2) {\n        bits.emplace_back(n & 1);\n        n\
    \ >>= 1;\n    }\n    std::vector<T> x = d, y(k);\n    for (int i = k; i < n; ++i)\
    \ {\n        std::swap(x, y);\n        for (int i = 0; i < k; ++i) x[i] = d[i]\
    \ * y[k - 1];\n        for (int i = 0; i + 1 < k; ++i) x[i + 1] += y[i];\n   \
    \ }\n    std::reverse(std::begin(bits), std::end(bits));\n    std::vector<std::vector<T>>\
    \ v(k, std::vector<T>(k));\n    for (auto &&bit : bits) {\n        v[0] = x;\n\
    \        for (int i = 0; i + 1 < k; ++i) {\n            for (int j = 0; j < k;\
    \ ++j) v[i + 1][j] = d[j] * v[i][k - 1];\n            for (int j = 0; j + 1 <\
    \ k; ++j) v[i + 1][j + 1] += v[i][j];\n        }\n        std::fill(std::begin(x),\
    \ std::end(x), T());\n        for (int i = 0; i < k; ++i) {\n            for (int\
    \ j = 0; j < k; ++j) x[j] += v[0][i] * v[i][j];\n        }\n        if (bit) {\n\
    \            std::swap(x, y);\n            for (int i = 0; i < k; ++i) x[i] =\
    \ d[i] * y[k - 1];\n            for (int i = 0; i + 1 < k; ++i) x[i + 1] += y[i];\n\
    \        }\n    }\n    T res{};\n    for (int i = 0; i < k; ++i) res += x[i] *\
    \ a[i];\n    return res;\n}\n"
  code: "#include <algorithm>\n#include <cassert>\n#include <iterator>\n#include <utility>\n\
    #include <vector>\n\n/**\n * @brief \u304D\u305F\u307E\u3055\u6CD5\n *\n * @tparam\
    \ T\n * @param a\n * @param d\n * @param n\n * @return T\n */\ntemplate <class\
    \ T>\nT kitamasa(const std::vector<T> &a, const std::vector<T> &d, std::int64_t\
    \ n) {\n    assert(a.size() == d.size());\n    const int k = d.size();\n    if\
    \ (n < k) return a[n];\n    std::vector<int> bits;\n    while (n > k * 2) {\n\
    \        bits.emplace_back(n & 1);\n        n >>= 1;\n    }\n    std::vector<T>\
    \ x = d, y(k);\n    for (int i = k; i < n; ++i) {\n        std::swap(x, y);\n\
    \        for (int i = 0; i < k; ++i) x[i] = d[i] * y[k - 1];\n        for (int\
    \ i = 0; i + 1 < k; ++i) x[i + 1] += y[i];\n    }\n    std::reverse(std::begin(bits),\
    \ std::end(bits));\n    std::vector<std::vector<T>> v(k, std::vector<T>(k));\n\
    \    for (auto &&bit : bits) {\n        v[0] = x;\n        for (int i = 0; i +\
    \ 1 < k; ++i) {\n            for (int j = 0; j < k; ++j) v[i + 1][j] = d[j] *\
    \ v[i][k - 1];\n            for (int j = 0; j + 1 < k; ++j) v[i + 1][j + 1] +=\
    \ v[i][j];\n        }\n        std::fill(std::begin(x), std::end(x), T());\n \
    \       for (int i = 0; i < k; ++i) {\n            for (int j = 0; j < k; ++j)\
    \ x[j] += v[0][i] * v[i][j];\n        }\n        if (bit) {\n            std::swap(x,\
    \ y);\n            for (int i = 0; i < k; ++i) x[i] = d[i] * y[k - 1];\n     \
    \       for (int i = 0; i + 1 < k; ++i) x[i + 1] += y[i];\n        }\n    }\n\
    \    T res{};\n    for (int i = 0; i < k; ++i) res += x[i] * a[i];\n    return\
    \ res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/math/kitamasa.hpp
  requiredBy: []
  timestamp: '2023-10-01 21:51:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/alds1/kitamasa.test.cpp
documentation_of: lib/math/kitamasa.hpp
layout: document
redirect_from:
- /library/lib/math/kitamasa.hpp
- /library/lib/math/kitamasa.hpp.html
title: "\u304D\u305F\u307E\u3055\u6CD5"
---
