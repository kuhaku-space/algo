---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/macro.hpp
    title: lib/template/macro.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/sonic.hpp
    title: lib/template/sonic.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/undo_union_find.hpp
    title: "Undo\u53EF\u80FDUnion-Find"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_unionfind
    links:
    - https://judge.yosupo.jp/problem/persistent_unionfind
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    #include \"graph/graph.hpp\"\n#include \"template/atcoder.hpp\"\n#include \"tree/undo_union_find.hpp\"\
    \n\nstruct S {\n    int k, u, v;\n};\n\nint main(void) {\n    sonic();\n    int\
    \ n, q;\n    cin >> n >> q;\n    Graph<pair<int, int>> g(q + 1);\n    vector<vector<S>>\
    \ querys(q + 1);\n    rep(i, q) {\n        int t, k, u, v;\n        cin >> t >>\
    \ k >> u >> v;\n        if (t == 0) {\n            g.add_edges(k + 1, i + 1, {u,\
    \ v});\n        } else {\n            querys[k + 1].push_back({i + 1, u, v});\n\
    \        }\n    }\n\n    undo_union_find uf(n);\n    vector<int> ans(q + 1, -1);\n\
    \    auto dfs = [&](auto self, int idx, int par) -> void {\n        for (auto\
    \ query : querys[idx]) {\n            ans[query.k] = uf.same(query.u, query.v);\n\
    \        }\n        for (auto e : g[idx]) {\n            if (e.to() == par)\n\
    \                continue;\n            bool flag = uf.unite(e.weight().first,\
    \ e.weight().second);\n            self(self, e.to(), idx);\n            if (flag)\n\
    \                uf.undo();\n        }\n    };\n\n    dfs(dfs, 0, -1);\n\n   \
    \ rep(i, q + 1) {\n        if (ans[i] != -1)\n            co(ans[i]);\n    }\n\
    \n    return 0;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/template.hpp
  - lib/template/sonic.hpp
  - lib/tree/undo_union_find.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/undo_union_find.test.cpp
  requiredBy: []
  timestamp: '2023-10-12 00:40:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/undo_union_find.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/undo_union_find.test.cpp
- /verify/test/yosupo/data_structure/undo_union_find.test.cpp.html
title: test/yosupo/data_structure/undo_union_find.test.cpp
---
