---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: "\u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_fft.hpp
    title: lib/internal/internal_fft.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_math.hpp
    title: lib/internal/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_type_traits.hpp
    title: lib/internal/internal_type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/sqrt.hpp
    title: lib/math/sqrt.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/polynomial/exp_of_formal_power_series.test.cpp
    title: test/yosupo/polynomial/exp_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/polynomial/inv_of_formal_power_series.test.cpp
    title: test/yosupo/polynomial/inv_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/polynomial/log_of_formal_power_series.test.cpp
    title: test/yosupo/polynomial/log_of_formal_power_series.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/polynomial/pow_of_formal_power_series.test.cpp
    title: test/yosupo/polynomial/pow_of_formal_power_series.test.cpp
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: fft/ntt.hpp: line\
    \ -1: no such header\n"
  code: "#include <algorithm>\r\n#include <cassert>\r\n#include <cstdint>\r\n#include\
    \ <vector>\r\n#include \"fft/ntt.hpp\"\r\n#include \"math/sqrt.hpp\"\r\n\r\nnamespace\
    \ fps {\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint> * = nullptr>\r\
    \nstd::vector<mint> inv(const std::vector<mint> &h, int deg) {\r\n    assert(!h.empty()\
    \ && h[0] != mint(0));\r\n    std::vector<mint> res(deg);\r\n    res[0] = h[0].inv();\r\
    \n    for (int d = 1; d < deg; d <<= 1) {\r\n        std::vector<mint> f(2 * d),\
    \ g(2 * d);\r\n        for (int i = 0; i < std::min((int)h.size(), 2 * d); ++i)\
    \ f[i] = h[i];\r\n        for (int i = 0; i < d; ++i) g[i] = res[i];\r\n     \
    \   internal::butterfly(f);\r\n        internal::butterfly(g);\r\n        for\
    \ (int i = 0; i < 2 * d; ++i) f[i] *= g[i];\r\n        internal::butterfly_inv(f);\r\
    \n        mint id = mint(2 * d).inv();\r\n        for (int i = 0; i < 2 * d; ++i)\
    \ f[i] *= id;\r\n        for (int i = 0; i < d; ++i) f[i] = 0;\r\n        internal::butterfly(f);\r\
    \n        for (int i = 0; i < 2 * d; ++i) f[i] *= g[i];\r\n        internal::butterfly_inv(f);\r\
    \n        for (int i = 0; i < 2 * d; ++i) f[i] *= id;\r\n        for (int i =\
    \ d; i < std::min(2 * d, deg); ++i) res[i] = -f[i];\r\n    }\r\n    res.resize(deg);\r\
    \n    return res;\r\n}\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint>\
    \ * = nullptr>\r\nstd::vector<mint> inv(const std::vector<mint> &h) {\r\n    return\
    \ inv(h, h.size());\r\n}\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint>\
    \ * = nullptr>\r\nstd::vector<mint> log(const std::vector<mint> &h, int deg) {\r\
    \n    assert(!h.empty() && h[0] == 1);\r\n    std::vector<mint> f(h.begin() +\
    \ 1, h.end());\r\n    for (int i = 0; i < (int)f.size(); ++i) f[i] *= i + 1;\r\
    \n    f = convolution(f, inv(h));\r\n    f.emplace(f.begin(), 0);\r\n    f.resize(deg);\r\
    \n    for (int i = 1; i < deg; ++i) f[i] /= i;\r\n    return f;\r\n}\r\n\r\ntemplate\
    \ <class mint, internal::is_static_modint_t<mint> * = nullptr>\r\nstd::vector<mint>\
    \ log(const std::vector<mint> &h) {\r\n    return log(h, h.size());\r\n}\r\n\r\
    \ntemplate <class mint, internal::is_static_modint_t<mint> * = nullptr>\r\nstd::vector<mint>\
    \ exp(const std::vector<mint> &h, int deg) {\r\n    std::vector<mint> f(deg),\
    \ g(deg);\r\n    f[0] = 1;\r\n    g[0] = 1;\r\n    for (int d = 1; d < deg; d\
    \ <<= 1) {\r\n        std::vector<mint> dt(d);\r\n        for (int i = 0; i <\
    \ d; ++i) dt[i] = h[i] * i;\r\n        std::vector<mint> tf(2 * d), tg(2 * d),\
    \ sf(d);\r\n        for (int i = 0; i < d; ++i) sf[i] = f[i];\r\n        for (int\
    \ i = 0; i < d; ++i) tf[i] = f[i];\r\n        for (int i = 0; i < d; ++i) tg[i]\
    \ = g[i];\r\n\r\n        tf = convolution(tf, dt);\r\n        tf.resize(2 * d);\r\
    \n        for (int i = 0; i < d; ++i) tf[i] -= f[i] * i;\r\n        tf = convolution(tf,\
    \ tg);\r\n        tf.resize(2 * d);\r\n        for (int i = 0; i < d; ++i) tf[i]\
    \ -= dt[i];\r\n        for (int i = 1; i < 2 * d; ++i) tf[i] = tf[i] / i;\r\n\
    \        tf[0] = 0;\r\n        for (int i = 0; i < std::min((int)h.size(), 2 *\
    \ d); ++i) tf[i] += h[i];\r\n        tf = convolution(sf, tf);\r\n        for\
    \ (int i = d; i < std::min(deg, 2 * d); ++i) f[i] = tf[i];\r\n\r\n        std::vector<mint>\
    \ ft(2 * d), gt(2 * d);\r\n        for (int i = 0; i < 2 * d; ++i) ft[i] = f[i];\r\
    \n        for (int i = 0; i < d; ++i) gt[i] = g[i];\r\n        internal::butterfly(ft);\r\
    \n        internal::butterfly(gt);\r\n        for (int i = 0; i < 2 * d; ++i)\
    \ ft[i] *= gt[i];\r\n        internal::butterfly_inv(ft);\r\n        mint id =\
    \ mint(2 * d).inv();\r\n        for (int i = 0; i < 2 * d; ++i) ft[i] *= id;\r\
    \n        for (int i = 0; i < d; ++i) ft[i] = 0;\r\n        internal::butterfly(ft);\r\
    \n        for (int i = 0; i < 2 * d; ++i) ft[i] *= gt[i];\r\n        internal::butterfly_inv(ft);\r\
    \n        for (int i = 0; i < 2 * d; ++i) ft[i] *= id;\r\n        for (int i =\
    \ d; i < std::min(deg, 2 * d); ++i) g[i] = -ft[i];\r\n    }\r\n    return f;\r\
    \n}\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint> * = nullptr>\r\
    \nstd::vector<mint> exp(const std::vector<mint> &h) {\r\n    return exp(h, h.size());\r\
    \n}\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint> * = nullptr>\r\
    \nstd::vector<mint> pow(const std::vector<mint> &h, std::int64_t m, int deg) {\r\
    \n    if (m == 0) {\r\n        std::vector<mint> res(deg, 0);\r\n        res[0]\
    \ = 1;\r\n        return res;\r\n    }\r\n    if (m == 1) return h;\r\n    if\
    \ (m < 0) return inv(pow(h, -m, deg));\r\n\r\n    int n = h.size();\r\n    int\
    \ k = 0;\r\n    while (k < n && h[k] == 0) ++k;\r\n    if (k >= (deg + m - 1)\
    \ / m) return std::vector<mint>(deg);\r\n    mint c = h[k];\r\n    mint ic = c.inv();\r\
    \n    mint pc = c.pow(m);\r\n    std::vector<mint> res = h;\r\n    res.erase(res.begin(),\
    \ res.begin() + k);\r\n    for (int i = 0; i < n - k; ++i) res[i] *= ic;\r\n \
    \   res = log(res, deg - k * m);\r\n    for (int i = 0; i < deg; ++i) res[i] *=\
    \ m;\r\n    res = exp(res, deg - k * m);\r\n    for (int i = 0; i < deg - k *\
    \ m; ++i) res[i] *= pc;\r\n    res.insert(res.begin(), k * m, mint());\r\n   \
    \ return res;\r\n}\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint>\
    \ * = nullptr>\r\nstd::vector<mint> pow(const std::vector<mint> &h, std::int64_t\
    \ m) {\r\n    return pow(h, m, h.size());\r\n}\r\n\r\n}  // namespace fps\r\n"
  dependsOn:
  - lib/fft/ntt.hpp
  - lib/internal/internal_fft.hpp
  - lib/internal/internal_bit.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  - lib/template/template.hpp
  - lib/math/sqrt.hpp
  isVerificationFile: false
  path: lib/fft/formal_power_series.hpp
  requiredBy: []
  timestamp: '2024-05-15 10:21:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/polynomial/log_of_formal_power_series.test.cpp
  - test/yosupo/polynomial/pow_of_formal_power_series.test.cpp
  - test/yosupo/polynomial/inv_of_formal_power_series.test.cpp
  - test/yosupo/polynomial/exp_of_formal_power_series.test.cpp
documentation_of: lib/fft/formal_power_series.hpp
layout: document
redirect_from:
- /library/lib/fft/formal_power_series.hpp
- /library/lib/fft/formal_power_series.hpp.html
title: lib/fft/formal_power_series.hpp
---
