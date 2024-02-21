---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/graph/functional_graph.hpp
    title: lib/graph/functional_graph.hpp
  - icon: ':heavy_check_mark:'
    path: lib/graph/kruskal.hpp
    title: "\u30AF\u30E9\u30B9\u30AB\u30EB\u6CD5"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/union_find.test.cpp
    title: test/aoj/dsl/union_find.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/kruskal.test.cpp
    title: test/aoj/grl/kruskal.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/unionfind.test.cpp
    title: test/yosupo/data_structure/unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1211.test.cpp
    title: test/yukicoder/1211.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1242.test.cpp
    title: test/yukicoder/1242.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
    links:
    - https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
  bundledCode: "#line 1 \"lib/tree/union_find.hpp\"\n#include <utility>\r\n#include\
    \ <vector>\r\n\r\n/**\r\n * @brief \u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020\
    \r\n * @details Implement (union by size) + (path compression)\r\n * @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp\r\
    \n */\r\nstruct union_find {\r\n    union_find() = default;\r\n    explicit union_find(int\
    \ _n) : _rank(_n), data(_n, -1) {}\r\n\r\n    int root(int x) { return data[x]\
    \ < 0 ? x : data[x] = root(data[x]); }\r\n    int get_root(int x) { return root(x);\
    \ }\r\n\r\n    bool is_root(int x) const { return data[x] < 0; }\r\n\r\n    bool\
    \ same(int x, int y) { return root(x) == root(y); }\r\n    bool is_same(int x,\
    \ int y) { return same(x, y); }\r\n\r\n    int rank() { return _rank; }\r\n\r\n\
    \    int size(int x) { return -(data[root(x)]); }\r\n    int get_size(int x) {\
    \ return size(x); }\r\n\r\n    std::vector<int> leaders() {\r\n        std::vector<int>\
    \ res;\r\n        for (int i = 0; i < (int)data.size(); ++i) {\r\n           \
    \ if (is_root(i)) res.emplace_back(i);\r\n        }\r\n        return res;\r\n\
    \    }\r\n\r\n    bool unite(int x, int y) {\r\n        x = root(x), y = root(y);\r\
    \n        if (x == y) return false;\r\n        --_rank;\r\n        if (data[x]\
    \ > data[y]) std::swap(x, y);\r\n        data[x] += data[y];\r\n        data[y]\
    \ = x;\r\n        return true;\r\n    }\r\n\r\n    template <class F>\r\n    bool\
    \ unite(int x, int y, F f) {\r\n        x = root(x), y = root(y);\r\n        if\
    \ (x != y) {\r\n            if (data[x] > data[y]) std::swap(x, y);\r\n      \
    \      data[x] += data[y];\r\n            data[y] = x;\r\n        }\r\n      \
    \  f(x, y);\r\n        return x != y;\r\n    }\r\n\r\n  private:\r\n    int _rank;\r\
    \n    std::vector<int> data;\r\n};\r\n"
  code: "#include <utility>\r\n#include <vector>\r\n\r\n/**\r\n * @brief \u7D20\u96C6\
    \u5408\u30C7\u30FC\u30BF\u69CB\u9020\r\n * @details Implement (union by size)\
    \ + (path compression)\r\n * @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp\r\
    \n */\r\nstruct union_find {\r\n    union_find() = default;\r\n    explicit union_find(int\
    \ _n) : _rank(_n), data(_n, -1) {}\r\n\r\n    int root(int x) { return data[x]\
    \ < 0 ? x : data[x] = root(data[x]); }\r\n    int get_root(int x) { return root(x);\
    \ }\r\n\r\n    bool is_root(int x) const { return data[x] < 0; }\r\n\r\n    bool\
    \ same(int x, int y) { return root(x) == root(y); }\r\n    bool is_same(int x,\
    \ int y) { return same(x, y); }\r\n\r\n    int rank() { return _rank; }\r\n\r\n\
    \    int size(int x) { return -(data[root(x)]); }\r\n    int get_size(int x) {\
    \ return size(x); }\r\n\r\n    std::vector<int> leaders() {\r\n        std::vector<int>\
    \ res;\r\n        for (int i = 0; i < (int)data.size(); ++i) {\r\n           \
    \ if (is_root(i)) res.emplace_back(i);\r\n        }\r\n        return res;\r\n\
    \    }\r\n\r\n    bool unite(int x, int y) {\r\n        x = root(x), y = root(y);\r\
    \n        if (x == y) return false;\r\n        --_rank;\r\n        if (data[x]\
    \ > data[y]) std::swap(x, y);\r\n        data[x] += data[y];\r\n        data[y]\
    \ = x;\r\n        return true;\r\n    }\r\n\r\n    template <class F>\r\n    bool\
    \ unite(int x, int y, F f) {\r\n        x = root(x), y = root(y);\r\n        if\
    \ (x != y) {\r\n            if (data[x] > data[y]) std::swap(x, y);\r\n      \
    \      data[x] += data[y];\r\n            data[y] = x;\r\n        }\r\n      \
    \  f(x, y);\r\n        return x != y;\r\n    }\r\n\r\n  private:\r\n    int _rank;\r\
    \n    std::vector<int> data;\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/tree/union_find.hpp
  requiredBy:
  - lib/graph/kruskal.hpp
  - lib/graph/functional_graph.hpp
  timestamp: '2024-02-04 08:44:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yukicoder/1211.test.cpp
  - test/yukicoder/1242.test.cpp
  - test/yosupo/data_structure/unionfind.test.cpp
  - test/aoj/dsl/union_find.test.cpp
  - test/aoj/grl/kruskal.test.cpp
documentation_of: lib/tree/union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/union_find.hpp
- /library/lib/tree/union_find.hpp.html
title: "\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
---
