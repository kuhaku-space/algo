---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/string/suffix_array.hpp
    title: Suffix Array
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
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: string/suffix_array.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n#include\
    \ \"string/suffix_array.hpp\"\n#include <iostream>\n#include <string>\n#include\
    \ <vector>\n\nint main(void) {\n    std::string s;\n    std::cin >> s;\n    auto\
    \ ans = suffix_array(s);\n    for (int i = 0; i < (int)ans.size(); ++i)\n    \
    \    std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\\n' : ' ');\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - lib/string/suffix_array.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/string/suffix_array.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 18:09:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/string/suffix_array.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/string/suffix_array.test.cpp
- /verify/test/yosupo/string/suffix_array.test.cpp.html
title: test/yosupo/string/suffix_array.test.cpp
---
