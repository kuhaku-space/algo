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
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC"
    links:
    - https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp)
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
    /**\r\n * @brief \u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC\r\n * @details [\u53C2\
    \u8003](https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp)\r\
    \n *\r\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\r\n */\r\ntemplate <class\
    \ T>\r\nstruct eular_tour {\r\n    eular_tour(const Graph<T> &_g, int r = 0) :\
    \ g(_g), ls(_g.size()), rs(_g.size()), pos() {\r\n        this->build(r);\r\n\
    \    }\r\n\r\n    std::pair<int, int> operator[](int i) const { return {this->ls[i],\
    \ this->rs[i]}; }\r\n\r\n    int size() const { return this->pos; }\r\n\r\n  \
    \  int get_l(int i) const { return this->ls[i]; }\r\n    int get_r(int i) const\
    \ { return this->rs[i]; }\r\n\r\n    template <class F>\r\n    void query(int\
    \ v, const F &f) const {\r\n        f(this->ls[v], this->rs[v]);\r\n    }\r\n\r\
    \n  private:\r\n    const Graph<T> &g;\r\n    std::vector<int> ls, rs;\r\n   \
    \ int pos;\r\n\r\n    void build(int r = 0) {\r\n        this->pos = 0;\r\n  \
    \      this->dfs(r, -1);\r\n    }\r\n\r\n    void dfs(int v, int p) {\r\n    \
    \    this->ls[v] = this->pos++;\r\n        for (auto &u : this->g[v]) {\r\n  \
    \          if (u != p) this->dfs(u, v);\r\n            this->rs[v] = this->pos;\r\
    \n        }\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/eular_tour.hpp
  requiredBy: []
  timestamp: '2022-04-14 07:10:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/eular_tour.hpp
layout: document
redirect_from:
- /library/lib/tree/eular_tour.hpp
- /library/lib/tree/eular_tour.hpp.html
title: "\u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC"
---
