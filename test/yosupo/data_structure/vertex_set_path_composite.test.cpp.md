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
    path: lib/tree/hld.hpp
    title: HLD
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n#include \"math/modint.hpp\"\n#include \"segment_tree/segment_tree.hpp\"\n#include\
    \ \"template/atcoder.hpp\"\n#include \"tree/hld.hpp\"\n\nusing Mint = modint998;\n\
    \nint main(void) {\n    int n, q;\n    cin >> n >> q;\n    vector<pair<Mint, Mint>>\
    \ a(n);\n    cin >> a;\n    HLD hld(n);\n    hld.input_edges(0);\n    hld.build();\n\
    \    using M = Affine<Mint>;\n    using RM = Rev<M>;\n    segment_tree<M> st1(n);\n\
    \    segment_tree<RM> st2(n);\n    rep (i, n) {\n        st1.set(hld.get(i), a[i]);\n\
    \        st2.set(hld.get(i), a[i]);\n    }\n    while (q--) {\n        int c;\n\
    \        cin >> c;\n        if (c == 0) {\n            int p, a, b;\n        \
    \    cin >> p >> a >> b;\n            st1.set(hld.get(p), {a, b});\n         \
    \   st2.set(hld.get(p), {a, b});\n        } else {\n            int u, v, x;\n\
    \            cin >> u >> v >> x;\n            auto l = M::id, r = M::id;\n   \
    \         auto f = [&](int u, int v) {\n                l = M::op(st1.prod(u,\
    \ v), l);\n            };\n            auto g = [&](int u, int v) {\n        \
    \        r = RM::op(st2.prod(u, v), r);\n            };\n            int lca =\
    \ hld.lca(u, v);\n            hld.for_each(lca, u, f);\n            hld.for_each_edge(lca,\
    \ v, g);\n            auto ans = RM::op(l, r);\n            co(ans.first * x +\
    \ ans.second);\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/template/template.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/segment_tree/segment_tree.hpp
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  - lib/tree/hld.hpp
  - lib/graph/graph.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  requiredBy: []
  timestamp: '2023-07-13 20:24:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/vertex_set_path_composite.test.cpp
- /verify/test/yosupo/data_structure/vertex_set_path_composite.test.cpp.html
title: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
---
