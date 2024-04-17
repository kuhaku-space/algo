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
    path: test/yosupo/graph/maximum_independent_set.test.cpp
    title: test/yosupo/graph/maximum_independent_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5927\u72EC\u7ACB\u96C6\u5408"
    links:
    - https://www.slideshare.net/wata_orz/ss-12131479
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\
    \n\n/**\n * @brief \u6700\u5927\u72EC\u7ACB\u96C6\u5408\n * @see https://www.slideshare.net/wata_orz/ss-12131479\n\
    \ *\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\n * @param graph \u30B0\
    \u30E9\u30D5\n * @return std::vector<int> \u6700\u5927\u72EC\u7ACB\u96C6\u5408\
    \n */\ntemplate <class T>\nstd::vector<int> maximum_independent_set(const Graph<T>\
    \ &graph) {\n    int n = graph.size();\n    std::vector<std::int64_t> g(n);\n\
    \    for (auto es : graph) {\n        for (auto e : es) {\n            g[e.from()]\
    \ |= 1LL << e.to();\n        }\n    }\n\n    std::int64_t mv = 0, v = 0;\n   \
    \ int msz = 0, sz = 0;\n    auto f = [&](auto self, std::int64_t used) {\n   \
    \     if (used == (1LL << n) - 1) {\n            if (chmax(msz, sz)) {\n     \
    \           mv = v;\n            }\n            return;\n        }\n        int\
    \ deg = 0, x = -1;\n        for (int i = 0; i < n; ++i) {\n            if (used\
    \ >> i & 1) continue;\n            int d = __builtin_popcountl(~used & g[i]);\n\
    \            if (d <= 1) {\n                x = i;\n                break;\n \
    \           }\n            if (chmax(deg, d)) x = i;\n        }\n        used\
    \ |= 1LL << x;\n\n        if (deg > 2) {\n            self(self, used);\n    \
    \    }\n\n        v |= 1LL << x;\n        ++sz;\n        used |= g[x];\n     \
    \   self(self, used);\n        v &= ~(1LL << x);\n        --sz;\n    };\n    f(f,\
    \ 0);\n\n    std::vector<int> res;\n    for (int i = 0; i < n; ++i) {\n      \
    \  if (mv >> i & 1) res.emplace_back(i);\n    }\n    return res;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/maximum_independent_set.hpp
  requiredBy: []
  timestamp: '2023-10-12 00:40:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/graph/maximum_independent_set.test.cpp
documentation_of: lib/graph/maximum_independent_set.hpp
layout: document
redirect_from:
- /library/lib/graph/maximum_independent_set.hpp
- /library/lib/graph/maximum_independent_set.hpp.html
title: "\u6700\u5927\u72EC\u7ACB\u96C6\u5408"
---
