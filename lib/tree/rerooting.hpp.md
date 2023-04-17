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
    document_title: "\u5168\u65B9\u4F4D\u6728dp"
    links:
    - https://algo-logic.info/tree-dp/
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\
    \n\n/**\n * @brief \u5168\u65B9\u4F4D\u6728dp\n * @see https://algo-logic.info/tree-dp/\n\
    \ *\n * @tparam M \u30E2\u30CE\u30A4\u30C9\n * @tparam T \u8FBA\u306E\u91CD\u307F\
    \u306E\u578B\n */\ntemplate <class M, class T>\nstruct ReRooting {\n  private:\n\
    \    using Value = typename M::value_type;\n\n  public:\n    ReRooting(const Graph<T>\
    \ &g) : graph(g), dp(g.size()), data(g.size()) { this->build(); }\n\n    const\
    \ auto &operator[](int i) const { return this->data[i]; }\n    auto &operator[](int\
    \ i) { return this->data[i]; }\n    const auto begin() const { return this->data.begin();\
    \ }\n    auto begin() { return this->data.begin(); }\n    const auto end() const\
    \ { return this->data.end(); }\n    auto end() { return this->data.end(); }\n\n\
    \  private:\n    Graph<T> graph;\n    std::vector<std::vector<Value>> dp;\n  \
    \  std::vector<Value> data;\n\n    void build() {\n        this->dfs(0);\n   \
    \     this->bfs(0);\n    }\n\n    Value dfs(int v, int p = -1) {\n        Value\
    \ res = M::id;\n        int deg = graph[v].size();\n        dp[v] = std::vector<Value>(deg,\
    \ M::id);\n        for (int i = 0; i < deg; ++i) {\n            auto e = graph[v][i];\n\
    \            if (e.to() == p) continue;\n            dp[v][i] = M::f(dfs(e.to(),\
    \ v), e.weight());\n            res = M::op(res, dp[v][i]);\n        }\n     \
    \   return M::g(res, v);\n    }\n    void bfs(int v, int p = -1, Value dp_p =\
    \ M::id) {\n        int deg = graph[v].size();\n        std::vector<Value> dp_r(deg\
    \ + 1, M::id);\n        for (int i = deg - 1; i >= 0; --i) {\n            auto\
    \ e = graph[v][i];\n            if (e.to() == p) dp[v][i] = M::f(dp_p, e.weight());\n\
    \            dp_r[i] = M::op(dp[v][i], dp_r[i + 1]);\n        }\n        Value\
    \ dp_l = M::id;\n        for (int i = 0; i < deg; ++i) {\n            int u =\
    \ graph[v][i].to();\n            if (u != p) this->bfs(u, v, M::g(M::op(dp_l,\
    \ dp_r[i + 1]), v));\n            dp_l = M::op(dp_l, dp[v][i]);\n        }\n \
    \       data[v] = M::g(dp_l, v);\n    }\n};\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/rerooting.hpp
  requiredBy: []
  timestamp: '2022-07-30 08:42:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/rerooting.hpp
layout: document
redirect_from:
- /library/lib/tree/rerooting.hpp
- /library/lib/tree/rerooting.hpp.html
title: "\u5168\u65B9\u4F4D\u6728dp"
---
