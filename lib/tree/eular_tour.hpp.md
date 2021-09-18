---
data:
  _extendedDependsOn:
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
    - https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n// reference :\r\n// https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp\r\
    \n\r\nstruct eular_tour {\r\n    vector<vector<int>> G;\r\n    vector<int> ls,\
    \ rs;\r\n    int pos;\r\n\r\n    eular_tour(int n) : G(n), ls(n), rs(n) {}\r\n\
    \r\n    pair<int, int> operator[](int i) const { return {ls[i], rs[i]}; }\r\n\r\
    \n    int size() const { return pos; }\r\n\r\n    void add_edge(int a, int b)\
    \ {\r\n        G[a].emplace_back(b);\r\n        G[b].emplace_back(a);\r\n    }\r\
    \n\r\n    void dfs(int v, int p) {\r\n        ls[v] = pos++;\r\n        for (auto\
    \ &u : G[v]) {\r\n            if (u != p) dfs(u, v);\r\n            rs[v] = pos;\r\
    \n        }\r\n    }\r\n\r\n    void build(int r = 0) {\r\n        pos = 0;\r\n\
    \        dfs(r, -1);\r\n    }\r\n\r\n    int get_l(int i) const { return ls[i];\
    \ }\r\n    int get_r(int i) const { return rs[i]; }\r\n\r\n    template <class\
    \ F>\r\n    void query(int v, const F &f) {\r\n        f(ls[v], rs[v]);\r\n  \
    \  }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/eular_tour.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/eular_tour.hpp
layout: document
redirect_from:
- /library/lib/tree/eular_tour.hpp
- /library/lib/tree/eular_tour.hpp.html
title: lib/tree/eular_tour.hpp
---
