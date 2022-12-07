---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u90E8\u5206\u6C38\u7D9AUnion-Find"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u90E8\u5206\u6C38\
    \u7D9AUnion-Find\r\n *\r\n */\r\nstruct partially_persistent_union_find {\r\n\
    \    partially_persistent_union_find(int _n)\r\n        : _now(0), _data(_n, std::vector<std::pair<int,\
    \ int>>(1, {0, -1})) {}\r\n\r\n    int root(int x, int t) const {\r\n        auto\
    \ p = this->_data[x].back();\r\n        if (p.first > t || p.second < 0) return\
    \ x;\r\n        return this->root(p.second, t);\r\n    }\r\n    int get_root(int\
    \ x, int t) const { return this->root(x, t); }\r\n\r\n    bool is_root(int x,\
    \ int t) const {\r\n        return this->_data[x].back().first > t || this->_data[x].back().second\
    \ < 0;\r\n    }\r\n\r\n    bool same(int x, int y, int t) const { return this->root(x,\
    \ t) == this->root(y, t); }\r\n    bool is_same(int x, int y, int t) const { return\
    \ this->same(x, y, t); }\r\n\r\n    int size(int x, int t) const {\r\n       \
    \ x = this->root(x, t);\r\n        return -std::prev(std::upper_bound(this->_data[x].begin(),\
    \ this->_data[x].end(),\r\n                                           std::pair<int,\
    \ int>{t, this->_data.size()}))\r\n                    ->second;\r\n    }\r\n\
    \    int get_size(int x, int t) const { return this->size(x, t); }\r\n\r\n   \
    \ int unite(int x, int y) {\r\n        ++_now;\r\n        x = this->root(x, _now),\
    \ y = this->root(y, _now);\r\n        if (x == y) return _now;\r\n        auto\
    \ p = this->_data[x].back(), q = this->_data[y].back();\r\n        if (p.second\
    \ > q.second) swap(x, y), swap(p, q);\r\n        this->_data[x].emplace_back(_now,\
    \ p.second + q.second);\r\n        this->_data[y].emplace_back(_now, x);\r\n \
    \       return _now;\r\n    }\r\n\r\n  private:\r\n    int _now;\r\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _data;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/partially_persistent_union_find.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/partially_persistent_union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/partially_persistent_union_find.hpp
- /library/lib/tree/partially_persistent_union_find.hpp.html
title: "\u90E8\u5206\u6C38\u7D9AUnion-Find"
---
