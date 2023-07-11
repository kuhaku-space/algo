---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/string/zalgorithm.test.cpp
    title: test/yosupo/string/zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Z algorithm
    links:
    - https://snuke.hatenablog.com/entry/2014/12/03/214243
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief Z algorithm\r\n\
    \ *\r\n * @tparam Container\r\n *\r\n * @see https://snuke.hatenablog.com/entry/2014/12/03/214243\r\
    \n *\r\n * Z[i] := S[i:Z[i]] == S[0:Z[i]-i]\r\n */\r\ntemplate <class Container>\r\
    \nstd::vector<int> z_algorithm(const Container &s) {\r\n    int n = s.size();\r\
    \n    std::vector<int> res(n);\r\n    res[0] = n;\r\n    int i = 1, j = 0;\r\n\
    \    while (i < n) {\r\n        while (i + j < n && s[j] == s[i + j]) ++j;\r\n\
    \        res[i] = j;\r\n        if (!j) {\r\n            ++i;\r\n            continue;\r\
    \n        }\r\n        int k = 1;\r\n        while (i + k < n && k + res[k] <\
    \ j) res[i + k] = res[k], ++k;\r\n        i += k, j -= k;\r\n    }\r\n    return\
    \ res;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2023-05-22 19:46:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/string/zalgorithm.test.cpp
documentation_of: lib/string/z_algorithm.hpp
layout: document
redirect_from:
- /library/lib/string/z_algorithm.hpp
- /library/lib/string/z_algorithm.hpp.html
title: Z algorithm
---
