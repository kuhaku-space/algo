---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/eular_tour.hpp
    title: "\u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC"
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/segment_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n#include <cstdint>\n#include <iostream>\n#include <vector>\n#include \"segment_tree/segment_tree.hpp\"\
    \n#include \"tree/eular_tour.hpp\"\n\nint main(void) {\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<int> a(n), p(n - 1);\n    for (auto &e : a) std::cin\
    \ >> e;\n    for (auto &e : p) std::cin >> e;\n    Graph<void> g(n);\n    for\
    \ (int i = 0; i < n - 1; ++i) g.add_edges(i + 1, p[i]);\n    eular_tour et(g);\n\
    \    segment_tree<Add<std::int64_t>> st(n);\n    for (int i = 0; i < n; ++i) st.set(et.get_l(i),\
    \ a[i]);\n\n    while (q--) {\n        int c;\n        std::cin >> c;\n      \
    \  if (c == 0) {\n            int v, x;\n            std::cin >> v >> x;\n   \
    \         st.set(et.get_l(v), st.get(et.get_l(v)) + x);\n        } else {\n  \
    \          int v;\n            std::cin >> v;\n            auto f = [&](int l,\
    \ int r) { std::cout << st.prod(l, r) << '\\n'; };\n            et.query(v, f);\n\
    \        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/segment_tree/segment_tree.hpp
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  - lib/tree/eular_tour.hpp
  - lib/graph/graph.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 06:42:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
- /verify/test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp.html
title: test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
---
