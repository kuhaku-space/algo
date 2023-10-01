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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra.test.cpp
    title: test/aoj/grl/dijkstra.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5"
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
  code: "#pragma once\r\n#include \"graph/graph.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\n/**\r\n * @brief \u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\r\n *\r\n\
    \ * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\r\n * @param g \u30B0\u30E9\
    \u30D5\r\n * @param s \u59CB\u70B9\r\n * @param inf \u6B63\u306E\u7121\u9650\u8868\
    \u73FE\r\n * @retval std::vector<T> \u5404\u9802\u70B9\u307E\u3067\u306E\u6700\
    \u77ED\u8DDD\u96E2\r\n */\r\ntemplate <class T>\r\nstd::vector<T> dijkstra(const\
    \ Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {\r\n    struct\
    \ _node {\r\n        constexpr _node() : _to(), _dist() {}\r\n        constexpr\
    \ _node(int to, T dist) : _to(to), _dist(dist) {}\r\n        constexpr bool operator<(const\
    \ _node &rhs) const { return this->dist() < rhs.dist(); }\r\n        constexpr\
    \ bool operator>(const _node &rhs) const { return rhs < *this; }\r\n\r\n     \
    \   constexpr int to() const { return this->_to; }\r\n        constexpr T dist()\
    \ const { return this->_dist; }\r\n\r\n      private:\r\n        int _to;\r\n\
    \        T _dist;\r\n    };\r\n    std::vector<T> dists(g.size(), inf);\r\n  \
    \  std::priority_queue<_node, std::vector<_node>, std::greater<>> p_que;\r\n \
    \   dists[s] = T();\r\n    p_que.emplace(s, T());\r\n    while (!p_que.empty())\
    \ {\r\n        auto node = p_que.top();\r\n        p_que.pop();\r\n        if\
    \ (dists[node.to()] < node.dist()) continue;\r\n        for (auto &e : g[node.to()])\
    \ {\r\n            if (chmin(dists[e.to()], node.dist() + e.weight()))\r\n   \
    \             p_que.emplace(e.to(), node.dist() + e.weight());\r\n        }\r\n\
    \    }\r\n    return dists;\r\n}\r\n\r\nstd::vector<int> dijkstra(const Graph<void>\
    \ &g, int s = 0,\r\n                          int inf = std::numeric_limits<int>::max())\
    \ {\r\n    std::vector<int> dists(g.size(), inf);\r\n    std::queue<int> que;\r\
    \n    dists[s] = 0;\r\n    que.emplace(s);\r\n    while (!que.empty()) {\r\n \
    \       auto index = que.front();\r\n        que.pop();\r\n        for (auto &e\
    \ : g[index]) {\r\n            if (chmin(dists[e.to()], dists[index] + 1)) que.emplace(e.to());\r\
    \n        }\r\n    }\r\n    return dists;\r\n}\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/dijkstra.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/dijkstra.test.cpp
documentation_of: lib/graph/dijkstra.hpp
layout: document
redirect_from:
- /library/lib/graph/dijkstra.hpp
- /library/lib/graph/dijkstra.hpp.html
title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5"
---
