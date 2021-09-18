---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/algo/modint.hpp
    title: lib/algo/modint.hpp
  - icon: ':warning:'
    path: lib/fft/ntt.hpp
    title: lib/fft/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_A
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_B
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_F
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"fft/ntt.hpp\"\r\n\r\n/*\r\
    \n * verify:\r\n * https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_A 21/03/02\r\
    \n * https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_B 21/03/02\r\n * https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_F\
    \ 21/03/02\r\n */\r\n\r\nstruct BigInt {\r\n    vector<int> data;\r\n\r\n    BigInt()\
    \ {}\r\n    BigInt(string s) : data(s.size()) {\r\n        bool flg = s[0] ==\
    \ '-';\r\n        reverse(s.begin(), s.end());\r\n        if (flg) s.pop_back(),\
    \ data.pop_back();\r\n        for (int i = 0; i < s.size(); ++i) {\r\n       \
    \     if (flg)\r\n                data[i] = -(s[i] - '0');\r\n            else\r\
    \n                data[i] = s[i] - '0';\r\n        }\r\n    }\r\n\r\n    BigInt\
    \ &operator+=(const BigInt &rhs) {\r\n        int n = max(size(), rhs.size());\r\
    \n        data.resize(n, 0);\r\n        for (int i = 0; i < rhs.size(); ++i) data[i]\
    \ += rhs.data[i];\r\n        format();\r\n        return *this;\r\n    }\r\n \
    \   BigInt &operator-=(const BigInt &rhs) {\r\n        int n = max(size(), rhs.size());\r\
    \n        data.resize(n, 0);\r\n        for (int i = 0; i < rhs.size(); ++i) data[i]\
    \ -= rhs.data[i];\r\n        format();\r\n        return *this;\r\n    }\r\n \
    \   BigInt &operator*=(const BigInt &rhs) {\r\n        const int mod = 469762049;\r\
    \n        NTT<469762049, 3> ntt;  // 2^26 * 7 + 1\r\n        ntt.convolution_self(data,\
    \ rhs.data);\r\n        for (int i = 0; i < size(); ++i) {\r\n            if (data[i]\
    \ >= mod / 2) data[i] -= mod;\r\n        }\r\n        format();\r\n        return\
    \ *this;\r\n    }\r\n\r\n    BigInt operator-() const {\r\n        BigInt res(*this);\r\
    \n        for (int i = 0; i < res.size(); ++i) res.data[i] = -res.data[i];\r\n\
    \        return res;\r\n    }\r\n    BigInt operator+(const BigInt &rhs) const\
    \ { return BigInt(*this) += rhs; }\r\n    BigInt operator-(const BigInt &rhs)\
    \ const { return BigInt(*this) -= rhs; }\r\n    BigInt operator*(const BigInt\
    \ &rhs) const { return BigInt(*this) *= rhs; }\r\n\r\n    bool operator<(const\
    \ BigInt &rhs) const {\r\n        if (is_negative() ^ rhs.is_negative()) return\
    \ back() < rhs.back();\r\n        if (size() ^ rhs.size()) return size() < rhs.size();\r\
    \n        for (int i = size() - 1; i >= 0; --i) {\r\n            if (data[i] ^\
    \ rhs.data[i]) return data[i] < rhs.data[i];\r\n        }\r\n        return false;\r\
    \n    }\r\n\r\n    friend ostream &operator<<(ostream &os, const BigInt &rhs)\
    \ {\r\n        string s;\r\n        bool flg = rhs.is_negative();\r\n        for\
    \ (auto i : rhs.data) {\r\n            if (flg)\r\n                s.push_back(char('0'\
    \ - i));\r\n            else\r\n                s.push_back(char('0' + i));\r\n\
    \        }\r\n        if (rhs.is_negative()) s.push_back('-');\r\n        reverse(s.begin(),\
    \ s.end());\r\n        os << s;\r\n        return os;\r\n    }\r\n\r\n    friend\
    \ istream &operator>>(istream &is, BigInt &rhs) {\r\n        string s;\r\n   \
    \     is >> s;\r\n        rhs = BigInt(s);\r\n        return is;\r\n    }\r\n\r\
    \n    inline int size() const { return data.size(); }\r\n\r\n    int back() const\
    \ {\r\n        assert(data.size() > 0);\r\n        return data.back();\r\n   \
    \ }\r\n\r\n    bool is_negative() const { return back() < 0; }\r\n\r\n    inline\
    \ bool is_zero() const { return data.size() == 1 && data[0] == 0; }\r\n\r\n  \
    \  void format() {\r\n        while (size() > 1 && back() == 0) data.pop_back();\r\
    \n        bool flg = is_negative();\r\n        data.emplace_back(0);\r\n     \
    \   for (int i = 0; i < size() - 1; ++i) {\r\n            data[i + 1] += data[i]\
    \ / 10;\r\n            data[i] %= 10;\r\n            if (flg && data[i] > 0) ++data[i\
    \ + 1], data[i] -= 10;\r\n            if (!flg && data[i] < 0) --data[i + 1],\
    \ data[i] += 10;\r\n        }\r\n        while (size() > 1 && back() == 0) data.pop_back();\r\
    \n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/fft/ntt.hpp
  - lib/algo/modint.hpp
  isVerificationFile: false
  path: lib/data_struct/bigint_beta.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_struct/bigint_beta.hpp
layout: document
redirect_from:
- /library/lib/data_struct/bigint_beta.hpp
- /library/lib/data_struct/bigint_beta.hpp.html
title: lib/data_struct/bigint_beta.hpp
---
