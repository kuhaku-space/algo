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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <int N = (1 << 22)>\r\n\
    struct eratosthenes {\r\n    constexpr eratosthenes() : prime_number() {\r\n \
    \       this->prime_number.set();\r\n        this->prime_number[0] = this->prime_number[1]\
    \ = false;\r\n        for (int i = 2; i <= N; ++i) {\r\n            if (!this->prime_number[i])\
    \ continue;\r\n            if ((std::int64_t)i * i > N) continue;\r\n        \
    \    for (int j = i * i; j <= N; j += i) {\r\n                if (this->prime_number[j])\
    \ this->prime_number[j] = false;\r\n            }\r\n        }\r\n    }\r\n\r\n\
    \    bool is_prime(int x) const {\r\n        return this->prime_number[x];\r\n\
    \    }\r\n\r\n    std::vector<int> prime_numbers(int x) const {\r\n        if\
    \ (x < 2) return std::vector<int>();\r\n        std::vector<int> res = {2};\r\n\
    \        for (int i = 3; i <= x; i += 2) {\r\n            if (this->is_prime(i))\
    \ res.emplace_back(i);\r\n        }\r\n        return res;\r\n    }\r\n\r\n  private:\r\
    \n    std::bitset<N + 1> prime_number;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/eratosthenes.hpp
  requiredBy: []
  timestamp: '2022-09-24 19:18:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/eratosthenes.hpp
layout: document
redirect_from:
- /library/lib/math/eratosthenes.hpp
- /library/lib/math/eratosthenes.hpp.html
title: lib/math/eratosthenes.hpp
---
