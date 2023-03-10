---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/graph/two_sat.hpp
    title: 2-SAT
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/scc.test.cpp
    title: test/aoj/grl/scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/graph/scc.test.cpp
    title: test/yosupo/graph/scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/two_sat.test.cpp
    title: test/yosupo/math/two_sat.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\r\n#include \"template/template.hpp\"\r\n\r\n\
    /**\r\n * @brief \u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3\r\n *\r\n * @tparam\
    \ T \u8FBA\u306E\u91CD\u307F\u306E\u578B\r\n * @param g \u30B0\u30E9\u30D5\r\n\
    \ * @return std::vector<int> \u5404\u9802\u70B9\u304C\u5C5E\u3059\u308B\u5F37\u9023\
    \u7D50\u6210\u5206\u306E\u756A\u53F7\r\n */\r\ntemplate <class T>\r\nstd::vector<int>\
    \ scc(const Graph<T> &g) {\r\n    int n = g.size();\r\n    Graph<void> rg(n);\r\
    \n    std::vector<int> comp(n, -1), order;\r\n    std::vector<bool> used(n);\r\
    \n\r\n    for (auto &es : g) {\r\n        for (auto &e : es) rg.add_edge(e.to(),\
    \ e.from());\r\n    }\r\n\r\n    auto dfs = [&](auto self, int index) {\r\n  \
    \      if (used[index]) return;\r\n        used[index] = true;\r\n        for\
    \ (auto &e : g[index]) self(self, e.to());\r\n        order.emplace_back(index);\r\
    \n    };\r\n    auto rdfs = [&](auto self, int index, int count) {\r\n       \
    \ if (~comp[index]) return;\r\n        comp[index] = count;\r\n        for (auto\
    \ &e : rg[index]) self(self, e.to(), count);\r\n    };\r\n\r\n    for (int i =\
    \ 0; i < n; ++i) dfs(dfs, i);\r\n    std::reverse(order.begin(), order.end());\r\
    \n    int ptr = 0;\r\n    for (auto i : order) {\r\n        if (comp[i] == -1)\
    \ rdfs(rdfs, i, ptr++);\r\n    }\r\n\r\n    return comp;\r\n};\r\n\r\n/**\r\n\
    \ * @brief \u6709\u5411\u975E\u5DE1\u56DE\u30B0\u30E9\u30D5\u306E\u69CB\u7BC9\r\
    \n *\r\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\r\n * @param g \u30B0\
    \u30E9\u30D5\r\n * @param v \u5404\u9802\u70B9\u304C\u5C5E\u3059\u308B\u5F37\u9023\
    \u7D50\u6210\u5206\u306E\u756A\u53F7\r\n * @return Graph<T> \u6709\u5411\u975E\
    \u5DE1\u56DE\u30B0\u30E9\u30D5\r\n */\r\ntemplate <class T>\r\nGraph<T> make_DAG(const\
    \ Graph<T> &g, const std::vector<int> &v) {\r\n    Graph<T> res(*std::max_element(v.begin(),\
    \ v.end()) + 1);\r\n    for (auto &es : g) {\r\n        for (auto &e : es) {\r\
    \n            int x = v[e.from()], y = v[e.to()];\r\n            if (x != y) res.add_edge(x,\
    \ y, e.weight());\r\n        }\r\n    }\r\n    return res;\r\n}\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/scc.hpp
  requiredBy:
  - lib/graph/two_sat.hpp
  timestamp: '2022-07-30 08:42:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/graph/scc.test.cpp
  - test/yosupo/math/two_sat.test.cpp
  - test/aoj/grl/scc.test.cpp
documentation_of: lib/graph/scc.hpp
layout: document
redirect_from:
- /library/lib/graph/scc.hpp
- /library/lib/graph/scc.hpp.html
title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3"
---
