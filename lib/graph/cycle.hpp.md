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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/cycle.test.cpp
    title: test/aoj/grl/cycle.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9589\u8DEF\u691C\u51FA"
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
  code: "#pragma once\n#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\
    \n\n/**\n * @brief \u9589\u8DEF\u691C\u51FA\n *\n * @tparam T \u8FBA\u306E\u91CD\
    \u307F\u306E\u578B\n * @param g \u30B0\u30E9\u30D5\n * @retval true \u9589\u8DEF\
    \u3042\u308A\n * @retval false \u9589\u8DEF\u306A\u3057\n */\ntemplate <class\
    \ T>\nbool has_cycle(const Graph<T> &g) {\n    int n = g.size();\n    std::vector<bool>\
    \ seen(n), finished(n);\n    bool res = false;\n\n    auto dfs = [&](auto self,\
    \ int index) {\n        if (finished[index]) return;\n        seen[index] = true;\n\
    \        for (auto &e : g[index]) {\n            if (res |= seen[e.to()]) return;\n\
    \            self(self, e.to());\n        }\n        seen[index] = false;\n  \
    \      finished[index] = true;\n    };\n\n    for (int i = 0; i < n; ++i) {\n\
    \        if (res) break;\n        dfs(dfs, i);\n    }\n    return res;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/cycle.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/cycle.test.cpp
documentation_of: lib/graph/cycle.hpp
layout: document
redirect_from:
- /library/lib/graph/cycle.hpp
- /library/lib/graph/cycle.hpp.html
title: "\u9589\u8DEF\u691C\u51FA"
---
