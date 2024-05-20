---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/0416.test.cpp
    title: test/yukicoder/0416.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u90E8\u5206\u6C38\u7D9AUnion-Find"
    links: []
  bundledCode: "#line 1 \"lib/tree/partially_persistent_union_find.hpp\"\n#include\
    \ <algorithm>\r\n#include <iterator>\r\n#include <utility>\r\n#include <vector>\r\
    \n\r\n/**\r\n * @brief \u90E8\u5206\u6C38\u7D9AUnion-Find\r\n *\r\n */\r\nstruct\
    \ partially_persistent_union_find {\r\n    partially_persistent_union_find(int\
    \ _n)\r\n        : _now(0), _data(_n, std::vector<std::pair<int, int>>(1, {0,\
    \ -1})) {}\r\n\r\n    int root(int x) const { return root(x, _now); }\r\n    int\
    \ root(int x, int t) const {\r\n        auto p = _data[x].back();\r\n        if\
    \ (p.first > t || p.second < 0) return x;\r\n        return root(p.second, t);\r\
    \n    }\r\n    int get_root(int x, int t) const { return root(x, t); }\r\n\r\n\
    \    bool is_root(int x, int t) const {\r\n        return _data[x].back().first\
    \ > t || _data[x].back().second < 0;\r\n    }\r\n\r\n    bool same(int x, int\
    \ y) const { return same(x, y, _now); }\r\n    bool same(int x, int y, int t)\
    \ const { return root(x, t) == root(y, t); }\r\n    bool is_same(int x, int y,\
    \ int t) const { return same(x, y, t); }\r\n\r\n    int size(int x) const { return\
    \ size(x, _now); }\r\n    int size(int x, int t) const {\r\n        x = root(x,\
    \ t);\r\n        return -std::prev(std::upper_bound(_data[x].begin(), _data[x].end(),\r\
    \n                                           std::pair<int, int>{t, _data.size()}))\r\
    \n                    ->second;\r\n    }\r\n    int get_size(int x, int t) const\
    \ { return size(x, t); }\r\n\r\n    int unite(int x, int y) {\r\n        ++_now;\r\
    \n        x = root(x, _now), y = root(y, _now);\r\n        if (x == y) return\
    \ false;\r\n        auto p = _data[x].back(), q = _data[y].back();\r\n       \
    \ if (p.second > q.second) std::swap(x, y), std::swap(p, q);\r\n        _data[x].emplace_back(_now,\
    \ p.second + q.second);\r\n        _data[y].emplace_back(_now, x);\r\n       \
    \ return true;\r\n    }\r\n\r\n  private:\r\n    int _now;\r\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _data;\r\n};\r\n"
  code: "#include <algorithm>\r\n#include <iterator>\r\n#include <utility>\r\n#include\
    \ <vector>\r\n\r\n/**\r\n * @brief \u90E8\u5206\u6C38\u7D9AUnion-Find\r\n *\r\n\
    \ */\r\nstruct partially_persistent_union_find {\r\n    partially_persistent_union_find(int\
    \ _n)\r\n        : _now(0), _data(_n, std::vector<std::pair<int, int>>(1, {0,\
    \ -1})) {}\r\n\r\n    int root(int x) const { return root(x, _now); }\r\n    int\
    \ root(int x, int t) const {\r\n        auto p = _data[x].back();\r\n        if\
    \ (p.first > t || p.second < 0) return x;\r\n        return root(p.second, t);\r\
    \n    }\r\n    int get_root(int x, int t) const { return root(x, t); }\r\n\r\n\
    \    bool is_root(int x, int t) const {\r\n        return _data[x].back().first\
    \ > t || _data[x].back().second < 0;\r\n    }\r\n\r\n    bool same(int x, int\
    \ y) const { return same(x, y, _now); }\r\n    bool same(int x, int y, int t)\
    \ const { return root(x, t) == root(y, t); }\r\n    bool is_same(int x, int y,\
    \ int t) const { return same(x, y, t); }\r\n\r\n    int size(int x) const { return\
    \ size(x, _now); }\r\n    int size(int x, int t) const {\r\n        x = root(x,\
    \ t);\r\n        return -std::prev(std::upper_bound(_data[x].begin(), _data[x].end(),\r\
    \n                                           std::pair<int, int>{t, _data.size()}))\r\
    \n                    ->second;\r\n    }\r\n    int get_size(int x, int t) const\
    \ { return size(x, t); }\r\n\r\n    int unite(int x, int y) {\r\n        ++_now;\r\
    \n        x = root(x, _now), y = root(y, _now);\r\n        if (x == y) return\
    \ false;\r\n        auto p = _data[x].back(), q = _data[y].back();\r\n       \
    \ if (p.second > q.second) std::swap(x, y), std::swap(p, q);\r\n        _data[x].emplace_back(_now,\
    \ p.second + q.second);\r\n        _data[y].emplace_back(_now, x);\r\n       \
    \ return true;\r\n    }\r\n\r\n  private:\r\n    int _now;\r\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _data;\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/tree/partially_persistent_union_find.hpp
  requiredBy: []
  timestamp: '2024-05-04 03:07:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yukicoder/0416.test.cpp
documentation_of: lib/tree/partially_persistent_union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/partially_persistent_union_find.hpp
- /library/lib/tree/partially_persistent_union_find.hpp.html
title: "\u90E8\u5206\u6C38\u7D9AUnion-Find"
---
