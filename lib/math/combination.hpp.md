---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: modint
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#include \"math/modint.hpp\"\r\n#include \"template/template.hpp\"\r\n\r\n\
    template <int mod = MOD_N>\r\nstruct Combination {\r\n    using mint = ModInt<mod>;\r\
    \n\r\n    Combination() : _fact(), _finv() {}\r\n\r\n    mint operator()(int n,\
    \ int k) {\r\n        if (n < k || n < 0 || k < 0) return 0;\r\n        this->_init(n);\r\
    \n        return this->_fact[n] * this->_finv[k] * this->_finv[n - k];\r\n   \
    \ }\r\n\r\n    mint fact(int x) {\r\n        assert(x >= 0);\r\n        this->_init(x);\r\
    \n        return this->_fact[x];\r\n    }\r\n\r\n    mint finv(int x) {\r\n  \
    \      assert(x >= 0);\r\n        this->_init(x);\r\n        return this->_finv[x];\r\
    \n    }\r\n\r\n    mint naive(int n, int k) const {\r\n        if (n < k || n\
    \ < 0 || k < 0) return 0;\r\n        if (n - k < k) k = n - k;\r\n        mint\
    \ res = 1;\r\n        for (int i = 0; i < k; ++i) {\r\n            res *= n -\
    \ i;\r\n            res /= i + 1;\r\n        }\r\n        return res;\r\n    }\r\
    \n\r\n    mint lucas(int n, int k) {\r\n        if (n < k || n < 0 || k < 0) return\
    \ 0;\r\n        if (n - k < k) k = n - k;\r\n        static vector<vector<mint>>\
    \ v;\r\n        if (v.empty()) {\r\n            v = vector<vector<mint>>(mod,\
    \ vector<mint>(mod));\r\n            for (int i = 0; i < mod; ++i) v[i][0] = 1;\r\
    \n            for (int i = 0; i < mod; ++i) {\r\n                for (int j =\
    \ 1; j < mod; ++j) {\r\n                    if (i < j) v[i][j] = 0;\r\n      \
    \              else if (i - j < j) v[i][j] = v[i][i - j];\r\n                \
    \    else v[i][j] = v[i][j - 1] * mint(i + 1 - j) / mint(j);\r\n             \
    \   }\r\n            }\r\n        }\r\n        mint res = 1;\r\n        while\
    \ (n || k) {\r\n            res *= v[n % mod][k % mod];\r\n            n /= mod,\
    \ k /= mod;\r\n        }\r\n        return res;\r\n    }\r\n\r\n    mint permu(int\
    \ n, int k) {\r\n        if (n < k || n < 0 || k < 0) return 0;\r\n        this->_init(n);\r\
    \n        return this->_fact[n] * this->_finv[n - k];\r\n    }\r\n\r\n  private:\r\
    \n    vector<mint> _fact, _finv;\r\n\r\n    void _init(int n) {\r\n        if\
    \ (this->_fact.size() > n) return;\r\n        int m = this->_fact.size();\r\n\
    \        this->_fact.resize(n + 1);\r\n        for (int i = m; i <= n; ++i) {\r\
    \n            if (i == 0) this->_fact[i] = 1;\r\n            else this->_fact[i]\
    \ = this->_fact[i - 1] * i;\r\n        }\r\n        this->_finv.resize(n + 1);\r\
    \n        this->_finv[n] = this->_fact[n].inverse();\r\n        for (int i = n\
    \ - 1; i >= m; --i) this->_finv[i] = this->_finv[i + 1] * (i + 1);\r\n    }\r\n\
    };\r\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/combination.hpp
  requiredBy:
  - lib/math/enumeration.hpp
  timestamp: '2022-08-02 10:37:25+09:00'
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
