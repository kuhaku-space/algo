---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/bipartite_matching.test.cpp
    title: test/aoj/grl/bipartite_matching.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/max_flow.test.cpp
    title: test/aoj/grl/max_flow.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5927\u6D41"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u6700\u5927\u6D41\
    \r\n *\r\n * @tparam Cap\r\n */\r\ntemplate <class Cap>\r\nstruct mf_graph {\r\
    \n    mf_graph() : _n(0) {}\r\n    explicit mf_graph(int n) : _n(n), g(n) {}\r\
    \n\r\n    int add_edge(int from, int to, Cap cap) {\r\n        assert(0 <= from\
    \ && from < _n);\r\n        assert(0 <= to && to < _n);\r\n        assert(0 <=\
    \ cap);\r\n        int m = int(pos.size());\r\n        pos.emplace_back(from,\
    \ int(g[from].size()));\r\n        int from_id = int(g[from].size());\r\n    \
    \    int to_id = int(g[to].size());\r\n        if (from == to) ++to_id;\r\n  \
    \      g[from].emplace_back(to, to_id, cap);\r\n        g[to].emplace_back(from,\
    \ from_id, 0);\r\n        return m;\r\n    }\r\n\r\n    struct edge {\r\n    \
    \    int from, to;\r\n        Cap cap, flow;\r\n    };\r\n\r\n    edge get_edge(int\
    \ i) {\r\n        int m = int(pos.size());\r\n        assert(0 <= i && i < m);\r\
    \n        auto _e = g[pos[i].first][pos[i].second];\r\n        auto _re = g[_e.to][_e.rev];\r\
    \n        return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};\r\n   \
    \ }\r\n    std::vector<edge> edges() {\r\n        int m = int(pos.size());\r\n\
    \        std::vector<edge> result;\r\n        for (int i = 0; i < m; ++i) {\r\n\
    \            result.emplace_back(get_edge(i));\r\n        }\r\n        return\
    \ result;\r\n    }\r\n    void change_edge(int i, Cap new_cap, Cap new_flow) {\r\
    \n        int m = int(pos.size());\r\n        assert(0 <= i && i < m);\r\n   \
    \     assert(0 <= new_flow && new_flow <= new_cap);\r\n        auto &_e = g[pos[i].first][pos[i].second];\r\
    \n        auto &_re = g[_e.to][_e.rev];\r\n        _e.cap = new_cap - new_flow;\r\
    \n        _re.cap = new_flow;\r\n    }\r\n\r\n    Cap flow(int s, int t) { return\
    \ flow(s, t, std::numeric_limits<Cap>::max()); }\r\n    Cap flow(int s, int t,\
    \ Cap flow_limit) {\r\n        assert(0 <= s && s < _n);\r\n        assert(0 <=\
    \ t && t < _n);\r\n        assert(s != t);\r\n\r\n        std::vector<int> level(_n),\
    \ iter(_n);\r\n        auto bfs = [&]() {\r\n            std::fill(level.begin(),\
    \ level.end(), -1);\r\n            level[s] = 0;\r\n            std::queue<int>\
    \ que;\r\n            que.emplace(s);\r\n            while (!que.empty()) {\r\n\
    \                int v = que.front();\r\n                que.pop();\r\n      \
    \          for (auto e : g[v]) {\r\n                    if (e.cap == 0 || level[e.to]\
    \ >= 0) continue;\r\n                    level[e.to] = level[v] + 1;\r\n     \
    \               if (e.to == t) return;\r\n                    que.emplace(e.to);\r\
    \n                }\r\n            }\r\n        };\r\n        auto dfs = [&](auto\
    \ self, int v, Cap up) {\r\n            if (v == s) return up;\r\n           \
    \ Cap res = 0;\r\n            int level_v = level[v];\r\n            for (int\
    \ &i = iter[v]; i < int(g[v].size()); ++i) {\r\n                _edge &e = g[v][i];\r\
    \n                if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;\r\
    \n                Cap d = self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));\r\
    \n                if (d <= 0) continue;\r\n                g[v][i].cap += d;\r\
    \n                g[e.to][e.rev].cap -= d;\r\n                res += d;\r\n  \
    \              if (res == up) return res;\r\n            }\r\n            level[v]\
    \ = _n;\r\n            return res;\r\n        };\r\n\r\n        Cap flow = 0;\r\
    \n        while (flow < flow_limit) {\r\n            bfs();\r\n            if\
    \ (level[t] == -1) break;\r\n            std::fill(iter.begin(), iter.end(), 0);\r\
    \n            Cap f = dfs(dfs, t, flow_limit - flow);\r\n            if (!f) break;\r\
    \n            flow += f;\r\n        }\r\n        return flow;\r\n    }\r\n\r\n\
    \    std::vector<bool> min_cut(int s) {\r\n        std::vector<bool> visited(_n);\r\
    \n        std::queue<int> que;\r\n        que.emplace(s);\r\n        while (!que.empty())\
    \ {\r\n            int p = que.front();\r\n            que.pop();\r\n        \
    \    visited[p] = true;\r\n            for (auto e : g[p]) {\r\n             \
    \   if (e.cap && !visited[e.to]) {\r\n                    visited[e.to] = true;\r\
    \n                    que.emplace(e.to);\r\n                }\r\n            }\r\
    \n        }\r\n        return visited;\r\n    }\r\n\r\n  private:\r\n    int _n;\r\
    \n    struct _edge {\r\n        int to, rev;\r\n        Cap cap;\r\n\r\n     \
    \   constexpr _edge(int _to, int _rev, Cap _cap) : to(_to), rev(_rev), cap(_cap)\
    \ {}\r\n    };\r\n    std::vector<std::pair<int, int>> pos;\r\n    std::vector<std::vector<_edge>>\
    \ g;\r\n};"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/flow/max_flow.hpp
  requiredBy: []
  timestamp: '2022-07-16 07:23:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/bipartite_matching.test.cpp
  - test/aoj/grl/max_flow.test.cpp
documentation_of: lib/flow/max_flow.hpp
layout: document
redirect_from:
- /library/lib/flow/max_flow.hpp
- /library/lib/flow/max_flow.hpp.html
title: "\u6700\u5927\u6D41"
---
