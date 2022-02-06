---
data:
  _extendedDependsOn:
  - icon: ':question:'
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u30AA\u30A4\u30E9\
    \u30FC\u30C4\u30A2\u30FC\r\n * @details [\u53C2\u8003](https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp)\r\
    \n *\r\n */\r\nstruct eular_tour {\r\n    eular_tour(int n) : G(n), ls(n), rs(n),\
    \ pos() {}\r\n\r\n    pair<int, int> operator[](int i) const { return make_pair(this->ls[i],\
    \ this->rs[i]); }\r\n\r\n    int size() const { return this->pos; }\r\n\r\n  \
    \  void add_edge(int a, int b) {\r\n        this->G[a].emplace_back(b);\r\n  \
    \      this->G[b].emplace_back(a);\r\n    }\r\n    void add_edges(int a, int b)\
    \ { this->add_edge(a, b); }\r\n\r\n    void dfs(int v, int p) {\r\n        this->ls[v]\
    \ = this->pos++;\r\n        for (auto &u : this->G[v]) {\r\n            if (u\
    \ != p) this->dfs(u, v);\r\n            this->rs[v] = this->pos;\r\n        }\r\
    \n    }\r\n\r\n    void build(int r = 0) {\r\n        this->pos = 0;\r\n     \
    \   this->dfs(r, -1);\r\n    }\r\n\r\n    int get_l(int i) const { return this->ls[i];\
    \ }\r\n    int get_r(int i) const { return this->rs[i]; }\r\n\r\n    template\
    \ <class F>\r\n    void query(int v, const F &f) const {\r\n        f(this->ls[v],\
    \ this->rs[v]);\r\n    }\r\n\r\n  private:\r\n    vector<vector<int>> G;\r\n \
    \   vector<int> ls, rs;\r\n    int pos;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/eular_tour.hpp
  requiredBy: []
  timestamp: '2022-01-13 01:17:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/eular_tour.hpp
layout: document
redirect_from:
- /library/lib/tree/eular_tour.hpp
- /library/lib/tree/eular_tour.hpp.html
title: "\u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC"
---
