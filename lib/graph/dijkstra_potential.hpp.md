---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\
    \n\ntemplate <class T, class U>\nstd::vector<T> dijkstra(const Graph<T> &g, const\
    \ std::vector<U> &potentials, int s = 0,\n                        T inf = std::numeric_limits<T>::max())\
    \ {\n    struct _node {\n        constexpr _node() : _to(), _dist() {}\n     \
    \   constexpr _node(int to, T dist) : _to(to), _dist(dist) {}\n        constexpr\
    \ bool operator<(const _node &rhs) const { return this->dist() < rhs.dist(); }\n\
    \        constexpr bool operator>(const _node &rhs) const { return rhs < *this;\
    \ }\n\n        constexpr int to() const { return this->_to; }\n        constexpr\
    \ T dist() const { return this->_dist; }\n\n      private:\n        int _to;\n\
    \        T _dist;\n    };\n    int n = g.size();\n    std::vector<T> dists(n,\
    \ inf);\n    std::priority_queue<_node, std::vector<_node>, std::greater<>> p_que;\n\
    \    dists[s] = T();\n    p_que.emplace(s, T());\n    while (!p_que.empty()) {\n\
    \        auto node = p_que.top();\n        p_que.pop();\n        if (dists[node.to()]\
    \ < node.dist()) continue;\n        for (auto &e : g[node.to()]) {\n         \
    \   auto next_dist = node.dist() + e.weight() + potentials[node.to()] - potentials[e.to()];\n\
    \            if (chmin(dists[e.to()], next_dist)) p_que.emplace(e.to(), next_dist);\n\
    \        }\n    }\n    for (int i = 0; i < n; ++i) {\n        dists[i] += potentials[i]\
    \ - potentials[s];\n    }\n    return dists;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/dijkstra_potential.hpp
  requiredBy: []
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/dijkstra_potential.hpp
layout: document
redirect_from:
- /library/lib/graph/dijkstra_potential.hpp
- /library/lib/graph/dijkstra_potential.hpp.html
title: lib/graph/dijkstra_potential.hpp
---
