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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u90E8\u5206\u6C38\
    \u7D9AUnion-Find\r\n * \r\n */\r\nstruct partially_persistent_union_find {\r\n\
    \    partially_persistent_union_find(int _n) : now(0), data(_n, -1), time(_n,\
    \ 0) {}\r\n\r\n    int root(int x, int t) const {\r\n        if (data[x] < 0 ||\
    \ time[x] > t) return x;\r\n        return root(data[x], t);\r\n    }\r\n\r\n\
    \    int unite(int x, int y) {\r\n        ++now;\r\n        x = root(x, now),\
    \ y = root(y, now);\r\n        if (x == y) return now;\r\n        if (data[x]\
    \ > data[y]) swap(x, y);\r\n        time[y] = now;\r\n        data[x] += data[y];\r\
    \n        data[y] = x;\r\n        return now;\r\n    }\r\n\r\n    int size(int\
    \ x) const { return -data[root(x, now)]; }\r\n\r\n    bool same(int x, int y,\
    \ int t) const { return root(x, t) == root(y, t); }\r\n\r\n  private:\r\n    int\
    \ now;\r\n    vector<int> data;\r\n    vector<int> time;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/partially_persistent_union_find.hpp
  requiredBy: []
  timestamp: '2021-12-13 01:04:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/partially_persistent_union_find.hpp
layout: document
redirect_from:
- /library/lib/_new/partially_persistent_union_find.hpp
- /library/lib/_new/partially_persistent_union_find.hpp.html
title: "\u90E8\u5206\u6C38\u7D9AUnion-Find"
---
