---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/bipartite_matching.2.test.cpp
    title: test/aoj/grl/bipartite_matching.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/hopcroft_karp.test.cpp
    title: test/aoj/jag/hopcroft_karp.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/graph/matching_on_bipartite_garph.2.test.cpp
    title: test/yosupo/graph/matching_on_bipartite_garph.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Hopcroft-Karp algorithm
    links:
    - https://judge.yosupo.jp/submission/99577
  bundledCode: "#line 1 \"lib/flow/hopcroft_karp.hpp\"\n#include <cassert>\n#include\
    \ <utility>\n#include <vector>\n\n/**\n * @brief Hopcroft-Karp algorithm\n * @see\
    \ https://judge.yosupo.jp/submission/99577\n */\nstruct hopcroft_karp {\n    hopcroft_karp(int\
    \ _n, int _m) : n(_n), m(_m), g(_n), match_left(_n, -1), match_right(_m, -1) {}\n\
    \n    void add_edge(int u, int v) {\n        assert(0 <= u && u < n);\n      \
    \  assert(0 <= v && v < m);\n        g[u].emplace_back(v);\n    }\n\n    int matching()\
    \ {\n        int flow = 0;\n        std::vector<int> root(n), prev(n), qq(n);\n\
    \        for (bool updated = true; updated;) {\n            updated = false;\n\
    \            int qi = 0, qj = 0;\n            std::fill(root.begin(), root.end(),\
    \ -1);\n            std::fill(prev.begin(), prev.end(), -1);\n            for\
    \ (int i = 0; i < n; i++) {\n                if (match_left[i] == -1) qq[qj++]\
    \ = i, root[i] = i, prev[i] = i;\n            }\n            while (qi < qj) {\n\
    \                int u = qq[qi++];\n                if (match_left[root[u]] !=\
    \ -1) continue;\n                for (int v : g[u]) {\n                    if\
    \ (match_right[v] == -1) {\n                        while (v != -1)\n        \
    \                    match_right[v] = u, std::swap(match_left[u], v), u = prev[u];\n\
    \                        updated = true, flow++;\n                        break;\n\
    \                    }\n\n                    if (prev[match_right[v]] == -1)\n\
    \                        v = match_right[v], prev[v] = u, root[v] = root[u], qq[qj++]\
    \ = v;\n                }\n            }\n        }\n        return flow;\n  \
    \  }\n\n    std::vector<std::pair<int, int>> get_pairs() const {\n        std::vector<std::pair<int,\
    \ int>> res;\n        for (int i = 0; i < n; i++) {\n            if (~match_left[i])\
    \ res.emplace_back(i, match_left[i]);\n        }\n        return res;\n    }\n\
    \n  private:\n    const int n, m;\n    std::vector<std::vector<int>> g;\n    std::vector<int>\
    \ match_left, match_right;\n};\n"
  code: "#include <cassert>\n#include <utility>\n#include <vector>\n\n/**\n * @brief\
    \ Hopcroft-Karp algorithm\n * @see https://judge.yosupo.jp/submission/99577\n\
    \ */\nstruct hopcroft_karp {\n    hopcroft_karp(int _n, int _m) : n(_n), m(_m),\
    \ g(_n), match_left(_n, -1), match_right(_m, -1) {}\n\n    void add_edge(int u,\
    \ int v) {\n        assert(0 <= u && u < n);\n        assert(0 <= v && v < m);\n\
    \        g[u].emplace_back(v);\n    }\n\n    int matching() {\n        int flow\
    \ = 0;\n        std::vector<int> root(n), prev(n), qq(n);\n        for (bool updated\
    \ = true; updated;) {\n            updated = false;\n            int qi = 0, qj\
    \ = 0;\n            std::fill(root.begin(), root.end(), -1);\n            std::fill(prev.begin(),\
    \ prev.end(), -1);\n            for (int i = 0; i < n; i++) {\n              \
    \  if (match_left[i] == -1) qq[qj++] = i, root[i] = i, prev[i] = i;\n        \
    \    }\n            while (qi < qj) {\n                int u = qq[qi++];\n   \
    \             if (match_left[root[u]] != -1) continue;\n                for (int\
    \ v : g[u]) {\n                    if (match_right[v] == -1) {\n             \
    \           while (v != -1)\n                            match_right[v] = u, std::swap(match_left[u],\
    \ v), u = prev[u];\n                        updated = true, flow++;\n        \
    \                break;\n                    }\n\n                    if (prev[match_right[v]]\
    \ == -1)\n                        v = match_right[v], prev[v] = u, root[v] = root[u],\
    \ qq[qj++] = v;\n                }\n            }\n        }\n        return flow;\n\
    \    }\n\n    std::vector<std::pair<int, int>> get_pairs() const {\n        std::vector<std::pair<int,\
    \ int>> res;\n        for (int i = 0; i < n; i++) {\n            if (~match_left[i])\
    \ res.emplace_back(i, match_left[i]);\n        }\n        return res;\n    }\n\
    \n  private:\n    const int n, m;\n    std::vector<std::vector<int>> g;\n    std::vector<int>\
    \ match_left, match_right;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/flow/hopcroft_karp.hpp
  requiredBy: []
  timestamp: '2023-12-09 13:20:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/graph/matching_on_bipartite_garph.2.test.cpp
  - test/aoj/jag/hopcroft_karp.test.cpp
  - test/aoj/grl/bipartite_matching.2.test.cpp
documentation_of: lib/flow/hopcroft_karp.hpp
layout: document
redirect_from:
- /library/lib/flow/hopcroft_karp.hpp
- /library/lib/flow/hopcroft_karp.hpp.html
title: Hopcroft-Karp algorithm
---
