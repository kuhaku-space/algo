---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/min_cost_flow.test.cpp
    title: test/aoj/grl/min_cost_flow.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5C0F\u8CBB\u7528\u6D41"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u6700\u5C0F\u8CBB\
    \u7528\u6D41\r\n *\r\n * @tparam Cap\r\n * @tparam Cost\r\n */\r\ntemplate <class\
    \ Cap, class Cost>\r\nstruct mcf_graph {\r\n    mcf_graph() {}\r\n    explicit\
    \ mcf_graph(int n) : _n(n) {}\r\n\r\n    int add_edge(int from, int to, Cap cap,\
    \ Cost cost) {\r\n        assert(0 <= from && from < _n);\r\n        assert(0\
    \ <= to && to < _n);\r\n        assert(0 <= cap);\r\n        assert(0 <= cost);\r\
    \n        int m = int(_edges.size());\r\n        _edges.emplace_back(from, to,\
    \ cap, 0, cost);\r\n        return m;\r\n    }\r\n\r\n    struct edge {\r\n  \
    \      int from, to;\r\n        Cap cap, flow;\r\n        Cost cost;\r\n\r\n \
    \       constexpr edge(int _from, int _to, Cap _cap, Cap _flow, Cost _cost)\r\n\
    \            : from(_from), to(_to), cap(_cap), flow(_flow), cost(_cost) {}\r\n\
    \    };\r\n\r\n    edge get_edge(int i) {\r\n        int m = int(_edges.size());\r\
    \n        assert(0 <= i && i < m);\r\n        return _edges[i];\r\n    }\r\n \
    \   std::vector<edge> edges() { return _edges; }\r\n\r\n    std::pair<Cap, Cost>\
    \ flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max()); }\r\
    \n    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {\r\n        return\
    \ slope(s, t, flow_limit).back();\r\n    }\r\n    std::vector<std::pair<Cap, Cost>>\
    \ slope(int s, int t) {\r\n        return slope(s, t, std::numeric_limits<Cap>::max());\r\
    \n    }\r\n    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit)\
    \ {\r\n        assert(0 <= s && s < _n);\r\n        assert(0 <= t && t < _n);\r\
    \n        assert(s != t);\r\n\r\n        int m = int(_edges.size());\r\n     \
    \   std::vector<int> edge_idx(m);\r\n\r\n        auto g = [&]() {\r\n        \
    \    std::vector<int> degree(_n), redge_idx(m);\r\n            std::vector<std::pair<int,\
    \ _edge>> elist;\r\n            elist.reserve(2 * m);\r\n            for (int\
    \ i = 0; i < m; ++i) {\r\n                auto e = _edges[i];\r\n            \
    \    edge_idx[i] = degree[e.from]++;\r\n                redge_idx[i] = degree[e.to]++;\r\
    \n                elist.emplace_back(e.from, _edge(e.to, -1, e.cap - e.flow, e.cost));\r\
    \n                elist.emplace_back(e.to, _edge(e.from, -1, e.flow, -e.cost));\r\
    \n            }\r\n            auto _g = csr<_edge>(_n, elist);\r\n          \
    \  for (int i = 0; i < m; ++i) {\r\n                auto e = _edges[i];\r\n  \
    \              edge_idx[i] += _g.start[e.from];\r\n                redge_idx[i]\
    \ += _g.start[e.to];\r\n                _g.elist[edge_idx[i]].rev = redge_idx[i];\r\
    \n                _g.elist[redge_idx[i]].rev = edge_idx[i];\r\n            }\r\
    \n            return _g;\r\n        }();\r\n\r\n        auto result = slope(g,\
    \ s, t, flow_limit);\r\n\r\n        for (int i = 0; i < m; ++i) {\r\n        \
    \    auto e = g.elist[edge_idx[i]];\r\n            _edges[i].flow = _edges[i].cap\
    \ - e.cap;\r\n        }\r\n\r\n        return result;\r\n    }\r\n\r\n  private:\r\
    \n    int _n;\r\n    std::vector<edge> _edges;\r\n\r\n    struct _edge {\r\n \
    \       int to, rev;\r\n        Cap cap;\r\n        Cost cost;\r\n\r\n       \
    \ constexpr _edge() : to(), rev(), cap(), cost() {}\r\n        constexpr _edge(int\
    \ _to, int _rev, Cap _cap, Cost _cost)\r\n            : to(_to), rev(_rev), cap(_cap),\
    \ cost(_cost) {}\r\n    };\r\n\r\n    template <class E>\r\n    struct csr {\r\
    \n        std::vector<int> start;\r\n        std::vector<E> elist;\r\n       \
    \ explicit csr(int n, const std::vector<std::pair<int, E>> &edges)\r\n       \
    \     : start(n + 1), elist(edges.size()) {\r\n            for (auto e : edges)\
    \ {\r\n                start[e.first + 1]++;\r\n            }\r\n            for\
    \ (int i = 1; i <= n; i++) {\r\n                start[i] += start[i - 1];\r\n\
    \            }\r\n            auto counter = start;\r\n            for (auto e\
    \ : edges) {\r\n                elist[counter[e.first]++] = e.second;\r\n    \
    \        }\r\n        }\r\n    };\r\n\r\n    std::vector<std::pair<Cap, Cost>>\
    \ slope(csr<_edge> &g, int s, int t, Cap flow_limit) {\r\n        std::vector<std::pair<Cost,\
    \ Cost>> dual_dist(_n);\r\n        std::vector<int> prev_e(_n);\r\n        std::vector<bool>\
    \ vis(_n);\r\n        struct Q {\r\n            Cost key;\r\n            int to;\r\
    \n            constexpr Q(Cost _key, int _to) : key(_key), to(_to) {}\r\n    \
    \        bool operator<(Q r) const { return key > r.key; }\r\n        };\r\n \
    \       std::vector<int> que_min;\r\n        std::vector<Q> que;\r\n        auto\
    \ dual_ref = [&]() {\r\n            for (int i = 0; i < _n; ++i) {\r\n       \
    \         dual_dist[i].second = std::numeric_limits<Cost>::max();\r\n        \
    \    }\r\n            std::fill(vis.begin(), vis.end(), false);\r\n          \
    \  que_min.clear();\r\n            que.clear();\r\n\r\n            size_t heap_r\
    \ = 0;\r\n\r\n            dual_dist[s].second = 0;\r\n            que_min.emplace_back(s);\r\
    \n            while (!que_min.empty() || !que.empty()) {\r\n                int\
    \ v;\r\n                if (!que_min.empty()) {\r\n                    v = que_min.back();\r\
    \n                    que_min.pop_back();\r\n                } else {\r\n    \
    \                while (heap_r < que.size()) {\r\n                        ++heap_r;\r\
    \n                        std::push_heap(que.begin(), que.begin() + heap_r);\r\
    \n                    }\r\n                    v = que.front().to;\r\n       \
    \             std::pop_heap(que.begin(), que.end());\r\n                    que.pop_back();\r\
    \n                    heap_r--;\r\n                }\r\n                if (vis[v])\
    \ continue;\r\n                vis[v] = true;\r\n                if (v == t) break;\r\
    \n                Cost dual_v = dual_dist[v].first, dist_v = dual_dist[v].second;\r\
    \n                for (int i = g.start[v]; i < g.start[v + 1]; ++i) {\r\n    \
    \                auto e = g.elist[i];\r\n                    if (!e.cap) continue;\r\
    \n                    Cost cost = e.cost - dual_dist[e.to].first + dual_v;\r\n\
    \                    if (dual_dist[e.to].second - dist_v > cost) {\r\n       \
    \                 Cost dist_to = dist_v + cost;\r\n                        dual_dist[e.to].second\
    \ = dist_to;\r\n                        prev_e[e.to] = e.rev;\r\n            \
    \            if (dist_to == dist_v) {\r\n                            que_min.emplace_back(e.to);\r\
    \n                        } else {\r\n                            que.emplace_back(dist_to,\
    \ e.to);\r\n                        }\r\n                    }\r\n           \
    \     }\r\n            }\r\n            if (!vis[t]) {\r\n                return\
    \ false;\r\n            }\r\n\r\n            for (int v = 0; v < _n; ++v) {\r\n\
    \                if (!vis[v]) continue;\r\n                dual_dist[v].first\
    \ -= dual_dist[t].second - dual_dist[v].second;\r\n            }\r\n         \
    \   return true;\r\n        };\r\n        Cap flow = 0;\r\n        Cost cost =\
    \ 0, prev_cost_per_flow = -1;\r\n        std::vector<std::pair<Cap, Cost>> result\
    \ = {{Cap(0), Cost(0)}};\r\n        while (flow < flow_limit) {\r\n          \
    \  if (!dual_ref()) break;\r\n            Cap c = flow_limit - flow;\r\n     \
    \       for (int v = t; v != s; v = g.elist[prev_e[v]].to) {\r\n             \
    \   c = std::min(c, g.elist[g.elist[prev_e[v]].rev].cap);\r\n            }\r\n\
    \            for (int v = t; v != s; v = g.elist[prev_e[v]].to) {\r\n        \
    \        auto &e = g.elist[prev_e[v]];\r\n                e.cap += c;\r\n    \
    \            g.elist[e.rev].cap -= c;\r\n            }\r\n            Cost d =\
    \ -dual_dist[s].first;\r\n            flow += c;\r\n            cost += c * d;\r\
    \n            if (prev_cost_per_flow == d) {\r\n                result.pop_back();\r\
    \n            }\r\n            result.emplace_back(flow, cost);\r\n          \
    \  prev_cost_per_flow = d;\r\n        }\r\n        return result;\r\n    }\r\n\
    };\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/flow/min_cost_flow.hpp
  requiredBy: []
  timestamp: '2022-07-16 07:44:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/min_cost_flow.test.cpp
documentation_of: lib/flow/min_cost_flow.hpp
layout: document
redirect_from:
- /library/lib/flow/min_cost_flow.hpp
- /library/lib/flow/min_cost_flow.hpp.html
title: "\u6700\u5C0F\u8CBB\u7528\u6D41"
---
