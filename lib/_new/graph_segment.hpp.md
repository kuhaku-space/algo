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
    \ {\r\n    struct edge {\r\n        int64_t from, to;\r\n        T dist;\r\n\r\
    \n        bool operator<(const edge &rhs) const { return dist < rhs.dist; }\r\n\
    \        bool operator>(const edge &rhs) const { return dist > rhs.dist; }\r\n\
    \        edge &operator+=(const edge &rhs) {\r\n            to = rhs.to, dist\
    \ += rhs.dist;\r\n            return *this;\r\n        }\r\n        edge operator+(const\
    \ edge &rhs) { return edge(*this) += rhs; }\r\n    };\r\n\r\n    int64_t V;\r\n\
    \    vector<T> dist;\r\n    vector<vector<edge>> edges;\r\n\r\n    Graph(int64_t\
    \ v) : V(v), edges(v * 5), dist(v, numeric_limits<T>::max()) {\r\n        for\
    \ (int64_t i = 2; i < v * 2; ++i) {\r\n            edges.push_back(edge{v + i\
    \ >> 1, v + i, 0});\r\n            edges.push_back(edge{v * 3 + i, v * 3 + i >>\
    \ 1, 0});\r\n        }\r\n        for (int64_t i = 0; i < v; ++i) {\r\n      \
    \      edges.push_back(edge{v * 2 + i, i, 0});\r\n            edges.push_back(edge{v\
    \ * 4 + i, i, 0});\r\n        }\r\n    }\r\n\r\n    void add_edge(int64_t a1,\
    \ int64_t b1, int64_t a2, int64_t b2, T d = 1,\r\n                  bool is_dual\
    \ = false) {\r\n        if (is_dual) add_edge(a2, b2, a1, b1, d, !is_dual);\r\n\
    \        int64_t n = edges.size();\r\n        edges.resize(n + 2);\r\n       \
    \ edges[n].emplace_back(edge{n, n + 1, d});\r\n        for (a1 += V, b1 += V;\
    \ a1 < b1; a1 >>= 1, b1 >>= 1) {\r\n            if (a1 & 1)\r\n              \
    \  edges[V * 3 + a1].emplace_back(edge{V * 3 + a1, n, 0}), ++a1;\r\n         \
    \   if (b1 & 1)\r\n                --b1, edges[V * 3 + b1].emplace_back(edge{V\
    \ * 3 + b1, n, 0});\r\n        }\r\n        for (a2 += V, b2 += V; a2 < b2; a2\
    \ >>= 1, b2 >>= 1) {\r\n            if (a2 & 1) edges[n + 1].emplace_back(edge{n\
    \ + 1, V + a2, 0}), ++a2;\r\n            if (b2 & 1) --b2, edges[n + 1].emplace_back(edge{n\
    \ + 1, V + b2, 0});\r\n        }\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/graph_segment.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/graph_segment.hpp
layout: document
redirect_from:
- /library/lib/_new/graph_segment.hpp
- /library/lib/_new/graph_segment.hpp.html
title: lib/_new/graph_segment.hpp
---
