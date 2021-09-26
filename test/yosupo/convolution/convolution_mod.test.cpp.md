---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/algo/modint.hpp
    title: modint
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: lib/fft/ntt.hpp
  - icon: ':question:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: fft/ntt.hpp: line\
    \ -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n#include\
    \ \"fft/ntt.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void) {\n   \
    \ sonic();\n    int n, m;\n    cin >> n >> m;\n    vector<int> a(n), b(m);\n \
    \   cin >> a >> b;\n    NTT_N ntt;\n\n    auto ans = ntt.convolution(a, b);\n\
    \    co(ans);\n\n    return 0;\n}\n"
  dependsOn:
  - lib/fft/ntt.hpp
  - lib/template/template.hpp
  - lib/algo/modint.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/yosupo/convolution/convolution_mod.test.cpp
  requiredBy: []
  timestamp: '2021-09-26 10:08:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/convolution/convolution_mod.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/convolution/convolution_mod.test.cpp
- /verify/test/yosupo/convolution/convolution_mod.test.cpp.html
title: test/yosupo/convolution/convolution_mod.test.cpp
---
