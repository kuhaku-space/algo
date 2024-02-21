---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/rolling_hash.test.cpp
    title: test/aoj/alds1/rolling_hash.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5"
    links:
    - https://qiita.com/keymoon/items/11fac5627672a6d6a9f6)
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include <random>\r\n\r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n\
    \ * @brief \u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5\r\n * @details\
    \ [\u53C2\u8003](https://qiita.com/keymoon/items/11fac5627672a6d6a9f6)\r\n */\r\
    \nstruct rolling_hash {\r\n    rolling_hash(const std::string &_s) : len(_s.size()\
    \ + 1), base(), data(1), p(1, 1) {\r\n        std::mt19937 rnd((std::random_device::result_type)std::random_device()());\r\
    \n        this->base = rnd() + 2;\r\n        std::uint64_t x = 0, t = 1;\r\n \
    \       for (const auto c : _s) {\r\n            x = this->_mod(this->_mul(x,\
    \ this->base) + c);\r\n            this->data.emplace_back(x);\r\n           \
    \ t = this->_mod(this->_mul(t, this->base));\r\n            this->p.emplace_back(t);\r\
    \n        }\r\n    }\r\n\r\n    /**\r\n     * @brief get hash of s[l...r]\r\n\
    \     *\r\n     * @param l first index\r\n     * @param r last index\r\n     *\
    \ @return std::uint64_t\r\n     */\r\n    std::uint64_t get(int l, int r) const\
    \ {\r\n        return this->_mod(this->data[r] + this->mod * 4 -\r\n         \
    \                 this->_mul(this->data[l], this->p[r - l]));\r\n    }\r\n\r\n\
    \    /**\r\n     * @brief search string\r\n     *\r\n     * @param s\r\n     *\
    \ @return std::vector<int>\r\n     */\r\n    std::vector<int> search(const std::string\
    \ &s) {\r\n        std::vector<int> res;\r\n        int n = s.size();\r\n    \
    \    if (n >= this->len) return res;\r\n        std::uint64_t x = 0;\r\n     \
    \   for (const auto c : s) x = this->_mod(this->_mul(x, this->base) + c);\r\n\
    \        for (int i = 0; i < this->len - n; ++i) {\r\n            if (this->get(i,\
    \ i + n) == x) res.emplace_back(i);\r\n        }\r\n        return res;\r\n  \
    \  }\r\n\r\n  private:\r\n    static constexpr std::uint64_t mod = (1ul << 61)\
    \ - 1;\r\n    static constexpr std::uint64_t mask30 = (1ul << 30) - 1;\r\n   \
    \ static constexpr std::uint64_t mask31 = (1ul << 31) - 1;\r\n    int len;\r\n\
    \    std::uint64_t base;\r\n    std::vector<std::uint64_t> data, p;\r\n\r\n  \
    \  constexpr std::uint64_t _mul(std::uint64_t a, std::uint64_t b) const {\r\n\
    \        std::uint64_t au = a >> 31, ad = a & this->mask31;\r\n        std::uint64_t\
    \ bu = b >> 31, bd = b & this->mask31;\r\n        std::uint64_t mid = ad * bu\
    \ + au * bd;\r\n        std::uint64_t midu = mid >> 30, midd = mid & this->mask30;\r\
    \n        return au * bu * 2 + midu + (midd << 31) + ad * bd;\r\n    }\r\n   \
    \ constexpr std::uint64_t _mod(std::uint64_t x) const {\r\n        std::uint64_t\
    \ xu = x >> 61, xd = x & this->mod;\r\n        std::uint64_t res = xu + xd;\r\n\
    \        if (res >= this->mod) res -= this->mod;\r\n        return res;\r\n  \
    \  }\r\n    constexpr std::uint64_t _pow(std::uint64_t x, std::uint64_t k) const\
    \ {\r\n        std::uint64_t res = 1;\r\n        for (; k; k >>= 1) {\r\n    \
    \        if (k & 1) res = this->_mod(this->_mul(res, x));\r\n            x = this->_mod(this->_mul(x,\
    \ x));\r\n        }\r\n        return res;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/rolling_hash.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/alds1/rolling_hash.test.cpp
documentation_of: lib/string/rolling_hash.hpp
layout: document
redirect_from:
- /library/lib/string/rolling_hash.hpp
- /library/lib/string/rolling_hash.hpp.html
title: "\u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5"
---
