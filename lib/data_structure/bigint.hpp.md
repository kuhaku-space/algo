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
  _extendedVerifiedWith:
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
    path: test/aoj/ntl/remainder.test.cpp
    title: test/aoj/ntl/remainder.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u591A\u500D\u9577\u6574\u6570"
    links:
    - http://yamatyuu.net/computer/program/long/div/index.html
    - https://qiita.com/square1001/items/1aa12e04934b6e749962
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: fft/ntt.hpp: line\
    \ -1: no such header\n"
  code: "#include \"fft/ntt.hpp\"\r\n#include \"template/template.hpp\"\r\n\r\n/**\r\
    \n * @brief \u591A\u500D\u9577\u6574\u6570\r\n *\r\n * @see https://qiita.com/square1001/items/1aa12e04934b6e749962\r\
    \n * @see http://yamatyuu.net/computer/program/long/div/index.html\r\n */\r\n\
    struct BigInt {\r\n    BigInt() : data(1), sign() {}\r\n    explicit BigInt(std::int64_t\
    \ x) : data(), sign() {\r\n        if (!x) {\r\n            this->data = std::vector<int>(1);\r\
    \n            return;\r\n        }\r\n        bool flag = x < 0;\r\n        if\
    \ (x < 0) x = -x;\r\n        std::vector<int> v;\r\n        while (x) {\r\n  \
    \          v.emplace_back(x % 10);\r\n            x /= 10;\r\n        }\r\n  \
    \      this->sign = flag;\r\n        this->data = v;\r\n    }\r\n    explicit\
    \ BigInt(std::string s) : data(s.size()), sign(false) {\r\n        if (s[0] ==\
    \ '-') {\r\n            this->sign = true;\r\n            this->data.pop_back();\r\
    \n        }\r\n        std::reverse(s.begin(), s.end());\r\n        for (int i\
    \ = 0; i < (int)s.size() - int(this->sign); ++i) {\r\n            this->data[i]\
    \ = s[i] - '0';\r\n        }\r\n    }\r\n    explicit BigInt(const std::vector<int>\
    \ &v) : data(v) { this->format(); }\r\n    explicit BigInt(const std::vector<int>\
    \ &v, bool flag) : data(v), sign(flag) { this->format(); }\r\n\r\n    BigInt &operator+=(const\
    \ BigInt &rhs) {\r\n        if (this->sign == rhs.sign) add(this->data, rhs.data);\r\
    \n        else sub(this->data, rhs.data);\r\n        this->format();\r\n     \
    \   return *this;\r\n    }\r\n    BigInt &operator-=(const BigInt &rhs) {\r\n\
    \        if (sign == rhs.sign) sub(this->data, rhs.data);\r\n        else add(this->data,\
    \ rhs.data);\r\n        this->format();\r\n        return *this;\r\n    }\r\n\
    \    BigInt &operator*=(const BigInt &rhs) {\r\n        this->mul(this->data,\
    \ rhs.data);\r\n        this->sign ^= rhs.sign;\r\n        this->format();\r\n\
    \        return *this;\r\n    }\r\n    BigInt &operator*=(int rhs) {\r\n     \
    \   this->mul(this->data, rhs);\r\n        return *this;\r\n    }\r\n    BigInt\
    \ &operator/=(const BigInt &rhs) {\r\n        assert(!rhs.is_zero());\r\n    \
    \    if (this->abs_less(rhs)) return (*this = BigInt());\r\n        if (this->size()\
    \ < 9) return (*this = BigInt(this->to_int() / rhs.to_int()));\r\n        if (rhs.size()\
    \ < 8) return (*this /= rhs.to_int());\r\n        std::vector<int> v = rhs.data;\r\
    \n        int k = 10 / (1 + v.back());\r\n        *this *= k;\r\n        this->mul(v,\
    \ k);\r\n        int d = this->size() - v.size();\r\n        std::vector<int>\
    \ u(this->data.end() - v.size() + 1, this->data.end());\r\n        std::vector<int>\
    \ ans(d + 1);\r\n        for (int i = d; i >= 0; --i) {\r\n            u.insert(u.begin(),\
    \ this->data[i]);\r\n            if (u.size() > v.size()) {\r\n              \
    \  int x = 0, y = 0;\r\n                for (int j = 0; j < 3; ++j) x = x * 10\
    \ + u[(int)u.size() - 1 - j];\r\n                for (int j = 0; j < 2; ++j) y\
    \ = y * 10 + v[(int)v.size() - 1 - j];\r\n                int z = x / y - 1;\r\
    \n                auto cp = v;\r\n                this->mul(cp, z);\r\n      \
    \          this->sub(u, cp);\r\n                ans[i] = z;\r\n            }\r\
    \n            if (!this->less(u, v)) {\r\n                this->sub(u, v);\r\n\
    \                ++ans[i];\r\n            }\r\n        }\r\n\r\n        return\
    \ (*this = BigInt(ans, this->sign != rhs.sign));\r\n    }\r\n    BigInt &operator/=(int\
    \ rhs) {\r\n        bool flag = rhs < 0;\r\n        if (rhs < 0) rhs = -rhs;\r\
    \n        int x = 0;\r\n        std::vector<int> ans(this->size());\r\n      \
    \  for (int i = this->size() - 1; i >= 0; --i) {\r\n            x = x * 10 + this->data[i];\r\
    \n            ans[i] = x / rhs;\r\n            x -= ans[i] * rhs;\r\n        }\r\
    \n        return (*this = BigInt(ans, this->sign != flag));\r\n    }\r\n    BigInt\
    \ &operator%=(const BigInt &rhs) {\r\n        assert(!rhs.is_zero());\r\n    \
    \    if (this->abs_less(rhs)) return *this;\r\n        if (this->size() < 9) return\
    \ (*this = BigInt(this->to_int() % rhs.to_int()));\r\n        if (rhs.size() <\
    \ 8) return (*this %= rhs.to_int());\r\n        std::vector<int> v = rhs.data;\r\
    \n        int k = 10 / (1 + v.back());\r\n        *this *= k;\r\n        this->mul(v,\
    \ k);\r\n        int d = this->size() - v.size();\r\n        std::vector<int>\
    \ u(this->data.end() - v.size() + 1, this->data.end());\r\n        for (int i\
    \ = d; i >= 0; --i) {\r\n            u.insert(u.begin(), this->data[i]);\r\n \
    \           if (u.size() > v.size()) {\r\n                int x = 0, y = 0;\r\n\
    \                for (int j = 0; j < 3; ++j) x = x * 10 + u[(int)u.size() - 1\
    \ - j];\r\n                for (int j = 0; j < 2; ++j) y = y * 10 + v[(int)v.size()\
    \ - 1 - j];\r\n                int z = x / y - 1;\r\n                auto cp =\
    \ v;\r\n                this->mul(cp, z);\r\n                this->sub(u, cp);\r\
    \n            }\r\n            if (!this->less(u, v)) this->sub(u, v);\r\n   \
    \     }\r\n\r\n        this->div(u, k);\r\n        return (*this = BigInt(u, this->sign\
    \ != rhs.sign));\r\n    }\r\n    BigInt &operator%=(int rhs) {\r\n        bool\
    \ flag = rhs < 0;\r\n        if (rhs < 0) rhs = -rhs;\r\n        int x = 0;\r\n\
    \        for (int i = this->size() - 1; i >= 0; --i) {\r\n            x = x *\
    \ 10 + this->data[i];\r\n            int k = x / rhs;\r\n            x -= k *\
    \ rhs;\r\n        }\r\n        return (*this = (this->sign != flag ? BigInt(-x)\
    \ : BigInt(x)));\r\n    }\r\n\r\n    BigInt &operator>>=(int rhs) {\r\n      \
    \  this->data.erase(this->data.begin(), this->data.begin() + rhs);\r\n       \
    \ return *this;\r\n    }\r\n    BigInt &operator<<=(int rhs) {\r\n        this->data.insert(this->data.begin(),\
    \ rhs, 0);\r\n        return *this;\r\n    }\r\n\r\n    BigInt operator-() const\
    \ {\r\n        BigInt res = *this;\r\n        if (!res.is_zero()) res.sign = !res.sign;\r\
    \n        return res;\r\n    }\r\n    BigInt operator+(const BigInt &rhs) const\
    \ { return BigInt(*this) += rhs; }\r\n    BigInt operator-(const BigInt &rhs)\
    \ const { return BigInt(*this) -= rhs; }\r\n    BigInt operator*(const BigInt\
    \ &rhs) const { return BigInt(*this) *= rhs; }\r\n    BigInt operator*(int rhs)\
    \ const { return BigInt(*this) *= rhs; }\r\n    BigInt operator/(const BigInt\
    \ &rhs) const { return BigInt(*this) /= rhs; }\r\n    BigInt operator%(const BigInt\
    \ &rhs) const { return BigInt(*this) %= rhs; }\r\n\r\n    bool operator==(const\
    \ BigInt &rhs) const {\r\n        if (this->sign != rhs.sign) return false;\r\n\
    \        if (this->size() != rhs.size()) return false;\r\n        for (int i =\
    \ 0; i < this->size(); ++i) {\r\n            if (this->data[i] != rhs.data[i])\
    \ return false;\r\n        }\r\n        return true;\r\n    }\r\n\r\n    bool\
    \ operator<(const BigInt &rhs) const {\r\n        if (sign != rhs.sign) return\
    \ sign;\r\n        return this->abs_less(rhs);\r\n    }\r\n    bool operator>(const\
    \ BigInt &rhs) const { return rhs < *this; }\r\n    bool operator<=(const BigInt\
    \ &rhs) const { return !(*this > rhs); }\r\n    bool operator>=(const BigInt &rhs)\
    \ const { return !(*this < rhs); }\r\n\r\n    friend std::istream &operator>>(std::istream\
    \ &is, BigInt &rhs) {\r\n        std::string s;\r\n        is >> s;\r\n      \
    \  rhs = BigInt(s);\r\n        return is;\r\n    }\r\n\r\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const BigInt &rhs) {\r\n        std::string s;\r\
    \n        for (auto i : rhs.data) s.push_back(char(i + '0'));\r\n        if (rhs.sign)\
    \ s.push_back('-');\r\n        std::reverse(s.begin(), s.end());\r\n        os\
    \ << s;\r\n        return os;\r\n    }\r\n\r\n    inline int size() const { return\
    \ this->data.size(); }\r\n    inline bool is_zero() const { return this->data.size()\
    \ == 1 && this->data[0] == 0; }\r\n\r\n    int back() const {\r\n        assert(this->size()\
    \ > 0);\r\n        return this->data.back();\r\n    }\r\n\r\n    BigInt abs()\
    \ const {\r\n        if (!this->sign) return *this;\r\n        return -(*this);\r\
    \n    }\r\n    bool abs_less(const BigInt &rhs) const { return less(this->data,\
    \ rhs.data); }\r\n\r\n  private:\r\n    std::vector<int> data;\r\n    bool sign;\r\
    \n\r\n    static bool less(const std::vector<int> &a, const std::vector<int> &b)\
    \ {\r\n        if (a.size() != b.size()) return a.size() < b.size();\r\n     \
    \   for (int i = (int)a.size() - 1; i >= 0; --i) {\r\n            if (a[i] !=\
    \ b[i]) return a[i] < b[i];\r\n        }\r\n        return false;\r\n    }\r\n\
    \r\n    static void add(std::vector<int> &a, const std::vector<int> &b) {\r\n\
    \        int n = std::max(a.size(), b.size());\r\n        a.resize(n);\r\n   \
    \     for (int i = 0; i < (int)b.size(); ++i) a[i] += b[i];\r\n        format(a);\r\
    \n    }\r\n    static void sub(std::vector<int> &a, const std::vector<int> &b)\
    \ {\r\n        int n = std::max(a.size(), b.size());\r\n        a.resize(n);\r\
    \n        for (int i = 0; i < (int)b.size(); ++i) a[i] -= b[i];\r\n        format(a);\r\
    \n    }\r\n    static void mul(std::vector<int> &a, const std::vector<int> &b)\
    \ {\r\n        a = convolution(a, b);\r\n        format(a);\r\n    }\r\n    static\
    \ void mul(std::vector<int> &data, int k) {\r\n        std::for_each(data.begin(),\
    \ data.end(), [k](auto &x) {\r\n            x *= k;\r\n        });\r\n       \
    \ format(data);\r\n    }\r\n    static void div(std::vector<int> &data, int k)\
    \ {\r\n        int x = 0;\r\n        for (int i = (int)data.size() - 1; i >= 0;\
    \ --i) {\r\n            int r = (10 * x + data[i]) % k;\r\n            data[i]\
    \ = (10 * x + data[i]) / k;\r\n            x = r;\r\n        }\r\n        format(data);\r\
    \n    }\r\n\r\n    static void format(std::vector<int> &data) {\r\n        for\
    \ (int i = 0;; ++i) {\r\n            if ((int)data.size() == i + 1) {\r\n    \
    \            if (std::abs(data[i]) <= 9) break;\r\n                else data.emplace_back(0);\r\
    \n            }\r\n            data[i + 1] += data[i] / 10;\r\n            data[i]\
    \ %= 10;\r\n            if (data[i] < 0) --data[i + 1], data[i] += 10;\r\n   \
    \     }\r\n        while ((int)data.size() > 1 && data.back() == 0) data.pop_back();\r\
    \n    }\r\n\r\n    void format() {\r\n        this->format(this->data);\r\n  \
    \      if (this->back() < 0) {\r\n            this->inverse();\r\n           \
    \ this->format();\r\n        }\r\n        if (this->is_zero()) this->sign = false;\r\
    \n    }\r\n\r\n    void inverse() {\r\n        this->sign = !this->sign;\r\n \
    \       std::for_each(this->data.begin(), this->data.end(), [](auto &x) {\r\n\
    \            x = -x;\r\n        });\r\n    }\r\n\r\n    int to_int() const { return\
    \ this->sign ? -this->to_uint() : this->to_uint(); }\r\n    unsigned int to_uint()\
    \ const {\r\n        int res = 0;\r\n        for (int i = this->size() - 1; i\
    \ >= 0; --i) res = res * 10 + this->data[i];\r\n        return res;\r\n    }\r\
    \n};\r\n"
  dependsOn:
  - lib/fft/ntt.hpp
  - lib/internal/internal_fft.hpp
  - lib/internal/internal_bit.hpp
  - lib/template/template.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  isVerificationFile: false
  path: lib/data_structure/bigint.hpp
  requiredBy: []
  timestamp: '2023-07-12 23:02:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/ntl/addition.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/ntl/division.test.cpp
documentation_of: lib/data_structure/bigint.hpp
layout: document
redirect_from:
- /library/lib/data_structure/bigint.hpp
- /library/lib/data_structure/bigint.hpp.html
title: "\u591A\u500D\u9577\u6574\u6570"
---
