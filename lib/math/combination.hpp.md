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
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/math/enumeration.hpp
    title: lib/math/enumeration.hpp
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#include <cassert>\r\n#include <vector>\r\n#include \"math/modint.hpp\"\r\
    \n\r\ntemplate <class mint = modint998, internal::is_modint_t<mint> * = nullptr>\r\
    \nstruct Combination {\r\n    Combination() : _fact(), _finv() {}\r\n\r\n    mint\
    \ operator()(int n, int k) {\r\n        if (n < k || n < 0 || k < 0) return 0;\r\
    \n        _init(n);\r\n        return _fact[n] * _finv[k] * _finv[n - k];\r\n\
    \    }\r\n\r\n    mint fact(int x) {\r\n        assert(x >= 0);\r\n        _init(x);\r\
    \n        return _fact[x];\r\n    }\r\n\r\n    mint finv(int x) {\r\n        assert(x\
    \ >= 0);\r\n        _init(x);\r\n        return _finv[x];\r\n    }\r\n\r\n   \
    \ mint naive(int n, int k) const {\r\n        if (n < k || n < 0 || k < 0) return\
    \ 0;\r\n        if (n - k < k) k = n - k;\r\n        mint res = 1;\r\n       \
    \ for (int i = 0; i < k; ++i) {\r\n            res *= n - i;\r\n            res\
    \ /= i + 1;\r\n        }\r\n        return res;\r\n    }\r\n\r\n    mint permu(int\
    \ n, int k) {\r\n        if (n < k || n < 0 || k < 0) return 0;\r\n        _init(n);\r\
    \n        return _fact[n] * _finv[n - k];\r\n    }\r\n\r\n  private:\r\n    std::vector<mint>\
    \ _fact, _finv;\r\n\r\n    void _init(int n) {\r\n        if ((int)_fact.size()\
    \ > n) return;\r\n        int m = _fact.size();\r\n        _fact.resize(n + 1);\r\
    \n        for (int i = m; i <= n; ++i) {\r\n            if (i == 0) _fact[i] =\
    \ 1;\r\n            else _fact[i] = _fact[i - 1] * i;\r\n        }\r\n       \
    \ _finv.resize(n + 1);\r\n        _finv[n] = _fact[n].inv();\r\n        for (int\
    \ i = n - 1; i >= m; --i) _finv[i] = _finv[i + 1] * (i + 1);\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  isVerificationFile: false
  path: lib/math/combination.hpp
  requiredBy:
  - lib/math/enumeration.hpp
  timestamp: '2024-04-17 14:43:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dpl/bell.test.cpp
  - test/aoj/dpl/stirling.test.cpp
documentation_of: lib/math/combination.hpp
layout: document
redirect_from:
- /library/lib/math/combination.hpp
- /library/lib/math/combination.hpp.html
title: lib/math/combination.hpp
---
