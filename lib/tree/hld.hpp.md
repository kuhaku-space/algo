---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/graph/functional_graph.hpp
    title: lib/graph/functional_graph.hpp
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
    path: test/yosupo/tree/jump_on_tree.test.cpp
    title: test/yosupo/tree/jump_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/tree/lowest_common_ancestor.test.cpp
    title: test/yosupo/tree/lowest_common_ancestor.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1211.test.cpp
    title: test/yukicoder/1211.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1242.test.cpp
    title: test/yukicoder/1242.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "HL\u5206\u89E3"
    links:
    - https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"graph/graph.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\n/**\r\n * @brief HL\u5206\u89E3\r\n * @see https://beet-aizu.github.io/library/tree/heavylightdecomposition.cpp\r\
    \n */\r\nstruct heavy_light_decomposition {\r\n    heavy_light_decomposition()\
    \ = default;\r\n    template <class T>\r\n    heavy_light_decomposition(const\
    \ Graph<T> &g, int r = 0) : heavy_light_decomposition(g.size()) {\r\n        build(g,\
    \ r);\r\n    }\r\n\r\n    constexpr int size() const { return _size; }\r\n\r\n\
    \    int get(int v) const { return vid[v]; }\r\n    int get_parent(int v) const\
    \ { return par[v]; }\r\n    int get_depth(int v) const { return depth[v]; }\r\n\
    \r\n    int dist(int u, int v) const {\r\n        int d = 0;\r\n        while\
    \ (true) {\r\n            if (vid[u] > vid[v]) std::swap(u, v);\r\n          \
    \  if (nxt[u] == nxt[v]) return d + vid[v] - vid[u];\r\n            d += vid[v]\
    \ - vid[nxt[v]] + 1;\r\n            v = par[nxt[v]];\r\n        }\r\n    }\r\n\
    \r\n    int jump(int u, int v, int k) const {\r\n        int d = dist(u, v);\r\
    \n        if (d < k) return -1;\r\n        int l = lca(u, v);\r\n        if (dist(u,\
    \ l) >= k) return la(u, k);\r\n        else return la(v, d - k);\r\n    }\r\n\r\
    \n    int la(int v, int k) const {\r\n        while (true) {\r\n            int\
    \ u = nxt[v];\r\n            if (vid[v] - k >= vid[u]) return inv[vid[v] - k];\r\
    \n            k -= vid[v] - vid[u] + 1;\r\n            v = par[u];\r\n       \
    \ }\r\n    }\r\n\r\n    int lca(int u, int v) const {\r\n        while (true)\
    \ {\r\n            if (vid[u] > vid[v]) std::swap(u, v);\r\n            if (nxt[u]\
    \ == nxt[v]) return u;\r\n            v = par[nxt[v]];\r\n        }\r\n    }\r\
    \n\r\n    template <class F>\r\n    void for_each(int u, int v, const F &f) const\
    \ {\r\n        while (true) {\r\n            if (vid[u] > vid[v]) std::swap(u,\
    \ v);\r\n            f(std::max(vid[nxt[v]], vid[u]), vid[v] + 1);\r\n       \
    \     if (nxt[u] != nxt[v]) v = par[nxt[v]];\r\n            else break;\r\n  \
    \      }\r\n    }\r\n\r\n    template <class F>\r\n    void for_each_edge(int\
    \ u, int v, const F &f) const {\r\n        while (true) {\r\n            if (vid[u]\
    \ > vid[v]) std::swap(u, v);\r\n            if (nxt[u] != nxt[v]) {\r\n      \
    \          f(vid[nxt[v]], vid[v] + 1);\r\n                v = par[nxt[v]];\r\n\
    \            } else {\r\n                if (u != v) f(vid[u] + 1, vid[v] + 1);\r\
    \n                break;\r\n            }\r\n        }\r\n    }\r\n\r\n  private:\r\
    \n    int _size;\r\n    std::vector<int> vid, nxt, sub, par, depth, inv;\r\n\r\
    \n    heavy_light_decomposition(int n)\r\n        : _size(n), vid(n, -1), nxt(n),\
    \ sub(n, 1), par(n, -1), depth(n), inv(n) {}\r\n\r\n    template <class T>\r\n\
    \    void build(const Graph<T> &g, int r = 0) {\r\n        std::vector<int> heavy_path(_size,\
    \ -1);\r\n        dfs_sz(g, r, heavy_path);\r\n        nxt[r] = r;\r\n       \
    \ int pos = 0;\r\n        dfs_hld(g, r, pos, heavy_path);\r\n    }\r\n\r\n   \
    \ template <class T>\r\n    void dfs_sz(const Graph<T> &g, int v, std::vector<int>\
    \ &heavy_path) {\r\n        int max_sub = 0;\r\n        for (auto &e : g[v]) {\r\
    \n            int u = e.to();\r\n            if (u == par[v]) continue;\r\n  \
    \          par[u] = v;\r\n            depth[u] = depth[v] + 1;\r\n           \
    \ dfs_sz(g, u, heavy_path);\r\n            sub[v] += sub[u];\r\n            if\
    \ (chmax(max_sub, sub[u])) heavy_path[v] = u;\r\n        }\r\n    }\r\n\r\n  \
    \  template <class T>\r\n    void dfs_hld(const Graph<T> &g, int v, int &pos,\
    \ const std::vector<int> &heavy_path) {\r\n        vid[v] = pos++;\r\n       \
    \ inv[vid[v]] = v;\r\n        int hp = heavy_path[v];\r\n        if (hp != -1)\
    \ {\r\n            nxt[hp] = nxt[v];\r\n            dfs_hld(g, hp, pos, heavy_path);\r\
    \n        }\r\n        for (auto &e : g[v]) {\r\n            int u = e.to();\r\
    \n            if (u == par[v] || u == heavy_path[v]) continue;\r\n           \
    \ nxt[u] = u;\r\n            dfs_hld(g, u, pos, heavy_path);\r\n        }\r\n\
    \    }\r\n};\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/hld.hpp
  requiredBy:
  - lib/graph/functional_graph.hpp
  timestamp: '2023-10-12 00:40:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yukicoder/1211.test.cpp
  - test/yukicoder/1242.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/data_structure/vertex_add_path_sum.test.cpp
  - test/yosupo/tree/lowest_common_ancestor.test.cpp
  - test/yosupo/tree/jump_on_tree.test.cpp
  - test/aoj/grl/range_query_on_tree.test.cpp
  - test/aoj/grl/hld.test.cpp
  - test/aoj/grl/range_query_on_tree_2.test.cpp
documentation_of: lib/tree/hld.hpp
layout: document
redirect_from:
- /library/lib/tree/hld.hpp
- /library/lib/tree/hld.hpp.html
title: "HL\u5206\u89E3"
---
