---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/treap.hpp
    title: Treap
  - icon: ':heavy_check_mark:'
    path: lib/random/xorshift.hpp
    title: "\u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ITP2_7_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ITP2_7_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/treap.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ITP2_7_B\"\n\
    #include \"binary_tree/treap.hpp\"\n#include <iostream>\n\nint main(void) {\n\
    \    int q;\n    std::cin >> q;\n    int size = 0;\n    Treap<int> treap;\n  \
    \  while (q--) {\n        int x, y;\n        std::cin >> x >> y;\n        if (x\
    \ == 0) {\n            if (!treap.contains(y)) treap.insert(y), ++size;\n    \
    \        std::cout << size << std::endl;\n        } else if (x == 1) {\n     \
    \       std::cout << treap.contains(y) << std::endl;\n        } else if (x ==\
    \ 2) {\n            if (treap.contains(y)) treap.erase(y), --size;\n        }\n\
    \    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/treap.hpp
  - lib/random/xorshift.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/itp2/treap.test.cpp
  requiredBy: []
  timestamp: '2023-11-14 23:34:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/itp2/treap.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/itp2/treap.test.cpp
- /verify/test/aoj/itp2/treap.test.cpp.html
title: test/aoj/itp2/treap.test.cpp
---
