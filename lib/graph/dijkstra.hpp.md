---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/data_structure/radix_heap.hpp
    title: lib/data_structure/radix_heap.hpp
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
    links:
    - https://atcoder.jp/contests/abc148/tasks/abc148_f
    - https://atcoder.jp/contests/abc190/tasks/abc190_e
    - https://atcoder.jp/contests/abc191/tasks/abc191_e
    - https://atcoder.jp/contests/abc192/tasks/abc192_e
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/radix_heap.hpp:\
    \ line -1: no such header\n"
  code: "#include \"data_structure/radix_heap.hpp\"\r\n#include \"graph/graph.hpp\"\
    \r\n#include \"template/template.hpp\"\r\n\r\n/*\r\n * verify :\r\n * https://atcoder.jp/contests/abc192/tasks/abc192_e\
    \ 21/02/24\r\n * https://atcoder.jp/contests/abc191/tasks/abc191_e 21/04/08\r\n\
    \ * https://atcoder.jp/contests/abc190/tasks/abc190_e 21/04/08\r\n * https://atcoder.jp/contests/abc148/tasks/abc148_f\
    \ 21/04/08\r\n */\r\n\r\ntemplate <class T>\r\nvector<T> dijkstra(const Graph<T>\
    \ &g, int s = 0, T inf = numeric_limits<T>::max()) {\r\n    struct _edge {\r\n\
    \        int to;\r\n        T dist;\r\n        bool operator<(const _edge &rhs)\
    \ const { return dist < rhs.dist; }\r\n        bool operator>(const _edge &rhs)\
    \ const { return rhs < *this; }\r\n    };\r\n    vector<T> dist(g.size(), inf);\r\
    \n    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;\r\n    dist[s]\
    \ = T();\r\n    p_que.push(_edge{s, T()});\r\n    while (!p_que.empty()) {\r\n\
    \        _edge e = p_que.top();\r\n        p_que.pop();\r\n        if (dist[e.to]\
    \ < e.dist) continue;\r\n        for (auto &i : g[e.to]) {\r\n            if (chmin(dist[i.to],\
    \ e.dist + i.dist)) p_que.push(_edge{i.to, e.dist + i.dist});\r\n        }\r\n\
    \    }\r\n    return dist;\r\n}\r\n\r\ntemplate <class T>\r\nvector<T> dijkstra_late(const\
    \ Graph<T> &g, int s = 0, T inf = numeric_limits<T>::max()) {\r\n    struct _edge\
    \ {\r\n        int to;\r\n        T dist;\r\n        bool operator<(const _edge\
    \ &rhs) const { return dist < rhs.dist; }\r\n        bool operator>(const _edge\
    \ &rhs) const { return rhs < *this; }\r\n    };\r\n    vector<T> dist(g.size(),\
    \ inf);\r\n    priority_queue<_edge, vector<_edge>, greater<_edge>> p_que;\r\n\
    \    p_que.push(_edge{s, T()});\r\n    while (!p_que.empty()) {\r\n        _edge\
    \ e = p_que.top();\r\n        p_que.pop();\r\n        if (chmin(dist[e.to], e.dist))\r\
    \n            for (auto &i : g[e.to]) p_que.push(_edge{i.to, e.dist + i.dist});\r\
    \n    }\r\n    return dist;\r\n}\r\n\r\ntemplate <class T>\r\nvector<T> dijkstra_fast(const\
    \ Graph<T> &g, int s = 0, T inf = numeric_limits<T>::max()) {\r\n    struct _edge\
    \ {\r\n        int to;\r\n        T dist;\r\n        bool operator<(const _edge\
    \ &rhs) const { return dist < rhs.dist; }\r\n        bool operator>(const _edge\
    \ &rhs) const { return rhs < *this; }\r\n    };\r\n    vector<T> dist(g.size(),\
    \ inf);\r\n    radix_heap_dijkstra<_edge> p_que;\r\n    dist[s] = T();\r\n   \
    \ p_que.push(_edge{s, T()});\r\n    while (!p_que.empty()) {\r\n        _edge\
    \ e = p_que.top();\r\n        p_que.pop();\r\n        if (dist[e.to] < e.dist)\
    \ continue;\r\n        for (auto &i : g[e.to]) {\r\n            if (chmin(dist[i.to],\
    \ e.dist + i.dist)) p_que.push(_edge{i.to, e.dist + i.dist});\r\n        }\r\n\
    \    }\r\n    return dist;\r\n}\r\n"
  dependsOn:
  - lib/data_structure/radix_heap.hpp
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/graph/dijkstra.hpp
  requiredBy: []
  timestamp: '2021-10-01 05:46:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/dijkstra.hpp
layout: document
redirect_from:
- /library/lib/graph/dijkstra.hpp
- /library/lib/graph/dijkstra.hpp.html
title: lib/graph/dijkstra.hpp
---
