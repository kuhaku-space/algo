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
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: fft/ntt.hpp: line\
    \ -1: no such header\n"
  code: "#include \"fft/ntt.hpp\"\r\n#include \"math/modint.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\ntemplate <class mint>\r\nstruct formal_power_series : std::vector<mint>\
    \ {\r\n    using fps = formal_power_series;\r\n\r\n    formal_power_series(std::vector<T>\
    \ &&v) : std::vector<mint>(v) {}\r\n    formal_power_series(const std::vector<T>\
    \ &v) : std::vector<mint>(v) {}\r\n\r\n    constexpr fps &operator+=(const mint\
    \ &v) {\r\n        if (this->empty()) this->resize(1);\r\n        (*this)[0] +=\
    \ v;\r\n        return *this;\r\n    }\r\n    constexpr fps &operator+=(const\
    \ fps &f) {\r\n        if (f.size() > this->size()) this->resize(f.size());\r\n\
    \        for (int i = 0; i < (int)f.size(); ++i) (*this)[i] += f[i];\r\n     \
    \   return this->normalize();\r\n    }\r\n    constexpr fps &operator-=(const\
    \ mint &v) {\r\n        if (this->empty()) this->resize(1);\r\n        (*this)[0]\
    \ -= v;\r\n        return *this;\r\n    }\r\n    constexpr fps &operator-=(const\
    \ fps &f) {\r\n        if (f.size() > this->size()) this->resize(f.size());\r\n\
    \        for (int i = 0; i < (int)f.size(); ++i) (*this)[i] -= f[i];\r\n     \
    \   return this->normalize();\r\n    }\r\n    constexpr fps &operator*=(const\
    \ mint &v) {\r\n        for (int i = 0; i < (int)this->size(); ++i) (*this)[i]\
    \ *= v;\r\n        return *this;\r\n    }\r\n    constexpr fps &operator*=(const\
    \ fps &f) { return *this = convolution((*this), f); }\r\n    constexpr fps &operator/=(const\
    \ mint &v) {\r\n        assert(v != 0);\r\n        mint iv = modinv(v);\r\n  \
    \      for (int i = 0; i < (int)this->size(); ++i) (*this)[i] *= iv;\r\n     \
    \   return *this;\r\n    }\r\n    constexpr fps &operator<<=(int x) {\r\n    \
    \    fps res(x, 0);\r\n        res.insert(res.end(), begin(*this), end(*this));\r\
    \n        return *this = res;\r\n    }\r\n    constexpr fps &operator>>=(int x)\
    \ {\r\n        fps res;\r\n        res.insert(res.end(), begin(*this) + x, end(*this));\r\
    \n        return *this = res;\r\n    }\r\n\r\n    constexpr fps operator+(const\
    \ mint &v) const { return fps(*this) += v; }\r\n    constexpr fps operator+(const\
    \ fps &f) const { return fps(*this) += f; }\r\n    constexpr fps operator-(const\
    \ mint &v) const { return fps(*this) -= v; }\r\n    constexpr fps operator-(const\
    \ fps &f) const { return fps(*this) -= f; }\r\n    constexpr fps operator*(const\
    \ mint &v) const { return fps(*this) *= v; }\r\n    constexpr fps operator*(const\
    \ fps &f) const { return fps(*this) *= f; }\r\n    constexpr fps operator/(const\
    \ mint &v) const { return fps(*this) /= v; }\r\n    constexpr fps operator<<(int\
    \ x) const { return fps(*this) <<= x; }\r\n    constexpr fps operator>>(int x)\
    \ const { return fps(*this) >>= x; }\r\n\r\n    constexpr fps operator+() const\
    \ { return fps(*this); }\r\n    constexpr fps operator-() const {\r\n        fps\
    \ res = *this;\r\n        for (int i = 0; i < (int)res.size(); ++i) res[i] = -res[i];\r\
    \n        return res;\r\n    }\r\n\r\n    constexpr fps pre(int sz) const {\r\n\
    \        return fps(std::begin(*this), std::begin(*this) + std::min((int)this->size(),\
    \ sz));\r\n    }\r\n    constexpr fps inv(int deg) {\r\n        assert((*this)[0]\
    \ != 0);\r\n        if (deg < 0) deg = (int)v.size();\r\n        fps res({mint(1)\
    \ / (*this)[0]});\r\n        for (int i = 1; i < deg; i <<= 1) {\r\n         \
    \   res = (res + res - res * res * this->pre(i << 1)).pre(i << 1);\r\n       \
    \ }\r\n        res.resize(deg);\r\n        return res;\r\n    }\r\n    constexpr\
    \ fps inv() { return inv(v.size()); }\r\n};\r\n"
  dependsOn:
  - lib/fft/ntt.hpp
  - lib/internal/internal_fft.hpp
  - lib/internal/internal_bit.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/fft/formal_power_series.hpp
  requiredBy: []
  timestamp: '2023-10-01 18:31:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/fft/formal_power_series.hpp
layout: document
redirect_from:
- /library/lib/fft/formal_power_series.hpp
- /library/lib/fft/formal_power_series.hpp.html
title: lib/fft/formal_power_series.hpp
---
