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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T>\r\nstruct Graph\
    \ {\r\n    struct edge {\r\n        int64_t from, to;\r\n        T dist;\r\n\r\
    \n        bool operator<(const edge &rhs) const { return dist < rhs.dist; }\r\n\
    \        bool operator>(const edge &rhs) const { return dist > rhs.dist; }\r\n\
    \        edge &operator+=(const edge &rhs) {\r\n            to = rhs.to;\r\n \
    \           dist += rhs.dist;\r\n            return *this;\r\n        }\r\n  \
    \      edge operator+(const edge &rhs) { return edge(*this) += rhs; }\r\n    };\r\
    \n\r\n    int64_t V;\r\n    vector<T> dist;\r\n    vector<vector<edge>> edges;\r\
    \n    bitset<1 << 20> negative_cycle;\r\n\r\n    Graph(int64_t v) : V(v) {\r\n\
    \        edges = vector<vector<edge>>(V);\r\n        dist = vector<T>(V);\r\n\
    \    }\r\n\r\n    const T &operator[](int64_t i) const { return dist[i]; }\r\n\
    \    T &operator[](int64_t i) { return dist[i]; }\r\n\r\n    void add_edge(int64_t\
    \ a, int64_t b, T d = T(1)) {\r\n        edges[a].push_back(edge{a, b, d});\r\n\
    \    }\r\n    void add_edges(int64_t a, int64_t b, T d = T(1)) {\r\n        edges[a].push_back(edge{a,\
    \ b, d});\r\n        edges[b].push_back(edge{b, a, d});\r\n    }\r\n\r\n    void\
    \ dijkstra(int64_t s, T inf = numeric_limits<T>::max()) {\r\n        dist.assign(V,\
    \ inf);\r\n        priority_queue<edge, vector<edge>, greater<edge>> p_que;\r\n\
    \        p_que.push(edge{s, s, T()});\r\n        while (!p_que.empty()) {\r\n\
    \            edge e = p_que.top();\r\n            p_que.pop();\r\n           \
    \ if (chmin(dist[e.to], e.dist))\r\n                for (auto i : edges[e.to])\
    \ p_que.push(e + i);\r\n        }\r\n    }\r\n\r\n    void bellman_ford(int64_t\
    \ s, T inf = numeric_limits<T>::max()) {\r\n        dist.assign(V, inf);\r\n \
    \       dist[s] = T();\r\n        negative_cycle = bitset<1 << 20>();\r\n\r\n\
    \        bool flg = true;\r\n        int64_t cnt = 0;\r\n        while (flg &&\
    \ cnt <= V << 1) {\r\n            flg = false;\r\n            for (int64_t i =\
    \ 0; i < V; ++i) {\r\n                if (dist[i] == inf) continue;\r\n      \
    \          for (auto j : edges[i]) {\r\n                    if (chmin(dist[j.to],\
    \ dist[i] + j.dist)) {\r\n                        flg = true;\r\n            \
    \            if (cnt >= V) negative_cycle.set(j.to);\r\n                    }\r\
    \n                }\r\n            }\r\n            ++cnt;\r\n        }\r\n  \
    \  }\r\n\r\n    bool is_visit(int64_t a) const {\r\n        return dist[a] !=\
    \ numeric_limits<T>::max();\r\n    }\r\n\r\n    bool is_negative_cycle(int64_t\
    \ a) const { return negative_cycle[a]; }\r\n\r\n    vector<int64_t> topological_sort()\
    \ {\r\n        vector<int64_t> res;\r\n        bitset<1 << 20> is_seen;\r\n  \
    \      for (int64_t i = 0; i < V; ++i) {\r\n            if (is_seen[i]) continue;\r\
    \n            stack<int64_t> st;\r\n            st.push(~i);\r\n            st.push(i);\r\
    \n            while (!st.empty()) {\r\n                auto v = st.top();\r\n\
    \                st.pop();\r\n                if (v < 0) {\r\n               \
    \     if (!is_seen[~v]) res.push_back(~v);\r\n                    is_seen.set(~v);\r\
    \n                    continue;\r\n                }\r\n                for (auto\
    \ e : edges[v]) {\r\n                    if (is_seen[e.to]) continue;\r\n    \
    \                st.push(~e.to);\r\n                    st.push(e.to);\r\n   \
    \             }\r\n            }\r\n        }\r\n        reverse(res.begin(),\
    \ res.end());\r\n        return res;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_old/graph_algorithm.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_old/graph_algorithm.hpp
layout: document
redirect_from:
- /library/lib/_old/graph_algorithm.hpp
- /library/lib/_old/graph_algorithm.hpp.html
title: lib/_old/graph_algorithm.hpp
---
