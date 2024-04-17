---
data:
  _extendedDependsOn: []
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
    - https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
  bundledCode: "#line 1 \"lib/string/rolling_hash.hpp\"\n#include <cstdint>\r\n#include\
    \ <random>\r\n#include <string>\r\n#include <vector>\r\n\r\n/**\r\n * @brief \u30ED\
    \u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5\r\n * @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\r\
    \n */\r\nstruct rolling_hash {\r\n    rolling_hash(const std::string &_s) : len(_s.size()\
    \ + 1), base(), data(1), p(1, 1) {\r\n        std::mt19937 rnd((std::random_device::result_type)std::random_device()());\r\
    \n        base = rnd() + 2;\r\n        std::uint64_t x = 0, t = 1;\r\n       \
    \ for (const auto c : _s) {\r\n            x = _mod(_mul(x, base) + c);\r\n  \
    \          data.emplace_back(x);\r\n            t = _mod(_mul(t, base));\r\n \
    \           p.emplace_back(t);\r\n        }\r\n    }\r\n\r\n    /**\r\n     *\
    \ @brief get hash of s[l...r]\r\n     *\r\n     * @param l first index\r\n   \
    \  * @param r last index\r\n     * @return std::uint64_t\r\n     */\r\n    std::uint64_t\
    \ get(int l, int r) const {\r\n        return _mod(data[r] + mod * 4 - _mul(data[l],\
    \ p[r - l]));\r\n    }\r\n\r\n    /**\r\n     * @brief search string\r\n     *\r\
    \n     * @param s\r\n     * @return std::vector<int>\r\n     */\r\n    std::vector<int>\
    \ search(const std::string &s) {\r\n        std::vector<int> res;\r\n        int\
    \ n = s.size();\r\n        if (n >= len) return res;\r\n        std::uint64_t\
    \ x = 0;\r\n        for (char c : s) x = _mod(_mul(x, base) + c);\r\n        for\
    \ (int i = 0; i < len - n; ++i) {\r\n            if (get(i, i + n) == x) res.emplace_back(i);\r\
    \n        }\r\n        return res;\r\n    }\r\n\r\n  private:\r\n    static constexpr\
    \ std::uint64_t mod = (1ul << 61) - 1;\r\n    static constexpr std::uint64_t mask30\
    \ = (1ul << 30) - 1;\r\n    static constexpr std::uint64_t mask31 = (1ul << 31)\
    \ - 1;\r\n    int len;\r\n    std::uint64_t base;\r\n    std::vector<std::uint64_t>\
    \ data, p;\r\n\r\n    constexpr std::uint64_t _mul(std::uint64_t a, std::uint64_t\
    \ b) const {\r\n        std::uint64_t au = a >> 31, ad = a & mask31;\r\n     \
    \   std::uint64_t bu = b >> 31, bd = b & mask31;\r\n        std::uint64_t mid\
    \ = ad * bu + au * bd;\r\n        std::uint64_t midu = mid >> 30, midd = mid &\
    \ mask30;\r\n        return au * bu * 2 + midu + (midd << 31) + ad * bd;\r\n \
    \   }\r\n    constexpr std::uint64_t _mod(std::uint64_t x) const {\r\n       \
    \ std::uint64_t xu = x >> 61, xd = x & mod;\r\n        std::uint64_t res = xu\
    \ + xd;\r\n        if (res >= mod) res -= mod;\r\n        return res;\r\n    }\r\
    \n    constexpr std::uint64_t _pow(std::uint64_t x, std::uint64_t k) const {\r\
    \n        std::uint64_t res = 1;\r\n        for (; k; k >>= 1) {\r\n         \
    \   if (k & 1) res = _mod(_mul(res, x));\r\n            x = _mod(_mul(x, x));\r\
    \n        }\r\n        return res;\r\n    }\r\n};\r\n"
  code: "#include <cstdint>\r\n#include <random>\r\n#include <string>\r\n#include\
    \ <vector>\r\n\r\n/**\r\n * @brief \u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\
    \u30E5\r\n * @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\r\n */\r\
    \nstruct rolling_hash {\r\n    rolling_hash(const std::string &_s) : len(_s.size()\
    \ + 1), base(), data(1), p(1, 1) {\r\n        std::mt19937 rnd((std::random_device::result_type)std::random_device()());\r\
    \n        base = rnd() + 2;\r\n        std::uint64_t x = 0, t = 1;\r\n       \
    \ for (const auto c : _s) {\r\n            x = _mod(_mul(x, base) + c);\r\n  \
    \          data.emplace_back(x);\r\n            t = _mod(_mul(t, base));\r\n \
    \           p.emplace_back(t);\r\n        }\r\n    }\r\n\r\n    /**\r\n     *\
    \ @brief get hash of s[l...r]\r\n     *\r\n     * @param l first index\r\n   \
    \  * @param r last index\r\n     * @return std::uint64_t\r\n     */\r\n    std::uint64_t\
    \ get(int l, int r) const {\r\n        return _mod(data[r] + mod * 4 - _mul(data[l],\
    \ p[r - l]));\r\n    }\r\n\r\n    /**\r\n     * @brief search string\r\n     *\r\
    \n     * @param s\r\n     * @return std::vector<int>\r\n     */\r\n    std::vector<int>\
    \ search(const std::string &s) {\r\n        std::vector<int> res;\r\n        int\
    \ n = s.size();\r\n        if (n >= len) return res;\r\n        std::uint64_t\
    \ x = 0;\r\n        for (char c : s) x = _mod(_mul(x, base) + c);\r\n        for\
    \ (int i = 0; i < len - n; ++i) {\r\n            if (get(i, i + n) == x) res.emplace_back(i);\r\
    \n        }\r\n        return res;\r\n    }\r\n\r\n  private:\r\n    static constexpr\
    \ std::uint64_t mod = (1ul << 61) - 1;\r\n    static constexpr std::uint64_t mask30\
    \ = (1ul << 30) - 1;\r\n    static constexpr std::uint64_t mask31 = (1ul << 31)\
    \ - 1;\r\n    int len;\r\n    std::uint64_t base;\r\n    std::vector<std::uint64_t>\
    \ data, p;\r\n\r\n    constexpr std::uint64_t _mul(std::uint64_t a, std::uint64_t\
    \ b) const {\r\n        std::uint64_t au = a >> 31, ad = a & mask31;\r\n     \
    \   std::uint64_t bu = b >> 31, bd = b & mask31;\r\n        std::uint64_t mid\
    \ = ad * bu + au * bd;\r\n        std::uint64_t midu = mid >> 30, midd = mid &\
    \ mask30;\r\n        return au * bu * 2 + midu + (midd << 31) + ad * bd;\r\n \
    \   }\r\n    constexpr std::uint64_t _mod(std::uint64_t x) const {\r\n       \
    \ std::uint64_t xu = x >> 61, xd = x & mod;\r\n        std::uint64_t res = xu\
    \ + xd;\r\n        if (res >= mod) res -= mod;\r\n        return res;\r\n    }\r\
    \n    constexpr std::uint64_t _pow(std::uint64_t x, std::uint64_t k) const {\r\
    \n        std::uint64_t res = 1;\r\n        for (; k; k >>= 1) {\r\n         \
    \   if (k & 1) res = _mod(_mul(res, x));\r\n            x = _mod(_mul(x, x));\r\
    \n        }\r\n        return res;\r\n    }\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/string/rolling_hash.hpp
  requiredBy: []
  timestamp: '2024-04-17 13:53:52+09:00'
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
