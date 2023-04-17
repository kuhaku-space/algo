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
    document_title: "\u91CD\u5FC3\u5206\u89E3"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\n\n/**\n\
    \ * @brief \u91CD\u5FC3\u5206\u89E3\n *\n * @tparam T \u8FBA\u306E\u91CD\u307F\
    \u306E\u578B\n * @param g \u30B0\u30E9\u30D5\n * @return std::vector<int> \u89AA\
    \u306E\u9802\u70B9\n */\ntemplate <class T>\nstd::vector<int> centroid_decomposition(const\
    \ Graph<T> &g) {\n    int n = g.size();\n    std::vector<int> par(n, -1), size(n),\
    \ size_par(n, -2);\n    std::vector<bool> used(n, false);\n    auto dfs = [&](auto\
    \ self, int x, int p) -> int {\n        if (size_par[x] == p) return size[x];\n\
    \        int sum = 1;\n        for (auto e : g[x]) {\n            if (used[e.to()]\
    \ || e.to() == p) continue;\n            sum += self(self, e.to(), x);\n     \
    \   }\n        size_par[x] = p;\n        return size[x] = sum;\n    };\n    auto\
    \ build = [&](auto self, int x, int p) -> void {\n        int sz = dfs(dfs, x,\
    \ p);\n        bool is_centroid = false;\n        while (!is_centroid) {\n   \
    \         is_centroid = true;\n            for (auto e : g[x]) {\n           \
    \     if (size[e.to()] > size[x] || size[e.to()] * 2 <= sz) continue;\n      \
    \          x = e.to();\n                is_centroid = false;\n               \
    \ break;\n            }\n        }\n        par[x] = p;\n        used[x] = true;\n\
    \        for (auto e : g[x]) {\n            if (used[e.to()]) continue;\n    \
    \        self(self, e.to(), x);\n        }\n    };\n\n    build(build, 0, -1);\n\
    \n    return par;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/centroid_decomposition.hpp
  requiredBy: []
  timestamp: '2023-03-08 14:44:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/centroid_decomposition.hpp
layout: document
redirect_from:
- /library/lib/tree/centroid_decomposition.hpp
- /library/lib/tree/centroid_decomposition.hpp.html
title: "\u91CD\u5FC3\u5206\u89E3"
---
