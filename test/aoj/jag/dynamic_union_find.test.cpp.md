---
data:
  _extendedDependsOn:
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
    path: lib/tree/dynamic_union_find.hpp
    title: "\u52D5\u7684Union-Find"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2995
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2995
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: tree/dynamic_union_find.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2995\"\n#include\
    \ \"tree/dynamic_union_find.hpp\"\n#include <iostream>\n#include <unordered_map>\n\
    #include <utility>\n#include <vector>\n#include \"graph/graph.hpp\"\n#include\
    \ \"tree/dsu_on_tree.hpp\"\n\nint main(void) {\n    int n, k;\n    std::cin >>\
    \ n >> k;\n    Graph<void> g(n);\n    g.input_edges(n - 1);\n    dsu_on_tree dsu(g);\n\
    \    std::vector<std::pair<int, int>> a(n);\n    for (auto &[x, y] : a) std::cin\
    \ >> x >> y, --x, --y;\n    std::vector<int> ans(n);\n    int sum = 0;\n    dynamic_union_find\
    \ duf;\n    std::unordered_map<int, bool> flag;\n    auto rem = [&](int x) { ans[x]\
    \ = sum; };\n    auto clear = [&]() {\n        sum = 0;\n        duf.clear();\n\
    \        flag.clear();\n    };\n    auto f = [&](int x, int y) {\n        if (x\
    \ == y) {\n            if (!flag[x]) {\n                ++sum;\n             \
    \   flag[x] = true;\n            }\n        } else {\n            if (!flag[x]\
    \ || !flag[y]) ++sum;\n            flag[x] |= flag[y];\n        }\n    };\n  \
    \  auto query = [&](int v) {\n        auto [s, t] = a[v];\n        duf.unite(s,\
    \ t, f);\n    };\n    dsu.solve(rem, clear, query);\n    for (int i = 0; i < n;\
    \ ++i) std::cout << ans[i] << '\\n';\n\n    return 0;\n}\n"
  dependsOn:
  - lib/tree/dynamic_union_find.hpp
  - lib/graph/graph.hpp
  - lib/tree/dsu_on_tree.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/jag/dynamic_union_find.test.cpp
  requiredBy: []
  timestamp: '2024-04-28 00:42:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/jag/dynamic_union_find.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/jag/dynamic_union_find.test.cpp
- /verify/test/aoj/jag/dynamic_union_find.test.cpp.html
title: test/aoj/jag/dynamic_union_find.test.cpp
---
