---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\n\ntemplate\
    \ <class T, class U>\nstd::vector<T> dijkstra(const Graph<T> &graph, const vector<U>\
    \ &potentials, int s = 0,\n                        T inf = std::numeric_limits<T>::max())\
    \ {\n    struct _edge {\n        int to;\n        T dist;\n        constexpr _edge()\
    \ : to(), dist() {}\n        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist)\
    \ {}\n        bool operator<(const _edge &rhs) const { return this->dist < rhs.dist;\
    \ }\n        bool operator>(const _edge &rhs) const { return rhs < *this; }\n\
    \    };\n    int n = graph.size();\n    std::vector<T> dists(n, inf);\n    std::priority_queue<_edge,\
    \ std::vector<_edge>, std::greater<_edge>> p_que;\n    dists[s] = T();\n    p_que.emplace(s,\
    \ T());\n    while (!p_que.empty()) {\n        auto e = p_que.top();\n       \
    \ p_que.pop();\n        if (dists[e.to] < e.dist) continue;\n        for (auto\
    \ &next : graph[e.to]) {\n            if (chmin(dists[next.to], e.dist + next.dist\
    \ + potentials[e.to] - potentials[next.to]))\n                p_que.emplace(next.to,\
    \ e.dist + next.dist + potentials[e.to] - potentials[next.to]);\n        }\n \
    \   }\n    for (int i = 0; i < n; ++i) { dists[i] += potentials[i] - potentials[s];\
    \ }\n    return dists;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/dijkstra_potential.hpp
  requiredBy: []
  timestamp: '2022-02-06 19:58:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/dijkstra_potential.hpp
layout: document
redirect_from:
- /library/lib/graph/dijkstra_potential.hpp
- /library/lib/graph/dijkstra_potential.hpp.html
title: lib/graph/dijkstra_potential.hpp
---
