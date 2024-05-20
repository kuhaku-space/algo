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
    path: lib/internal/internal_math.hpp
    title: lib/internal/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_type_traits.hpp
    title: lib/internal/internal_type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
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
    path: lib/tree/hld.hpp
    title: "HL\u5206\u89E3"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/vertex_set_path_composite
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n#include <iostream>\n#include <utility>\n#include <vector>\n#include \"math/modint.hpp\"\
    \n#include \"segment_tree/segment_tree.hpp\"\n#include \"tree/hld.hpp\"\n\nusing\
    \ Mint = modint998;\nusing M = Affine<Mint>;\nusing RM = Rev<M>;\n\nint main(void)\
    \ {\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<std::pair<Mint, Mint>>\
    \ a(n);\n    for (auto &[x, y] : a) std::cin >> x >> y;\n    Graph<void> g(n);\n\
    \    g.input_edges(n - 1, 0);\n    heavy_light_decomposition hld(g);\n    segment_tree<M>\
    \ st1(n);\n    segment_tree<RM> st2(n);\n    for (int i = 0; i < n; ++i) {\n \
    \       st1.set(hld.get(i), a[i]);\n        st2.set(hld.get(i), a[i]);\n    }\n\
    \n    while (q--) {\n        int c;\n        std::cin >> c;\n        if (c ==\
    \ 0) {\n            int p, a, b;\n            std::cin >> p >> a >> b;\n     \
    \       st1.set(hld.get(p), {a, b});\n            st2.set(hld.get(p), {a, b});\n\
    \        } else {\n            int u, v, x;\n            std::cin >> u >> v >>\
    \ x;\n            auto l = M::id, r = M::id;\n            auto f = [&](int u,\
    \ int v) { l = M::op(st1.prod(u, v), l); };\n            auto g = [&](int u, int\
    \ v) { r = RM::op(st2.prod(u, v), r); };\n            int lca = hld.lca(u, v);\n\
    \            hld.for_each(lca, u, f);\n            hld.for_each_edge(lca, v, g);\n\
    \            auto ans = RM::op(l, r);\n            std::cout << (ans.first * x\
    \ + ans.second) << '\\n';\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/segment_tree/segment_tree.hpp
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  - lib/tree/hld.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  requiredBy: []
  timestamp: '2024-05-06 21:20:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/vertex_set_path_composite.test.cpp
- /verify/test/yosupo/data_structure/vertex_set_path_composite.test.cpp.html
title: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
---
