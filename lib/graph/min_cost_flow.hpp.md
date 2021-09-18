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
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class Cap, class Cost>\r\
    \nstruct mcf_graph {\r\n   public:\r\n    mcf_graph() {}\r\n    mcf_graph(int\
    \ n) : _n(n), g(n) {}\r\n\r\n    int add_edge(int from, int to, Cap cap, Cost\
    \ cost) {\r\n        assert(0 <= from && from < _n);\r\n        assert(0 <= to\
    \ && to < _n);\r\n        int m = int(pos.size());\r\n        pos.push_back({from,\
    \ int(g[from].size())});\r\n        g[from].push_back(_edge{to, int(g[to].size()),\
    \ cap, cost});\r\n        g[to].push_back(_edge{from, int(g[from].size()) - 1,\
    \ 0, -cost});\r\n        return m;\r\n    }\r\n\r\n    struct edge {\r\n     \
    \   int from, to;\r\n        Cap cap, flow;\r\n        Cost cost;\r\n    };\r\n\
    \r\n    edge get_edge(int i) {\r\n        int m = int(pos.size());\r\n       \
    \ assert(0 <= i && i < m);\r\n        auto _e = g[pos[i].first][pos[i].second];\r\
    \n        auto _re = g[_e.to][_e.rev];\r\n        return edge{\r\n           \
    \ pos[i].first, _e.to, _e.cap + _re.cap, _re.cap, _e.cost,\r\n        };\r\n \
    \   }\r\n    vector<edge> edges() {\r\n        int m = int(pos.size());\r\n  \
    \      vector<edge> result(m);\r\n        for (int i = 0; i < m; i++) result[i]\
    \ = get_edge(i);\r\n\r\n        return result;\r\n    }\r\n\r\n    pair<Cap, Cost>\
    \ flow(int s, int t) {\r\n        return flow(s, t, numeric_limits<Cap>::max());\r\
    \n    }\r\n    pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {\r\n      \
    \  return slope(s, t, flow_limit).back();\r\n    }\r\n    vector<pair<Cap, Cost>>\
    \ slope(int s, int t) {\r\n        return slope(s, t, numeric_limits<Cap>::max());\r\
    \n    }\r\n    vector<pair<Cap, Cost>> slope(int s, int t, Cap flow_limit) {\r\
    \n        assert(0 <= s && s < _n);\r\n        assert(0 <= t && t < _n);\r\n \
    \       assert(s != t);\r\n        vector<Cost> dual(_n, 0), dist(_n);\r\n   \
    \     vector<int> pv(_n), pe(_n);\r\n        vector<bool> vis(_n);\r\n       \
    \ auto dual_ref = [&]() {\r\n            fill(dist.begin(), dist.end(), numeric_limits<Cost>::max());\r\
    \n            fill(pv.begin(), pv.end(), -1);\r\n            fill(pe.begin(),\
    \ pe.end(), -1);\r\n            fill(vis.begin(), vis.end(), false);\r\n     \
    \       struct Q {\r\n                Cost key;\r\n                int to;\r\n\
    \                bool operator<(Q r) const { return key > r.key; }\r\n       \
    \     };\r\n            priority_queue<Q> que;\r\n            dist[s] = 0;\r\n\
    \            que.push(Q{0, s});\r\n            while (!que.empty()) {\r\n    \
    \            int v = que.top().to;\r\n                que.pop();\r\n         \
    \       if (vis[v]) continue;\r\n                vis[v] = true;\r\n          \
    \      if (v == t) break;\r\n                for (int i = 0; i < int(g[v].size());\
    \ i++) {\r\n                    auto e = g[v][i];\r\n                    if (vis[e.to]\
    \ || !e.cap) continue;\r\n                    Cost cost = e.cost - dual[e.to]\
    \ + dual[v];\r\n                    if (dist[e.to] - dist[v] > cost) {\r\n   \
    \                     dist[e.to] = dist[v] + cost;\r\n                       \
    \ pv[e.to] = v;\r\n                        pe[e.to] = i;\r\n                 \
    \       que.push(Q{dist[e.to], e.to});\r\n                    }\r\n          \
    \      }\r\n            }\r\n            if (!vis[t]) return false;\r\n\r\n  \
    \          for (int v = 0; v < _n; v++) {\r\n                if (!vis[v]) continue;\r\
    \n                dual[v] -= dist[t] - dist[v];\r\n            }\r\n         \
    \   return true;\r\n        };\r\n        Cap flow = 0;\r\n        Cost cost =\
    \ 0, prev_cost = -1;\r\n        vector<pair<Cap, Cost>> result;\r\n        result.push_back({flow,\
    \ cost});\r\n        while (flow < flow_limit) {\r\n            if (!dual_ref())\
    \ break;\r\n            Cap c = flow_limit - flow;\r\n            for (int v =\
    \ t; v != s; v = pv[v]) {\r\n                c = min(c, g[pv[v]][pe[v]].cap);\r\
    \n            }\r\n            for (int v = t; v != s; v = pv[v]) {\r\n      \
    \          auto& e = g[pv[v]][pe[v]];\r\n                e.cap -= c;\r\n     \
    \           g[v][e.rev].cap += c;\r\n            }\r\n            Cost d = -dual[s];\r\
    \n            flow += c;\r\n            cost += c * d;\r\n            if (prev_cost\
    \ == d) {\r\n                result.pop_back();\r\n            }\r\n         \
    \   result.push_back({flow, cost});\r\n            prev_cost = cost;\r\n     \
    \   }\r\n        return result;\r\n    }\r\n\r\n   private:\r\n    int _n;\r\n\
    \r\n    struct _edge {\r\n        int to, rev;\r\n        Cap cap;\r\n       \
    \ Cost cost;\r\n    };\r\n\r\n    vector<pair<int, int>> pos;\r\n    vector<vector<_edge>>\
    \ g;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/min_cost_flow.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/min_cost_flow.hpp
layout: document
redirect_from:
- /library/lib/graph/min_cost_flow.hpp
- /library/lib/graph/min_cost_flow.hpp.html
title: lib/graph/min_cost_flow.hpp
---
