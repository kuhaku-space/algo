---
data:
  _extendedDependsOn:
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
    - https://github.com/beet-aizu/library/blob/master/tree/heavylightdecomposition.cpp
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_E
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/*\r\n * reference :\r\n * https://github.com/beet-aizu/library/blob/master/tree/heavylightdecomposition.cpp\r\
    \n * verify :\r\n * https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_E 21/04/08\r\
    \n */\r\n\r\nstruct HLD {\r\n    vector<vector<int>> G;\r\n\r\n    // vid: vertex\
    \ -> idx\r\n    // inv: idx -> vertex\r\n    vector<int> vid, nxt, sub, par, inv;\r\
    \n\r\n    HLD(int n) : G(n), vid(n, -1), nxt(n), sub(n, 1), par(n, -1), inv(n)\
    \ {}\r\n\r\n    void dfs_sz(int v) {\r\n        auto &es = G[v];\r\n        if\
    \ (~par[v]) es.erase(find(es.begin(), es.end(), par[v]));\r\n\r\n        for (auto\
    \ &u : es) {\r\n            par[u] = v;\r\n            this->dfs_sz(u);\r\n  \
    \          sub[v] += sub[u];\r\n            if (sub[u] > sub[es[0]]) swap(u, es[0]);\r\
    \n        }\r\n    }\r\n\r\n    void dfs_hld(int v, int &pos) {\r\n        vid[v]\
    \ = pos++;\r\n        inv[vid[v]] = v;\r\n        for (auto u : G[v]) {\r\n  \
    \          if (u == par[v]) continue;\r\n            nxt[u] = (u == G[v][0] ?\
    \ nxt[v] : u);\r\n            this->dfs_hld(u, pos);\r\n        }\r\n    }\r\n\
    \r\n    void add_edge(int u, int v) {\r\n        G[u].emplace_back(v);\r\n   \
    \     G[v].emplace_back(u);\r\n    }\r\n\r\n    void build(int r = 0) {\r\n  \
    \      int pos = 0;\r\n        this->dfs_sz(r);\r\n        nxt[r] = r;\r\n   \
    \     this->dfs_hld(r, pos);\r\n    }\r\n\r\n    int lca(int u, int v) {\r\n \
    \       while (true) {\r\n            if (vid[u] > vid[v]) swap(u, v);\r\n   \
    \         if (nxt[u] == nxt[v]) return u;\r\n            v = par[nxt[v]];\r\n\
    \        }\r\n    }\r\n\r\n    template <class F>\r\n    void for_each(int u,\
    \ int v, const F &f) {\r\n        while (true) {\r\n            if (vid[u] > vid[v])\
    \ swap(u, v);\r\n            f(max(vid[nxt[v]], vid[u]), vid[v] + 1);\r\n    \
    \        if (nxt[u] != nxt[v])\r\n                v = par[nxt[v]];\r\n       \
    \     else\r\n                break;\r\n        }\r\n    }\r\n\r\n    template\
    \ <class F>\r\n    void for_each_edge(int u, int v, const F &f) {\r\n        while\
    \ (true) {\r\n            if (vid[u] > vid[v]) swap(u, v);\r\n            if (nxt[u]\
    \ != nxt[v]) {\r\n                f(vid[nxt[v]], vid[v] + 1);\r\n            \
    \    v = par[nxt[v]];\r\n            } else {\r\n                if (u != v) f(vid[u]\
    \ + 1, vid[v] + 1);\r\n                break;\r\n            }\r\n        }\r\n\
    \    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/hld.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/hld.hpp
layout: document
redirect_from:
- /library/lib/tree/hld.hpp
- /library/lib/tree/hld.hpp.html
title: lib/tree/hld.hpp
---
