---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/graph/maximum_independent_set.hpp
    title: "\u6700\u5927\u72EC\u7ACB\u96C6\u5408"
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
    PROBLEM: https://judge.yosupo.jp/problem/maximum_independent_set
    links:
    - https://judge.yosupo.jp/problem/maximum_independent_set
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/maximum_independent_set.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/maximum_independent_set\"\
    \n#include \"graph/maximum_independent_set.hpp\"\n#include <iostream>\n#include\
    \ <vector>\n\nint main(void) {\n    int n, m;\n    std::cin >> n >> m;\n    Graph<void>\
    \ g(n);\n    g.input_edges(m, 0);\n    auto ans = maximum_independent_set(g);\n\
    \    std::cout << ans.size() << '\\n';\n    for (auto &&e : ans) std::cout <<\
    \ e << '\\n';\n\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/maximum_independent_set.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/graph/maximum_independent_set.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 07:01:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/graph/maximum_independent_set.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/graph/maximum_independent_set.test.cpp
- /verify/test/yosupo/graph/maximum_independent_set.test.cpp.html
title: test/yosupo/graph/maximum_independent_set.test.cpp
---
