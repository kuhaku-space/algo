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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\nint64_t inv_mod(int64_t a, int64_t\
    \ mod) {\r\n    int64_t b = mod, u = 1, v = 0, t;\r\n    while (b > 0) {\r\n \
    \       t = a / b;\r\n        swap(a -= t * b, b);\r\n        swap(u -= t * v,\
    \ v);\r\n    }\r\n    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;\r\n\
    }\r\n\r\nint64_t garner(vector<int64_t> r, vector<int64_t> m, const int mod) {\r\
    \n    int64_t n = r.size();\r\n    r.emplace_back(0);\r\n    m.emplace_back(mod);\r\
    \n\r\n    vector<int64_t> coffs(n + 1, 1);\r\n    vector<int64_t> constants(n\
    \ + 1, 0);\r\n    for (int64_t i = 0; i < n; ++i) {\r\n        int64_t v = (r[i]\
    \ - constants[i]) * inv_mod(coffs[i], m[i]) % m[i];\r\n        if (v < 0) v +=\
    \ m[i];\r\n\r\n        for (int64_t j = i + 1; j < n + 1; ++j) {\r\n         \
    \   (constants[j] += coffs[j] * v) %= m[j];\r\n            (coffs[j] *= m[i])\
    \ %= m[j];\r\n        }\r\n    }\r\n\r\n    return constants[n];\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/fft/garner.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/fft/garner.hpp
layout: document
redirect_from:
- /library/lib/fft/garner.hpp
- /library/lib/fft/garner.hpp.html
title: lib/fft/garner.hpp
---
