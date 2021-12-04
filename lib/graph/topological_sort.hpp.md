---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':x:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph.hpp\"\r\n\r\n\
    // verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A 21/02/24\r\n\r\n\
    template <class T>\r\nbool is_cycle(const Graph<T> &g) {\r\n    int n = g.size();\r\
    \n    vector<bool> is_seen(n), is_finish(n);\r\n    bool res = false;\r\n\r\n\
    \    auto dfs = [&](auto self, int idx) {\r\n        if (is_finish[idx]) return;\r\
    \n        is_seen[idx] = true;\r\n        for (auto &e : g[idx]) {\r\n       \
    \     if (res |= is_seen[e.to]) return;\r\n            self(self, e.to);\r\n \
    \       }\r\n        is_seen[idx] = false;\r\n        is_finish[idx] = true;\r\
    \n    };\r\n\r\n    for (int i = 0; i < n; ++i) {\r\n        is_seen.assign(n,\
    \ false);\r\n        dfs(dfs, i);\r\n    }\r\n    return res;\r\n}\r\n\r\n// verify\
    \ : https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_B 21/02/24\r\n\r\ntemplate\
    \ <class T>\r\nvector<int> topological_sort(const Graph<T> &g) {\r\n    int n\
    \ = g.size();\r\n    vector<int> res;\r\n    vector<bool> is_seen(n);\r\n    auto\
    \ dfs = [&](auto self, int v) {\r\n        if (is_seen[v]) return;\r\n       \
    \ is_seen[v] = true;\r\n        for (auto &e : g[v])\r\n            if (!is_seen[e.to])\
    \ self(self, e.to);\r\n        res.emplace_back(v);\r\n    };\r\n    for (int\
    \ i = 0; i < n; ++i) dfs(dfs, i);\r\n    reverse(res.begin(), res.end());\r\n\
    \    return res;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/graph/topological_sort.hpp
  requiredBy: []
  timestamp: '2021-09-22 06:52:24+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/topological_sort.hpp
layout: document
redirect_from:
- /library/lib/graph/topological_sort.hpp
- /library/lib/graph/topological_sort.hpp.html
title: lib/graph/topological_sort.hpp
---
