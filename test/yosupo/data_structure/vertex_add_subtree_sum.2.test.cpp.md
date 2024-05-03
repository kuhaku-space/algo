---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/fenwick_tree.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/dsu_on_tree.hpp
    title: lib/tree/dsu_on_tree.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/union_find.hpp
    title: "\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/fenwick_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n#include <iostream>\n#include <utility>\n#include <vector>\n#include \"binary_tree/fenwick_tree.hpp\"\
    \n#include \"graph/graph.hpp\"\n#include \"tree/dsu_on_tree.hpp\"\n#include \"\
    tree/union_find.hpp\"\n\nint main(void) {\n    int n, q;\n    std::cin >> n >>\
    \ q;\n    Graph<void> g(n);\n    std::vector<int> a(n);\n    for (int &x : a)\
    \ std::cin >> x;\n    for (int i = 0; i < n - 1; ++i) {\n        int p;\n    \
    \    std::cin >> p;\n        g.add_edge(p, i + 1);\n    }\n    std::vector<std::vector<std::pair<int,\
    \ int>>> sol(n);\n    std::vector<std::pair<int, int>> queries;\n    int solve_count\
    \ = 0;\n    for (int i = 0; i < n; ++i) queries.emplace_back(i, a[i]);\n    while\
    \ (q--) {\n        int t;\n        std::cin >> t;\n        if (t == 0) {\n   \
    \         int u, x;\n            std::cin >> u >> x;\n            queries.emplace_back(u,\
    \ x);\n        } else {\n            int u;\n            std::cin >> u;\n    \
    \        sol[u].emplace_back(solve_count++, queries.size());\n        }\n    }\n\
    \    std::vector<int> corr(queries.size());\n    for (int i = 0; i < (int)queries.size();\
    \ ++i) { corr[i] = queries[i].first; }\n    dsu_on_tree dsu(g, corr);\n    std::vector<std::int64_t>\
    \ ans(solve_count);\n    fenwick_tree<std::int64_t> ft(queries.size());\n    std::vector<std::pair<int,\
    \ int>> history;\n    auto rem = [&](int v) {\n        for (auto &[u, x] : sol[v])\
    \ ans[u] = ft.sum(x);\n    };\n    auto clear = [&]() {\n        for (auto [x,\
    \ y] : history) ft.add(x, -y);\n        history.clear();\n    };\n    auto query\
    \ = [&](int i) {\n        auto [x, y] = queries[i];\n        ft.add(i, y);\n \
    \       history.emplace_back(i, y);\n    };\n    dsu.solve(rem, clear, query);\n\
    \    for (int i = 0; i < solve_count; ++i) std::cout << ans[i] << '\\n';\n\n \
    \   return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/fenwick_tree.hpp
  - lib/graph/graph.hpp
  - lib/tree/dsu_on_tree.hpp
  - lib/template/template.hpp
  - lib/tree/union_find.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
  requiredBy: []
  timestamp: '2024-04-28 00:44:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
- /verify/test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp.html
title: test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
---
