---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/atcoder/internal_scc.hpp
    title: lib/atcoder/internal_scc.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/scc.hpp\"\n\n\n\r\n#include <algorithm>\r\n\
    #include <atcoder/internal_scc>\r\n#include <cassert>\r\n#include <vector>\r\n\
    \r\nnamespace atcoder {\r\n\r\nstruct scc_graph {\r\n  public:\r\n    scc_graph()\
    \ : internal(0) {}\r\n    scc_graph(int n) : internal(n) {}\r\n\r\n    void add_edge(int\
    \ from, int to) {\r\n        int n = internal.num_vertices();\r\n        assert(0\
    \ <= from && from < n);\r\n        assert(0 <= to && to < n);\r\n        internal.add_edge(from,\
    \ to);\r\n    }\r\n\r\n    std::vector<std::vector<int>> scc() { return internal.scc();\
    \ }\r\n\r\n  private:\r\n    internal::scc_graph internal;\r\n};\r\n\r\n}  //\
    \ namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_SCC_HPP\r\n#define ATCODER_SCC_HPP 1\r\n\r\n#include <algorithm>\r\
    \n#include <atcoder/internal_scc>\r\n#include <cassert>\r\n#include <vector>\r\
    \n\r\nnamespace atcoder {\r\n\r\nstruct scc_graph {\r\n  public:\r\n    scc_graph()\
    \ : internal(0) {}\r\n    scc_graph(int n) : internal(n) {}\r\n\r\n    void add_edge(int\
    \ from, int to) {\r\n        int n = internal.num_vertices();\r\n        assert(0\
    \ <= from && from < n);\r\n        assert(0 <= to && to < n);\r\n        internal.add_edge(from,\
    \ to);\r\n    }\r\n\r\n    std::vector<std::vector<int>> scc() { return internal.scc();\
    \ }\r\n\r\n  private:\r\n    internal::scc_graph internal;\r\n};\r\n\r\n}  //\
    \ namespace atcoder\r\n\r\n#endif  // ATCODER_SCC_HPP\r\n"
  dependsOn:
  - lib/atcoder/internal_scc.hpp
  isVerificationFile: false
  path: lib/atcoder/scc.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/scc.hpp
layout: document
redirect_from:
- /library/lib/atcoder/scc.hpp
- /library/lib/atcoder/scc.hpp.html
title: lib/atcoder/scc.hpp
---
