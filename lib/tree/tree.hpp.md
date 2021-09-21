---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':question:'
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
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph.hpp\"\r\n\r\n\
    template <class T>\r\nstruct Tree {\r\n    Graph<T> g;\r\n    vector<int> parent;\r\
    \n\r\n    Tree(const Graph<T> &_g, int r = 0) : g(_g), parent(_g.size()) { build(r)\
    \ }\r\n\r\n    void build(int r = 0) {\r\n        struct node {\r\n          \
    \  int v, p, d;\r\n        };\r\n        stack<node> st;\r\n        st.push(node{r,\
    \ -1, 0});\r\n        while (!st.empty()) {\r\n            auto [v, p, d] = st.top();\r\
    \n            st.pop();\r\n            parent[v] = p;\r\n            for (auto\
    \ i : data[v]) {\r\n                if (i == p) continue;\r\n                st.push(node{i,\
    \ v, d + 1});\r\n            }\r\n        }\r\n    }\r\n\r\n    void bfs(int s)\
    \ {\r\n        struct node {\r\n            int v, p;\r\n        };\r\n      \
    \  stack<node> st;\r\n        st.push(node{s, -1});\r\n        while (!st.empty())\
    \ {\r\n            auto [v, p] = st.top();\r\n            st.pop();\r\n      \
    \      parent[v] = p;\r\n            for (auto i : data[v]) {\r\n            \
    \    if (i == p) continue;\r\n                st.push(node{i, v});\r\n       \
    \     }\r\n        }\r\n    }\r\n\r\n    void dfs(int v, int p) {\r\n        for\
    \ (auto i : data[v]) {\r\n            if (i == p) continue;\r\n            dfs(i,\
    \ v);\r\n        }\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/tree/tree.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/tree.hpp
layout: document
redirect_from:
- /library/lib/tree/tree.hpp
- /library/lib/tree/tree.hpp.html
title: lib/tree/tree.hpp
---
