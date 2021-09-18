---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/atcoder/internal_queue.hpp
    title: lib/atcoder/internal_queue.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/maxflow.hpp\"\n\n\n\r\n#include <algorithm>\r\
    \n#include <atcoder/internal_queue>\r\n#include <cassert>\r\n#include <limits>\r\
    \n#include <queue>\r\n#include <vector>\r\n\r\nnamespace atcoder {\r\n\r\ntemplate\
    \ <class Cap> struct mf_graph {\r\n  public:\r\n    mf_graph() : _n(0) {}\r\n\
    \    mf_graph(int n) : _n(n), g(n) {}\r\n\r\n    int add_edge(int from, int to,\
    \ Cap cap) {\r\n        assert(0 <= from && from < _n);\r\n        assert(0 <=\
    \ to && to < _n);\r\n        assert(0 <= cap);\r\n        int m = int(pos.size());\r\
    \n        pos.push_back({from, int(g[from].size())});\r\n        g[from].push_back(_edge{to,\
    \ int(g[to].size()), cap});\r\n        g[to].push_back(_edge{from, int(g[from].size())\
    \ - 1, 0});\r\n        return m;\r\n    }\r\n\r\n    struct edge {\r\n       \
    \ int from, to;\r\n        Cap cap, flow;\r\n    };\r\n\r\n    edge get_edge(int\
    \ i) {\r\n        int m = int(pos.size());\r\n        assert(0 <= i && i < m);\r\
    \n        auto _e = g[pos[i].first][pos[i].second];\r\n        auto _re = g[_e.to][_e.rev];\r\
    \n        return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};\r\n   \
    \ }\r\n    std::vector<edge> edges() {\r\n        int m = int(pos.size());\r\n\
    \        std::vector<edge> result;\r\n        for (int i = 0; i < m; i++) {\r\n\
    \            result.push_back(get_edge(i));\r\n        }\r\n        return result;\r\
    \n    }\r\n    void change_edge(int i, Cap new_cap, Cap new_flow) {\r\n      \
    \  int m = int(pos.size());\r\n        assert(0 <= i && i < m);\r\n        assert(0\
    \ <= new_flow && new_flow <= new_cap);\r\n        auto& _e = g[pos[i].first][pos[i].second];\r\
    \n        auto& _re = g[_e.to][_e.rev];\r\n        _e.cap = new_cap - new_flow;\r\
    \n        _re.cap = new_flow;\r\n    }\r\n\r\n    Cap flow(int s, int t) {\r\n\
    \        return flow(s, t, std::numeric_limits<Cap>::max());\r\n    }\r\n    Cap\
    \ flow(int s, int t, Cap flow_limit) {\r\n        assert(0 <= s && s < _n);\r\n\
    \        assert(0 <= t && t < _n);\r\n\r\n        std::vector<int> level(_n),\
    \ iter(_n);\r\n        internal::simple_queue<int> que;\r\n\r\n        auto bfs\
    \ = [&]() {\r\n            std::fill(level.begin(), level.end(), -1);\r\n    \
    \        level[s] = 0;\r\n            que.clear();\r\n            que.push(s);\r\
    \n            while (!que.empty()) {\r\n                int v = que.front();\r\
    \n                que.pop();\r\n                for (auto e : g[v]) {\r\n    \
    \                if (e.cap == 0 || level[e.to] >= 0) continue;\r\n           \
    \         level[e.to] = level[v] + 1;\r\n                    if (e.to == t) return;\r\
    \n                    que.push(e.to);\r\n                }\r\n            }\r\n\
    \        };\r\n        auto dfs = [&](auto self, int v, Cap up) {\r\n        \
    \    if (v == s) return up;\r\n            Cap res = 0;\r\n            int level_v\
    \ = level[v];\r\n            for (int& i = iter[v]; i < int(g[v].size()); i++)\
    \ {\r\n                _edge& e = g[v][i];\r\n                if (level_v <= level[e.to]\
    \ || g[e.to][e.rev].cap == 0) continue;\r\n                Cap d =\r\n       \
    \             self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));\r\n  \
    \              if (d <= 0) continue;\r\n                g[v][i].cap += d;\r\n\
    \                g[e.to][e.rev].cap -= d;\r\n                res += d;\r\n   \
    \             if (res == up) break;\r\n            }\r\n            return res;\r\
    \n        };\r\n\r\n        Cap flow = 0;\r\n        while (flow < flow_limit)\
    \ {\r\n            bfs();\r\n            if (level[t] == -1) break;\r\n      \
    \      std::fill(iter.begin(), iter.end(), 0);\r\n            while (flow < flow_limit)\
    \ {\r\n                Cap f = dfs(dfs, t, flow_limit - flow);\r\n           \
    \     if (!f) break;\r\n                flow += f;\r\n            }\r\n      \
    \  }\r\n        return flow;\r\n    }\r\n\r\n    std::vector<bool> min_cut(int\
    \ s) {\r\n        std::vector<bool> visited(_n);\r\n        internal::simple_queue<int>\
    \ que;\r\n        que.push(s);\r\n        while (!que.empty()) {\r\n         \
    \   int p = que.front();\r\n            que.pop();\r\n            visited[p] =\
    \ true;\r\n            for (auto e : g[p]) {\r\n                if (e.cap && !visited[e.to])\
    \ {\r\n                    visited[e.to] = true;\r\n                    que.push(e.to);\r\
    \n                }\r\n            }\r\n        }\r\n        return visited;\r\
    \n    }\r\n\r\n  private:\r\n    int _n;\r\n    struct _edge {\r\n        int\
    \ to, rev;\r\n        Cap cap;\r\n    };\r\n    std::vector<std::pair<int, int>>\
    \ pos;\r\n    std::vector<std::vector<_edge>> g;\r\n};\r\n\r\n}  // namespace\
    \ atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_MAXFLOW_HPP\r\n#define ATCODER_MAXFLOW_HPP 1\r\n\r\n#include\
    \ <algorithm>\r\n#include <atcoder/internal_queue>\r\n#include <cassert>\r\n#include\
    \ <limits>\r\n#include <queue>\r\n#include <vector>\r\n\r\nnamespace atcoder {\r\
    \n\r\ntemplate <class Cap> struct mf_graph {\r\n  public:\r\n    mf_graph() :\
    \ _n(0) {}\r\n    mf_graph(int n) : _n(n), g(n) {}\r\n\r\n    int add_edge(int\
    \ from, int to, Cap cap) {\r\n        assert(0 <= from && from < _n);\r\n    \
    \    assert(0 <= to && to < _n);\r\n        assert(0 <= cap);\r\n        int m\
    \ = int(pos.size());\r\n        pos.push_back({from, int(g[from].size())});\r\n\
    \        g[from].push_back(_edge{to, int(g[to].size()), cap});\r\n        g[to].push_back(_edge{from,\
    \ int(g[from].size()) - 1, 0});\r\n        return m;\r\n    }\r\n\r\n    struct\
    \ edge {\r\n        int from, to;\r\n        Cap cap, flow;\r\n    };\r\n\r\n\
    \    edge get_edge(int i) {\r\n        int m = int(pos.size());\r\n        assert(0\
    \ <= i && i < m);\r\n        auto _e = g[pos[i].first][pos[i].second];\r\n   \
    \     auto _re = g[_e.to][_e.rev];\r\n        return edge{pos[i].first, _e.to,\
    \ _e.cap + _re.cap, _re.cap};\r\n    }\r\n    std::vector<edge> edges() {\r\n\
    \        int m = int(pos.size());\r\n        std::vector<edge> result;\r\n   \
    \     for (int i = 0; i < m; i++) {\r\n            result.push_back(get_edge(i));\r\
    \n        }\r\n        return result;\r\n    }\r\n    void change_edge(int i,\
    \ Cap new_cap, Cap new_flow) {\r\n        int m = int(pos.size());\r\n       \
    \ assert(0 <= i && i < m);\r\n        assert(0 <= new_flow && new_flow <= new_cap);\r\
    \n        auto& _e = g[pos[i].first][pos[i].second];\r\n        auto& _re = g[_e.to][_e.rev];\r\
    \n        _e.cap = new_cap - new_flow;\r\n        _re.cap = new_flow;\r\n    }\r\
    \n\r\n    Cap flow(int s, int t) {\r\n        return flow(s, t, std::numeric_limits<Cap>::max());\r\
    \n    }\r\n    Cap flow(int s, int t, Cap flow_limit) {\r\n        assert(0 <=\
    \ s && s < _n);\r\n        assert(0 <= t && t < _n);\r\n\r\n        std::vector<int>\
    \ level(_n), iter(_n);\r\n        internal::simple_queue<int> que;\r\n\r\n   \
    \     auto bfs = [&]() {\r\n            std::fill(level.begin(), level.end(),\
    \ -1);\r\n            level[s] = 0;\r\n            que.clear();\r\n          \
    \  que.push(s);\r\n            while (!que.empty()) {\r\n                int v\
    \ = que.front();\r\n                que.pop();\r\n                for (auto e\
    \ : g[v]) {\r\n                    if (e.cap == 0 || level[e.to] >= 0) continue;\r\
    \n                    level[e.to] = level[v] + 1;\r\n                    if (e.to\
    \ == t) return;\r\n                    que.push(e.to);\r\n                }\r\n\
    \            }\r\n        };\r\n        auto dfs = [&](auto self, int v, Cap up)\
    \ {\r\n            if (v == s) return up;\r\n            Cap res = 0;\r\n    \
    \        int level_v = level[v];\r\n            for (int& i = iter[v]; i < int(g[v].size());\
    \ i++) {\r\n                _edge& e = g[v][i];\r\n                if (level_v\
    \ <= level[e.to] || g[e.to][e.rev].cap == 0) continue;\r\n                Cap\
    \ d =\r\n                    self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));\r\
    \n                if (d <= 0) continue;\r\n                g[v][i].cap += d;\r\
    \n                g[e.to][e.rev].cap -= d;\r\n                res += d;\r\n  \
    \              if (res == up) break;\r\n            }\r\n            return res;\r\
    \n        };\r\n\r\n        Cap flow = 0;\r\n        while (flow < flow_limit)\
    \ {\r\n            bfs();\r\n            if (level[t] == -1) break;\r\n      \
    \      std::fill(iter.begin(), iter.end(), 0);\r\n            while (flow < flow_limit)\
    \ {\r\n                Cap f = dfs(dfs, t, flow_limit - flow);\r\n           \
    \     if (!f) break;\r\n                flow += f;\r\n            }\r\n      \
    \  }\r\n        return flow;\r\n    }\r\n\r\n    std::vector<bool> min_cut(int\
    \ s) {\r\n        std::vector<bool> visited(_n);\r\n        internal::simple_queue<int>\
    \ que;\r\n        que.push(s);\r\n        while (!que.empty()) {\r\n         \
    \   int p = que.front();\r\n            que.pop();\r\n            visited[p] =\
    \ true;\r\n            for (auto e : g[p]) {\r\n                if (e.cap && !visited[e.to])\
    \ {\r\n                    visited[e.to] = true;\r\n                    que.push(e.to);\r\
    \n                }\r\n            }\r\n        }\r\n        return visited;\r\
    \n    }\r\n\r\n  private:\r\n    int _n;\r\n    struct _edge {\r\n        int\
    \ to, rev;\r\n        Cap cap;\r\n    };\r\n    std::vector<std::pair<int, int>>\
    \ pos;\r\n    std::vector<std::vector<_edge>> g;\r\n};\r\n\r\n}  // namespace\
    \ atcoder\r\n\r\n#endif  // ATCODER_MAXFLOW_HPP\r\n"
  dependsOn:
  - lib/atcoder/internal_queue.hpp
  isVerificationFile: false
  path: lib/atcoder/maxflow.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/maxflow.hpp
layout: document
redirect_from:
- /library/lib/atcoder/maxflow.hpp
- /library/lib/atcoder/maxflow.hpp.html
title: lib/atcoder/maxflow.hpp
---
