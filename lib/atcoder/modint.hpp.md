---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/atcoder/internal_math.hpp
    title: lib/atcoder/internal_math.hpp
  - icon: ':warning:'
    path: lib/atcoder/internal_type_traits.hpp
    title: lib/atcoder/internal_type_traits.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/atcoder/convolution.hpp
    title: lib/atcoder/convolution.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/modint.hpp\"\n\n\n\r\n#include <atcoder/internal_math>\r\
    \n#include <atcoder/internal_type_traits>\r\n#include <cassert>\r\n#include <numeric>\r\
    \n#include <type_traits>\r\n\r\n#ifdef _MSC_VER\r\n#include <intrin.h>\r\n#endif\r\
    \n\r\nnamespace atcoder {\r\n\r\nnamespace internal {\r\n\r\nstruct modint_base\
    \ {};\r\nstruct static_modint_base : modint_base {};\r\n\r\ntemplate <class T>\
    \ using is_modint = std::is_base_of<modint_base, T>;\r\ntemplate <class T> using\
    \ is_modint_t = std::enable_if_t<is_modint<T>::value>;\r\n\r\n}  // namespace\
    \ internal\r\n\r\ntemplate <int m, std::enable_if_t<(1 <= m)>* = nullptr>\r\n\
    struct static_modint : internal::static_modint_base {\r\n    using mint = static_modint;\r\
    \n\r\n  public:\r\n    static constexpr int mod() { return m; }\r\n    static\
    \ mint raw(int v) {\r\n        mint x;\r\n        x._v = v;\r\n        return\
    \ x;\r\n    }\r\n\r\n    static_modint() : _v(0) {}\r\n    template <class T,\
    \ internal::is_signed_int_t<T>* = nullptr>\r\n    static_modint(T v) {\r\n   \
    \     long long x = (long long)(v % (long long)(umod()));\r\n        if (x < 0)\
    \ x += umod();\r\n        _v = (unsigned int)(x);\r\n    }\r\n    template <class\
    \ T, internal::is_unsigned_int_t<T>* = nullptr>\r\n    static_modint(T v) {\r\n\
    \        _v = (unsigned int)(v % umod());\r\n    }\r\n    static_modint(bool v)\
    \ { _v = ((unsigned int)(v) % umod()); }\r\n\r\n    unsigned int val() const {\
    \ return _v; }\r\n\r\n    mint& operator++() {\r\n        _v++;\r\n        if\
    \ (_v == umod()) _v = 0;\r\n        return *this;\r\n    }\r\n    mint& operator--()\
    \ {\r\n        if (_v == 0) _v = umod();\r\n        _v--;\r\n        return *this;\r\
    \n    }\r\n    mint operator++(int) {\r\n        mint result = *this;\r\n    \
    \    ++*this;\r\n        return result;\r\n    }\r\n    mint operator--(int) {\r\
    \n        mint result = *this;\r\n        --*this;\r\n        return result;\r\
    \n    }\r\n\r\n    mint& operator+=(const mint& rhs) {\r\n        _v += rhs._v;\r\
    \n        if (_v >= umod()) _v -= umod();\r\n        return *this;\r\n    }\r\n\
    \    mint& operator-=(const mint& rhs) {\r\n        _v -= rhs._v;\r\n        if\
    \ (_v >= umod()) _v += umod();\r\n        return *this;\r\n    }\r\n    mint&\
    \ operator*=(const mint& rhs) {\r\n        unsigned long long z = _v;\r\n    \
    \    z *= rhs._v;\r\n        _v = (unsigned int)(z % umod());\r\n        return\
    \ *this;\r\n    }\r\n    mint& operator/=(const mint& rhs) { return *this = *this\
    \ * rhs.inv(); }\r\n\r\n    mint operator+() const { return *this; }\r\n    mint\
    \ operator-() const { return mint() - *this; }\r\n\r\n    mint pow(long long n)\
    \ const {\r\n        assert(0 <= n);\r\n        mint x = *this, r = 1;\r\n   \
    \     while (n) {\r\n            if (n & 1) r *= x;\r\n            x *= x;\r\n\
    \            n >>= 1;\r\n        }\r\n        return r;\r\n    }\r\n    mint inv()\
    \ const {\r\n        if (prime) {\r\n            assert(_v);\r\n            return\
    \ pow(umod() - 2);\r\n        } else {\r\n            auto eg = internal::inv_gcd(_v,\
    \ m);\r\n            assert(eg.first == 1);\r\n            return eg.second;\r\
    \n        }\r\n    }\r\n\r\n    friend mint operator+(const mint& lhs, const mint&\
    \ rhs) {\r\n        return mint(lhs) += rhs;\r\n    }\r\n    friend mint operator-(const\
    \ mint& lhs, const mint& rhs) {\r\n        return mint(lhs) -= rhs;\r\n    }\r\
    \n    friend mint operator*(const mint& lhs, const mint& rhs) {\r\n        return\
    \ mint(lhs) *= rhs;\r\n    }\r\n    friend mint operator/(const mint& lhs, const\
    \ mint& rhs) {\r\n        return mint(lhs) /= rhs;\r\n    }\r\n    friend bool\
    \ operator==(const mint& lhs, const mint& rhs) {\r\n        return lhs._v == rhs._v;\r\
    \n    }\r\n    friend bool operator!=(const mint& lhs, const mint& rhs) {\r\n\
    \        return lhs._v != rhs._v;\r\n    }\r\n\r\n  private:\r\n    unsigned int\
    \ _v;\r\n    static constexpr unsigned int umod() { return m; }\r\n    static\
    \ constexpr bool prime = internal::is_prime<m>;\r\n};\r\n\r\ntemplate <int id>\
    \ struct dynamic_modint : internal::modint_base {\r\n    using mint = dynamic_modint;\r\
    \n\r\n  public:\r\n    static int mod() { return (int)(bt.umod()); }\r\n    static\
    \ void set_mod(int m) {\r\n        assert(1 <= m);\r\n        bt = internal::barrett(m);\r\
    \n    }\r\n    static mint raw(int v) {\r\n        mint x;\r\n        x._v = v;\r\
    \n        return x;\r\n    }\r\n\r\n    dynamic_modint() : _v(0) {}\r\n    template\
    \ <class T, internal::is_signed_int_t<T>* = nullptr>\r\n    dynamic_modint(T v)\
    \ {\r\n        long long x = (long long)(v % (long long)(mod()));\r\n        if\
    \ (x < 0) x += mod();\r\n        _v = (unsigned int)(x);\r\n    }\r\n    template\
    \ <class T, internal::is_unsigned_int_t<T>* = nullptr>\r\n    dynamic_modint(T\
    \ v) {\r\n        _v = (unsigned int)(v % mod());\r\n    }\r\n    dynamic_modint(bool\
    \ v) { _v = ((unsigned int)(v) % mod()); }\r\n\r\n    unsigned int val() const\
    \ { return _v; }\r\n\r\n    mint& operator++() {\r\n        _v++;\r\n        if\
    \ (_v == umod()) _v = 0;\r\n        return *this;\r\n    }\r\n    mint& operator--()\
    \ {\r\n        if (_v == 0) _v = umod();\r\n        _v--;\r\n        return *this;\r\
    \n    }\r\n    mint operator++(int) {\r\n        mint result = *this;\r\n    \
    \    ++*this;\r\n        return result;\r\n    }\r\n    mint operator--(int) {\r\
    \n        mint result = *this;\r\n        --*this;\r\n        return result;\r\
    \n    }\r\n\r\n    mint& operator+=(const mint& rhs) {\r\n        _v += rhs._v;\r\
    \n        if (_v >= umod()) _v -= umod();\r\n        return *this;\r\n    }\r\n\
    \    mint& operator-=(const mint& rhs) {\r\n        _v += mod() - rhs._v;\r\n\
    \        if (_v >= umod()) _v -= umod();\r\n        return *this;\r\n    }\r\n\
    \    mint& operator*=(const mint& rhs) {\r\n        _v = bt.mul(_v, rhs._v);\r\
    \n        return *this;\r\n    }\r\n    mint& operator/=(const mint& rhs) { return\
    \ *this = *this * rhs.inv(); }\r\n\r\n    mint operator+() const { return *this;\
    \ }\r\n    mint operator-() const { return mint() - *this; }\r\n\r\n    mint pow(long\
    \ long n) const {\r\n        assert(0 <= n);\r\n        mint x = *this, r = 1;\r\
    \n        while (n) {\r\n            if (n & 1) r *= x;\r\n            x *= x;\r\
    \n            n >>= 1;\r\n        }\r\n        return r;\r\n    }\r\n    mint\
    \ inv() const {\r\n        auto eg = internal::inv_gcd(_v, mod());\r\n       \
    \ assert(eg.first == 1);\r\n        return eg.second;\r\n    }\r\n\r\n    friend\
    \ mint operator+(const mint& lhs, const mint& rhs) {\r\n        return mint(lhs)\
    \ += rhs;\r\n    }\r\n    friend mint operator-(const mint& lhs, const mint& rhs)\
    \ {\r\n        return mint(lhs) -= rhs;\r\n    }\r\n    friend mint operator*(const\
    \ mint& lhs, const mint& rhs) {\r\n        return mint(lhs) *= rhs;\r\n    }\r\
    \n    friend mint operator/(const mint& lhs, const mint& rhs) {\r\n        return\
    \ mint(lhs) /= rhs;\r\n    }\r\n    friend bool operator==(const mint& lhs, const\
    \ mint& rhs) {\r\n        return lhs._v == rhs._v;\r\n    }\r\n    friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) {\r\n        return lhs._v != rhs._v;\r\
    \n    }\r\n\r\n  private:\r\n    unsigned int _v;\r\n    static internal::barrett\
    \ bt;\r\n    static unsigned int umod() { return bt.umod(); }\r\n};\r\ntemplate\
    \ <int id> internal::barrett dynamic_modint<id>::bt = 998244353;\r\n\r\nusing\
    \ modint998244353 = static_modint<998244353>;\r\nusing modint1000000007 = static_modint<1000000007>;\r\
    \nusing modint = dynamic_modint<-1>;\r\n\r\nnamespace internal {\r\n\r\ntemplate\
    \ <class T>\r\nusing is_static_modint = std::is_base_of<internal::static_modint_base,\
    \ T>;\r\n\r\ntemplate <class T>\r\nusing is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;\r\
    \n\r\ntemplate <class> struct is_dynamic_modint : public std::false_type {};\r\
    \ntemplate <int id>\r\nstruct is_dynamic_modint<dynamic_modint<id>> : public std::true_type\
    \ {};\r\n\r\ntemplate <class T>\r\nusing is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;\r\
    \n\r\n}  // namespace internal\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_MODINT_HPP\r\n#define ATCODER_MODINT_HPP 1\r\n\r\n#include\
    \ <atcoder/internal_math>\r\n#include <atcoder/internal_type_traits>\r\n#include\
    \ <cassert>\r\n#include <numeric>\r\n#include <type_traits>\r\n\r\n#ifdef _MSC_VER\r\
    \n#include <intrin.h>\r\n#endif\r\n\r\nnamespace atcoder {\r\n\r\nnamespace internal\
    \ {\r\n\r\nstruct modint_base {};\r\nstruct static_modint_base : modint_base {};\r\
    \n\r\ntemplate <class T> using is_modint = std::is_base_of<modint_base, T>;\r\n\
    template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\r\
    \n\r\n}  // namespace internal\r\n\r\ntemplate <int m, std::enable_if_t<(1 <=\
    \ m)>* = nullptr>\r\nstruct static_modint : internal::static_modint_base {\r\n\
    \    using mint = static_modint;\r\n\r\n  public:\r\n    static constexpr int\
    \ mod() { return m; }\r\n    static mint raw(int v) {\r\n        mint x;\r\n \
    \       x._v = v;\r\n        return x;\r\n    }\r\n\r\n    static_modint() : _v(0)\
    \ {}\r\n    template <class T, internal::is_signed_int_t<T>* = nullptr>\r\n  \
    \  static_modint(T v) {\r\n        long long x = (long long)(v % (long long)(umod()));\r\
    \n        if (x < 0) x += umod();\r\n        _v = (unsigned int)(x);\r\n    }\r\
    \n    template <class T, internal::is_unsigned_int_t<T>* = nullptr>\r\n    static_modint(T\
    \ v) {\r\n        _v = (unsigned int)(v % umod());\r\n    }\r\n    static_modint(bool\
    \ v) { _v = ((unsigned int)(v) % umod()); }\r\n\r\n    unsigned int val() const\
    \ { return _v; }\r\n\r\n    mint& operator++() {\r\n        _v++;\r\n        if\
    \ (_v == umod()) _v = 0;\r\n        return *this;\r\n    }\r\n    mint& operator--()\
    \ {\r\n        if (_v == 0) _v = umod();\r\n        _v--;\r\n        return *this;\r\
    \n    }\r\n    mint operator++(int) {\r\n        mint result = *this;\r\n    \
    \    ++*this;\r\n        return result;\r\n    }\r\n    mint operator--(int) {\r\
    \n        mint result = *this;\r\n        --*this;\r\n        return result;\r\
    \n    }\r\n\r\n    mint& operator+=(const mint& rhs) {\r\n        _v += rhs._v;\r\
    \n        if (_v >= umod()) _v -= umod();\r\n        return *this;\r\n    }\r\n\
    \    mint& operator-=(const mint& rhs) {\r\n        _v -= rhs._v;\r\n        if\
    \ (_v >= umod()) _v += umod();\r\n        return *this;\r\n    }\r\n    mint&\
    \ operator*=(const mint& rhs) {\r\n        unsigned long long z = _v;\r\n    \
    \    z *= rhs._v;\r\n        _v = (unsigned int)(z % umod());\r\n        return\
    \ *this;\r\n    }\r\n    mint& operator/=(const mint& rhs) { return *this = *this\
    \ * rhs.inv(); }\r\n\r\n    mint operator+() const { return *this; }\r\n    mint\
    \ operator-() const { return mint() - *this; }\r\n\r\n    mint pow(long long n)\
    \ const {\r\n        assert(0 <= n);\r\n        mint x = *this, r = 1;\r\n   \
    \     while (n) {\r\n            if (n & 1) r *= x;\r\n            x *= x;\r\n\
    \            n >>= 1;\r\n        }\r\n        return r;\r\n    }\r\n    mint inv()\
    \ const {\r\n        if (prime) {\r\n            assert(_v);\r\n            return\
    \ pow(umod() - 2);\r\n        } else {\r\n            auto eg = internal::inv_gcd(_v,\
    \ m);\r\n            assert(eg.first == 1);\r\n            return eg.second;\r\
    \n        }\r\n    }\r\n\r\n    friend mint operator+(const mint& lhs, const mint&\
    \ rhs) {\r\n        return mint(lhs) += rhs;\r\n    }\r\n    friend mint operator-(const\
    \ mint& lhs, const mint& rhs) {\r\n        return mint(lhs) -= rhs;\r\n    }\r\
    \n    friend mint operator*(const mint& lhs, const mint& rhs) {\r\n        return\
    \ mint(lhs) *= rhs;\r\n    }\r\n    friend mint operator/(const mint& lhs, const\
    \ mint& rhs) {\r\n        return mint(lhs) /= rhs;\r\n    }\r\n    friend bool\
    \ operator==(const mint& lhs, const mint& rhs) {\r\n        return lhs._v == rhs._v;\r\
    \n    }\r\n    friend bool operator!=(const mint& lhs, const mint& rhs) {\r\n\
    \        return lhs._v != rhs._v;\r\n    }\r\n\r\n  private:\r\n    unsigned int\
    \ _v;\r\n    static constexpr unsigned int umod() { return m; }\r\n    static\
    \ constexpr bool prime = internal::is_prime<m>;\r\n};\r\n\r\ntemplate <int id>\
    \ struct dynamic_modint : internal::modint_base {\r\n    using mint = dynamic_modint;\r\
    \n\r\n  public:\r\n    static int mod() { return (int)(bt.umod()); }\r\n    static\
    \ void set_mod(int m) {\r\n        assert(1 <= m);\r\n        bt = internal::barrett(m);\r\
    \n    }\r\n    static mint raw(int v) {\r\n        mint x;\r\n        x._v = v;\r\
    \n        return x;\r\n    }\r\n\r\n    dynamic_modint() : _v(0) {}\r\n    template\
    \ <class T, internal::is_signed_int_t<T>* = nullptr>\r\n    dynamic_modint(T v)\
    \ {\r\n        long long x = (long long)(v % (long long)(mod()));\r\n        if\
    \ (x < 0) x += mod();\r\n        _v = (unsigned int)(x);\r\n    }\r\n    template\
    \ <class T, internal::is_unsigned_int_t<T>* = nullptr>\r\n    dynamic_modint(T\
    \ v) {\r\n        _v = (unsigned int)(v % mod());\r\n    }\r\n    dynamic_modint(bool\
    \ v) { _v = ((unsigned int)(v) % mod()); }\r\n\r\n    unsigned int val() const\
    \ { return _v; }\r\n\r\n    mint& operator++() {\r\n        _v++;\r\n        if\
    \ (_v == umod()) _v = 0;\r\n        return *this;\r\n    }\r\n    mint& operator--()\
    \ {\r\n        if (_v == 0) _v = umod();\r\n        _v--;\r\n        return *this;\r\
    \n    }\r\n    mint operator++(int) {\r\n        mint result = *this;\r\n    \
    \    ++*this;\r\n        return result;\r\n    }\r\n    mint operator--(int) {\r\
    \n        mint result = *this;\r\n        --*this;\r\n        return result;\r\
    \n    }\r\n\r\n    mint& operator+=(const mint& rhs) {\r\n        _v += rhs._v;\r\
    \n        if (_v >= umod()) _v -= umod();\r\n        return *this;\r\n    }\r\n\
    \    mint& operator-=(const mint& rhs) {\r\n        _v += mod() - rhs._v;\r\n\
    \        if (_v >= umod()) _v -= umod();\r\n        return *this;\r\n    }\r\n\
    \    mint& operator*=(const mint& rhs) {\r\n        _v = bt.mul(_v, rhs._v);\r\
    \n        return *this;\r\n    }\r\n    mint& operator/=(const mint& rhs) { return\
    \ *this = *this * rhs.inv(); }\r\n\r\n    mint operator+() const { return *this;\
    \ }\r\n    mint operator-() const { return mint() - *this; }\r\n\r\n    mint pow(long\
    \ long n) const {\r\n        assert(0 <= n);\r\n        mint x = *this, r = 1;\r\
    \n        while (n) {\r\n            if (n & 1) r *= x;\r\n            x *= x;\r\
    \n            n >>= 1;\r\n        }\r\n        return r;\r\n    }\r\n    mint\
    \ inv() const {\r\n        auto eg = internal::inv_gcd(_v, mod());\r\n       \
    \ assert(eg.first == 1);\r\n        return eg.second;\r\n    }\r\n\r\n    friend\
    \ mint operator+(const mint& lhs, const mint& rhs) {\r\n        return mint(lhs)\
    \ += rhs;\r\n    }\r\n    friend mint operator-(const mint& lhs, const mint& rhs)\
    \ {\r\n        return mint(lhs) -= rhs;\r\n    }\r\n    friend mint operator*(const\
    \ mint& lhs, const mint& rhs) {\r\n        return mint(lhs) *= rhs;\r\n    }\r\
    \n    friend mint operator/(const mint& lhs, const mint& rhs) {\r\n        return\
    \ mint(lhs) /= rhs;\r\n    }\r\n    friend bool operator==(const mint& lhs, const\
    \ mint& rhs) {\r\n        return lhs._v == rhs._v;\r\n    }\r\n    friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) {\r\n        return lhs._v != rhs._v;\r\
    \n    }\r\n\r\n  private:\r\n    unsigned int _v;\r\n    static internal::barrett\
    \ bt;\r\n    static unsigned int umod() { return bt.umod(); }\r\n};\r\ntemplate\
    \ <int id> internal::barrett dynamic_modint<id>::bt = 998244353;\r\n\r\nusing\
    \ modint998244353 = static_modint<998244353>;\r\nusing modint1000000007 = static_modint<1000000007>;\r\
    \nusing modint = dynamic_modint<-1>;\r\n\r\nnamespace internal {\r\n\r\ntemplate\
    \ <class T>\r\nusing is_static_modint = std::is_base_of<internal::static_modint_base,\
    \ T>;\r\n\r\ntemplate <class T>\r\nusing is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;\r\
    \n\r\ntemplate <class> struct is_dynamic_modint : public std::false_type {};\r\
    \ntemplate <int id>\r\nstruct is_dynamic_modint<dynamic_modint<id>> : public std::true_type\
    \ {};\r\n\r\ntemplate <class T>\r\nusing is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;\r\
    \n\r\n}  // namespace internal\r\n\r\n}  // namespace atcoder\r\n\r\n#endif  //\
    \ ATCODER_MODINT_HPP\r\n"
  dependsOn:
  - lib/atcoder/internal_math.hpp
  - lib/atcoder/internal_type_traits.hpp
  isVerificationFile: false
  path: lib/atcoder/modint.hpp
  requiredBy:
  - lib/atcoder/convolution.hpp
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/modint.hpp
layout: document
redirect_from:
- /library/lib/atcoder/modint.hpp
- /library/lib/atcoder/modint.hpp.html
title: lib/atcoder/modint.hpp
---
