---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/graph/chromatic_number.hpp
    title: lib/graph/chromatic_number.hpp
  - icon: ':warning:'
    path: lib/graph/warshall_floyd.hpp
    title: lib/graph/warshall_floyd.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T>\r\nstruct Graph\
    \ {\r\n    int V;\r\n    vector<vector<T>> m;\r\n\r\n    Graph(int v, T _e = T())\
    \ : V(v) {\r\n        m = vector<vector<T>>(V, vector<T>(V, _e));\r\n    }\r\n\
    \r\n    const auto &operator[](int i) const { return m[i]; }\r\n    auto &operator[](int\
    \ i) { return m[i]; }\r\n    const auto begin() const { return m.begin(); }\r\n\
    \    auto begin() { return m.begin(); }\r\n    const auto end() const { return\
    \ m.end(); }\r\n    auto end() { return m.end(); }\r\n\r\n    int size() const\
    \ { return V; }\r\n\r\n    void add_edge(int a, int b, T d = T(1)) { m[a][b] =\
    \ d; }\r\n    void add_edges(int a, int b, T d = T(1)) {\r\n        m[a][b] =\
    \ d;\r\n        m[b][a] = d;\r\n    }\r\n\r\n    void complement() {\r\n     \
    \   for (int i = 0; i < V; ++i) {\r\n            for (int j = 0; j < V; ++j) m[i][j]\
    \ = !m[i][j];\r\n        }\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/graph_matrix.hpp
  requiredBy:
  - lib/graph/chromatic_number.hpp
  - lib/graph/warshall_floyd.hpp
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/graph_matrix.hpp
layout: document
redirect_from:
- /library/lib/graph/graph_matrix.hpp
- /library/lib/graph/graph_matrix.hpp.html
title: lib/graph/graph_matrix.hpp
---
