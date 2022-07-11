---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u6728\u306E\u8DDD\u96E2\u3092\u6C42\u3081\u308B"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\n\ntemplate\
    \ <class T>\nstd::vector<int> tree_bfs(const Graph<T> &g, int r = 0) {\n    int\
    \ pos = 0;\n    std::vector<int> res;\n    std::vector<bool> visited(g.size());\n\
    \    res.emplace_back(r);\n    visited[r] = true;\n    while (pos < res.size())\
    \ {\n        auto index = res[pos++];\n        for (auto &e : g[index]) {\n  \
    \          if (visited[e.to()]) continue;\n            res.emplace_back(e.to());\n\
    \            visited[e.to()] = true;\n        }\n    }\n    return res;\n}\n\n\
    template <class T>\nstd::vector<int> tree_dfs(const Graph<T> &g, int r = 0) {\n\
    \    std::vector<int> res;\n    auto dfs = [&g, &res](auto self, int index, int\
    \ parent) {\n        res.emplace_back(index);\n        for (auto &e : g[index])\
    \ {\n            if (e.to() == parent) continue;\n            self(self, e.to(),\
    \ index);\n        }\n    };\n    dfs(dfs, r, -1);\n    return res;\n}\n\n/**\n\
    \ * @brief \u6728\u306E\u8DDD\u96E2\u3092\u6C42\u3081\u308B\n *\n * @tparam T\
    \ \u8FBA\u306E\u91CD\u307F\u306E\u578B\n * @param g \u6728\n * @param r \u6839\
    \n * @return std::vector<int>\n */\ntemplate <class T>\nstd::vector<int> tree_dist(const\
    \ Graph<T> &g, int r = 0) {\n    std::vector<int> res(g.size(), -1);\n    std::stack<int>\
    \ st;\n    res[r] = 0;\n    st.emplace(r);\n    while (!st.empty()) {\n      \
    \  auto index = st.top();\n        st.pop();\n        for (auto &e : g[index])\
    \ {\n            if (res[e.to()] != -1) continue;\n            res[e.to()] = res[index]\
    \ + e.weight();\n            st.emplace(e.to());\n        }\n    }\n    return\
    \ res;\n}\n\n/**\n * @brief \u6728\u306E\u9802\u70B9\u306E\u89AA\u3092\u6C42\u3081\
    \u308B\n *\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\n * @param g \u6728\
    \n * @param r \u6839\n * @return std::vector<int>\n */\ntemplate <class T>\nstd::vector<int>\
    \ tree_parent(const Graph<T> &g, int r = 0) {\n    std::vector<int> res(g.size(),\
    \ -2);\n    std::stack<int> st;\n    res[r] = -1;\n    st.emplace(r);\n    while\
    \ (!st.empty()) {\n        auto index = st.top();\n        st.pop();\n       \
    \ for (auto &e : g[index]) {\n            if (res[e.to()] != -2) continue;\n \
    \           res[e.to()] = index;\n            st.emplace(e.to());\n        }\n\
    \    }\n    return res;\n}\n\n/**\n * @brief \u90E8\u5206\u6728\u306E\u5927\u304D\
    \u3055\u3092\u6C42\u3081\u308B\n *\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\
    \u578B\n * @param g \u30B0\u30E9\u30D5\n * @param r \u6839\n * @return std::vector<int>\n\
    \ */\ntemplate <class T>\nstd::vector<int> tree_subtree(const Graph<T> &g, int\
    \ r = 0) {\n    std::vector<int> res(g.size());\n    auto dfs = [&g, &res](auto\
    \ self, int index) {\n        res[index] = 1;\n        for (auto &e : g[index])\
    \ {\n            if (res[e.to()] != 0) continue;\n            res[index] += self(self,\
    \ e.to());\n        }\n        return res[index];\n    };\n    dfs(dfs, r);\n\
    \    return res;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/tree_function.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/tree_function.hpp
layout: document
redirect_from:
- /library/lib/tree/tree_function.hpp
- /library/lib/tree/tree_function.hpp.html
title: "\u6728\u306E\u8DDD\u96E2\u3092\u6C42\u3081\u308B"
---
