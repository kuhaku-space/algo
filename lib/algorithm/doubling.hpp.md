---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/doubling.test.cpp
    title: test/aoj/jag/doubling.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1013.test.cpp
    title: test/yukicoder/1013.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1097.test.cpp
    title: test/yukicoder/1097.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1242.2.test.cpp
    title: test/yukicoder/1242.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1977.test.cpp
    title: test/yukicoder/1977.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30C0\u30D6\u30EA\u30F3\u30B0"
    links: []
  bundledCode: "#line 1 \"lib/algorithm/doubling.hpp\"\n#include <cassert>\r\n#include\
    \ <cstdint>\r\n#include <utility>\r\n#include <vector>\r\n\r\n/**\r\n * @brief\
    \ \u30C0\u30D6\u30EA\u30F3\u30B0\r\n *\r\n * @tparam L\r\n * @tparam Monoid \u30E2\
    \u30CE\u30A4\u30C9\r\n */\r\ntemplate <int L, class Monoid = void>\r\nstruct Doubling\
    \ {\r\n  private:\r\n    using T = typename Monoid::value_type;\r\n\r\n  public:\r\
    \n    template <class U>\r\n    Doubling(const std::vector<int> &to, const std::vector<U>\
    \ &v) : Doubling(to.size()) {\r\n        build(to, v);\r\n    }\r\n    std::pair<int,\
    \ T> jump(int f, std::uint64_t k) { return solve(f, k); }\r\n    std::pair<int,\
    \ T> solve(int f, std::uint64_t k) {\r\n        assert(-1 <= f && f < _size);\r\
    \n        T res = Monoid::id;\r\n        for (int cnt = 0; k > 0; k >>= 1, ++cnt)\
    \ {\r\n            if ((k & 1) && f != -1) {\r\n                res = Monoid::op(res,\
    \ data[cnt][f]);\r\n                f = table[cnt][f];\r\n            }\r\n  \
    \      }\r\n        return std::make_pair(f, res);\r\n    }\r\n\r\n  private:\r\
    \n    int _size;\r\n    std::vector<std::vector<int>> table;\r\n    std::vector<std::vector<T>>\
    \ data;\r\n\r\n    Doubling(int n) : _size(n), table(L, std::vector<int>(n)),\
    \ data(L, std::vector<T>(n)) {}\r\n\r\n    template <class U>\r\n    void build(const\
    \ std::vector<int> &to, const std::vector<U> &v) {\r\n        assert(to.size()\
    \ == v.size());\r\n        for (int i = 0; i < _size; ++i) {\r\n            assert(-1\
    \ <= to[i] && to[i] < _size);\r\n            table[0][i] = to[i];\r\n        \
    \    data[0][i] = v[i];\r\n        }\r\n\r\n        for (int i = 0; i < L - 1;\
    \ ++i) {\r\n            for (int j = 0; j < _size; ++j) {\r\n                int\
    \ k = table[i][j];\r\n                if (k != -1) {\r\n                    table[i\
    \ + 1][j] = table[i][k];\r\n                    data[i + 1][j] = Monoid::op(data[i][j],\
    \ data[i][k]);\r\n                } else {\r\n                    table[i + 1][j]\
    \ = table[i][j];\r\n                    data[i + 1][j] = data[i][j];\r\n     \
    \           }\r\n            }\r\n        }\r\n    }\r\n};\r\n\r\n/**\r\n * @brief\
    \ \u30C0\u30D6\u30EA\u30F3\u30B0\r\n *\r\n * @tparam L\r\n */\r\ntemplate <int\
    \ L>\r\nstruct Doubling<L, void> {\r\n    Doubling(const std::vector<int> &v)\
    \ : Doubling(v.size()) { build(v); }\r\n\r\n    int jump(int f, std::uint64_t\
    \ k) { return solve(f, k); }\r\n    int solve(int f, std::uint64_t k) {\r\n  \
    \      assert(-1 <= f && f < _size);\r\n        for (int cnt = 0; k > 0; k >>=\
    \ 1, ++cnt) {\r\n            if ((k & 1) && f != -1) f = table[cnt][f];\r\n  \
    \      }\r\n        return f;\r\n    }\r\n\r\n  private:\r\n    int _size;\r\n\
    \    std::vector<std::vector<int>> table;\r\n\r\n    Doubling(int n) : _size(n),\
    \ table(L, std::vector<int>(n)) {}\r\n\r\n    void build(const std::vector<int>\
    \ &v) {\r\n        for (int i = 0; i < _size; ++i) {\r\n            assert(-1\
    \ <= v[i] && v[i] < _size);\r\n            table[0][i] = v[i];\r\n        }\r\n\
    \r\n        for (int i = 0; i < L - 1; ++i) {\r\n            for (int j = 0; j\
    \ < _size; ++j) {\r\n                if (table[i][j] != -1) table[i + 1][j] =\
    \ table[i][table[i][j]];\r\n            }\r\n        }\r\n    }\r\n};\r\n"
  code: "#include <cassert>\r\n#include <cstdint>\r\n#include <utility>\r\n#include\
    \ <vector>\r\n\r\n/**\r\n * @brief \u30C0\u30D6\u30EA\u30F3\u30B0\r\n *\r\n *\
    \ @tparam L\r\n * @tparam Monoid \u30E2\u30CE\u30A4\u30C9\r\n */\r\ntemplate <int\
    \ L, class Monoid = void>\r\nstruct Doubling {\r\n  private:\r\n    using T =\
    \ typename Monoid::value_type;\r\n\r\n  public:\r\n    template <class U>\r\n\
    \    Doubling(const std::vector<int> &to, const std::vector<U> &v) : Doubling(to.size())\
    \ {\r\n        build(to, v);\r\n    }\r\n    std::pair<int, T> jump(int f, std::uint64_t\
    \ k) { return solve(f, k); }\r\n    std::pair<int, T> solve(int f, std::uint64_t\
    \ k) {\r\n        assert(-1 <= f && f < _size);\r\n        T res = Monoid::id;\r\
    \n        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {\r\n            if ((k & 1)\
    \ && f != -1) {\r\n                res = Monoid::op(res, data[cnt][f]);\r\n  \
    \              f = table[cnt][f];\r\n            }\r\n        }\r\n        return\
    \ std::make_pair(f, res);\r\n    }\r\n\r\n  private:\r\n    int _size;\r\n   \
    \ std::vector<std::vector<int>> table;\r\n    std::vector<std::vector<T>> data;\r\
    \n\r\n    Doubling(int n) : _size(n), table(L, std::vector<int>(n)), data(L, std::vector<T>(n))\
    \ {}\r\n\r\n    template <class U>\r\n    void build(const std::vector<int> &to,\
    \ const std::vector<U> &v) {\r\n        assert(to.size() == v.size());\r\n   \
    \     for (int i = 0; i < _size; ++i) {\r\n            assert(-1 <= to[i] && to[i]\
    \ < _size);\r\n            table[0][i] = to[i];\r\n            data[0][i] = v[i];\r\
    \n        }\r\n\r\n        for (int i = 0; i < L - 1; ++i) {\r\n            for\
    \ (int j = 0; j < _size; ++j) {\r\n                int k = table[i][j];\r\n  \
    \              if (k != -1) {\r\n                    table[i + 1][j] = table[i][k];\r\
    \n                    data[i + 1][j] = Monoid::op(data[i][j], data[i][k]);\r\n\
    \                } else {\r\n                    table[i + 1][j] = table[i][j];\r\
    \n                    data[i + 1][j] = data[i][j];\r\n                }\r\n  \
    \          }\r\n        }\r\n    }\r\n};\r\n\r\n/**\r\n * @brief \u30C0\u30D6\u30EA\
    \u30F3\u30B0\r\n *\r\n * @tparam L\r\n */\r\ntemplate <int L>\r\nstruct Doubling<L,\
    \ void> {\r\n    Doubling(const std::vector<int> &v) : Doubling(v.size()) { build(v);\
    \ }\r\n\r\n    int jump(int f, std::uint64_t k) { return solve(f, k); }\r\n  \
    \  int solve(int f, std::uint64_t k) {\r\n        assert(-1 <= f && f < _size);\r\
    \n        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {\r\n            if ((k & 1)\
    \ && f != -1) f = table[cnt][f];\r\n        }\r\n        return f;\r\n    }\r\n\
    \r\n  private:\r\n    int _size;\r\n    std::vector<std::vector<int>> table;\r\
    \n\r\n    Doubling(int n) : _size(n), table(L, std::vector<int>(n)) {}\r\n\r\n\
    \    void build(const std::vector<int> &v) {\r\n        for (int i = 0; i < _size;\
    \ ++i) {\r\n            assert(-1 <= v[i] && v[i] < _size);\r\n            table[0][i]\
    \ = v[i];\r\n        }\r\n\r\n        for (int i = 0; i < L - 1; ++i) {\r\n  \
    \          for (int j = 0; j < _size; ++j) {\r\n                if (table[i][j]\
    \ != -1) table[i + 1][j] = table[i][table[i][j]];\r\n            }\r\n       \
    \ }\r\n    }\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/algorithm/doubling.hpp
  requiredBy: []
  timestamp: '2023-10-01 20:08:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yukicoder/1242.2.test.cpp
  - test/yukicoder/1977.test.cpp
  - test/yukicoder/1097.test.cpp
  - test/yukicoder/1013.test.cpp
  - test/aoj/jag/doubling.test.cpp
documentation_of: lib/algorithm/doubling.hpp
layout: document
redirect_from:
- /library/lib/algorithm/doubling.hpp
- /library/lib/algorithm/doubling.hpp.html
title: "\u30C0\u30D6\u30EA\u30F3\u30B0"
---
