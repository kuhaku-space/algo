---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/aupc/namori_graph.test.cpp
    title: test/aoj/aupc/namori_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include <stack>\n#include <vector>\n#include \"graph/graph.hpp\"\n\ntemplate\
    \ <class T>\nstd::vector<int> cycle_detection_on_namori_graph(const Graph<T> &g)\
    \ {\n    int n = g.size();\n    std::vector<int> cnt(n);\n    std::stack<int>\
    \ st;\n    for (int i = 0; i < n; ++i) {\n        cnt[i] = g[i].size();\n    \
    \    if (cnt[i] == 1) st.emplace(i);\n    }\n    while (!st.empty()) {\n     \
    \   int x = st.top();\n        st.pop();\n        for (auto &e : g[x]) {\n   \
    \         if ((--cnt[e.to()]) == 1) st.emplace(e.to());\n        }\n    }\n\n\
    \    std::vector<int> parent(n, -2);\n    st = std::stack<int>();\n    for (int\
    \ i = 0; i < n; ++i) {\n        if (cnt[i] >= 2) {\n            parent[i] = -1;\n\
    \            st.emplace(i);\n        }\n    }\n\n    while (!st.empty()) {\n \
    \       int x = st.top();\n        st.pop();\n        for (auto &e : g[x]) {\n\
    \            if (parent[e.to()] == -2) {\n                parent[e.to()] = x;\n\
    \                st.emplace(e.to());\n            }\n        }\n    }\n\n    return\
    \ parent;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/graph/namori_graph.hpp
  requiredBy: []
  timestamp: '2024-04-17 13:11:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/aupc/namori_graph.test.cpp
documentation_of: lib/graph/namori_graph.hpp
layout: document
redirect_from:
- /library/lib/graph/namori_graph.hpp
- /library/lib/graph/namori_graph.hpp.html
title: lib/graph/namori_graph.hpp
---
