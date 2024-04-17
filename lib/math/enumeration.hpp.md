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
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/bell.test.cpp
    title: test/aoj/dpl/bell.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/stirling.test.cpp
    title: test/aoj/dpl/stirling.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/combination.hpp:\
    \ line -1: no such header\n"
  code: "#include <vector>\n#include \"math/combination.hpp\"\n#include \"math/modint.hpp\"\
    \n\ntemplate <class mint = modint998, internal::is_modint_t<mint> * = nullptr>\n\
    struct Enumeration {\n    Enumeration() : combi(), data() {}\n\n    mint stirling(int\
    \ n, int k) {\n        mint res = 0;\n        for (int i = 0; i < k; ++i) {\n\
    \            if (i & 1) res -= combi(k, k - i) * mint(k - i).pow(n);\n       \
    \     else res += combi(k, k - i) * mint(k - i).pow(n);\n        }\n        res\
    \ *= combi.finv(k);\n        return res;\n    }\n\n    mint bell(int n, int k)\
    \ {\n        _init(k);\n        mint res = 0;\n        for (int i = 0; i <= k;\
    \ ++i) res += mint(i).pow(n) * combi.finv(i) * data[k - i];\n        return res;\n\
    \    }\n\n  private:\n    Combination<mint> combi;\n    std::vector<mint> data;\n\
    \n    void _init(int n) {\n        if (data.size() > n) return;\n        int m\
    \ = data.size();\n        data.resize(n + 1);\n        for (int i = m; i <= n;\
    \ ++i) {\n            if (i == 0) data[i] = 1;\n            else if (i & 1) data[i]\
    \ = data[i - 1] - combi.finv(i);\n            else data[i] = data[i - 1] + combi.finv(i);\n\
    \        }\n    }\n};\n"
  dependsOn:
  - lib/math/combination.hpp
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  isVerificationFile: false
  path: lib/math/enumeration.hpp
  requiredBy: []
  timestamp: '2024-04-17 14:43:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dpl/stirling.test.cpp
  - test/aoj/dpl/bell.test.cpp
documentation_of: lib/math/enumeration.hpp
layout: document
redirect_from:
- /library/lib/math/enumeration.hpp
- /library/lib/math/enumeration.hpp.html
title: lib/math/enumeration.hpp
---
