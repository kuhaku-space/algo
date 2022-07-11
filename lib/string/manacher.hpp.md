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
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2934
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n// verify : https://onlinejudge.u-aizu.ac.jp/problems/2934\r\
    \n\r\n/*\r\n * O(|S|)\r\n * R[i] := S[i-(R[i]-1):i] == S[i:i+(R[i]-1)]\r\n */\r\
    \ntemplate <typename Type>\r\nstruct Manacher {\r\n    Type s;\r\n    vector<int>\
    \ data;\r\n\r\n    Manacher(const Type &_s) : s(_s), data(_s.size()) {\r\n   \
    \     int i = 0, j = 0;\r\n        while (i < s.size()) {\r\n            while\
    \ (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) ++j;\r\n          \
    \  data[i] = j;\r\n            int k = 1;\r\n            while (i - k >= 0 &&\
    \ i + k < s.size() && k + data[i - k] < j)\r\n                data[i + k] = data[i\
    \ - k], ++k;\r\n            i += k, j -= k;\r\n        }\r\n    }\r\n\r\n    const\
    \ int &operator[](int i) const { return data[i]; }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/manacher.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/manacher.hpp
layout: document
redirect_from:
- /library/lib/string/manacher.hpp
- /library/lib/string/manacher.hpp.html
title: lib/string/manacher.hpp
---
