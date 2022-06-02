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
    path: test/aoj/grl/articulation_points.test.cpp
    title: test/aoj/grl/articulation_points.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/bridges.test.cpp
    title: test/aoj/grl/bridges.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: LowLink
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\r\n#include \"template/template.hpp\"\r\n\r\n\
    /**\r\n * @brief LowLink\r\n *\r\n * @tparam T\r\n */\r\ntemplate <class T>\r\n\
    struct LowLink {\r\n    LowLink(const Graph<T> &_graph)\r\n        : g(_graph),\
    \ ord(_graph.size()), low(_graph.size()), used(_graph.size()) {\r\n        this->build();\r\
    \n    }\r\n\r\n    /**\r\n     * @brief Get the articulation points object\r\n\
    \     *\r\n     * @return std::vector<int>\r\n     */\r\n    auto get_articulation_points()\
    \ { return this->articulation_points; }\r\n    /**\r\n     * @brief Get the bridges\
    \ object\r\n     *\r\n     * @return std::vector<typename Graph<T>::edge_type>\r\
    \n     */\r\n    auto get_bridges() { return this->bridges; }\r\n\r\n  private:\r\
    \n    const Graph<T> &g;\r\n    std::vector<int> ord, low;\r\n    std::vector<bool>\
    \ used;\r\n    std::vector<int> articulation_points;               // \u95A2\u7BC0\
    \u70B9\r\n    std::vector<typename Graph<T>::edge_type> bridges;  // \u6A4B\r\n\
    \r\n    void build() {\r\n        int number = 0;\r\n        for (int i = 0; i\
    \ < this->g.size(); i++) {\r\n            if (!this->used[i]) number = this->dfs(i,\
    \ number, -1);\r\n        }\r\n    }\r\n\r\n    int dfs(int index, int number,\
    \ int parent) {\r\n        this->used[index] = true;\r\n        this->ord[index]\
    \ = number++;\r\n        this->low[index] = this->ord[index];\r\n        bool\
    \ is_articulation_point = false;\r\n        int count = 0;\r\n        for (auto\
    \ &e : this->g[index]) {\r\n            if (!this->used[e.to()]) {\r\n       \
    \         ++count;\r\n                number = this->dfs(e.to(), number, index);\r\
    \n                chmin(low[index], low[e.to()]);\r\n                is_articulation_point\
    \ |= ~parent && this->low[e.to()] >= this->ord[index];\r\n                if (this->ord[index]\
    \ < this->low[e.to()]) this->bridges.emplace_back(e);\r\n            } else if\
    \ (e.to() != parent) {\r\n                chmin(this->low[index], this->ord[e.to()]);\r\
    \n            }\r\n        }\r\n        is_articulation_point |= parent == -1\
    \ && count > 1;\r\n        if (is_articulation_point) this->articulation_points.emplace_back(index);\r\
    \n        return number;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/lowlink.hpp
  requiredBy: []
  timestamp: '2022-05-13 04:24:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/articulation_points.test.cpp
  - test/aoj/grl/bridges.test.cpp
documentation_of: lib/graph/lowlink.hpp
layout: document
redirect_from:
- /library/lib/graph/lowlink.hpp
- /library/lib/graph/lowlink.hpp.html
title: LowLink
---
