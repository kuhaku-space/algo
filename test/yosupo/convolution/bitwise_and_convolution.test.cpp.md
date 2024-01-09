---
data:
  _extendedDependsOn:
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
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n#include <algorithm>\n#include <iostream>\n#include <iterator>\n#include <vector>\n\
    #include \"math/modint.hpp\"\n\nusing Mint = modint998;\n\ntemplate <typename\
    \ T>\nvoid fwt(std::vector<T> &f) {\n    int n = f.size();\n    for (int i = 1;\
    \ i < n; i <<= 1) {\n        for (int j = 0; j < n; j++) {\n            if ((j\
    \ & i) == 0) f[j] += f[j | i];\n        }\n    }\n}\n\ntemplate <typename T>\n\
    void ifwt(std::vector<T> &f) {\n    int n = f.size();\n    for (int i = 1; i <\
    \ n; i <<= 1) {\n        for (int j = 0; j < n; j++) {\n            if ((j & i)\
    \ == 0) f[j] -= f[j | i];\n        }\n    }\n}\n\nint main(void) {\n    int n;\n\
    \    std::cin >> n;\n    n = 1 << n;\n    std::vector<Mint> a(n), b(n);\n    std::copy_n(std::istream_iterator<Mint>(std::cin),\
    \ n, std::begin(a));\n    std::copy_n(std::istream_iterator<Mint>(std::cin), n,\
    \ std::begin(b));\n    fwt(a), fwt(b);\n    std::vector<Mint> c(n);\n    for (int\
    \ i = 0; i < n; ++i) c[i] = a[i] * b[i];\n    ifwt(c);\n    for (int i = 0; i\
    \ < n; ++i) std::cout << c[i] << (i == n - 1 ? '\\n' : ' ');\n\n    return 0;\n\
    }\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/convolution/bitwise_and_convolution.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 05:00:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/convolution/bitwise_and_convolution.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/convolution/bitwise_and_convolution.test.cpp
- /verify/test/yosupo/convolution/bitwise_and_convolution.test.cpp.html
title: test/yosupo/convolution/bitwise_and_convolution.test.cpp
---
