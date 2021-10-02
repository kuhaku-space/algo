---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/list/skip_list.hpp
    title: lib/list/skip_list.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\nstruct Xorshift {\n \
    \   unsigned int x, y, z, w;\n\n    Xorshift() { x = 123456789, y = 362436069,\
    \ z = 521288629, w = 88675123; }\n\n    unsigned int operator()() {\n        unsigned\
    \ int t = (x ^ (x << 11));\n        x = y, y = z, z = w;\n        return w = (w\
    \ ^ (w >> 19)) ^ (t ^ (t >> 8));\n    }\n\n    double rand_d() { return (double)(*this)()\
    \ / (1LL << 32); }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/xorshift.hpp
  requiredBy:
  - lib/list/skip_list.hpp
  timestamp: '2021-09-29 10:00:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/xorshift.hpp
layout: document
redirect_from:
- /library/lib/algorithm/xorshift.hpp
- /library/lib/algorithm/xorshift.hpp.html
title: lib/algorithm/xorshift.hpp
---
