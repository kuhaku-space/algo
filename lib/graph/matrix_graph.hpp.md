---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/graph/chromatic_number.hpp
    title: "\u5F69\u8272\u6570\u3092\u6C42\u3081\u308B"
  - icon: ':heavy_check_mark:'
    path: lib/graph/warshall_floyd.hpp
    title: lib/graph/warshall_floyd.hpp
  - icon: ':warning:'
    path: test/aoj/jag/hopcroft_karp.cpp
    title: test/aoj/jag/hopcroft_karp.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/warshall_floyd.test.cpp
    title: test/aoj/grl/warshall_floyd.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/graph/chromatic_number.test.cpp
    title: test/yosupo/graph/chromatic_number.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u96A3\u63A5\u884C\u5217"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief\
    \ \u96A3\u63A5\u884C\u5217\r\n *\r\n * @tparam T\r\n */\r\ntemplate <class T>\r\
    \nstruct matrix_graph {\r\n    matrix_graph(int v, T e = T()) : _size(v), m(v,\
    \ std::vector<T>(v, e)) {}\r\n\r\n    const auto &operator[](int i) const { return\
    \ this->m[i]; }\r\n    auto &operator[](int i) { return this->m[i]; }\r\n    const\
    \ auto begin() const { return this->m.begin(); }\r\n    auto begin() { return\
    \ this->m.begin(); }\r\n    const auto end() const { return this->m.end(); }\r\
    \n    auto end() { return this->m.end(); }\r\n\r\n    constexpr int size() const\
    \ { return this->_size; }\r\n\r\n    void add_edge(int a, int b, T d = T(1)) {\
    \ this->m[a][b] = d; }\r\n    void add_edges(int a, int b, T d = T(1)) { this->m[a][b]\
    \ = this->m[b][a] = d; }\r\n\r\n    void input_edge(int m, int base = 1) {\r\n\
    \        for (int i = 0; i < m; ++i) {\r\n            int from, to;\r\n      \
    \      T weight;\r\n            std::cin >> from >> to >> weight;\r\n        \
    \    this->add_edge(from - base, to - base, weight);\r\n        }\r\n    }\r\n\
    \    void input_edges(int m, int base = 1) {\r\n        for (int i = 0; i < m;\
    \ ++i) {\r\n            int from, to;\r\n            T weight;\r\n           \
    \ std::cin >> from >> to >> weight;\r\n            this->add_edges(from - base,\
    \ to - base, weight);\r\n        }\r\n    }\r\n\r\n  private:\r\n    int _size;\r\
    \n    std::vector<std::vector<T>> m;\r\n};\r\n\r\ntemplate <>\r\nstruct matrix_graph<void>\
    \ {\r\n    matrix_graph(int v) : _size(v), m(v, std::vector<bool>(v)) {}\r\n\r\
    \n    const auto &operator[](int i) const { return this->m[i]; }\r\n    auto &operator[](int\
    \ i) { return this->m[i]; }\r\n    const auto begin() const { return this->m.begin();\
    \ }\r\n    auto begin() { return this->m.begin(); }\r\n    const auto end() const\
    \ { return this->m.end(); }\r\n    auto end() { return this->m.end(); }\r\n\r\n\
    \    constexpr int size() const { return this->_size; }\r\n\r\n    void add_edge(int\
    \ a, int b) { this->m[a][b] = true; }\r\n    void add_edges(int a, int b) { this->m[a][b]\
    \ = this->m[b][a] = true; }\r\n\r\n    void input_edge(int m, int base = 1) {\r\
    \n        for (int i = 0; i < m; ++i) {\r\n            int from, to;\r\n     \
    \       std::cin >> from >> to;\r\n            this->add_edge(from - base, to\
    \ - base);\r\n        }\r\n    }\r\n    void input_edges(int m, int base = 1)\
    \ {\r\n        for (int i = 0; i < m; ++i) {\r\n            int from, to;\r\n\
    \            std::cin >> from >> to;\r\n            this->add_edges(from - base,\
    \ to - base);\r\n        }\r\n    }\r\n\r\n    void complement() {\r\n       \
    \ for (int i = 0; i < this->_size; ++i) {\r\n            for (int j = 0; j < this->_size;\
    \ ++j) this->m[i][j] = !this->m[i][j];\r\n        }\r\n    }\r\n\r\n  private:\r\
    \n    int _size;\r\n    std::vector<std::vector<bool>> m;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/matrix_graph.hpp
  requiredBy:
  - lib/graph/chromatic_number.hpp
  - lib/graph/warshall_floyd.hpp
  - test/aoj/jag/hopcroft_karp.cpp
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/warshall_floyd.test.cpp
  - test/yosupo/graph/chromatic_number.test.cpp
documentation_of: lib/graph/matrix_graph.hpp
layout: document
redirect_from:
- /library/lib/graph/matrix_graph.hpp
- /library/lib/graph/matrix_graph.hpp.html
title: "\u96A3\u63A5\u884C\u5217"
---
