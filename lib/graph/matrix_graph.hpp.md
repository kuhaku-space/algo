---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/graph/chromatic_number.hpp
    title: "\u5F69\u8272\u6570\u3092\u6C42\u3081\u308B"
  - icon: ':heavy_check_mark:'
    path: lib/graph/warshall_floyd.hpp
    title: lib/graph/warshall_floyd.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/warshall_floyd.test.cpp
    title: test/aoj/grl/warshall_floyd.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/hopcroft_karp.test.cpp
    title: test/aoj/jag/hopcroft_karp.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/graph/chromatic_number.test.cpp
    title: test/yosupo/graph/chromatic_number.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u96A3\u63A5\u884C\u5217"
    links: []
  bundledCode: "#line 2 \"lib/graph/matrix_graph.hpp\"\n#include <iostream>\r\n#include\
    \ <vector>\r\n\r\n/**\r\n * @brief \u96A3\u63A5\u884C\u5217\r\n *\r\n * @tparam\
    \ T\r\n */\r\ntemplate <class T>\r\nstruct matrix_graph {\r\n    matrix_graph(int\
    \ v, T e = T()) : _size(v), m(v, std::vector<T>(v, e)) {}\r\n\r\n    const auto\
    \ &operator[](int i) const { return m[i]; }\r\n    auto &operator[](int i) { return\
    \ m[i]; }\r\n    const auto begin() const { return m.begin(); }\r\n    auto begin()\
    \ { return m.begin(); }\r\n    const auto end() const { return m.end(); }\r\n\
    \    auto end() { return m.end(); }\r\n\r\n    constexpr int size() const { return\
    \ _size; }\r\n\r\n    void add_edge(int a, int b, T d = T(1)) { m[a][b] = d; }\r\
    \n    void add_edges(int a, int b, T d = T(1)) { m[a][b] = m[b][a] = d; }\r\n\r\
    \n    void input_edge(int m, int base = 1) {\r\n        for (int i = 0; i < m;\
    \ ++i) {\r\n            int from, to;\r\n            T weight;\r\n           \
    \ std::cin >> from >> to >> weight;\r\n            add_edge(from - base, to -\
    \ base, weight);\r\n        }\r\n    }\r\n    void input_edges(int m, int base\
    \ = 1) {\r\n        for (int i = 0; i < m; ++i) {\r\n            int from, to;\r\
    \n            T weight;\r\n            std::cin >> from >> to >> weight;\r\n \
    \           add_edges(from - base, to - base, weight);\r\n        }\r\n    }\r\
    \n\r\n  private:\r\n    int _size;\r\n    std::vector<std::vector<T>> m;\r\n};\r\
    \n\r\ntemplate <>\r\nstruct matrix_graph<void> {\r\n    matrix_graph(int v) :\
    \ _size(v), m(v, std::vector<bool>(v)) {}\r\n\r\n    const auto &operator[](int\
    \ i) const { return m[i]; }\r\n    auto &operator[](int i) { return m[i]; }\r\n\
    \    const auto begin() const { return m.begin(); }\r\n    auto begin() { return\
    \ m.begin(); }\r\n    const auto end() const { return m.end(); }\r\n    auto end()\
    \ { return m.end(); }\r\n\r\n    constexpr int size() const { return _size; }\r\
    \n\r\n    void add_edge(int a, int b) { m[a][b] = true; }\r\n    void add_edges(int\
    \ a, int b) { m[a][b] = m[b][a] = true; }\r\n\r\n    void input_edge(int m, int\
    \ base = 1) {\r\n        for (int i = 0; i < m; ++i) {\r\n            int from,\
    \ to;\r\n            std::cin >> from >> to;\r\n            add_edge(from - base,\
    \ to - base);\r\n        }\r\n    }\r\n    void input_edges(int m, int base =\
    \ 1) {\r\n        for (int i = 0; i < m; ++i) {\r\n            int from, to;\r\
    \n            std::cin >> from >> to;\r\n            add_edges(from - base, to\
    \ - base);\r\n        }\r\n    }\r\n\r\n    void complement() {\r\n        for\
    \ (int i = 0; i < _size; ++i) {\r\n            for (int j = 0; j < _size; ++j)\
    \ m[i][j] = !m[i][j];\r\n        }\r\n    }\r\n\r\n  private:\r\n    int _size;\r\
    \n    std::vector<std::vector<bool>> m;\r\n};\r\n"
  code: "#pragma once\r\n#include <iostream>\r\n#include <vector>\r\n\r\n/**\r\n *\
    \ @brief \u96A3\u63A5\u884C\u5217\r\n *\r\n * @tparam T\r\n */\r\ntemplate <class\
    \ T>\r\nstruct matrix_graph {\r\n    matrix_graph(int v, T e = T()) : _size(v),\
    \ m(v, std::vector<T>(v, e)) {}\r\n\r\n    const auto &operator[](int i) const\
    \ { return m[i]; }\r\n    auto &operator[](int i) { return m[i]; }\r\n    const\
    \ auto begin() const { return m.begin(); }\r\n    auto begin() { return m.begin();\
    \ }\r\n    const auto end() const { return m.end(); }\r\n    auto end() { return\
    \ m.end(); }\r\n\r\n    constexpr int size() const { return _size; }\r\n\r\n \
    \   void add_edge(int a, int b, T d = T(1)) { m[a][b] = d; }\r\n    void add_edges(int\
    \ a, int b, T d = T(1)) { m[a][b] = m[b][a] = d; }\r\n\r\n    void input_edge(int\
    \ m, int base = 1) {\r\n        for (int i = 0; i < m; ++i) {\r\n            int\
    \ from, to;\r\n            T weight;\r\n            std::cin >> from >> to >>\
    \ weight;\r\n            add_edge(from - base, to - base, weight);\r\n       \
    \ }\r\n    }\r\n    void input_edges(int m, int base = 1) {\r\n        for (int\
    \ i = 0; i < m; ++i) {\r\n            int from, to;\r\n            T weight;\r\
    \n            std::cin >> from >> to >> weight;\r\n            add_edges(from\
    \ - base, to - base, weight);\r\n        }\r\n    }\r\n\r\n  private:\r\n    int\
    \ _size;\r\n    std::vector<std::vector<T>> m;\r\n};\r\n\r\ntemplate <>\r\nstruct\
    \ matrix_graph<void> {\r\n    matrix_graph(int v) : _size(v), m(v, std::vector<bool>(v))\
    \ {}\r\n\r\n    const auto &operator[](int i) const { return m[i]; }\r\n    auto\
    \ &operator[](int i) { return m[i]; }\r\n    const auto begin() const { return\
    \ m.begin(); }\r\n    auto begin() { return m.begin(); }\r\n    const auto end()\
    \ const { return m.end(); }\r\n    auto end() { return m.end(); }\r\n\r\n    constexpr\
    \ int size() const { return _size; }\r\n\r\n    void add_edge(int a, int b) {\
    \ m[a][b] = true; }\r\n    void add_edges(int a, int b) { m[a][b] = m[b][a] =\
    \ true; }\r\n\r\n    void input_edge(int m, int base = 1) {\r\n        for (int\
    \ i = 0; i < m; ++i) {\r\n            int from, to;\r\n            std::cin >>\
    \ from >> to;\r\n            add_edge(from - base, to - base);\r\n        }\r\n\
    \    }\r\n    void input_edges(int m, int base = 1) {\r\n        for (int i =\
    \ 0; i < m; ++i) {\r\n            int from, to;\r\n            std::cin >> from\
    \ >> to;\r\n            add_edges(from - base, to - base);\r\n        }\r\n  \
    \  }\r\n\r\n    void complement() {\r\n        for (int i = 0; i < _size; ++i)\
    \ {\r\n            for (int j = 0; j < _size; ++j) m[i][j] = !m[i][j];\r\n   \
    \     }\r\n    }\r\n\r\n  private:\r\n    int _size;\r\n    std::vector<std::vector<bool>>\
    \ m;\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/graph/matrix_graph.hpp
  requiredBy:
  - lib/graph/chromatic_number.hpp
  - lib/graph/warshall_floyd.hpp
  timestamp: '2024-05-03 20:12:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/jag/hopcroft_karp.test.cpp
  - test/aoj/grl/warshall_floyd.test.cpp
  - test/yosupo/graph/chromatic_number.test.cpp
documentation_of: lib/graph/matrix_graph.hpp
layout: document
redirect_from:
- /library/lib/graph/matrix_graph.hpp
- /library/lib/graph/matrix_graph.hpp.html
title: "\u96A3\u63A5\u884C\u5217"
---
