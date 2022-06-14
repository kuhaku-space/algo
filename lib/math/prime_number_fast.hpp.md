---
data:
  _extendedDependsOn:
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\nstruct prime_number {\r\n    static\
    \ constexpr int sz = 1 << 22;\r\n    array<int, sz> factor;\r\n\r\n    prime_number()\
    \ { init(); }\r\n\r\n    void init() {\r\n        iota(factor.begin(), factor.end(),\
    \ 0);\r\n        for (int i = 2; i < sz; ++i) {\r\n            if (factor[i] <\
    \ i) continue;\r\n            if ((int64_t)i * i > sz) continue;\r\n         \
    \   for (int j = i * i; j < sz; j += i) {\r\n                if (factor[j] ==\
    \ j) factor[j] = i;\r\n            }\r\n        }\r\n    }\r\n\r\n    bool is_prime(int\
    \ x) const {\r\n        assert(0 <= x && x < sz);\r\n        return this->factor[x]\
    \ == x;\r\n    }\r\n\r\n    vector<int> prime_numbers(int x) const {\r\n     \
    \   if (x < 2) return vector<int>();\r\n        vector<int> res = {2};\r\n   \
    \     for (int i = 3; i <= x; i += 2) {\r\n            if (this->is_prime(i))\
    \ res.emplace_back(i);\r\n        }\r\n        return res;\r\n    }\r\n\r\n  \
    \  // \u7D20\u56E0\u6570\u5206\u89E3\r\n    vector<int> prime_factorization(int\
    \ x) {\r\n        vector<int> res;\r\n        while (x > 1) {\r\n            res.emplace_back(factor[x]);\r\
    \n            x /= factor[x];\r\n        }\r\n        return res;\r\n    }\r\n\
    };\r\nprime_number pn;\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/prime_number_fast.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/prime_number_fast.hpp
layout: document
redirect_from:
- /library/lib/math/prime_number_fast.hpp
- /library/lib/math/prime_number_fast.hpp.html
title: lib/math/prime_number_fast.hpp
---
