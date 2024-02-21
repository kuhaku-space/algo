---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/hupc/manacher.test.cpp
    title: test/aoj/hupc/manacher.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/string/enumerate_palindromes.test.cpp
    title: test/yosupo/string/enumerate_palindromes.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Manacher
    links: []
  bundledCode: "#line 1 \"lib/string/manacher.hpp\"\n#include <vector>\r\n\r\n/**\r\
    \n * @brief Manacher\r\n * @details R[i] := S[i-R[i]:i] == S[i:i+R[i]]\r\n *\r\
    \n * @tparam Container\r\n */\r\ntemplate <typename Container>\r\nstruct Manacher\
    \ {\r\n    Manacher(const Container &_s) : _size(_s.size()), s(_s), r(_s.size())\
    \ {\r\n        int i = 0, j = 0;\r\n        while (i < _size) {\r\n          \
    \  while (i - j >= 0 && i + j < _size && s[i - j] == s[i + j]) ++j;\r\n      \
    \      r[i] = j;\r\n            int k = 1;\r\n            while (i - k >= 0 &&\
    \ i + k < _size && k + r[i - k] < j) r[i + k] = r[i - k], ++k;\r\n           \
    \ i += k, j -= k;\r\n        }\r\n    }\r\n\r\n    const auto &operator[](int\
    \ i) const { return r[i]; }\r\n    auto &operator[](int i) { return r[i]; }\r\n\
    \    const auto begin() const { return r.begin(); }\r\n    auto begin() { return\
    \ r.begin(); }\r\n    const auto end() const { return r.end(); }\r\n    auto end()\
    \ { return r.end(); }\r\n\r\n    const std::vector<int> &get() { return r; }\r\
    \n\r\n  private:\r\n    int _size;\r\n    const Container &s;\r\n    std::vector<int>\
    \ r;\r\n};\r\n"
  code: "#include <vector>\r\n\r\n/**\r\n * @brief Manacher\r\n * @details R[i] :=\
    \ S[i-R[i]:i] == S[i:i+R[i]]\r\n *\r\n * @tparam Container\r\n */\r\ntemplate\
    \ <typename Container>\r\nstruct Manacher {\r\n    Manacher(const Container &_s)\
    \ : _size(_s.size()), s(_s), r(_s.size()) {\r\n        int i = 0, j = 0;\r\n \
    \       while (i < _size) {\r\n            while (i - j >= 0 && i + j < _size\
    \ && s[i - j] == s[i + j]) ++j;\r\n            r[i] = j;\r\n            int k\
    \ = 1;\r\n            while (i - k >= 0 && i + k < _size && k + r[i - k] < j)\
    \ r[i + k] = r[i - k], ++k;\r\n            i += k, j -= k;\r\n        }\r\n  \
    \  }\r\n\r\n    const auto &operator[](int i) const { return r[i]; }\r\n    auto\
    \ &operator[](int i) { return r[i]; }\r\n    const auto begin() const { return\
    \ r.begin(); }\r\n    auto begin() { return r.begin(); }\r\n    const auto end()\
    \ const { return r.end(); }\r\n    auto end() { return r.end(); }\r\n\r\n    const\
    \ std::vector<int> &get() { return r; }\r\n\r\n  private:\r\n    int _size;\r\n\
    \    const Container &s;\r\n    std::vector<int> r;\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/string/manacher.hpp
  requiredBy: []
  timestamp: '2024-01-23 18:07:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/string/enumerate_palindromes.test.cpp
  - test/aoj/hupc/manacher.test.cpp
documentation_of: lib/string/manacher.hpp
layout: document
redirect_from:
- /library/lib/string/manacher.hpp
- /library/lib/string/manacher.hpp.html
title: Manacher
---
