---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/dsu.hpp\"\n\n\n\r\n#include <algorithm>\r\n\
    #include <cassert>\r\n#include <vector>\r\n\r\nnamespace atcoder {\r\n\r\n// Implement\
    \ (union by size) + (path compression)\r\n// Reference:\r\n// Zvi Galil and Giuseppe\
    \ F. Italiano,\r\n// Data structures and algorithms for disjoint set union problems\r\
    \nstruct dsu {\r\n  public:\r\n    dsu() : _n(0) {}\r\n    dsu(int n) : _n(n),\
    \ parent_or_size(n, -1) {}\r\n\r\n    int merge(int a, int b) {\r\n        assert(0\
    \ <= a && a < _n);\r\n        assert(0 <= b && b < _n);\r\n        int x = leader(a),\
    \ y = leader(b);\r\n        if (x == y) return x;\r\n        if (-parent_or_size[x]\
    \ < -parent_or_size[y]) std::swap(x, y);\r\n        parent_or_size[x] += parent_or_size[y];\r\
    \n        parent_or_size[y] = x;\r\n        return x;\r\n    }\r\n\r\n    bool\
    \ same(int a, int b) {\r\n        assert(0 <= a && a < _n);\r\n        assert(0\
    \ <= b && b < _n);\r\n        return leader(a) == leader(b);\r\n    }\r\n\r\n\
    \    int leader(int a) {\r\n        assert(0 <= a && a < _n);\r\n        if (parent_or_size[a]\
    \ < 0) return a;\r\n        return parent_or_size[a] = leader(parent_or_size[a]);\r\
    \n    }\r\n\r\n    int size(int a) {\r\n        assert(0 <= a && a < _n);\r\n\
    \        return -parent_or_size[leader(a)];\r\n    }\r\n\r\n    std::vector<std::vector<int>>\
    \ groups() {\r\n        std::vector<int> leader_buf(_n), group_size(_n);\r\n \
    \       for (int i = 0; i < _n; i++) {\r\n            leader_buf[i] = leader(i);\r\
    \n            group_size[leader_buf[i]]++;\r\n        }\r\n        std::vector<std::vector<int>>\
    \ result(_n);\r\n        for (int i = 0; i < _n; i++) {\r\n            result[i].reserve(group_size[i]);\r\
    \n        }\r\n        for (int i = 0; i < _n; i++) {\r\n            result[leader_buf[i]].push_back(i);\r\
    \n        }\r\n        result.erase(\r\n            std::remove_if(result.begin(),\
    \ result.end(),\r\n                           [&](const std::vector<int>& v) {\
    \ return v.empty(); }),\r\n            result.end());\r\n        return result;\r\
    \n    }\r\n\r\n  private:\r\n    int _n;\r\n    // root node: -1 * component size\r\
    \n    // otherwise: parent\r\n    std::vector<int> parent_or_size;\r\n};\r\n\r\
    \n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_DSU_HPP\r\n#define ATCODER_DSU_HPP 1\r\n\r\n#include <algorithm>\r\
    \n#include <cassert>\r\n#include <vector>\r\n\r\nnamespace atcoder {\r\n\r\n//\
    \ Implement (union by size) + (path compression)\r\n// Reference:\r\n// Zvi Galil\
    \ and Giuseppe F. Italiano,\r\n// Data structures and algorithms for disjoint\
    \ set union problems\r\nstruct dsu {\r\n  public:\r\n    dsu() : _n(0) {}\r\n\
    \    dsu(int n) : _n(n), parent_or_size(n, -1) {}\r\n\r\n    int merge(int a,\
    \ int b) {\r\n        assert(0 <= a && a < _n);\r\n        assert(0 <= b && b\
    \ < _n);\r\n        int x = leader(a), y = leader(b);\r\n        if (x == y) return\
    \ x;\r\n        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);\r\
    \n        parent_or_size[x] += parent_or_size[y];\r\n        parent_or_size[y]\
    \ = x;\r\n        return x;\r\n    }\r\n\r\n    bool same(int a, int b) {\r\n\
    \        assert(0 <= a && a < _n);\r\n        assert(0 <= b && b < _n);\r\n  \
    \      return leader(a) == leader(b);\r\n    }\r\n\r\n    int leader(int a) {\r\
    \n        assert(0 <= a && a < _n);\r\n        if (parent_or_size[a] < 0) return\
    \ a;\r\n        return parent_or_size[a] = leader(parent_or_size[a]);\r\n    }\r\
    \n\r\n    int size(int a) {\r\n        assert(0 <= a && a < _n);\r\n        return\
    \ -parent_or_size[leader(a)];\r\n    }\r\n\r\n    std::vector<std::vector<int>>\
    \ groups() {\r\n        std::vector<int> leader_buf(_n), group_size(_n);\r\n \
    \       for (int i = 0; i < _n; i++) {\r\n            leader_buf[i] = leader(i);\r\
    \n            group_size[leader_buf[i]]++;\r\n        }\r\n        std::vector<std::vector<int>>\
    \ result(_n);\r\n        for (int i = 0; i < _n; i++) {\r\n            result[i].reserve(group_size[i]);\r\
    \n        }\r\n        for (int i = 0; i < _n; i++) {\r\n            result[leader_buf[i]].push_back(i);\r\
    \n        }\r\n        result.erase(\r\n            std::remove_if(result.begin(),\
    \ result.end(),\r\n                           [&](const std::vector<int>& v) {\
    \ return v.empty(); }),\r\n            result.end());\r\n        return result;\r\
    \n    }\r\n\r\n  private:\r\n    int _n;\r\n    // root node: -1 * component size\r\
    \n    // otherwise: parent\r\n    std::vector<int> parent_or_size;\r\n};\r\n\r\
    \n}  // namespace atcoder\r\n\r\n#endif  // ATCODER_DSU_HPP\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/atcoder/dsu.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/dsu.hpp
layout: document
redirect_from:
- /library/lib/atcoder/dsu.hpp
- /library/lib/atcoder/dsu.hpp.html
title: lib/atcoder/dsu.hpp
---
