---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/macro.hpp
    title: lib/template/macro.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/sonic.hpp
    title: lib/template/sonic.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n#include\
    \ \"graph/graph.hpp\"\n#include \"template/atcoder.hpp\"\n\ntemplate <class T>\n\
    pair<vector<T>, vector<int>> dijkstra(const Graph<T> &g, int s = 0,\n        \
    \                              T inf = numeric_limits<T>::max()) {\n    struct\
    \ _node {\n        constexpr _node() : _to(), _dist() {}\n        constexpr _node(int\
    \ to, T dist) : _to(to), _dist(dist) {}\n\n        constexpr bool operator<(const\
    \ _node &rhs) const { return this->dist() < rhs.dist(); }\n        constexpr bool\
    \ operator>(const _node &rhs) const { return rhs < *this; }\n\n        constexpr\
    \ int to() const { return this->_to; }\n        constexpr T dist() const { return\
    \ this->_dist; }\n\n      private:\n        int _to;\n        T _dist;\n    };\n\
    \    vector<T> dists(g.size(), inf);\n    vector<int> v(g.size(), -1);\n    priority_queue<_node,\
    \ vector<_node>, greater<>> p_que;\n    dists[s] = T();\n    p_que.emplace(s,\
    \ T());\n    while (!p_que.empty()) {\n        auto node = p_que.top();\n    \
    \    p_que.pop();\n        if (dists[node.to()] < node.dist()) continue;\n   \
    \     for (auto &e : g[node.to()]) {\n            if (chmin(dists[e.to()], node.dist()\
    \ + e.weight())) {\n                v[e.to()] = node.to();\n                p_que.emplace(e.to(),\
    \ node.dist() + e.weight());\n            }\n        }\n    }\n    return {dists,\
    \ v};\n}\n\nint main(void) {\n    sonic();\n    int n, m, s, t;\n    cin >> n\
    \ >> m >> s >> t;\n    Graph<ll> g(n);\n    g.input_edge(m, 0);\n    auto [dist,\
    \ v] = dijkstra(g, s, INF);\n\n    if (dist[t] == INF) {\n        co(-1);\n  \
    \  } else {\n        vector<pair<int, int>> ans;\n        int idx = t;\n     \
    \   while (idx != s) {\n            ans.emplace_back(v[idx], idx);\n         \
    \   idx = v[idx];\n        }\n        reverse(ans.begin(), ans.end());\n     \
    \   co(dist[t], ans.size());\n        for (auto p : ans) { co(p.first, p.second);\
    \ }\n    }\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/graph/shortest_path.test.cpp
  requiredBy: []
  timestamp: '2023-05-22 19:46:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/graph/shortest_path.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/graph/shortest_path.test.cpp
- /verify/test/yosupo/graph/shortest_path.test.cpp.html
title: test/yosupo/graph/shortest_path.test.cpp
---
