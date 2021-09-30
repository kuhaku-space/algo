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
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\nstruct union_find {\r\n    int64_t\
    \ now;\r\n    vector<int64_t> parent;\r\n    vector<int64_t> size;\r\n    vector<int64_t>\
    \ time;\r\n\r\n    union_find(int64_t _n) : now(0), size(_n, 1), time(_n, 0) {\r\
    \n        for (int64_t i = 0; i < _n; ++i) parent.emplace_back(i);\r\n    }\r\n\
    \r\n    int64_t root(int64_t x, int64_t t) const {\r\n        if (time[x] > t)\
    \ return x;\r\n        return root(parent[x], t);\r\n    }\r\n\r\n    int64_t\
    \ unite(int64_t x, int64_t y) {\r\n        ++now;\r\n        x = root(now, x),\
    \ y = root(now, y);\r\n        if (x == y) return now;\r\n        if (size[x]\
    \ < size[y]) swap(x, y);\r\n        parent[y] = x;\r\n        time[y] = now;\r\
    \n        size[x] += size[y];\r\n        return now;\r\n    }\r\n\r\n    int64_t\
    \ get_size(int64_t x) const { return size[root(x, now)]; }\r\n\r\n    bool is_same(int64_t\
    \ x, int64_t y, int64_t t) const {\r\n        return root(x, t) == root(y, t);\r\
    \n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/partially_persistent_union_find.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/partially_persistent_union_find.hpp
layout: document
redirect_from:
- /library/lib/_new/partially_persistent_union_find.hpp
- /library/lib/_new/partially_persistent_union_find.hpp.html
title: lib/_new/partially_persistent_union_find.hpp
---
