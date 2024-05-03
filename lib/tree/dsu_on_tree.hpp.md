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
    path: test/aoj/jag/dsu_on_tree.test.cpp
    title: test/aoj/jag/dsu_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/dynamic_union_find.test.cpp
    title: test/aoj/jag/dynamic_union_find.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
    title: test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include <cassert>\n#include <vector>\n#include \"graph/graph.hpp\"\n#include\
    \ \"template/template.hpp\"\n\ntemplate <class T>\nstruct dsu_on_tree {\n    dsu_on_tree(const\
    \ Graph<T> &_g, const std::vector<int> &query, int r = 0)\n        : g(_g), size(_g.size()),\
    \ root(r), par(size, -1), sub(), euler(size), left(size),\n          right(size),\
    \ heavy_path(size, -1), query_order(query.size()), query_size(size) {\n      \
    \  if (size == 0) return;\n        for (int x : query) ++query_size[x];\n    \
    \    sub = query_size;\n        dfs_sz(root);\n        if (size > 1) {\n     \
    \       int pos = 0, len = 0;\n            dfs_hld(root, pos, len);\n        }\n\
    \        std::vector<int> cnt = left;\n        for (int i = 0; i < (int)query.size();\
    \ ++i) query_order[cnt[query[i]]++] = i;\n    }\n    dsu_on_tree(const Graph<T>\
    \ &_g, int r = 0)\n        : g(_g), size(_g.size()), root(r), par(size, -1), sub(size,\
    \ 1), euler(size), left(size),\n          right(size), heavy_path(size, -1), query_order(),\
    \ query_size(size, 1) {\n        if (size == 0) return;\n        dfs_sz(root);\n\
    \        if (size > 1) {\n            int pos = 0, len = 0;\n            dfs_hld(root,\
    \ pos, len);\n        }\n        query_order = euler;\n    }\n\n    template <class\
    \ F, class G, class H>\n    void solve(F &rem, G &clear, H &query) {\n       \
    \ auto dsu = [&](auto self, int v) -> void {\n            int hp = heavy_path[v];\n\
    \            if (hp == -1) {\n                for (int i = left[v]; i < right[v];\
    \ ++i) query(query_order[i]);\n                rem(v);\n                return;\n\
    \            }\n            for (auto &e : g[v]) {\n                if (e.to()\
    \ == par[v] || e.to() == heavy_path[v]) continue;\n                self(self,\
    \ e.to());\n                clear();\n            }\n            self(self, hp);\n\
    \            for (int i = left[v]; i < left[hp]; ++i) query(query_order[i]);\n\
    \            for (int i = right[hp]; i < right[v]; ++i) query(query_order[i]);\n\
    \            rem(v);\n        };\n        dsu(dsu, 0);\n    }\n\n  private:\n\
    \    const Graph<T> &g;\n    int size, root;\n    std::vector<int> par, sub, euler,\
    \ left, right, heavy_path, query_order, query_size;\n\n    void dfs_sz(int v)\
    \ {\n        int max_sub = 0;\n        for (auto &e : g[v]) {\n            int\
    \ u = e.to();\n            if (u == par[v]) continue;\n            par[u] = v;\n\
    \            dfs_sz(u);\n            sub[v] += sub[u];\n            if (chmax(max_sub,\
    \ sub[u])) heavy_path[v] = u;\n        }\n    }\n\n    void dfs_hld(int v, int\
    \ &pos, int &len) {\n        euler[pos++] = v;\n        left[v] = len;\n     \
    \   right[v] = len + sub[v];\n        len += query_size[v];\n        int hp =\
    \ heavy_path[v];\n        if (hp == -1) {\n            right[v] = len;\n     \
    \       return;\n        }\n        dfs_hld(hp, pos, len);\n        for (auto\
    \ &e : g[v]) {\n            int u = e.to();\n            if (u == par[v] || u\
    \ == hp) continue;\n            dfs_hld(u, pos, len);\n        }\n    }\n};\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/dsu_on_tree.hpp
  requiredBy: []
  timestamp: '2024-04-28 00:39:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
  - test/aoj/jag/dynamic_union_find.test.cpp
  - test/aoj/jag/dsu_on_tree.test.cpp
documentation_of: lib/tree/dsu_on_tree.hpp
layout: document
redirect_from:
- /library/lib/tree/dsu_on_tree.hpp
- /library/lib/tree/dsu_on_tree.hpp.html
title: lib/tree/dsu_on_tree.hpp
---
