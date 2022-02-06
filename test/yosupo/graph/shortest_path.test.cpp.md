---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n#include\
    \ \"graph/graph.hpp\"\n#include \"template/atcoder.hpp\"\n\ntemplate <class T>\n\
    pair<vector<T>, vector<int>> dijkstra(const Graph<T> &g, int s = 0,\n        \
    \                              T inf = numeric_limits<T>::max()) {\n    struct\
    \ _edge {\n        int to;\n        T dist;\n        bool operator<(const _edge\
    \ &rhs) const { return dist < rhs.dist; }\n        bool operator>(const _edge\
    \ &rhs) const { return rhs < *this; }\n    };\n    vector<T> dist(g.size(), inf);\n\
    \    vector<int> v(g.size(), -1);\n    priority_queue<_edge, vector<_edge>, greater<_edge>>\
    \ p_que;\n    dist[s] = T();\n    p_que.push(_edge{s, T()});\n    while (!p_que.empty())\
    \ {\n        _edge e = p_que.top();\n        p_que.pop();\n        if (dist[e.to]\
    \ < e.dist) continue;\n        for (auto &i : g[e.to]) {\n            if (chmin(dist[i.to],\
    \ e.dist + i.dist)) {\n                v[i.to] = e.to;\n                p_que.push(_edge{i.to,\
    \ e.dist + i.dist});\n            }\n        }\n    }\n    return {dist, v};\n\
    }\n\nint main(void) {\n    sonic();\n    int n, m, s, t;\n    cin >> n >> m >>\
    \ s >> t;\n    Graph<ll> g(n);\n    g.input_edge(m, true);\n    auto [dist, v]\
    \ = dijkstra(g, s, INF);\n\n    if (dist[t] == INF) {\n        co(-1);\n    }\
    \ else {\n        vector<pair<int, int>> ans;\n        int idx = t;\n        while\
    \ (idx != s) {\n            ans.emplace_back(v[idx], idx);\n            idx =\
    \ v[idx];\n        }\n        reverse(ans.begin(), ans.end());\n        co(dist[t],\
    \ ans.size());\n        for (auto p : ans) {\n            co(p.first, p.second);\n\
    \        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/yosupo/graph/shortest_path.test.cpp
  requiredBy: []
  timestamp: '2022-02-06 19:56:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/graph/shortest_path.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/graph/shortest_path.test.cpp
- /verify/test/yosupo/graph/shortest_path.test.cpp.html
title: test/yosupo/graph/shortest_path.test.cpp
---
