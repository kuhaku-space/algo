---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/*\r\n * O(|S|)\r\n * A[i] := S[i:A[i]-1]\
    \ == S[0:A[i]-1-i]\r\n */\r\ntemplate <typename Type>\r\nstruct Z_algorithm {\r\
    \n    Type s;\r\n    vector<int> data;\r\n\r\n    Z_algorithm(const Type &_s)\
    \ : s(_s), data(_s.size()) {\r\n        data[0] = s.size();\r\n        int i =\
    \ 1, j = 0;\r\n        while (i < s.size()) {\r\n            while (i + j < s.size()\
    \ && s[j] == s[i + j]) ++j;\r\n            data[i] = j;\r\n            if (!j)\
    \ {\r\n                ++i;\r\n                continue;\r\n            }\r\n\
    \            int k = 1;\r\n            while (i + k < s.size() && k + data[k]\
    \ < j)\r\n                data[i + k] = data[k], ++k;\r\n            i += k, j\
    \ -= k;\r\n        }\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/z_algorithm.hpp
layout: document
redirect_from:
- /library/lib/string/z_algorithm.hpp
- /library/lib/string/z_algorithm.hpp.html
title: lib/string/z_algorithm.hpp
---
