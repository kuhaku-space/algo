---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\nint64_t gcd(int64_t a, int64_t\
    \ b) {\r\n    while (b) {\r\n        a %= b;\r\n        swap(a, b);\r\n    }\r\
    \n    return a;\r\n}\r\n\r\nint64_t gcd(const vector<int64_t> &v) {\r\n    if\
    \ (v.empty()) return 1;\r\n    int64_t res = v[0];\r\n    for (auto i : v) res\
    \ = gcd(res, i);\r\n    return res;\r\n}\r\n\r\nint64_t lcm(int64_t a, int64_t\
    \ b) {\r\n    return a / gcd(a, b) * b;\r\n}\r\n\r\nint64_t lcm(const vector<int64_t>\
    \ &v) {\r\n    int64_t res = 1;\r\n    for (auto i : v) res = lcm(res, i);\r\n\
    \    return res;\r\n}\r\n\r\nint64_t floor_div(int64_t p, int64_t q) {\r\n   \
    \ int64_t res = p / q;\r\n    if (q * res > p) --res;\r\n    return res;\r\n}\r\
    \n\r\nint64_t ceil_div(int64_t p, int64_t q) {\r\n    int64_t res = p / q;\r\n\
    \    if (q * res < p) ++res;\r\n    return res;\r\n}\r\n\r\nint64_t round_ll(double\
    \ d) {\r\n    if (d < 0) return -round_ll(-d);\r\n    return int64_t(d + 0.5);\r\
    \n}\r\n\r\nint64_t round_ll(long double d) {\r\n    if (d < 0) return -round_ll(-d);\r\
    \n    return int64_t(d + 0.5);\r\n}\r\n\r\nbool is_prime(int n) {\r\n    for (int\
    \ i = 2; i * i <= n; ++i) {\r\n        if (n % i == 0) return false;\r\n    }\r\
    \n    return true;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/math.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/math.hpp
layout: document
redirect_from:
- /library/lib/math/math.hpp
- /library/lib/math/math.hpp.html
title: lib/math/math.hpp
---
