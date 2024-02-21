---
data:
  _extendedDependsOn:
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/0723
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/0723
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: tree/undo_union_find.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/0723\"\n#include\
    \ \"tree/undo_union_find.hpp\"\n#include <algorithm>\n#include <iostream>\n#include\
    \ <map>\n#include <vector>\n\nint main(void) {\n    int n, m, k;\n    std::cin\
    \ >> n >> m >> k;\n    std::vector<std::pair<int, int>> edges(m);\n    for (auto\
    \ &[x, y] : edges) std::cin >> x >> y, --x, --y;\n    std::vector<int> s(n);\n\
    \    for (int &e : s) std::cin >> e;\n    int q;\n    std::cin >> q;\n    std::vector<std::pair<int,\
    \ int>> queries(q);\n    for (auto &[x, y] : queries) std::cin >> x >> y, --x,\
    \ --y;\n\n    undo_union_find uf(n);\n    std::map<std::pair<int, int>, std::vector<int>>\
    \ mp;\n    for (int i = 0; i < m; ++i) {\n        auto [x, y] = edges[i];\n  \
    \      if (s[x] == s[y]) {\n            uf.unite(x, y);\n        } else {\n  \
    \          if (s[x] > s[y]) std::swap(x, y);\n            mp[{s[x], s[y]}].emplace_back(i);\n\
    \        }\n    }\n\n    std::vector<int> ans(q, -1);\n    std::map<std::pair<int,\
    \ int>, std::vector<int>> pm;\n    for (int i = 0; i < q; ++i) {\n        auto\
    \ [x, y] = queries[i];\n        if (s[x] == s[y]) {\n            ans[i] = uf.same(x,\
    \ y);\n        } else {\n            if (s[x] > s[y]) std::swap(x, y);\n     \
    \       pm[{s[x], s[y]}].emplace_back(i);\n        }\n    }\n\n    int snap =\
    \ uf.snapshot();\n    for (auto &[p, v] : pm) {\n        for (auto e : mp[p])\
    \ uf.unite(edges[e].first, edges[e].second);\n        for (auto e : v) ans[e]\
    \ = uf.same(queries[e].first, queries[e].second);\n        uf.rollback(snap);\n\
    \    }\n\n    for (int i = 0; i < q; ++i) std::cout << ans[i] << '\\n';\n\n  \
    \  return 0;\n}\n"
  dependsOn:
  - lib/tree/undo_union_find.hpp
  isVerificationFile: true
  path: test/aoj/joi/undo_union_find.test.cpp
  requiredBy: []
  timestamp: '2024-01-14 20:27:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/joi/undo_union_find.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/joi/undo_union_find.test.cpp
- /verify/test/aoj/joi/undo_union_find.test.cpp.html
title: test/aoj/joi/undo_union_find.test.cpp
---
