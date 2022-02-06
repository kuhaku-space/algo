---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/matrix_graph.hpp
    title: lib/graph/matrix_graph.hpp
  - icon: ':heavy_check_mark:'
    path: lib/graph/warshall_floyd.hpp
    title: lib/graph/warshall_floyd.hpp
  - icon: ':question:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/matrix_graph.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C\"\
    \n#include \"graph/matrix_graph.hpp\"\n#include \"graph/warshall_floyd.hpp\"\n\
    #include \"template/atcoder.hpp\"\n\nint main(void) {\n    sonic();\n    int v,\
    \ e;\n    cin >> v >> e;\n    matrix_graph<ll> g(v, INF);\n    while (e--) {\n\
    \        int s, t, d;\n        cin >> s >> t >> d;\n        g.add_edge(s, t, d);\n\
    \    }\n    warshall_floyd(g);\n    rep(i, v) {\n        if (g[i][i] < 0) {\n\
    \            co(\"NEGATIVE CYCLE\");\n            return 0;\n        }\n    }\n\
    \n    rep(i, v) {\n        vector<string> ans;\n        rep(j, v) {\n        \
    \    if (g[i][j] >= INF / 2)\n                ans.emplace_back(\"INF\");\n   \
    \         else\n                ans.emplace_back(to_string(g[i][j]));\n      \
    \  }\n        co(ans);\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/matrix_graph.hpp
  - lib/template/template.hpp
  - lib/graph/warshall_floyd.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/aoj/all_pairs_shortest_path.test.cpp
  requiredBy: []
  timestamp: '2022-02-06 19:56:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/all_pairs_shortest_path.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/all_pairs_shortest_path.test.cpp
- /verify/test/aoj/all_pairs_shortest_path.test.cpp.html
title: test/aoj/all_pairs_shortest_path.test.cpp
---
