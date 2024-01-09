---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/flow/max_flow.hpp
    title: "\u6700\u5927\u6D41"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/max_flow.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n#include\
    \ <iostream>\n#include <utility>\n#include <vector>\n#include \"flow/max_flow.hpp\"\
    \n\nint main(void) {\n    int l, r, m;\n    std::cin >> l >> r >> m;\n    std::vector<std::pair<int,\
    \ int>> p(m);\n    for (auto &[a, b] : p) std::cin >> a >> b;\n    mf_graph<int>\
    \ mf(l + r + 2);\n    int s = l + r, g = s + 1;\n    for (auto &&x : p) mf.add_edge(x.first,\
    \ l + x.second, 1);\n    for (int i = 0; i < l; ++i) mf.add_edge(s, i, 1);\n \
    \   for (int i = 0; i < r; ++i) mf.add_edge(l + i, g, 1);\n    mf.flow(s, g);\n\
    \    std::vector<int> ans;\n    for (int i = 0; i < m; ++i) {\n        if (mf.get_edge(i).flow\
    \ == 1) ans.emplace_back(i);\n    }\n    std::cout << ans.size() << '\\n';\n \
    \   for (auto &&x : ans) std::cout << p[x].first << ' ' << p[x].second << '\\\
    n';\n\n    return 0;\n}\n"
  dependsOn:
  - lib/flow/max_flow.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/graph/matching_on_bipartite_garph.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 07:01:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/graph/matching_on_bipartite_garph.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/graph/matching_on_bipartite_garph.test.cpp
- /verify/test/yosupo/graph/matching_on_bipartite_garph.test.cpp.html
title: test/yosupo/graph/matching_on_bipartite_garph.test.cpp
---
