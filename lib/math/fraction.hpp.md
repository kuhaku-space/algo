---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u5206\u6570\u30E9\u30A4\u30D6\u30E9\u30EA"
    links: []
  bundledCode: "#line 1 \"lib/math/fraction.hpp\"\n#include <cstdint>\r\n#include\
    \ <iostream>\r\n#include <utility>\r\n\r\n/**\r\n * @brief \u5206\u6570\u30E9\u30A4\
    \u30D6\u30E9\u30EA\r\n *\r\n */\r\nstruct Fraction {\r\n    std::int64_t x, y;\r\
    \n\r\n    Fraction() : x(0), y(1) {}\r\n\r\n    Fraction(std::int64_t _x, std::int64_t\
    \ _y = 1) : x(_x), y(_y) { common(); }\r\n\r\n    std::int64_t gcd(std::int64_t\
    \ a, std::int64_t b) const {\r\n        while (b) {\r\n            a %= b;\r\n\
    \            std::swap(a, b);\r\n        }\r\n        return a;\r\n    }\r\n\r\
    \n    Fraction &operator+=(const Fraction &rhs) {\r\n        x = x * rhs.y + y\
    \ * rhs.x;\r\n        y *= rhs.y;\r\n        common();\r\n        return *this;\r\
    \n    }\r\n    Fraction &operator-=(const Fraction &rhs) {\r\n        x = x *\
    \ rhs.y - y * rhs.x;\r\n        y *= rhs.y;\r\n        common();\r\n        return\
    \ *this;\r\n    }\r\n    Fraction &operator*=(const Fraction &rhs) {\r\n     \
    \   x *= rhs.x, y *= rhs.y;\r\n        common();\r\n        return *this;\r\n\
    \    }\r\n    Fraction &operator/=(const Fraction &rhs) {\r\n        x *= rhs.y,\
    \ y *= rhs.x;\r\n        common();\r\n        return *this;\r\n    }\r\n\r\n \
    \   Fraction &operator++() {\r\n        x += y;\r\n        return *this;\r\n \
    \   }\r\n    Fraction operator++(int) {\r\n        Fraction tmp(*this);\r\n  \
    \      operator++();\r\n        return tmp;\r\n    }\r\n    Fraction &operator--()\
    \ {\r\n        x -= y;\r\n        return *this;\r\n    }\r\n    Fraction operator--(int)\
    \ {\r\n        Fraction tmp(*this);\r\n        operator--();\r\n        return\
    \ tmp;\r\n    }\r\n\r\n    Fraction operator-() const { return Fraction(-x, y);\
    \ }\r\n\r\n    Fraction operator+(const Fraction &rhs) const { return Fraction(*this)\
    \ += rhs; }\r\n    Fraction operator-(const Fraction &rhs) const { return Fraction(*this)\
    \ -= rhs; }\r\n    Fraction operator*(const Fraction &rhs) const { return Fraction(*this)\
    \ *= rhs; }\r\n    Fraction operator/(const Fraction &rhs) const { return Fraction(*this)\
    \ /= rhs; }\r\n\r\n    bool operator==(const Fraction &rhs) const { return x ==\
    \ rhs.x && y == rhs.y; }\r\n    bool operator!=(const Fraction &rhs) const { return\
    \ x != rhs.x || y != rhs.y; }\r\n    bool operator<(const Fraction &rhs) const\
    \ { return x * rhs.y < rhs.x * y; }\r\n    bool operator>(const Fraction &rhs)\
    \ const { return x * rhs.y > rhs.x * y; }\r\n\r\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const Fraction &rhs) {\r\n        return os << rhs.to_double();\r\n   \
    \ }\r\n\r\n    friend std::istream &operator>>(std::istream &is, Fraction &a)\
    \ {\r\n        std::string s;\r\n        is >> s;\r\n        bool f = false;\r\
    \n        std::int64_t x = 0, y = 1;\r\n        for (auto c : s) {\r\n       \
    \     if (c == '.') {\r\n                f = true;\r\n                continue;\r\
    \n            }\r\n\r\n            x *= 10, x += c - '0';\r\n            if (f)\
    \ y *= 10;\r\n        }\r\n        a = Fraction(x, y);\r\n        return is;\r\
    \n    }\r\n\r\n    double to_double() const { return (double)x / y; }\r\n\r\n\
    \  private:\r\n    void common() {\r\n        std::int64_t g = gcd(x, y);\r\n\
    \        if (g) x /= g, y /= g;\r\n        if (y < 0) x *= -1, y *= -1;\r\n  \
    \  }\r\n};\r\n"
  code: "#include <cstdint>\r\n#include <iostream>\r\n#include <utility>\r\n\r\n/**\r\
    \n * @brief \u5206\u6570\u30E9\u30A4\u30D6\u30E9\u30EA\r\n *\r\n */\r\nstruct\
    \ Fraction {\r\n    std::int64_t x, y;\r\n\r\n    Fraction() : x(0), y(1) {}\r\
    \n\r\n    Fraction(std::int64_t _x, std::int64_t _y = 1) : x(_x), y(_y) { common();\
    \ }\r\n\r\n    std::int64_t gcd(std::int64_t a, std::int64_t b) const {\r\n  \
    \      while (b) {\r\n            a %= b;\r\n            std::swap(a, b);\r\n\
    \        }\r\n        return a;\r\n    }\r\n\r\n    Fraction &operator+=(const\
    \ Fraction &rhs) {\r\n        x = x * rhs.y + y * rhs.x;\r\n        y *= rhs.y;\r\
    \n        common();\r\n        return *this;\r\n    }\r\n    Fraction &operator-=(const\
    \ Fraction &rhs) {\r\n        x = x * rhs.y - y * rhs.x;\r\n        y *= rhs.y;\r\
    \n        common();\r\n        return *this;\r\n    }\r\n    Fraction &operator*=(const\
    \ Fraction &rhs) {\r\n        x *= rhs.x, y *= rhs.y;\r\n        common();\r\n\
    \        return *this;\r\n    }\r\n    Fraction &operator/=(const Fraction &rhs)\
    \ {\r\n        x *= rhs.y, y *= rhs.x;\r\n        common();\r\n        return\
    \ *this;\r\n    }\r\n\r\n    Fraction &operator++() {\r\n        x += y;\r\n \
    \       return *this;\r\n    }\r\n    Fraction operator++(int) {\r\n        Fraction\
    \ tmp(*this);\r\n        operator++();\r\n        return tmp;\r\n    }\r\n   \
    \ Fraction &operator--() {\r\n        x -= y;\r\n        return *this;\r\n   \
    \ }\r\n    Fraction operator--(int) {\r\n        Fraction tmp(*this);\r\n    \
    \    operator--();\r\n        return tmp;\r\n    }\r\n\r\n    Fraction operator-()\
    \ const { return Fraction(-x, y); }\r\n\r\n    Fraction operator+(const Fraction\
    \ &rhs) const { return Fraction(*this) += rhs; }\r\n    Fraction operator-(const\
    \ Fraction &rhs) const { return Fraction(*this) -= rhs; }\r\n    Fraction operator*(const\
    \ Fraction &rhs) const { return Fraction(*this) *= rhs; }\r\n    Fraction operator/(const\
    \ Fraction &rhs) const { return Fraction(*this) /= rhs; }\r\n\r\n    bool operator==(const\
    \ Fraction &rhs) const { return x == rhs.x && y == rhs.y; }\r\n    bool operator!=(const\
    \ Fraction &rhs) const { return x != rhs.x || y != rhs.y; }\r\n    bool operator<(const\
    \ Fraction &rhs) const { return x * rhs.y < rhs.x * y; }\r\n    bool operator>(const\
    \ Fraction &rhs) const { return x * rhs.y > rhs.x * y; }\r\n\r\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const Fraction &rhs) {\r\n        return os <<\
    \ rhs.to_double();\r\n    }\r\n\r\n    friend std::istream &operator>>(std::istream\
    \ &is, Fraction &a) {\r\n        std::string s;\r\n        is >> s;\r\n      \
    \  bool f = false;\r\n        std::int64_t x = 0, y = 1;\r\n        for (auto\
    \ c : s) {\r\n            if (c == '.') {\r\n                f = true;\r\n   \
    \             continue;\r\n            }\r\n\r\n            x *= 10, x += c -\
    \ '0';\r\n            if (f) y *= 10;\r\n        }\r\n        a = Fraction(x,\
    \ y);\r\n        return is;\r\n    }\r\n\r\n    double to_double() const { return\
    \ (double)x / y; }\r\n\r\n  private:\r\n    void common() {\r\n        std::int64_t\
    \ g = gcd(x, y);\r\n        if (g) x /= g, y /= g;\r\n        if (y < 0) x *=\
    \ -1, y *= -1;\r\n    }\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/math/fraction.hpp
  requiredBy: []
  timestamp: '2024-04-17 14:43:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/fraction.hpp
layout: document
redirect_from:
- /library/lib/math/fraction.hpp
- /library/lib/math/fraction.hpp.html
title: "\u5206\u6570\u30E9\u30A4\u30D6\u30E9\u30EA"
---
