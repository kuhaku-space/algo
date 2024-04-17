---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/math/hashint.hpp\"\n#include <cstdint>\n#include <utility>\n\
    \nstruct HashInt {\n    static constexpr std::uint64_t get_mod() noexcept { return\
    \ mod; }\n\n    constexpr HashInt() noexcept : x(0) {}\n    constexpr HashInt(int\
    \ y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}\n    constexpr HashInt(unsigned\
    \ int y) noexcept : x(y % mod) {}\n    constexpr HashInt(long y) noexcept : x(y\
    \ >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}\n    constexpr HashInt(unsigned long\
    \ y) noexcept : x(y % mod) {}\n    constexpr HashInt(long long y) noexcept : x(y\
    \ >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}\n    constexpr HashInt(unsigned long\
    \ long y) noexcept : x(y % mod) {}\n\n    constexpr HashInt &operator+=(const\
    \ HashInt &rhs) noexcept {\n        if ((x += rhs.x) >= mod) x -= mod;\n     \
    \   return *this;\n    }\n    constexpr HashInt &operator-=(const HashInt &rhs)\
    \ noexcept {\n        if ((x += mod - rhs.x) >= mod) x -= mod;\n        return\
    \ *this;\n    }\n    constexpr HashInt &operator*=(const HashInt &rhs) noexcept\
    \ {\n        std::uint64_t au = x >> 31, ad = x & mask31;\n        std::uint64_t\
    \ bu = rhs.x >> 31, bd = rhs.x & mask31;\n        std::uint64_t mid = ad * bu\
    \ + au * bd;\n        std::uint64_t midu = mid >> 30, midd = mid & mask30;\n \
    \       x = _mod(au * bu * 2 + midu + (midd << 31) + ad * bd);\n        return\
    \ *this;\n    }\n    constexpr HashInt &operator/=(const HashInt &rhs) noexcept\
    \ {\n        *this *= rhs.inverse();\n        return *this;\n    }\n\n    constexpr\
    \ HashInt &operator++() noexcept {\n        if ((++x) >= mod) x -= mod;\n    \
    \    return *this;\n    }\n    constexpr HashInt operator++(int) noexcept {\n\
    \        HashInt tmp(*this);\n        operator++();\n        return tmp;\n   \
    \ }\n    constexpr HashInt &operator--() noexcept {\n        if ((x += mod - 1)\
    \ >= mod) x -= mod;\n        return *this;\n    }\n    constexpr HashInt operator--(int)\
    \ noexcept {\n        HashInt tmp(*this);\n        operator--();\n        return\
    \ tmp;\n    }\n\n    constexpr HashInt operator-() const noexcept { return HashInt(-x);\
    \ }\n    constexpr HashInt operator+(const HashInt &rhs) const noexcept { return\
    \ HashInt(*this) += rhs; }\n    constexpr HashInt operator-(const HashInt &rhs)\
    \ const noexcept { return HashInt(*this) -= rhs; }\n    constexpr HashInt operator*(const\
    \ HashInt &rhs) const noexcept { return HashInt(*this) *= rhs; }\n    constexpr\
    \ HashInt operator/(const HashInt &rhs) const noexcept { return HashInt(*this)\
    \ /= rhs; }\n\n    constexpr bool operator==(const HashInt &rhs) const noexcept\
    \ { return x == rhs.x; }\n    constexpr bool operator!=(const HashInt &rhs) const\
    \ noexcept { return x != rhs.x; }\n\n    constexpr explicit operator long() const\
    \ noexcept { return x; }\n    constexpr explicit operator unsigned long() const\
    \ noexcept { return x; }\n    constexpr explicit operator long long() const noexcept\
    \ { return x; }\n    constexpr explicit operator unsigned long long() const noexcept\
    \ { return x; }\n\n    constexpr HashInt inverse() const noexcept {\n        std::int64_t\
    \ a = x, b = mod, u = 1, v = 0, t = 0;\n        while (b > 0) {\n            t\
    \ = a / b;\n            std::swap(a -= t * b, b);\n            std::swap(u -=\
    \ t * v, v);\n        }\n        return HashInt(u);\n    }\n\n    constexpr HashInt\
    \ pow(std::uint64_t n) const noexcept { return HashInt(*this).pow_self(n); }\n\
    \    constexpr HashInt &pow_self(std::uint64_t n) noexcept {\n        HashInt\
    \ res(1);\n        for (; n > 0; n >>= 1) {\n            if (n & 1) res *= *this;\n\
    \            *this *= *this;\n        }\n        *this = res;\n        return\
    \ *this;\n    }\n\n  private:\n    std::uint64_t x;\n\n    static constexpr std::uint64_t\
    \ mod = (1ul << 61) - 1;\n    static constexpr std::uint64_t mask30 = (1ul <<\
    \ 30) - 1;\n    static constexpr std::uint64_t mask31 = (1ul << 31) - 1;\n\n \
    \   constexpr std::uint64_t _mod(std::uint64_t x) const {\n        std::uint64_t\
    \ xu = x >> 61, xd = x & mod;\n        std::uint64_t res = xu + xd;\n        if\
    \ (res >= mod) res -= mod;\n        return res;\n    }\n};\n"
  code: "#include <cstdint>\n#include <utility>\n\nstruct HashInt {\n    static constexpr\
    \ std::uint64_t get_mod() noexcept { return mod; }\n\n    constexpr HashInt()\
    \ noexcept : x(0) {}\n    constexpr HashInt(int y) noexcept : x(y >= 0 ? y % mod\
    \ : (mod - 1 - ~y % mod)) {}\n    constexpr HashInt(unsigned int y) noexcept :\
    \ x(y % mod) {}\n    constexpr HashInt(long y) noexcept : x(y >= 0 ? y % mod :\
    \ (mod - 1 - ~y % mod)) {}\n    constexpr HashInt(unsigned long y) noexcept :\
    \ x(y % mod) {}\n    constexpr HashInt(long long y) noexcept : x(y >= 0 ? y %\
    \ mod : (mod - 1 - ~y % mod)) {}\n    constexpr HashInt(unsigned long long y)\
    \ noexcept : x(y % mod) {}\n\n    constexpr HashInt &operator+=(const HashInt\
    \ &rhs) noexcept {\n        if ((x += rhs.x) >= mod) x -= mod;\n        return\
    \ *this;\n    }\n    constexpr HashInt &operator-=(const HashInt &rhs) noexcept\
    \ {\n        if ((x += mod - rhs.x) >= mod) x -= mod;\n        return *this;\n\
    \    }\n    constexpr HashInt &operator*=(const HashInt &rhs) noexcept {\n   \
    \     std::uint64_t au = x >> 31, ad = x & mask31;\n        std::uint64_t bu =\
    \ rhs.x >> 31, bd = rhs.x & mask31;\n        std::uint64_t mid = ad * bu + au\
    \ * bd;\n        std::uint64_t midu = mid >> 30, midd = mid & mask30;\n      \
    \  x = _mod(au * bu * 2 + midu + (midd << 31) + ad * bd);\n        return *this;\n\
    \    }\n    constexpr HashInt &operator/=(const HashInt &rhs) noexcept {\n   \
    \     *this *= rhs.inverse();\n        return *this;\n    }\n\n    constexpr HashInt\
    \ &operator++() noexcept {\n        if ((++x) >= mod) x -= mod;\n        return\
    \ *this;\n    }\n    constexpr HashInt operator++(int) noexcept {\n        HashInt\
    \ tmp(*this);\n        operator++();\n        return tmp;\n    }\n    constexpr\
    \ HashInt &operator--() noexcept {\n        if ((x += mod - 1) >= mod) x -= mod;\n\
    \        return *this;\n    }\n    constexpr HashInt operator--(int) noexcept\
    \ {\n        HashInt tmp(*this);\n        operator--();\n        return tmp;\n\
    \    }\n\n    constexpr HashInt operator-() const noexcept { return HashInt(-x);\
    \ }\n    constexpr HashInt operator+(const HashInt &rhs) const noexcept { return\
    \ HashInt(*this) += rhs; }\n    constexpr HashInt operator-(const HashInt &rhs)\
    \ const noexcept { return HashInt(*this) -= rhs; }\n    constexpr HashInt operator*(const\
    \ HashInt &rhs) const noexcept { return HashInt(*this) *= rhs; }\n    constexpr\
    \ HashInt operator/(const HashInt &rhs) const noexcept { return HashInt(*this)\
    \ /= rhs; }\n\n    constexpr bool operator==(const HashInt &rhs) const noexcept\
    \ { return x == rhs.x; }\n    constexpr bool operator!=(const HashInt &rhs) const\
    \ noexcept { return x != rhs.x; }\n\n    constexpr explicit operator long() const\
    \ noexcept { return x; }\n    constexpr explicit operator unsigned long() const\
    \ noexcept { return x; }\n    constexpr explicit operator long long() const noexcept\
    \ { return x; }\n    constexpr explicit operator unsigned long long() const noexcept\
    \ { return x; }\n\n    constexpr HashInt inverse() const noexcept {\n        std::int64_t\
    \ a = x, b = mod, u = 1, v = 0, t = 0;\n        while (b > 0) {\n            t\
    \ = a / b;\n            std::swap(a -= t * b, b);\n            std::swap(u -=\
    \ t * v, v);\n        }\n        return HashInt(u);\n    }\n\n    constexpr HashInt\
    \ pow(std::uint64_t n) const noexcept { return HashInt(*this).pow_self(n); }\n\
    \    constexpr HashInt &pow_self(std::uint64_t n) noexcept {\n        HashInt\
    \ res(1);\n        for (; n > 0; n >>= 1) {\n            if (n & 1) res *= *this;\n\
    \            *this *= *this;\n        }\n        *this = res;\n        return\
    \ *this;\n    }\n\n  private:\n    std::uint64_t x;\n\n    static constexpr std::uint64_t\
    \ mod = (1ul << 61) - 1;\n    static constexpr std::uint64_t mask30 = (1ul <<\
    \ 30) - 1;\n    static constexpr std::uint64_t mask31 = (1ul << 31) - 1;\n\n \
    \   constexpr std::uint64_t _mod(std::uint64_t x) const {\n        std::uint64_t\
    \ xu = x >> 61, xd = x & mod;\n        std::uint64_t res = xu + xd;\n        if\
    \ (res >= mod) res -= mod;\n        return res;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/math/hashint.hpp
  requiredBy: []
  timestamp: '2024-04-17 14:43:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/hashint.hpp
layout: document
redirect_from:
- /library/lib/math/hashint.hpp
- /library/lib/math/hashint.hpp.html
title: lib/math/hashint.hpp
---
