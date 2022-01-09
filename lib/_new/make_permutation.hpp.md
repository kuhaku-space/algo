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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\nvector<int> make_permutation_one_bit(int\
    \ n, int a, int b) {\r\n    if (n == 1) {\r\n        return {a, b};\r\n    }\r\
    \n    assert(__builtin_parity(a) != __builtin_parity(b));\r\n    int bit = 1 <<\
    \ (n - 1);\r\n    if ((a ^ b) & bit) {\r\n        auto res = make_permutation_one_bit(n\
    \ - 1, a, a ^ 1);\r\n        auto v = make_permutation_one_bit(n - 1, (a ^ 1)\
    \ ^ bit, b);\r\n        res.insert(res.end(), v.begin(), v.end());\r\n       \
    \ return res;\r\n    } else {\r\n        auto res = make_permutation_one_bit(n\
    \ - 1, a, b);\r\n        auto v = make_permutation_one_bit(n - 1, a ^ bit, res[1]\
    \ ^ bit);\r\n        res.insert(res.begin() + 1, v.begin(), v.end());\r\n    \
    \    return res;\r\n    }\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/make_permutation.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/make_permutation.hpp
layout: document
redirect_from:
- /library/lib/_new/make_permutation.hpp
- /library/lib/_new/make_permutation.hpp.html
title: lib/_new/make_permutation.hpp
---
