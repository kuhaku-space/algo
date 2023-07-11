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
    document_title: "\u5206\u6570\u30E9\u30A4\u30D6\u30E9\u30EA"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u5206\u6570\u30E9\
    \u30A4\u30D6\u30E9\u30EA\r\n *\r\n */\r\nstruct Fraction {\r\n    std::int64_t\
    \ x, y;\r\n\r\n    Fraction() : x(0), y(1) {}\r\n\r\n    Fraction(std::int64_t\
    \ _x, std::int64_t _y = 1) : x(_x), y(_y) { this->common(); }\r\n\r\n    std::int64_t\
    \ gcd(std::int64_t a, std::int64_t b) const {\r\n        while (b) {\r\n     \
    \       a %= b;\r\n            std::swap(a, b);\r\n        }\r\n        return\
    \ a;\r\n    }\r\n\r\n    Fraction &operator+=(const Fraction &rhs) {\r\n     \
    \   x = x * rhs.y + y * rhs.x;\r\n        y *= rhs.y;\r\n        this->common();\r\
    \n        return *this;\r\n    }\r\n    Fraction &operator-=(const Fraction &rhs)\
    \ {\r\n        x = x * rhs.y - y * rhs.x;\r\n        y *= rhs.y;\r\n        this->common();\r\
    \n        return *this;\r\n    }\r\n    Fraction &operator*=(const Fraction &rhs)\
    \ {\r\n        x *= rhs.x, y *= rhs.y;\r\n        this->common();\r\n        return\
    \ *this;\r\n    }\r\n    Fraction &operator/=(const Fraction &rhs) {\r\n     \
    \   x *= rhs.y, y *= rhs.x;\r\n        this->common();\r\n        return *this;\r\
    \n    }\r\n\r\n    Fraction &operator++() {\r\n        this->x += this->y;\r\n\
    \        return *this;\r\n    }\r\n    Fraction operator++(int) {\r\n        Fraction\
    \ tmp(*this);\r\n        this->operator++();\r\n        return tmp;\r\n    }\r\
    \n    Fraction &operator--() {\r\n        this->x -= this->y;\r\n        return\
    \ *this;\r\n    }\r\n    Fraction operator--(int) {\r\n        Fraction tmp(*this);\r\
    \n        this->operator--();\r\n        return tmp;\r\n    }\r\n\r\n    Fraction\
    \ operator-() const { return Fraction(-x, y); }\r\n\r\n    Fraction operator+(const\
    \ Fraction &rhs) const { return Fraction(*this) += rhs; }\r\n    Fraction operator-(const\
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
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/fraction.hpp
  requiredBy: []
  timestamp: '2023-05-22 20:02:34+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/fraction.hpp
layout: document
redirect_from:
- /library/lib/math/fraction.hpp
- /library/lib/math/fraction.hpp.html
title: "\u5206\u6570\u30E9\u30A4\u30D6\u30E9\u30EA"
---
