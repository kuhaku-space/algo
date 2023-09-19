---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: "\u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt_mod.hpp
    title: "\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_fft.hpp
    title: lib/internal/internal_fft.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_math.hpp
    title: lib/internal/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_type_traits.hpp
    title: lib/internal/internal_type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_1000000007
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_1000000007
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: fft/ntt_mod.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\
    \n#include \"fft/ntt_mod.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void)\
    \ {\n    int n, m;\n    cin >> n >> m;\n    vector<int> a(n), b(m);\n    cin >>\
    \ a >> b;\n\n    auto ans = convolution_mod<MOD>(a, b);\n    co(ans);\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - lib/fft/ntt_mod.hpp
  - lib/fft/ntt.hpp
  - lib/internal/internal_fft.hpp
  - lib/internal/internal_bit.hpp
  - lib/template/template.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/convolution/convolution_mod.test.cpp
  requiredBy: []
  timestamp: '2023-07-12 23:02:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/convolution/convolution_mod.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/convolution/convolution_mod.test.cpp
- /verify/test/yosupo/convolution/convolution_mod.test.cpp.html
title: test/yosupo/convolution/convolution_mod.test.cpp
---
