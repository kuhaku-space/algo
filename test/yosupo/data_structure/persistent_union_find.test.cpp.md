---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/persistent_array.hpp
    title: lib/data_structure/persistent_array.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/persistent_union_find.hpp
    title: lib/tree/persistent_union_find.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_unionfind
    links:
    - https://judge.yosupo.jp/problem/persistent_unionfind
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/atcoder.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    #include \"template/atcoder.hpp\"\n#include \"tree/persistent_union_find.hpp\"\
    \n\nint main(void) {\n    sonic();\n    int n, q;\n    cin >> n >> q;\n    vector<persistent_union_find>\
    \ ufs;\n    ufs.emplace_back(n);\n\n    rep (i, q) {\n        int t, k, u, v;\n\
    \        cin >> t >> k >> u >> v;\n        if (t == 0) {\n            ufs.emplace_back(ufs[k\
    \ + 1].unite(u, v));\n        } else {\n            co(ufs[k + 1].same(u, v));\n\
    \            ufs.emplace_back();\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/template/atcoder.hpp
  - lib/template/template.hpp
  - lib/tree/persistent_union_find.hpp
  - lib/data_structure/persistent_array.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/persistent_union_find.test.cpp
  requiredBy: []
  timestamp: '2022-05-15 04:01:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/persistent_union_find.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/persistent_union_find.test.cpp
- /verify/test/yosupo/data_structure/persistent_union_find.test.cpp.html
title: test/yosupo/data_structure/persistent_union_find.test.cpp
---
