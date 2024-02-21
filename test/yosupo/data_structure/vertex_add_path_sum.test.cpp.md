---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/fenwick_tree.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':question:'
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
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_path_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/fenwick_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\
    #include <cstdint>\n#include <iostream>\n#include <vector>\n#include \"binary_tree/fenwick_tree.hpp\"\
    \n#include \"tree/hld.hpp\"\n\nint main(void) {\n    int n, q;\n    std::cin >>\
    \ n >> q;\n    std::vector<int> a(n);\n    for (auto &e : a) std::cin >> e;\n\
    \    Graph<void> g(n);\n    g.input_edges(n - 1, 0);\n    heavy_light_decomposition\
    \ hld(g);\n    fenwick_tree<std::int64_t> ft(n);\n    for (int i = 0; i < n; ++i)\
    \ ft.add(hld.get(i), a[i]);\n\n    while (q--) {\n        int c;\n        std::cin\
    \ >> c;\n        if (c == 0) {\n            int p, x;\n            std::cin >>\
    \ p >> x;\n            ft.add(hld.get(p), x);\n        } else {\n            int\
    \ u, v;\n            std::cin >> u >> v;\n            std::int64_t ans = 0;\n\
    \            auto f = [&](int u, int v) { ans += ft.sum(u, v); };\n          \
    \  hld.for_each(u, v, f);\n            std::cout << ans << '\\n';\n        }\n\
    \    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/fenwick_tree.hpp
  - lib/tree/hld.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
  requiredBy: []
  timestamp: '2023-11-16 21:07:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/vertex_add_path_sum.test.cpp
- /verify/test/yosupo/data_structure/vertex_add_path_sum.test.cpp.html
title: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
---
