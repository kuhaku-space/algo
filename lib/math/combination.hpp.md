---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algo/modint.hpp
    title: lib/algo/modint.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"algo/modint.hpp\"\r\n\r\n\
    template <int mod>\r\nstruct Combination {\r\n    using mint = ModInt<mod>;\r\n\
    \    vector<mint> fac, finv;\r\n\r\n    Combination() {}\r\n\r\n    mint operator()(int\
    \ n, int k) {\r\n        if (n < k || n < 0 || k < 0) return 0;\r\n        _init(n);\r\
    \n        return fac[n] * finv[k] * finv[n - k];\r\n    }\r\n\r\n    void _init(int\
    \ n) {\r\n        if (fac.size() > n) return;\r\n        int m = fac.size();\r\
    \n        fac.resize(n + 1);\r\n        for (int i = m; i <= n; ++i) {\r\n   \
    \         if (i == 0)\r\n                fac[i] = 1;\r\n            else\r\n \
    \               fac[i] = fac[i - 1] * i;\r\n        }\r\n        finv.resize(n\
    \ + 1);\r\n        finv[n] = fac[n].inverse();\r\n        for (int i = n - 1;\
    \ i >= m; --i) finv[i] = finv[i + 1] * (i + 1);\r\n    }\r\n\r\n    mint fact(int\
    \ x) {\r\n        assert(x >= 0);\r\n        _init(x);\r\n        return fac[x];\r\
    \n    }\r\n\r\n    mint naive(int n, int k) const {\r\n        if (n < k || n\
    \ < 0 || k < 0) return 0;\r\n        if (n - k < k) k = n - k;\r\n        mint\
    \ res = 1;\r\n        for (int i = 0; i < k; ++i) {\r\n            res *= n -\
    \ i;\r\n            res /= i + 1;\r\n        }\r\n        return res;\r\n    }\r\
    \n\r\n    mint lucas(int n, int k) {\r\n        if (n < k || n < 0 || k < 0) return\
    \ 0;\r\n        if (n - k < k) k = n - k;\r\n        static vector<vector<mint>>\
    \ v;\r\n        if (v.empty()) {\r\n            v = vector<vector<mint>>(mod,\
    \ vector<mint>(mod));\r\n            for (int i = 0; i < mod; ++i) v[i][0] = 1;\r\
    \n            for (int i = 0; i < mod; ++i) {\r\n                for (int j =\
    \ 1; j < mod; ++j) {\r\n                    if (i < j)\r\n                   \
    \     v[i][j] = 0;\r\n                    else if (i - j < j)\r\n            \
    \            v[i][j] = v[i][i - j];\r\n                    else\r\n          \
    \              v[i][j] = v[i][j - 1] * mint(i + 1 - j) / mint(j);\r\n        \
    \        }\r\n            }\r\n        }\r\n        mint res = 1;\r\n        while\
    \ (n || k) {\r\n            res *= v[n % mod][k % mod];\r\n            n /= mod,\
    \ k /= mod;\r\n        }\r\n        return res;\r\n    }\r\n\r\n    mint permu(int\
    \ n, int k) {\r\n        if (n < k || n < 0 || k < 0) return 0;\r\n        _init(n);\r\
    \n        return fac[n] * finv[n - k];\r\n    }\r\n};\r\nCombination<MOD> combi;\r\
    \n"
  dependsOn:
  - lib/template/template.hpp
  - lib/algo/modint.hpp
  isVerificationFile: false
  path: lib/math/combination.hpp
  requiredBy: []
  timestamp: '2021-09-23 05:56:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/combination.hpp
layout: document
redirect_from:
- /library/lib/math/combination.hpp
- /library/lib/math/combination.hpp.html
title: lib/math/combination.hpp
---
