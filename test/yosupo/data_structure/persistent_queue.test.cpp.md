---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/persistent_queue.hpp
    title: lib/data_structure/persistent_queue.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/macro.hpp
    title: lib/template/macro.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/sonic.hpp
    title: lib/template/sonic.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_queue
    links:
    - https://judge.yosupo.jp/problem/persistent_queue
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/persistent_queue.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_queue\"\n#include\
    \ \"data_structure/persistent_queue.hpp\"\n#include \"template/atcoder.hpp\"\n\
    \nint main(void) {\n    sonic();\n    int q;\n    cin >> q;\n    vector<persistent_queue<int>>\
    \ qs;\n    qs.emplace_back();\n\n    rep (i, q) {\n        int t;\n        cin\
    \ >> t;\n        if (t == 0) {\n            int k, x;\n            cin >> k >>\
    \ x;\n            qs.emplace_back(qs[k + 1].push(x));\n        } else {\n    \
    \        int k;\n            cin >> k;\n            co(qs[k + 1].top());\n   \
    \         qs.emplace_back(qs[k + 1].pop());\n        }\n    }\n\n    return 0;\n\
    }\n"
  dependsOn:
  - lib/data_structure/persistent_queue.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/persistent_queue.test.cpp
  requiredBy: []
  timestamp: '2022-06-22 08:11:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/persistent_queue.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/persistent_queue.test.cpp
- /verify/test/yosupo/data_structure/persistent_queue.test.cpp.html
title: test/yosupo/data_structure/persistent_queue.test.cpp
---
