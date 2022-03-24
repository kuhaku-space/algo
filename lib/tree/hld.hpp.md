---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/hld.test.cpp
    title: test/aoj/grl/hld.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: HLD
    links:
    - https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp)
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief HLD\r\n * @details\
    \ [\u53C2\u8003](https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp)\r\
    \n *\r\n */\r\nstruct HLD {\r\n    HLD(int n) : g(n), vid(n, -1), nxt(n), sub(n,\
    \ 1), par(n, -1), inv(n) {}\r\n\r\n    void dfs_sz(int v) {\r\n        auto &es\
    \ = this->g[v];\r\n        if (~(this->par[v])) es.erase(find(es.begin(), es.end(),\
    \ this->par[v]));\r\n\r\n        for (auto &u : es) {\r\n            this->par[u]\
    \ = v;\r\n            this->dfs_sz(u);\r\n            this->sub[v] += this->sub[u];\r\
    \n            if (this->sub[u] > this->sub[es[0]]) swap(u, es[0]);\r\n       \
    \ }\r\n    }\r\n\r\n    void dfs_hld(int v, int &pos) {\r\n        this->vid[v]\
    \ = pos++;\r\n        this->inv[this->vid[v]] = v;\r\n        for (auto u : this->g[v])\
    \ {\r\n            if (u == this->par[v]) continue;\r\n            this->nxt[u]\
    \ = (u == this->g[v][0] ? this->nxt[v] : u);\r\n            this->dfs_hld(u, pos);\r\
    \n        }\r\n    }\r\n\r\n    void add_edge(int u, int v) {\r\n        this->g[u].emplace_back(v);\r\
    \n        this->g[v].emplace_back(u);\r\n    }\r\n    void add_edges(int u, int\
    \ v) { this->add_edge(u, v); }\r\n\r\n    void build(int r = 0) {\r\n        int\
    \ pos = 0;\r\n        this->dfs_sz(r);\r\n        this->nxt[r] = r;\r\n      \
    \  this->dfs_hld(r, pos);\r\n    }\r\n\r\n    int lca(int u, int v) {\r\n    \
    \    while (true) {\r\n            if (this->vid[u] > this->vid[v]) swap(u, v);\r\
    \n            if (this->nxt[u] == this->nxt[v]) return u;\r\n            v = this->par[this->nxt[v]];\r\
    \n        }\r\n    }\r\n\r\n    template <class F>\r\n    void for_each(int u,\
    \ int v, const F &f) {\r\n        while (true) {\r\n            if (this->vid[u]\
    \ > this->vid[v]) swap(u, v);\r\n            f(max(this->vid[this->nxt[v]], this->vid[u]),\
    \ this->vid[v] + 1);\r\n            if (this->nxt[u] != this->nxt[v])\r\n    \
    \            v = this->par[this->nxt[v]];\r\n            else\r\n            \
    \    break;\r\n        }\r\n    }\r\n\r\n    template <class F>\r\n    void for_each_edge(int\
    \ u, int v, const F &f) {\r\n        while (true) {\r\n            if (this->vid[u]\
    \ > this->vid[v]) swap(u, v);\r\n            if (this->nxt[u] != this->nxt[v])\
    \ {\r\n                f(this->vid[this->nxt[v]], this->vid[v] + 1);\r\n     \
    \           v = this->par[this->nxt[v]];\r\n            } else {\r\n         \
    \       if (u != v) f(this->vid[u] + 1, this->vid[v] + 1);\r\n               \
    \ break;\r\n            }\r\n        }\r\n    }\r\n\r\n  private:\r\n    vector<vector<int>>\
    \ g;\r\n\r\n    // vid: vertex -> idx\r\n    // inv: idx -> vertex\r\n    vector<int>\
    \ vid, nxt, sub, par, inv;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/hld.hpp
  requiredBy: []
  timestamp: '2022-01-14 02:20:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/hld.test.cpp
documentation_of: lib/tree/hld.hpp
layout: document
redirect_from:
- /library/lib/tree/hld.hpp
- /library/lib/tree/hld.hpp.html
title: HLD
---
