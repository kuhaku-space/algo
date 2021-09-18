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
  bundledCode: "#line 1 \"lib/atcoder/twosat.hpp\"\n\n\n\r\n#include <atcoder/internal_scc>\r\
    \n#include <cassert>\r\n#include <vector>\r\n\r\nnamespace atcoder {\r\n\r\n//\
    \ Reference:\r\n// B. Aspvall, M. Plass, and R. Tarjan,\r\n// A Linear-Time Algorithm\
    \ for Testing the Truth of Certain Quantified Boolean\r\n// Formulas\r\nstruct\
    \ two_sat {\r\n  public:\r\n    two_sat() : _n(0), scc(0) {}\r\n    two_sat(int\
    \ n) : _n(n), _answer(n), scc(2 * n) {}\r\n\r\n    void add_clause(int i, bool\
    \ f, int j, bool g) {\r\n        assert(0 <= i && i < _n);\r\n        assert(0\
    \ <= j && j < _n);\r\n        scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1\
    \ : 0));\r\n        scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));\r\n\
    \    }\r\n    bool satisfiable() {\r\n        auto id = scc.scc_ids().second;\r\
    \n        for (int i = 0; i < _n; i++) {\r\n            if (id[2 * i] == id[2\
    \ * i + 1]) return false;\r\n            _answer[i] = id[2 * i] < id[2 * i + 1];\r\
    \n        }\r\n        return true;\r\n    }\r\n    std::vector<bool> answer()\
    \ { return _answer; }\r\n\r\n  private:\r\n    int _n;\r\n    std::vector<bool>\
    \ _answer;\r\n    internal::scc_graph scc;\r\n};\r\n\r\n}  // namespace atcoder\r\
    \n\r\n\n"
  code: "#ifndef ATCODER_TWOSAT_HPP\r\n#define ATCODER_TWOSAT_HPP 1\r\n\r\n#include\
    \ <atcoder/internal_scc>\r\n#include <cassert>\r\n#include <vector>\r\n\r\nnamespace\
    \ atcoder {\r\n\r\n// Reference:\r\n// B. Aspvall, M. Plass, and R. Tarjan,\r\n\
    // A Linear-Time Algorithm for Testing the Truth of Certain Quantified Boolean\r\
    \n// Formulas\r\nstruct two_sat {\r\n  public:\r\n    two_sat() : _n(0), scc(0)\
    \ {}\r\n    two_sat(int n) : _n(n), _answer(n), scc(2 * n) {}\r\n\r\n    void\
    \ add_clause(int i, bool f, int j, bool g) {\r\n        assert(0 <= i && i < _n);\r\
    \n        assert(0 <= j && j < _n);\r\n        scc.add_edge(2 * i + (f ? 0 : 1),\
    \ 2 * j + (g ? 1 : 0));\r\n        scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f\
    \ ? 1 : 0));\r\n    }\r\n    bool satisfiable() {\r\n        auto id = scc.scc_ids().second;\r\
    \n        for (int i = 0; i < _n; i++) {\r\n            if (id[2 * i] == id[2\
    \ * i + 1]) return false;\r\n            _answer[i] = id[2 * i] < id[2 * i + 1];\r\
    \n        }\r\n        return true;\r\n    }\r\n    std::vector<bool> answer()\
    \ { return _answer; }\r\n\r\n  private:\r\n    int _n;\r\n    std::vector<bool>\
    \ _answer;\r\n    internal::scc_graph scc;\r\n};\r\n\r\n}  // namespace atcoder\r\
    \n\r\n#endif  // ATCODER_TWOSAT_HPP\r\n"
  dependsOn:
  - lib/atcoder/internal_scc.hpp
  isVerificationFile: false
  path: lib/atcoder/twosat.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/twosat.hpp
layout: document
redirect_from:
- /library/lib/atcoder/twosat.hpp
- /library/lib/atcoder/twosat.hpp.html
title: lib/atcoder/twosat.hpp
---
