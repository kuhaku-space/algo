---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/mincostflow.hpp\"\n\n\n\r\n#include <algorithm>\r\
    \n#include <cassert>\r\n#include <limits>\r\n#include <queue>\r\n#include <vector>\r\
    \n\r\nnamespace atcoder {\r\n\r\ntemplate <class Cap, class Cost> struct mcf_graph\
    \ {\r\n  public:\r\n    mcf_graph() {}\r\n    mcf_graph(int n) : _n(n), g(n) {}\r\
    \n\r\n    int add_edge(int from, int to, Cap cap, Cost cost) {\r\n        assert(0\
    \ <= from && from < _n);\r\n        assert(0 <= to && to < _n);\r\n        int\
    \ m = int(pos.size());\r\n        pos.push_back({from, int(g[from].size())});\r\
    \n        g[from].push_back(_edge{to, int(g[to].size()), cap, cost});\r\n    \
    \    g[to].push_back(_edge{from, int(g[from].size()) - 1, 0, -cost});\r\n    \
    \    return m;\r\n    }\r\n\r\n    struct edge {\r\n        int from, to;\r\n\
    \        Cap cap, flow;\r\n        Cost cost;\r\n    };\r\n\r\n    edge get_edge(int\
    \ i) {\r\n        int m = int(pos.size());\r\n        assert(0 <= i && i < m);\r\
    \n        auto _e = g[pos[i].first][pos[i].second];\r\n        auto _re = g[_e.to][_e.rev];\r\
    \n        return edge{\r\n            pos[i].first, _e.to, _e.cap + _re.cap, _re.cap,\
    \ _e.cost,\r\n        };\r\n    }\r\n    std::vector<edge> edges() {\r\n     \
    \   int m = int(pos.size());\r\n        std::vector<edge> result(m);\r\n     \
    \   for (int i = 0; i < m; i++) {\r\n            result[i] = get_edge(i);\r\n\
    \        }\r\n        return result;\r\n    }\r\n\r\n    std::pair<Cap, Cost>\
    \ flow(int s, int t) {\r\n        return flow(s, t, std::numeric_limits<Cap>::max());\r\
    \n    }\r\n    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {\r\n \
    \       return slope(s, t, flow_limit).back();\r\n    }\r\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t) {\r\n        return slope(s, t, std::numeric_limits<Cap>::max());\r\
    \n    }\r\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit)\
    \ {\r\n        assert(0 <= s && s < _n);\r\n        assert(0 <= t && t < _n);\r\
    \n        assert(s != t);\r\n        // variants (C = maxcost):\r\n        //\
    \ -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0\r\n        // reduced cost (= e.cost\
    \ + dual[e.from] - dual[e.to]) >= 0 for all edge\r\n        std::vector<Cost>\
    \ dual(_n, 0), dist(_n);\r\n        std::vector<int> pv(_n), pe(_n);\r\n     \
    \   std::vector<bool> vis(_n);\r\n        auto dual_ref = [&]() {\r\n        \
    \    std::fill(dist.begin(), dist.end(),\r\n                      std::numeric_limits<Cost>::max());\r\
    \n            std::fill(pv.begin(), pv.end(), -1);\r\n            std::fill(pe.begin(),\
    \ pe.end(), -1);\r\n            std::fill(vis.begin(), vis.end(), false);\r\n\
    \            struct Q {\r\n                Cost key;\r\n                int to;\r\
    \n                bool operator<(Q r) const { return key > r.key; }\r\n      \
    \      };\r\n            std::priority_queue<Q> que;\r\n            dist[s] =\
    \ 0;\r\n            que.push(Q{0, s});\r\n            while (!que.empty()) {\r\
    \n                int v = que.top().to;\r\n                que.pop();\r\n    \
    \            if (vis[v]) continue;\r\n                vis[v] = true;\r\n     \
    \           if (v == t) break;\r\n                // dist[v] = shortest(s, v)\
    \ + dual[s] - dual[v]\r\n                // dist[v] >= 0 (all reduced cost are\
    \ positive)\r\n                // dist[v] <= (n-1)C\r\n                for (int\
    \ i = 0; i < int(g[v].size()); i++) {\r\n                    auto e = g[v][i];\r\
    \n                    if (vis[e.to] || !e.cap) continue;\r\n                 \
    \   // |-dual[e.to] + dual[v]| <= (n-1)C\r\n                    // cost <= C -\
    \ -(n-1)C + 0 = nC\r\n                    Cost cost = e.cost - dual[e.to] + dual[v];\r\
    \n                    if (dist[e.to] - dist[v] > cost) {\r\n                 \
    \       dist[e.to] = dist[v] + cost;\r\n                        pv[e.to] = v;\r\
    \n                        pe[e.to] = i;\r\n                        que.push(Q{dist[e.to],\
    \ e.to});\r\n                    }\r\n                }\r\n            }\r\n \
    \           if (!vis[t]) {\r\n                return false;\r\n            }\r\
    \n\r\n            for (int v = 0; v < _n; v++) {\r\n                if (!vis[v])\
    \ continue;\r\n                // dual[v] = dual[v] - dist[t] + dist[v]\r\n  \
    \              //         = dual[v] - (shortest(s, t) + dual[s] - dual[t]) + (shortest(s,\
    \ v) + dual[s] - dual[v])\r\n                //         = - shortest(s, t) + dual[t]\
    \ + shortest(s, v)\r\n                //         = shortest(s, v) - shortest(s,\
    \ t) >= 0 - (n-1)C\r\n                dual[v] -= dist[t] - dist[v];\r\n      \
    \      }\r\n            return true;\r\n        };\r\n        Cap flow = 0;\r\n\
    \        Cost cost = 0, prev_cost = -1;\r\n        std::vector<std::pair<Cap,\
    \ Cost>> result;\r\n        result.push_back({flow, cost});\r\n        while (flow\
    \ < flow_limit) {\r\n            if (!dual_ref()) break;\r\n            Cap c\
    \ = flow_limit - flow;\r\n            for (int v = t; v != s; v = pv[v]) {\r\n\
    \                c = std::min(c, g[pv[v]][pe[v]].cap);\r\n            }\r\n  \
    \          for (int v = t; v != s; v = pv[v]) {\r\n                auto& e = g[pv[v]][pe[v]];\r\
    \n                e.cap -= c;\r\n                g[v][e.rev].cap += c;\r\n   \
    \         }\r\n            Cost d = -dual[s];\r\n            flow += c;\r\n  \
    \          cost += c * d;\r\n            if (prev_cost == d) {\r\n           \
    \     result.pop_back();\r\n            }\r\n            result.push_back({flow,\
    \ cost});\r\n            prev_cost = cost;\r\n        }\r\n        return result;\r\
    \n    }\r\n\r\n  private:\r\n    int _n;\r\n\r\n    struct _edge {\r\n       \
    \ int to, rev;\r\n        Cap cap;\r\n        Cost cost;\r\n    };\r\n\r\n   \
    \ std::vector<std::pair<int, int>> pos;\r\n    std::vector<std::vector<_edge>>\
    \ g;\r\n};\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_MINCOSTFLOW_HPP\r\n#define ATCODER_MINCOSTFLOW_HPP 1\r\n\r\
    \n#include <algorithm>\r\n#include <cassert>\r\n#include <limits>\r\n#include\
    \ <queue>\r\n#include <vector>\r\n\r\nnamespace atcoder {\r\n\r\ntemplate <class\
    \ Cap, class Cost> struct mcf_graph {\r\n  public:\r\n    mcf_graph() {}\r\n \
    \   mcf_graph(int n) : _n(n), g(n) {}\r\n\r\n    int add_edge(int from, int to,\
    \ Cap cap, Cost cost) {\r\n        assert(0 <= from && from < _n);\r\n       \
    \ assert(0 <= to && to < _n);\r\n        int m = int(pos.size());\r\n        pos.push_back({from,\
    \ int(g[from].size())});\r\n        g[from].push_back(_edge{to, int(g[to].size()),\
    \ cap, cost});\r\n        g[to].push_back(_edge{from, int(g[from].size()) - 1,\
    \ 0, -cost});\r\n        return m;\r\n    }\r\n\r\n    struct edge {\r\n     \
    \   int from, to;\r\n        Cap cap, flow;\r\n        Cost cost;\r\n    };\r\n\
    \r\n    edge get_edge(int i) {\r\n        int m = int(pos.size());\r\n       \
    \ assert(0 <= i && i < m);\r\n        auto _e = g[pos[i].first][pos[i].second];\r\
    \n        auto _re = g[_e.to][_e.rev];\r\n        return edge{\r\n           \
    \ pos[i].first, _e.to, _e.cap + _re.cap, _re.cap, _e.cost,\r\n        };\r\n \
    \   }\r\n    std::vector<edge> edges() {\r\n        int m = int(pos.size());\r\
    \n        std::vector<edge> result(m);\r\n        for (int i = 0; i < m; i++)\
    \ {\r\n            result[i] = get_edge(i);\r\n        }\r\n        return result;\r\
    \n    }\r\n\r\n    std::pair<Cap, Cost> flow(int s, int t) {\r\n        return\
    \ flow(s, t, std::numeric_limits<Cap>::max());\r\n    }\r\n    std::pair<Cap,\
    \ Cost> flow(int s, int t, Cap flow_limit) {\r\n        return slope(s, t, flow_limit).back();\r\
    \n    }\r\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t) {\r\n   \
    \     return slope(s, t, std::numeric_limits<Cap>::max());\r\n    }\r\n    std::vector<std::pair<Cap,\
    \ Cost>> slope(int s, int t, Cap flow_limit) {\r\n        assert(0 <= s && s <\
    \ _n);\r\n        assert(0 <= t && t < _n);\r\n        assert(s != t);\r\n   \
    \     // variants (C = maxcost):\r\n        // -(n-1)C <= dual[s] <= dual[i] <=\
    \ dual[t] = 0\r\n        // reduced cost (= e.cost + dual[e.from] - dual[e.to])\
    \ >= 0 for all edge\r\n        std::vector<Cost> dual(_n, 0), dist(_n);\r\n  \
    \      std::vector<int> pv(_n), pe(_n);\r\n        std::vector<bool> vis(_n);\r\
    \n        auto dual_ref = [&]() {\r\n            std::fill(dist.begin(), dist.end(),\r\
    \n                      std::numeric_limits<Cost>::max());\r\n            std::fill(pv.begin(),\
    \ pv.end(), -1);\r\n            std::fill(pe.begin(), pe.end(), -1);\r\n     \
    \       std::fill(vis.begin(), vis.end(), false);\r\n            struct Q {\r\n\
    \                Cost key;\r\n                int to;\r\n                bool\
    \ operator<(Q r) const { return key > r.key; }\r\n            };\r\n         \
    \   std::priority_queue<Q> que;\r\n            dist[s] = 0;\r\n            que.push(Q{0,\
    \ s});\r\n            while (!que.empty()) {\r\n                int v = que.top().to;\r\
    \n                que.pop();\r\n                if (vis[v]) continue;\r\n    \
    \            vis[v] = true;\r\n                if (v == t) break;\r\n        \
    \        // dist[v] = shortest(s, v) + dual[s] - dual[v]\r\n                //\
    \ dist[v] >= 0 (all reduced cost are positive)\r\n                // dist[v] <=\
    \ (n-1)C\r\n                for (int i = 0; i < int(g[v].size()); i++) {\r\n \
    \                   auto e = g[v][i];\r\n                    if (vis[e.to] ||\
    \ !e.cap) continue;\r\n                    // |-dual[e.to] + dual[v]| <= (n-1)C\r\
    \n                    // cost <= C - -(n-1)C + 0 = nC\r\n                    Cost\
    \ cost = e.cost - dual[e.to] + dual[v];\r\n                    if (dist[e.to]\
    \ - dist[v] > cost) {\r\n                        dist[e.to] = dist[v] + cost;\r\
    \n                        pv[e.to] = v;\r\n                        pe[e.to] =\
    \ i;\r\n                        que.push(Q{dist[e.to], e.to});\r\n           \
    \         }\r\n                }\r\n            }\r\n            if (!vis[t])\
    \ {\r\n                return false;\r\n            }\r\n\r\n            for (int\
    \ v = 0; v < _n; v++) {\r\n                if (!vis[v]) continue;\r\n        \
    \        // dual[v] = dual[v] - dist[t] + dist[v]\r\n                //      \
    \   = dual[v] - (shortest(s, t) + dual[s] - dual[t]) + (shortest(s, v) + dual[s]\
    \ - dual[v])\r\n                //         = - shortest(s, t) + dual[t] + shortest(s,\
    \ v)\r\n                //         = shortest(s, v) - shortest(s, t) >= 0 - (n-1)C\r\
    \n                dual[v] -= dist[t] - dist[v];\r\n            }\r\n         \
    \   return true;\r\n        };\r\n        Cap flow = 0;\r\n        Cost cost =\
    \ 0, prev_cost = -1;\r\n        std::vector<std::pair<Cap, Cost>> result;\r\n\
    \        result.push_back({flow, cost});\r\n        while (flow < flow_limit)\
    \ {\r\n            if (!dual_ref()) break;\r\n            Cap c = flow_limit -\
    \ flow;\r\n            for (int v = t; v != s; v = pv[v]) {\r\n              \
    \  c = std::min(c, g[pv[v]][pe[v]].cap);\r\n            }\r\n            for (int\
    \ v = t; v != s; v = pv[v]) {\r\n                auto& e = g[pv[v]][pe[v]];\r\n\
    \                e.cap -= c;\r\n                g[v][e.rev].cap += c;\r\n    \
    \        }\r\n            Cost d = -dual[s];\r\n            flow += c;\r\n   \
    \         cost += c * d;\r\n            if (prev_cost == d) {\r\n            \
    \    result.pop_back();\r\n            }\r\n            result.push_back({flow,\
    \ cost});\r\n            prev_cost = cost;\r\n        }\r\n        return result;\r\
    \n    }\r\n\r\n  private:\r\n    int _n;\r\n\r\n    struct _edge {\r\n       \
    \ int to, rev;\r\n        Cap cap;\r\n        Cost cost;\r\n    };\r\n\r\n   \
    \ std::vector<std::pair<int, int>> pos;\r\n    std::vector<std::vector<_edge>>\
    \ g;\r\n};\r\n\r\n}  // namespace atcoder\r\n\r\n#endif  // ATCODER_MINCOSTFLOW_HPP\r\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: lib/atcoder/mincostflow.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/mincostflow.hpp
layout: document
redirect_from:
- /library/lib/atcoder/mincostflow.hpp
- /library/lib/atcoder/mincostflow.hpp.html
title: lib/atcoder/mincostflow.hpp
---
