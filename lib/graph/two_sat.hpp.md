---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/graph/scc.hpp
    title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/two_sat.test.cpp
    title: test/yosupo/math/two_sat.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: 2-SAT
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\r\n#include \"graph/scc.hpp\"\r\n#include \"\
    template/template.hpp\"\r\n\r\n/**\r\n * @brief 2-SAT\r\n */\r\nstruct two_sat\
    \ {\r\n    two_sat(int n) : _size(n), G(n * 2) {}\r\n\r\n    void add(int i, bool\
    \ f, int j, bool g) {\r\n        i <<= 1, j <<= 1;\r\n        this->G.add_edge(i\
    \ + (f ? 0 : 1), j + (g ? 1 : 0));\r\n        this->G.add_edge(j + (g ? 0 : 1),\
    \ i + (f ? 1 : 0));\r\n    }\r\n\r\n    std::vector<int> solve() {\r\n       \
    \ auto res = scc(G);\r\n        return res;\r\n    }\r\n\r\n    bool is_satisfy(const\
    \ std::vector<int> &v) {\r\n        for (int i = 0; i < this->_size; ++i) {\r\n\
    \            if (v[i * 2] == v[i * 2 + 1]) return false;\r\n        }\r\n    \
    \    return true;\r\n    }\r\n\r\n    std::vector<bool> build(const vector<int>\
    \ &v) {\r\n        std::vector<bool> res(this->_size);\r\n        for (int i =\
    \ 0; i < this->_size; ++i) res[i] = v[i * 2] < v[i * 2 + 1];\r\n        return\
    \ res;\r\n    }\r\n\r\n  private:\r\n    int _size;\r\n    Graph<void> G;\r\n\
    };\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  - lib/graph/scc.hpp
  isVerificationFile: false
  path: lib/graph/two_sat.hpp
  requiredBy: []
  timestamp: '2022-07-30 08:42:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/math/two_sat.test.cpp
documentation_of: lib/graph/two_sat.hpp
layout: document
redirect_from:
- /library/lib/graph/two_sat.hpp
- /library/lib/graph/two_sat.hpp.html
title: 2-SAT
---
