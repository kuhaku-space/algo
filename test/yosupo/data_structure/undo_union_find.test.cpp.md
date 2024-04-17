---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: tree/undo_union_find.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    #include \"tree/undo_union_find.hpp\"\n#include <iostream>\n#include <utility>\n\
    #include <vector>\n#include \"graph/graph.hpp\"\n\nstruct S {\n    int k, u, v;\n\
    };\n\nint main(void) {\n    int n, q;\n    std::cin >> n >> q;\n    Graph<std::pair<int,\
    \ int>> g(q + 1);\n    std::vector<std::vector<S>> querys(q + 1);\n    for (int\
    \ i = 0; i < q; ++i) {\n        int t, k, u, v;\n        std::cin >> t >> k >>\
    \ u >> v;\n        if (t == 0) g.add_edges(k + 1, i + 1, {u, v});\n        else\
    \ querys[k + 1].emplace_back(S{i + 1, u, v});\n    }\n\n    undo_union_find uf(n);\n\
    \    std::vector<int> ans(q + 1, -1);\n    auto dfs = [&](auto self, int idx,\
    \ int par) -> void {\n        for (auto query : querys[idx]) ans[query.k] = uf.same(query.u,\
    \ query.v);\n        for (auto e : g[idx]) {\n            if (e.to() == par) continue;\n\
    \            bool flag = uf.unite(e.weight().first, e.weight().second);\n    \
    \        self(self, e.to(), idx);\n            if (flag) uf.undo();\n        }\n\
    \    };\n    dfs(dfs, 0, -1);\n    for (int i = 0; i < q + 1; ++i) {\n       \
    \ if (ans[i] != -1) std::cout << ans[i] << '\\n';\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/tree/undo_union_find.hpp
  - lib/graph/graph.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/undo_union_find.test.cpp
  requiredBy: []
  timestamp: '2024-01-14 19:57:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/undo_union_find.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/undo_union_find.test.cpp
- /verify/test/yosupo/data_structure/undo_union_find.test.cpp.html
title: test/yosupo/data_structure/undo_union_find.test.cpp
---
