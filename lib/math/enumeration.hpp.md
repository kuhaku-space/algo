---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/algo/modint.hpp
    title: modint
  - icon: ':heavy_check_mark:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dp/bell.test.cpp
    title: test/aoj/dp/bell.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dp/stirling.test.cpp
    title: test/aoj/dp/stirling.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algo/modint.hpp:\
    \ line -1: no such header\n"
  code: "#include \"algo/modint.hpp\"\n#include \"math/combination.hpp\"\n#include\
    \ \"template/template.hpp\"\n\ntemplate <int mod>\nstruct Enumeration {\n    using\
    \ mint = ModInt<mod>;\n    Combination<mod> combi;\n    vector<mint> data;\n\n\
    \    Enumeration() : combi(), data() {}\n\n    void _init(int n) {\n        if\
    \ (data.size() > n) return;\n        int m = data.size();\n        data.resize(n\
    \ + 1);\n        for (int i = m; i <= n; ++i) {\n            if (i == 0)\n   \
    \             data[i] = 1;\n            else if (i & 1)\n                data[i]\
    \ = data[i - 1] - combi.finv(i);\n            else\n                data[i] =\
    \ data[i - 1] + combi.finv(i);\n        }\n    }\n\n    mint stirling(int n, int\
    \ k) {\n        mint res = 0;\n        for (int i = 0; i < k; ++i) {\n       \
    \     if (i & 1)\n                res -= combi(k, k - i) * mint(k - i).pow(n);\n\
    \            else\n                res += combi(k, k - i) * mint(k - i).pow(n);\n\
    \        }\n        res /= combi.fact(k);\n        return res;\n    }\n\n    mint\
    \ bell(int n, int k) {\n        _init(k);\n        mint res = 0;\n        for\
    \ (int i = 0; i <= k; ++i) {\n            res += mint(i).pow(n) * combi.finv(i)\
    \ * data[k - i];\n        }\n        return res;\n    }\n};\nEnumeration<MOD>\
    \ enume;\n"
  dependsOn:
  - lib/algo/modint.hpp
  - lib/template/template.hpp
  - lib/math/combination.hpp
  isVerificationFile: false
  path: lib/math/enumeration.hpp
  requiredBy: []
  timestamp: '2021-09-26 10:13:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dp/bell.test.cpp
  - test/aoj/dp/stirling.test.cpp
documentation_of: lib/math/enumeration.hpp
layout: document
redirect_from:
- /library/lib/math/enumeration.hpp
- /library/lib/math/enumeration.hpp.html
title: lib/math/enumeration.hpp
---
