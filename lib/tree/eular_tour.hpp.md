---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/rupc/lazy_segment_tree.test.cpp
    title: test/aoj/rupc/lazy_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
    title: test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC"
    links:
    - https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include <utility>\r\n#include <vector>\r\n#include \"graph/graph.hpp\"\r\
    \n\r\n/**\r\n * @brief \u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC\r\n * @see https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp\r\
    \n *\r\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\r\n */\r\ntemplate <class\
    \ T>\r\nstruct eular_tour {\r\n    eular_tour(const Graph<T> &_g, int r = 0) :\
    \ g(_g), ls(_g.size()), rs(_g.size()), pos() {\r\n        build(r);\r\n    }\r\
    \n\r\n    std::pair<int, int> operator[](int i) const { return std::make_pair(ls[i],\
    \ rs[i]); }\r\n\r\n    int size() const { return pos; }\r\n\r\n    int get_l(int\
    \ i) const { return ls[i]; }\r\n    int get_r(int i) const { return rs[i]; }\r\
    \n\r\n    template <class F>\r\n    void query(int v, const F &f) const {\r\n\
    \        f(ls[v], rs[v]);\r\n    }\r\n\r\n  private:\r\n    const Graph<T> &g;\r\
    \n    std::vector<int> ls, rs;\r\n    int pos;\r\n\r\n    void build(int r = 0)\
    \ {\r\n        pos = 0;\r\n        dfs(r, -1);\r\n    }\r\n\r\n    void dfs(int\
    \ v, int p) {\r\n        ls[v] = pos++;\r\n        for (auto &e : g[v]) {\r\n\
    \            if (e.to() != p) dfs(e.to(), v);\r\n        }\r\n        rs[v] =\
    \ pos;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/tree/eular_tour.hpp
  requiredBy: []
  timestamp: '2024-01-23 17:21:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/rupc/lazy_segment_tree.test.cpp
  - test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
documentation_of: lib/tree/eular_tour.hpp
layout: document
redirect_from:
- /library/lib/tree/eular_tour.hpp
- /library/lib/tree/eular_tour.hpp.html
title: "\u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC"
---
