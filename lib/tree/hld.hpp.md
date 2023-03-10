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
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/range_query_on_tree.test.cpp
    title: test/aoj/grl/range_query_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/range_query_on_tree_2.test.cpp
    title: test/aoj/grl/range_query_on_tree_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
    title: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
    title: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/tree/lca.test.cpp
    title: test/yosupo/tree/lca.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: HLD
    links:
    - https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief\
    \ HLD\r\n * @see https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp\r\
    \n */\r\nstruct HLD {\r\n    HLD(int n) : _size(n), g(n), vid(n, -1), nxt(n),\
    \ sub(n, 1), par(n, -1), inv(n) {}\r\n\r\n    void add_edge(int u, int v) { this->add_edges(u,\
    \ v); }\r\n    void add_edges(int u, int v) {\r\n        this->g[u].emplace_back(v);\r\
    \n        this->g[v].emplace_back(u);\r\n    }\r\n\r\n    void input_edge(int\
    \ base = 1) { this->input_edges(base); }\r\n    void input_edges(int base = 1)\
    \ {\r\n        for (int i = 0; i < this->_size - 1; ++i) {\r\n            int\
    \ u, v;\r\n            cin >> u >> v;\r\n            this->add_edges(u - base,\
    \ v - base);\r\n        }\r\n    }\r\n\r\n    void build(int r = 0) {\r\n    \
    \    int pos = 0;\r\n        this->dfs_sz(r);\r\n        this->nxt[r] = r;\r\n\
    \        this->dfs_hld(r, pos);\r\n    }\r\n\r\n    int get(int v) const { return\
    \ this->vid[v]; }\r\n    int get_parent(int v) const { return this->par[v]; }\r\
    \n\r\n    int la(int v, int k) const {\r\n        while (true) {\r\n         \
    \   int u = this->nxt[v];\r\n            if (this->vid[v] - k >= this->vid[u])\
    \ return this->inv[this->vid[v] - k];\r\n            k -= this->vid[v] - this->vid[u]\
    \ + 1;\r\n            v = this->par[u];\r\n        }\r\n    }\r\n\r\n    int lca(int\
    \ u, int v) const {\r\n        while (true) {\r\n            if (this->vid[u]\
    \ > this->vid[v]) swap(u, v);\r\n            if (this->nxt[u] == this->nxt[v])\
    \ return u;\r\n            v = this->par[this->nxt[v]];\r\n        }\r\n    }\r\
    \n\r\n    template <class F>\r\n    void for_each(int u, int v, const F &f) const\
    \ {\r\n        while (true) {\r\n            if (this->vid[u] > this->vid[v])\
    \ swap(u, v);\r\n            f(max(this->vid[this->nxt[v]], this->vid[u]), this->vid[v]\
    \ + 1);\r\n            if (this->nxt[u] != this->nxt[v]) v = this->par[this->nxt[v]];\r\
    \n            else break;\r\n        }\r\n    }\r\n\r\n    template <class F>\r\
    \n    void for_each_edge(int u, int v, const F &f) const {\r\n        while (true)\
    \ {\r\n            if (this->vid[u] > this->vid[v]) swap(u, v);\r\n          \
    \  if (this->nxt[u] != this->nxt[v]) {\r\n                f(this->vid[this->nxt[v]],\
    \ this->vid[v] + 1);\r\n                v = this->par[this->nxt[v]];\r\n     \
    \       } else {\r\n                if (u != v) f(this->vid[u] + 1, this->vid[v]\
    \ + 1);\r\n                break;\r\n            }\r\n        }\r\n    }\r\n\r\
    \n  private:\r\n    int _size;\r\n    std::vector<std::vector<int>> g;\r\n   \
    \ std::vector<int> vid, nxt, sub, par, inv;\r\n\r\n    void dfs_sz(int v) {\r\n\
    \        auto &es = this->g[v];\r\n        if (~(this->par[v])) es.erase(find(es.begin(),\
    \ es.end(), this->par[v]));\r\n\r\n        for (auto &u : es) {\r\n          \
    \  this->par[u] = v;\r\n            this->dfs_sz(u);\r\n            this->sub[v]\
    \ += this->sub[u];\r\n            if (this->sub[u] > this->sub[es[0]]) swap(u,\
    \ es[0]);\r\n        }\r\n    }\r\n\r\n    void dfs_hld(int v, int &pos) {\r\n\
    \        this->vid[v] = pos++;\r\n        this->inv[this->vid[v]] = v;\r\n   \
    \     for (auto u : this->g[v]) {\r\n            if (u == this->par[v]) continue;\r\
    \n            this->nxt[u] = (u == this->g[v][0] ? this->nxt[v] : u);\r\n    \
    \        this->dfs_hld(u, pos);\r\n        }\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/hld.hpp
  requiredBy: []
  timestamp: '2022-07-31 09:58:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/vertex_add_path_sum.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/tree/lca.test.cpp
  - test/aoj/grl/range_query_on_tree.test.cpp
  - test/aoj/grl/range_query_on_tree_2.test.cpp
  - test/aoj/grl/hld.test.cpp
documentation_of: lib/tree/hld.hpp
layout: document
redirect_from:
- /library/lib/tree/hld.hpp
- /library/lib/tree/hld.hpp.html
title: HLD
---
