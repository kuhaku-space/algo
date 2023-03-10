---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bigint.hpp
    title: "\u591A\u500D\u9577\u6574\u6570"
  - icon: ':warning:'
    path: lib/fft/formal_power_series.hpp
    title: lib/fft/formal_power_series.hpp
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: "\u6570\u8AD6\u5909\u63DB"
  - icon: ':warning:'
    path: lib/fft/ntt_mod.hpp
    title: "\u4EFB\u610Fmod\u6570\u8AD6\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/enumeration.hpp
    title: lib/math/enumeration.hpp
  - icon: ':warning:'
    path: test/aoj/jag/aho_corasick.cpp
    title: test/aoj/jag/aho_corasick.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/bell.test.cpp
    title: test/aoj/dpl/bell.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/stirling.test.cpp
    title: test/aoj/dpl/stirling.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/addition.test.cpp
    title: test/aoj/ntl/addition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/difference.test.cpp
    title: test/aoj/ntl/difference.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/division.test.cpp
    title: test/aoj/ntl/division.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/multiplication.test.cpp
    title: test/aoj/ntl/multiplication.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/multiplication2.test.cpp
    title: test/aoj/ntl/multiplication2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/power.test.cpp
    title: test/aoj/ntl/power.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/remainder.test.cpp
    title: test/aoj/ntl/remainder.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution.test.cpp
    title: test/yosupo/convolution/convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_set_range_composite.test.cpp
    title: test/yosupo/data_structure/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
    title: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_affine_range_sum.test.cpp
    title: test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
    title: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/matrix/matrix_product.test.cpp
    title: test/yosupo/matrix/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/new/number_of_subsequences.test.cpp
    title: test/yosupo/new/number_of_subsequences.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: modint
    links:
    - https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief\
    \ modint\r\n * @see https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp\r\
    \n *\r\n * @tparam mod \u6CD5\r\n */\r\ntemplate <int mod = MOD_N>\r\nstruct ModInt\
    \ {\r\n    static constexpr int get_mod() noexcept { return mod; }\r\n\r\n   \
    \ constexpr ModInt() noexcept : x(0) {}\r\n    constexpr ModInt(int y) noexcept\
    \ : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}\r\n    constexpr ModInt(std::int64_t\
    \ y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}\r\n\r\n    constexpr\
    \ ModInt &operator+=(const ModInt &rhs) noexcept {\r\n        if ((this->x +=\
    \ rhs.x) >= mod) this->x -= mod;\r\n        return *this;\r\n    }\r\n    constexpr\
    \ ModInt &operator-=(const ModInt &rhs) noexcept {\r\n        if ((this->x +=\
    \ mod - rhs.x) >= mod) this->x -= mod;\r\n        return *this;\r\n    }\r\n \
    \   constexpr ModInt &operator*=(const ModInt &rhs) noexcept {\r\n        this->x\
    \ = (int)(1LL * this->x * rhs.x % mod);\r\n        return *this;\r\n    }\r\n\
    \    constexpr ModInt &operator/=(const ModInt &rhs) noexcept {\r\n        *this\
    \ *= rhs.inverse();\r\n        return *this;\r\n    }\r\n\r\n    constexpr ModInt\
    \ &operator++() noexcept {\r\n        if ((++(this->x)) >= mod) this->x -= mod;\r\
    \n        return *this;\r\n    }\r\n    constexpr ModInt operator++(int) noexcept\
    \ {\r\n        ModInt tmp(*this);\r\n        this->operator++();\r\n        return\
    \ tmp;\r\n    }\r\n    constexpr ModInt &operator--() noexcept {\r\n        if\
    \ ((this->x += mod - 1) >= mod) this->x -= mod;\r\n        return *this;\r\n \
    \   }\r\n    constexpr ModInt operator--(int) noexcept {\r\n        ModInt tmp(*this);\r\
    \n        this->operator--();\r\n        return tmp;\r\n    }\r\n\r\n    constexpr\
    \ ModInt operator-() const noexcept { return ModInt(-this->x); }\r\n    constexpr\
    \ ModInt operator+(const ModInt &rhs) const noexcept { return ModInt(*this) +=\
    \ rhs; }\r\n    constexpr ModInt operator-(const ModInt &rhs) const noexcept {\
    \ return ModInt(*this) -= rhs; }\r\n    constexpr ModInt operator*(const ModInt\
    \ &rhs) const noexcept { return ModInt(*this) *= rhs; }\r\n    constexpr ModInt\
    \ operator/(const ModInt &rhs) const noexcept { return ModInt(*this) /= rhs; }\r\
    \n\r\n    constexpr bool operator==(const ModInt &rhs) const noexcept { return\
    \ this->x == rhs.x; }\r\n    constexpr bool operator!=(const ModInt &rhs) const\
    \ noexcept { return this->x != rhs.x; }\r\n\r\n    explicit operator int() const\
    \ noexcept { return x; }\r\n\r\n    constexpr ModInt inverse() const noexcept\
    \ {\r\n        int a = x, b = mod, u = 1, v = 0, t;\r\n        while (b > 0) {\r\
    \n            t = a / b;\r\n            swap(a -= t * b, b);\r\n            swap(u\
    \ -= t * v, v);\r\n        }\r\n        return ModInt(u);\r\n    }\r\n\r\n   \
    \ constexpr ModInt pow(std::int64_t n) const noexcept { return ModInt(*this).pow_self(n);\
    \ }\r\n    constexpr ModInt &pow_self(std::int64_t n) noexcept {\r\n        ModInt\
    \ res(1);\r\n        for (; n > 0; n >>= 1) {\r\n            if (n & 1) res *=\
    \ *this;\r\n            *this *= *this;\r\n        }\r\n        *this = res;\r\
    \n        return *this;\r\n    }\r\n\r\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &rhs) {\r\n        std::int64_t t;\r\n        is >> t;\r\n     \
    \   rhs = ModInt<mod>(t);\r\n        return (is);\r\n    }\r\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const ModInt &rhs) { return os << rhs.x; }\r\n\
    \r\n  private:\r\n    int x;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/modint.hpp
  requiredBy:
  - test/aoj/jag/aho_corasick.cpp
  - lib/data_structure/bigint.hpp
  - lib/fft/ntt_mod.hpp
  - lib/fft/ntt.hpp
  - lib/fft/formal_power_series.hpp
  - lib/math/combination.hpp
  - lib/math/enumeration.hpp
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - test/yosupo/data_structure/point_set_range_composite.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - test/yosupo/new/number_of_subsequences.test.cpp
  - test/yosupo/convolution/convolution.test.cpp
  - test/yosupo/matrix/matrix_product.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
  - test/aoj/ntl/power.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/division.test.cpp
  - test/aoj/ntl/addition.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/dpl/stirling.test.cpp
  - test/aoj/dpl/bell.test.cpp
documentation_of: lib/math/modint.hpp
layout: document
redirect_from:
- /library/lib/math/modint.hpp
- /library/lib/math/modint.hpp.html
title: modint
---
