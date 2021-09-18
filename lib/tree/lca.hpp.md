---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\nstruct Tree {\r\n    int64_t V,\
    \ logV;\r\n    vector<vector<int64_t>> data;\r\n    vector<int64_t> depth;\r\n\
    \    vector<vector<int64_t>> parent;\r\n\r\n    Tree(int64_t v) : V(v), logV(0)\
    \ {\r\n        while (V > (1LL << logV)) ++logV;\r\n        data = vector<vector<int64_t>>(V);\r\
    \n        depth = vector<int64_t>(V);\r\n        parent = vector<vector<int64_t>>(logV,\
    \ vector<int64_t>(V));\r\n    }\r\n\r\n    void init(int64_t r) {\r\n        struct\
    \ node {\r\n            int64_t v, p, d;\r\n        };\r\n        stack<node>\
    \ st;\r\n        st.push(node{r, -1, 0});\r\n        while (!st.empty()) {\r\n\
    \            auto [v, p, d] = st.top();\r\n            st.pop();\r\n         \
    \   depth[v] = d;\r\n            parent[0][v] = p;\r\n            for (auto i\
    \ : data[v]) {\r\n                if (i == p) continue;\r\n                st.push(node{i,\
    \ v, d + 1});\r\n            }\r\n        }\r\n    }\r\n\r\n    void build(int64_t\
    \ r = 0) {\r\n        this->init(r);\r\n        for (int64_t k = 0; k < logV -\
    \ 1; ++k) {\r\n            for (int64_t v = 0; v < V; ++v) {\r\n             \
    \   if (parent[k][v] < 0)\r\n                    parent[k + 1][v] = -1;\r\n  \
    \              else\r\n                    parent[k + 1][v] = parent[k][parent[k][v]];\r\
    \n            }\r\n        }\r\n    }\r\n\r\n    void add_edge(int64_t a, int64_t\
    \ b) {\r\n        data[a].emplace_back(b);\r\n        data[b].emplace_back(a);\r\
    \n    }\r\n\r\n    int64_t lca(int64_t u, int64_t v) {\r\n        if (depth[u]\
    \ > depth[v]) swap(u, v);\r\n        for (int64_t k = 0; k < logV; ++k) {\r\n\
    \            if ((depth[v] - depth[u]) >> k & 1) v = parent[k][v];\r\n       \
    \ }\r\n        if (u == v) return u;\r\n\r\n        for (int64_t k = logV - 1;\
    \ k >= 0; --k) {\r\n            if (parent[k][u] != parent[k][v]) {\r\n      \
    \          u = parent[k][u];\r\n                v = parent[k][v];\r\n        \
    \    }\r\n        }\r\n        return parent[0][u];\r\n    }\r\n\r\n    int64_t\
    \ get_depth(int64_t a) { return depth[a]; }\r\n    int64_t get_parent(int64_t\
    \ a) { return parent[0][a]; }\r\n\r\n    int64_t get_ancestor(int64_t a, int64_t\
    \ d) {\r\n        for (int64_t k = 0; d; d >>= 1, ++k) {\r\n            if (d\
    \ & 1) a = parent[k][a];\r\n        }\r\n        return a;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/lca.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/lca.hpp
layout: document
redirect_from:
- /library/lib/tree/lca.hpp
- /library/lib/tree/lca.hpp.html
title: lib/tree/lca.hpp
---
