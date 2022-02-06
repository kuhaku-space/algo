---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/data_structure/radix_heap.hpp
    title: lib/data_structure/radix_heap.hpp
  - icon: ':question:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':question:'
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/radix_heap.hpp:\
    \ line -1: no such header\n"
  code: "#include \"data_structure/radix_heap.hpp\"\r\n#include \"graph/graph.hpp\"\
    \r\n#include \"template/template.hpp\"\r\n\r\ntemplate <class T>\r\nvector<T>\
    \ dijkstra(const Graph<T> &g, int s = 0, T inf = numeric_limits<T>::max()) {\r\
    \n    struct _edge {\r\n        int to;\r\n        T dist;\r\n        bool operator<(const\
    \ _edge &rhs) const { return dist < rhs.dist; }\r\n        bool operator>(const\
    \ _edge &rhs) const { return rhs < *this; }\r\n    };\r\n    vector<T> dist(g.size(),\
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
  path: lib/graph/dijkstra_radix_heap.hpp
  requiredBy: []
  timestamp: '2022-01-14 01:42:22+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/dijkstra_radix_heap.hpp
layout: document
redirect_from:
- /library/lib/graph/dijkstra_radix_heap.hpp
- /library/lib/graph/dijkstra_radix_heap.hpp.html
title: lib/graph/dijkstra_radix_heap.hpp
---
