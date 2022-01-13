---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph.hpp\"\r\n\r\n\
    // verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A 21/02/26\r\n// verify\
    \ : https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_B 21/02/26\r\n\r\ntemplate\
    \ <class T>\r\nstruct LowLink {\r\n    const Graph<T> &g;\r\n    vector<int> ord,\
    \ low;\r\n    vector<bool> used;\r\n    vector<int> articulation;            \
    \    // \u95A2\u7BC0\u70B9\r\n    vector<typename Graph<T>::edge> bridge;  //\
    \ \u6A4B\r\n\r\n    LowLink(const Graph<T> &_g)\r\n        : g(_g), ord(_g.size()),\
    \ low(_g.size()), used(_g.size()) {\r\n        build();\r\n    }\r\n\r\n    int\
    \ dfs(int idx, int k, int par) {\r\n        used[idx] = true;\r\n        ord[idx]\
    \ = k++;\r\n        low[idx] = ord[idx];\r\n        bool is_articulation = false;\r\
    \n        int cnt = 0;\r\n        for (auto &e : g[idx]) {\r\n            if (!used[e.to])\
    \ {\r\n                ++cnt;\r\n                k = dfs(e.to, k, idx);\r\n  \
    \              chmin(low[idx], low[e.to]);\r\n                is_articulation\
    \ |= ~par && low[e.to] >= ord[idx];\r\n                if (ord[idx] < low[e.to])\
    \ bridge.emplace_back(e);\r\n            } else if (e.to != par) {\r\n       \
    \         chmin(low[idx], ord[e.to]);\r\n            }\r\n        }\r\n      \
    \  is_articulation |= par == -1 && cnt > 1;\r\n        if (is_articulation) articulation.emplace_back(idx);\r\
    \n        return k;\r\n    }\r\n\r\n    void build() {\r\n        int k = 0;\r\
    \n        for (int i = 0; i < g.size(); i++) {\r\n            if (!used[i]) k\
    \ = dfs(i, k, -1);\r\n        }\r\n    }\r\n\r\n    auto get_articulation() {\
    \ return articulation; }\r\n    auto get_bridge() { return bridge; }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/graph/lowlink.hpp
  requiredBy: []
  timestamp: '2021-09-22 06:52:24+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/lowlink.hpp
layout: document
redirect_from:
- /library/lib/graph/lowlink.hpp
- /library/lib/graph/lowlink.hpp.html
title: lib/graph/lowlink.hpp
---
