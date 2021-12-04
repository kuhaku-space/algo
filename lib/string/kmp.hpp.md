---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n// verify : https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\r\
    \n\r\n/*\r\n * O(|S|)\r\n * A[i] := S[0:A[i]-1] == S[i-A[i]:i-1]\r\n */\r\ntemplate\
    \ <class Type>\r\nstruct KMP {\r\n    Type s;\r\n    vector<int> data;\r\n\r\n\
    \    KMP(const Type &_s) : s(_s), data(_s.size() + 1) {\r\n        data[0] = -1;\r\
    \n        int j = -1;\r\n        for (int i = 0; i < s.size(); ++i) {\r\n    \
    \        while (j >= 0 && s[i] != s[j]) j = data[j];\r\n            if (s[i +\
    \ 1] == s[++j])\r\n                data[i + 1] = data[j];\r\n            else\r\
    \n                data[i + 1] = j;\r\n        }\r\n    }\r\n\r\n    vector<int>\
    \ search(const Type &t) {\r\n        vector<int> res;\r\n        int i = 0, j\
    \ = 0;\r\n        while (i + j < t.size()) {\r\n            if (s[j] == t[i +\
    \ j]) {\r\n                if (++j != s.size()) continue;\r\n                res.emplace_back(i);\r\
    \n            }\r\n            i += j - data[j];\r\n            j = max(data[j],\
    \ int(0));\r\n        }\r\n        return res;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/kmp.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/kmp.hpp
layout: document
redirect_from:
- /library/lib/string/kmp.hpp
- /library/lib/string/kmp.hpp.html
title: lib/string/kmp.hpp
---
