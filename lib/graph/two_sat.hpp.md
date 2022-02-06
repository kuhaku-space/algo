---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':warning:'
    path: lib/graph/scc.hpp
    title: lib/graph/scc.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/practice2/tasks/practice2_h
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph.hpp\"\r\n#include\
    \ \"graph/scc.hpp\"\r\n\r\n// verify : https://atcoder.jp/contests/practice2/tasks/practice2_h\r\
    \n\r\nstruct two_sat {\r\n    int n;\r\n    Graph<void> G;\r\n\r\n    two_sat(int\
    \ _n) : n(_n), G(_n * 2) {}\r\n\r\n    void add(int i, bool f, int j, bool g)\
    \ {\r\n        i <<= 1, j <<= 1;\r\n        G.add_edge(i + (f ? 0 : 1), j + (g\
    \ ? 1 : 0));\r\n        G.add_edge(j + (g ? 0 : 1), i + (f ? 1 : 0));\r\n    }\r\
    \n\r\n    vector<int> solve() {\r\n        auto res = scc(G);\r\n        return\
    \ res;\r\n    }\r\n\r\n    bool is_satisfy(const vector<int> &v) {\r\n       \
    \ for (int i = 0; i < n; ++i) {\r\n            if (v[i * 2] == v[i * 2 + 1]) return\
    \ false;\r\n        }\r\n        return true;\r\n    }\r\n\r\n    vector<bool>\
    \ build(const vector<int> &v) {\r\n        vector<bool> res(n);\r\n        for\
    \ (int i = 0; i < n; ++i) res[i] = v[i * 2] < v[i * 2 + 1];\r\n        return\
    \ res;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  - lib/graph/scc.hpp
  isVerificationFile: false
  path: lib/graph/two_sat.hpp
  requiredBy: []
  timestamp: '2022-01-14 01:42:22+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/two_sat.hpp
layout: document
redirect_from:
- /library/lib/graph/two_sat.hpp
- /library/lib/graph/two_sat.hpp.html
title: lib/graph/two_sat.hpp
---
