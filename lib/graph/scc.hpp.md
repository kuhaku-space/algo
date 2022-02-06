---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/graph/two_sat.hpp
    title: lib/graph/two_sat.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph.hpp\"\r\n\r\n\
    // verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_C 21/02/24\r\n\r\n\
    template <class T>\r\nvector<int> scc(const Graph<T> &g) {\r\n    int n = g.size();\r\
    \n    Graph<T> rg(n);\r\n    vector<int> comp(n, -1), order;\r\n    vector<bool>\
    \ used(n);\r\n\r\n    for (auto &es : g) {\r\n        for (auto &e : es) rg.add_edge(e.to,\
    \ e.from);\r\n    }\r\n\r\n    auto dfs = [&](auto self, int idx) {\r\n      \
    \  if (used[idx]) return;\r\n        used[idx] = true;\r\n        for (auto &e\
    \ : g[idx]) self(self, e.to);\r\n        order.emplace_back(idx);\r\n    };\r\n\
    \    auto rdfs = [&](auto self, int idx, int cnt) {\r\n        if (~comp[idx])\
    \ return;\r\n        comp[idx] = cnt;\r\n        for (auto &e : rg[idx]) self(self,\
    \ e.to, cnt);\r\n    };\r\n\r\n    for (int i = 0; i < n; i++) dfs(dfs, i);\r\n\
    \    reverse(order.begin(), order.end());\r\n    int ptr = 0;\r\n    for (auto\
    \ i : order) {\r\n        if (comp[i] == -1) rdfs(rdfs, i, ptr++);\r\n    }\r\n\
    \r\n    return comp;\r\n};\r\n\r\ntemplate <class T>\r\nGraph<T> make_DAG(const\
    \ Graph<T> &g, const vector<int> &v) {\r\n    Graph<T> res(*max_element(v.begin(),\
    \ v.end()) + 1);\r\n    for (auto &es : g) {\r\n        for (auto &e : es) {\r\
    \n            int x = v[e.from], y = v[e.to];\r\n            if (x != y) res.add_edge(x,\
    \ y, e.dist);\r\n        }\r\n    }\r\n    return res;\r\n}\r\n\r\nvector<int>\
    \ scc(const Graph<void> &g) {\r\n    int n = g.size();\r\n    Graph<void> rg(n);\r\
    \n    vector<int> comp(n, -1), order;\r\n    vector<bool> used(n);\r\n\r\n   \
    \ for (int i = 0; i < n; ++i) {\r\n        for (auto &e : g[i]) rg.add_edge(e,\
    \ i);\r\n    }\r\n\r\n    auto dfs = [&](auto self, int idx) {\r\n        if (used[idx])\
    \ return;\r\n        used[idx] = true;\r\n        for (auto &e : g[idx]) self(self,\
    \ e);\r\n        order.emplace_back(idx);\r\n    };\r\n    auto rdfs = [&](auto\
    \ self, int idx, int cnt) {\r\n        if (~comp[idx]) return;\r\n        comp[idx]\
    \ = cnt;\r\n        for (auto &e : rg[idx]) self(self, e, cnt);\r\n    };\r\n\r\
    \n    for (int i = 0; i < n; i++) dfs(dfs, i);\r\n    reverse(order.begin(), order.end());\r\
    \n    int ptr = 0;\r\n    for (auto i : order) {\r\n        if (comp[i] == -1)\
    \ rdfs(rdfs, i, ptr++);\r\n    }\r\n\r\n    return comp;\r\n};\r\n\r\nGraph<void>\
    \ make_DAG(const Graph<void> &g, const vector<int> &v) {\r\n    int n = g.size();\r\
    \n    Graph<void> res(*max_element(v.begin(), v.end()) + 1);\r\n    for (int i\
    \ = 0; i < n; ++i) {\r\n        for (auto &e : g[i]) {\r\n            int x =\
    \ v[i], y = v[e];\r\n            if (x != y) res.add_edge(x, y);\r\n        }\r\
    \n    }\r\n    return res;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/graph/scc.hpp
  requiredBy:
  - lib/graph/two_sat.hpp
  timestamp: '2022-01-14 01:42:22+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/scc.hpp
layout: document
redirect_from:
- /library/lib/graph/scc.hpp
- /library/lib/graph/scc.hpp.html
title: lib/graph/scc.hpp
---
