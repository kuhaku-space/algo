---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Mex
    links: []
  bundledCode: "#line 1 \"lib/algorithm/mex.hpp\"\n#include <algorithm>\r\n#include\
    \ <iterator>\r\n#include <vector>\r\n\r\n/**\r\n * @brief Mex\r\n *\r\n */\r\n\
    struct minimum_excluded {\r\n    minimum_excluded() : n(), _size(), exists(64),\
    \ v() {}\r\n\r\n    constexpr int operator()() const noexcept { return n; }\r\n\
    \    constexpr int get() const noexcept { return n; }\r\n\r\n    void add(int\
    \ x) {\r\n        if (x < 0) return;\r\n        ++_size;\r\n        if (_size\
    \ == (int)exists.size()) {\r\n            exists.resize(_size << 1);\r\n     \
    \       v.erase(std::remove_if(v.begin(), v.end(),\r\n                       \
    \            [&](int y) {\r\n                                       if (y < (int)exists.size())\
    \ {\r\n                                           if (exists[y]) --_size;\r\n\
    \                                           else exists[y] = true;\r\n       \
    \                                    return true;\r\n                        \
    \               }\r\n                                       return false;\r\n\
    \                                   }),\r\n                    v.end());\r\n \
    \       }\r\n        if (x < (int)exists.size()) {\r\n            if (exists[x])\
    \ --_size;\r\n            else exists[x] = true;\r\n        } else {\r\n     \
    \       v.emplace_back(x);\r\n        }\r\n        while (exists[n]) ++n;\r\n\
    \    }\r\n\r\n  private:\r\n    int n, _size;\r\n    std::vector<bool> exists;\r\
    \n    std::vector<int> v;\r\n};\r\n"
  code: "#include <algorithm>\r\n#include <iterator>\r\n#include <vector>\r\n\r\n\
    /**\r\n * @brief Mex\r\n *\r\n */\r\nstruct minimum_excluded {\r\n    minimum_excluded()\
    \ : n(), _size(), exists(64), v() {}\r\n\r\n    constexpr int operator()() const\
    \ noexcept { return n; }\r\n    constexpr int get() const noexcept { return n;\
    \ }\r\n\r\n    void add(int x) {\r\n        if (x < 0) return;\r\n        ++_size;\r\
    \n        if (_size == (int)exists.size()) {\r\n            exists.resize(_size\
    \ << 1);\r\n            v.erase(std::remove_if(v.begin(), v.end(),\r\n       \
    \                            [&](int y) {\r\n                                \
    \       if (y < (int)exists.size()) {\r\n                                    \
    \       if (exists[y]) --_size;\r\n                                          \
    \ else exists[y] = true;\r\n                                           return\
    \ true;\r\n                                       }\r\n                      \
    \                 return false;\r\n                                   }),\r\n\
    \                    v.end());\r\n        }\r\n        if (x < (int)exists.size())\
    \ {\r\n            if (exists[x]) --_size;\r\n            else exists[x] = true;\r\
    \n        } else {\r\n            v.emplace_back(x);\r\n        }\r\n        while\
    \ (exists[n]) ++n;\r\n    }\r\n\r\n  private:\r\n    int n, _size;\r\n    std::vector<bool>\
    \ exists;\r\n    std::vector<int> v;\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/algorithm/mex.hpp
  requiredBy: []
  timestamp: '2023-11-16 02:35:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/mex.hpp
layout: document
redirect_from:
- /library/lib/algorithm/mex.hpp
- /library/lib/algorithm/mex.hpp.html
title: Mex
---
