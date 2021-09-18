---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/atcoder/internal_type_traits.hpp
    title: lib/atcoder/internal_type_traits.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Fenwick_tree
  bundledCode: "#line 1 \"lib/atcoder/fenwicktree.hpp\"\n\n\n\r\n#include <atcoder/internal_type_traits>\r\
    \n#include <cassert>\r\n#include <vector>\r\n\r\nnamespace atcoder {\r\n\r\n//\
    \ Reference: https://en.wikipedia.org/wiki/Fenwick_tree\r\ntemplate <class T>\
    \ struct fenwick_tree {\r\n    using U = internal::to_unsigned_t<T>;\r\n\r\n \
    \ public:\r\n    fenwick_tree() : _n(0) {}\r\n    fenwick_tree(int n) : _n(n),\
    \ data(n) {}\r\n\r\n    void add(int p, T x) {\r\n        assert(0 <= p && p <\
    \ _n);\r\n        p++;\r\n        while (p <= _n) {\r\n            data[p - 1]\
    \ += U(x);\r\n            p += p & -p;\r\n        }\r\n    }\r\n\r\n    T sum(int\
    \ l, int r) {\r\n        assert(0 <= l && l <= r && r <= _n);\r\n        return\
    \ sum(r) - sum(l);\r\n    }\r\n\r\n  private:\r\n    int _n;\r\n    std::vector<U>\
    \ data;\r\n\r\n    U sum(int r) {\r\n        U s = 0;\r\n        while (r > 0)\
    \ {\r\n            s += data[r - 1];\r\n            r -= r & -r;\r\n        }\r\
    \n        return s;\r\n    }\r\n};\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_FENWICKTREE_HPP\r\n#define ATCODER_FENWICKTREE_HPP 1\r\n\r\
    \n#include <atcoder/internal_type_traits>\r\n#include <cassert>\r\n#include <vector>\r\
    \n\r\nnamespace atcoder {\r\n\r\n// Reference: https://en.wikipedia.org/wiki/Fenwick_tree\r\
    \ntemplate <class T> struct fenwick_tree {\r\n    using U = internal::to_unsigned_t<T>;\r\
    \n\r\n  public:\r\n    fenwick_tree() : _n(0) {}\r\n    fenwick_tree(int n) :\
    \ _n(n), data(n) {}\r\n\r\n    void add(int p, T x) {\r\n        assert(0 <= p\
    \ && p < _n);\r\n        p++;\r\n        while (p <= _n) {\r\n            data[p\
    \ - 1] += U(x);\r\n            p += p & -p;\r\n        }\r\n    }\r\n\r\n    T\
    \ sum(int l, int r) {\r\n        assert(0 <= l && l <= r && r <= _n);\r\n    \
    \    return sum(r) - sum(l);\r\n    }\r\n\r\n  private:\r\n    int _n;\r\n   \
    \ std::vector<U> data;\r\n\r\n    U sum(int r) {\r\n        U s = 0;\r\n     \
    \   while (r > 0) {\r\n            s += data[r - 1];\r\n            r -= r & -r;\r\
    \n        }\r\n        return s;\r\n    }\r\n};\r\n\r\n}  // namespace atcoder\r\
    \n\r\n#endif  // ATCODER_FENWICKTREE_HPP\r\n"
  dependsOn:
  - lib/atcoder/internal_type_traits.hpp
  isVerificationFile: false
  path: lib/atcoder/fenwicktree.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/fenwicktree.hpp
layout: document
redirect_from:
- /library/lib/atcoder/fenwicktree.hpp
- /library/lib/atcoder/fenwicktree.hpp.html
title: lib/atcoder/fenwicktree.hpp
---
