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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/sqrt_mod.test.cpp
    title: test/yosupo/math/sqrt_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#include \"math/modint.hpp\"\n#include \"template/template.hpp\"\n\ntemplate\
    \ <class mint, internal::is_modint_t<mint> * = nullptr>\nbool has_sqrt_mod(mint\
    \ x) {\n    return x == 0 || x.pow(mint::mod() / 2) == 1;\n}\n\ntemplate <class\
    \ mint, internal::is_modint_t<mint> * = nullptr>\nmint sqrt_mod(mint x) {\n  \
    \  const int p = mint::mod();\n    if (x == 0 || x == 1) return x;\n    if (p\
    \ % 4 == 3) return x.pow(p / 4 + 1);\n    int q = p - 1, s = 0;\n    while (~q\
    \ & 1) q >>= 1, ++s;\n    mint z(1);\n    while (has_sqrt_mod(z)) ++z;\n    mint\
    \ c = z.pow(q);\n    mint t = x.pow(q);\n    mint r = x.pow(q / 2 + 1);\n    while\
    \ (t != 1) {\n        int m = 0;\n        mint u = t;\n        while (u != 1)\
    \ ++m, u *= u;\n        while (s != m) {\n            --s;\n            if (s\
    \ == m) r *= c;\n            c *= c;\n        }\n        t *= c;\n    }\n    return\
    \ r;\n}\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/sqrt.hpp
  requiredBy: []
  timestamp: '2023-10-01 18:31:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/math/sqrt_mod.test.cpp
documentation_of: lib/math/sqrt.hpp
layout: document
redirect_from:
- /library/lib/math/sqrt.hpp
- /library/lib/math/sqrt.hpp.html
title: lib/math/sqrt.hpp
---
