---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/link_cut_tree.hpp
    title: Link-Cut Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: tree/link_cut_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum\"\
    \n#include <algorithm>\n#include <cstdint>\n#include <iostream>\n#include <iterator>\n\
    #include <vector>\n#include \"tree/link_cut_tree.hpp\"\n\nint main(void) {\n \
    \   int n, q;\n    std::cin >> n >> q;\n    std::vector<int> a(n);\n    for (auto\
    \ &e : a) std::cin >> e;\n    link_cut_tree<Add<std::int64_t>> lct(n);\n    for\
    \ (int i = 0; i < n; ++i) lct.set(i, a[i]);\n    for (int i = 0; i < n - 1; ++i)\
    \ {\n        int u, v;\n        std::cin >> u >> v;\n        lct.link(u, v);\n\
    \    }\n\n    while (q--) {\n        int t;\n        std::cin >> t;\n        if\
    \ (t == 0) {\n            int u, v, w, x;\n            std::cin >> u >> v >> w\
    \ >> x;\n            lct.cut(u, v);\n            lct.link(w, x);\n        } else\
    \ if (t == 1) {\n            int p, x;\n            std::cin >> p >> x;\n    \
    \        lct.set(p, lct.get_val(p) + x);\n        } else if (t == 2) {\n     \
    \       int u, v;\n            std::cin >> u >> v;\n            lct.make_root(u);\n\
    \            lct.expose(v);\n            std::cout << lct.get_total(v) << '\\\
    n';\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/tree/link_cut_tree.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 06:42:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
- /verify/test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp.html
title: test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
---
