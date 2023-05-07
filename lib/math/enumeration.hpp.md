---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: modint
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/combination.hpp:\
    \ line -1: no such header\n"
  code: "#include \"math/combination.hpp\"\n#include \"math/modint.hpp\"\n#include\
    \ \"template/template.hpp\"\n\ntemplate <int mod>\nstruct Enumeration {\n    using\
    \ mint = ModInt<mod>;\n\n    Enumeration() : combi(), data() {}\n\n    mint stirling(int\
    \ n, int k) {\n        mint res = 0;\n        for (int i = 0; i < k; ++i) {\n\
    \            if (i & 1) res -= this->combi(k, k - i) * mint(k - i).pow(n);\n \
    \           else res += this->combi(k, k - i) * mint(k - i).pow(n);\n        }\n\
    \        res *= this->combi.finv(k);\n        return res;\n    }\n\n    mint bell(int\
    \ n, int k) {\n        this->_init(k);\n        mint res = 0;\n        for (int\
    \ i = 0; i <= k; ++i) {\n            res += mint(i).pow(n) * this->combi.finv(i)\
    \ * this->data[k - i];\n        }\n        return res;\n    }\n\n  private:\n\
    \    Combination<mod> combi;\n    std::vector<mint> data;\n\n    void _init(int\
    \ n) {\n        if (this->data.size() > n) return;\n        int m = this->data.size();\n\
    \        this->data.resize(n + 1);\n        for (int i = m; i <= n; ++i) {\n \
    \           if (i == 0) this->data[i] = 1;\n            else if (i & 1) this->data[i]\
    \ = this->data[i - 1] - this->combi.finv(i);\n            else this->data[i] =\
    \ this->data[i - 1] + this->combi.finv(i);\n        }\n    }\n};\n"
  dependsOn:
  - lib/math/combination.hpp
  - lib/math/modint.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/enumeration.hpp
  requiredBy: []
  timestamp: '2023-05-07 20:09:35+09:00'
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
