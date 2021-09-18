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
    links:
    - https://atcoder.jp/contests/abc141/tasks/abc141_e
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include <random>\r\n\r\n#include \"template/template.hpp\"\r\n\r\n// verify\
    \ : https://atcoder.jp/contests/abc141/tasks/abc141_e 21/02/24\r\n\r\nstruct rolling_hash\
    \ {\r\n    const uint64_t mod = (1ul << 61) - 1;\r\n    const uint64_t mask30\
    \ = (1ul << 30) - 1;\r\n    const uint64_t mask31 = (1ul << 31) - 1;\r\n    uint64_t\
    \ base, len;\r\n    vector<uint64_t> data, p;\r\n\r\n    rolling_hash(const string\
    \ &_s) : data(1), p(1, 1), len(_s.size() + 1) {\r\n        random_device seed;\r\
    \n        mt19937 mt(seed());\r\n        base = mt() + 2;\r\n        uint64_t\
    \ x = 0, t = 1;\r\n        for (const auto c : _s) {\r\n            x = _mod(_mul(x,\
    \ base) + c);\r\n            data.emplace_back(x);\r\n            t = _mod(_mul(t,\
    \ base));\r\n            p.emplace_back(t);\r\n        }\r\n    }\r\n\r\n    uint64_t\
    \ _mul(uint64_t a, uint64_t b) {\r\n        uint64_t au = a >> 31, ad = a & mask31;\r\
    \n        uint64_t bu = b >> 31, bd = b & mask31;\r\n        uint64_t mid = ad\
    \ * bu + au * bd;\r\n        uint64_t midu = mid >> 30, midd = mid & mask30;\r\
    \n        return au * bu * 2 + midu + (midd << 31) + ad * bd;\r\n    }\r\n\r\n\
    \    uint64_t _mod(uint64_t x) {\r\n        uint64_t xu = x >> 61, xd = x & mod;\r\
    \n        uint64_t res = xu + xd;\r\n        if (res >= mod) res -= mod;\r\n \
    \       return res;\r\n    }\r\n\r\n    uint64_t _pow(uint64_t x, uint64_t k)\
    \ {\r\n        uint64_t res = 1;\r\n        for (; k; k >>= 1) {\r\n         \
    \   if (k & 1) res = _mod(_mul(res, x));\r\n            x = _mod(_mul(x, x));\r\
    \n        }\r\n        return res;\r\n    }\r\n\r\n    inline uint64_t get(int\
    \ l, int r) {\r\n        return _mod(data[r] + mod * 4 - _mul(data[l], p[r - l]));\r\
    \n    }\r\n\r\n    vector<int> search(const string &s) {\r\n        vector<int>\
    \ res;\r\n        int n = s.size();\r\n        if (n >= len) return res;\r\n \
    \       uint64_t x = 0;\r\n        for (const auto c : s) x = _mod(_mul(x, base)\
    \ + c);\r\n        for (int i = n; i < len; ++i) {\r\n            if (get(i -\
    \ n, i) == x) res.emplace_back(i - n);\r\n            x = _mod(_mul(x, base));\r\
    \n        }\r\n        return res;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/rolling_hash.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/rolling_hash.hpp
layout: document
redirect_from:
- /library/lib/string/rolling_hash.hpp
- /library/lib/string/rolling_hash.hpp.html
title: lib/string/rolling_hash.hpp
---
