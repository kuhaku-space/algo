---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/hld.hpp
    title: "HL\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: lib/tree/union_find.hpp
    title: "\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1211.test.cpp
    title: test/yukicoder/1211.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/1242.test.cpp
    title: test/yukicoder/1242.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: tree/hld.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"tree/hld.hpp\"\n#include \"tree/union_find.hpp\"\
    \n\nstruct functional_graph {\n    functional_graph() = default;\n    functional_graph(const\
    \ std::vector<int> &_to) : functional_graph(_to.size(), _to) {\n        union_find\
    \ uf(_size);\n        for (int i = 0; i < _size; ++i) {\n            assert(0\
    \ <= to[i] && to[i] < _size);\n            if (!uf.unite(i, to[i])) root[i] =\
    \ i;\n        }\n        for (int i = 0; i < _size; ++i) {\n            if (root[i]\
    \ == i) root[uf.root(i)] = root[i];\n        }\n        for (int i = 0; i < _size;\
    \ ++i) root[i] = root[uf.root(i)];\n\n        for (int i = 0; i < _size; ++i)\
    \ {\n            if (root[i] == i) g.add_edge(_size, i);\n            else g.add_edge(to[i],\
    \ i);\n        }\n        hld = heavy_light_decomposition(g, _size);\n    }\n\n\
    \    constexpr int size() const { return _size; }\n\n    int jump(int v, std::uint64_t\
    \ step) const {\n        int d = hld.get_depth(v);\n        if (step <= (std::uint64_t)d\
    \ - 1) return hld.jump(v, _size, step);\n        v = root[v];\n        step -=\
    \ d - 1;\n        int bottom = to[v];\n        int c = hld.get_depth(bottom);\n\
    \        step %= c;\n        if (step == 0) return v;\n        return hld.jump(bottom,\
    \ _size, step - 1);\n    }\n\n    std::vector<int> jump_all(std::uint64_t step)\
    \ const {\n        std::vector<int> res(_size, -1);\n        std::vector<std::vector<std::pair<int,\
    \ int>>> query(_size);\n        for (int v = 0; v < _size; ++v) {\n          \
    \  int d = hld.get_depth(v);\n            int r = root[v];\n            if ((std::uint64_t)d\
    \ - 1 > step) {\n                query[v].emplace_back(v, step);\n           \
    \ } else {\n                std::int64_t k = step - (d - 1);\n               \
    \ int bottom = to[r];\n                int c = hld.get_depth(bottom);\n      \
    \          k %= c;\n                if (k == 0) {\n                    res[v]\
    \ = r;\n                    continue;\n                }\n                query[bottom].emplace_back(v,\
    \ k - 1);\n            }\n        }\n\n        std::vector<int> path;\n      \
    \  auto dfs = [&](auto self, int v) -> void {\n            path.emplace_back(v);\n\
    \            for (auto &&[w, k] : query[v]) res[w] = path[path.size() - 1 - k];\n\
    \            for (auto &&e : g[v]) self(self, e.to());\n            path.pop_back();\n\
    \        };\n        for (auto e : g[_size]) dfs(dfs, e.to());\n        return\
    \ res;\n    }\n\n    std::vector<std::vector<int>> get_cycles() const {\n    \
    \    std::vector<std::vector<int>> res;\n        for (int v = 0; v < _size; ++v)\
    \ {\n            if (v == root[v]) res.emplace_back(get_cycle(v));\n        }\n\
    \        return res;\n    }\n\n  private:\n    int _size;\n    const std::vector<int>\
    \ &to;\n    std::vector<int> root;\n    Graph<void> g;\n    heavy_light_decomposition\
    \ hld;\n\n    functional_graph(int n, const std::vector<int> &_to)\n        :\
    \ _size(n), to(_to), root(n, -1), g(n + 1), hld() {}\n\n    std::vector<int> get_cycle(int\
    \ v) const {\n        std::vector<int> res(1, v);\n        int u = to[v];\n  \
    \      while (u != v) {\n            res.emplace_back(u);\n            u = to[u];\n\
    \        }\n        return res;\n    }\n};\n"
  dependsOn:
  - lib/tree/hld.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  - lib/tree/union_find.hpp
  isVerificationFile: false
  path: lib/graph/functional_graph.hpp
  requiredBy: []
  timestamp: '2024-02-04 08:44:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yukicoder/1211.test.cpp
  - test/yukicoder/1242.test.cpp
documentation_of: lib/graph/functional_graph.hpp
layout: document
redirect_from:
- /library/lib/graph/functional_graph.hpp
- /library/lib/graph/functional_graph.hpp.html
title: lib/graph/functional_graph.hpp
---
