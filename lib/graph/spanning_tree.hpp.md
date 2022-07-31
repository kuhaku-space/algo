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
    document_title: "\u5168\u57DF\u6728"
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
  code: "#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\n\n/**\n\
    \ * @brief \u5168\u57DF\u6728\n * @details \u5168\u57DF\u6728\u3092\u69CB\u7BC9\
    \u3059\u308B\n *\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\n * @param\
    \ g \u30B0\u30E9\u30D5\n * @param r \u59CB\u70B9\n * @return Graph<T>\n */\ntemplate\
    \ <class T>\nGraph<T> spanning_tree(const Graph<T> &g, int r = 0) {\n    int n\
    \ = g.size();\n    Graph<T> res(n);\n    std::queue<int> que;\n    std::vector<bool>\
    \ visited(n);\n    que.emplace(r);\n    visited[r] = true;\n    while (!que.empty())\
    \ {\n        auto x = que.front();\n        que.pop();\n        for (auto &e :\
    \ g[x]) {\n            if (!visited[e.to()]) {\n                res.add_edges(e);\n\
    \                que.emplace(e.to());\n                visited[e.to()] = true;\n\
    \            }\n        }\n    }\n    return res;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/spanning_tree.hpp
  requiredBy: []
  timestamp: '2022-07-30 08:42:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/spanning_tree.hpp
layout: document
redirect_from:
- /library/lib/graph/spanning_tree.hpp
- /library/lib/graph/spanning_tree.hpp.html
title: "\u5168\u57DF\u6728"
---
