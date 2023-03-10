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
    document_title: "\u7D20\u6570\u5224\u5B9A"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <int N = (1 << 22)>\r\n\
    struct eratosthenes {\r\n  private:\r\n    static constexpr int SIZE = N / 30\
    \ + (N % 30 != 0);\r\n    static constexpr std::array<int, 8> kMod30 = {1, 7,\
    \ 11, 13, 17, 19, 23, 29};\r\n    static constexpr std::array<int, 8> C1 = {6,\
    \ 4, 2, 4, 2, 4, 6, 2};\r\n    static constexpr std::array<std::array<int, 8>,\
    \ 8> C0 = {\r\n        std::array<int, 8>{0, 0, 0, 0, 0, 0, 0, 1},\r\n       \
    \ {1, 1, 1, 0, 1, 1, 1, 1},\r\n        {2, 2, 0, 2, 0, 2, 2, 1},\r\n        {3,\
    \ 1, 1, 2, 1, 1, 3, 1},\r\n        {3, 3, 1, 2, 1, 3, 3, 1},\r\n        {4, 2,\
    \ 2, 2, 2, 2, 4, 1},\r\n        {5, 3, 1, 4, 1, 3, 5, 1},\r\n        {6, 4, 2,\
    \ 4, 2, 4, 6, 1},\r\n    };\r\n    static constexpr std::array<std::array<std::uint8_t,\
    \ 8>, 8> kMask = {\r\n        std::array<std::uint8_t, 8>{0xfe, 0xfd, 0xfb, 0xf7,\
    \ 0xef, 0xdf, 0xbf, 0x7f},\r\n        {0xfd, 0xdf, 0xef, 0xfe, 0x7f, 0xf7, 0xfb,\
    \ 0xbf},\r\n        {0xfb, 0xef, 0xfe, 0xbf, 0xfd, 0x7f, 0xf7, 0xdf},\r\n    \
    \    {0xf7, 0xfe, 0xbf, 0xdf, 0xfb, 0xfd, 0x7f, 0xef},\r\n        {0xef, 0x7f,\
    \ 0xfd, 0xfb, 0xdf, 0xbf, 0xfe, 0xf7},\r\n        {0xdf, 0xf7, 0x7f, 0xfd, 0xbf,\
    \ 0xfe, 0xef, 0xfb},\r\n        {0xbf, 0xfb, 0xf7, 0x7f, 0xfe, 0xef, 0xdf, 0xfd},\r\
    \n        {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe},\r\n    };\r\n\r\n\
    \  public:\r\n    constexpr eratosthenes() {\r\n        this->prime_number.fill(0xff);\r\
    \n        this->prime_number[0] = 0xfe;\r\n        if (int r = N % 30) {\r\n \
    \           if (r < 7) prime_number[SIZE - 1] = 0x1;\r\n            else if (r\
    \ < 11) prime_number[SIZE - 1] = 0x3;\r\n            else if (r < 13) prime_number[SIZE\
    \ - 1] = 0x7;\r\n            else if (r < 17) prime_number[SIZE - 1] = 0xf;\r\n\
    \            else if (r < 19) prime_number[SIZE - 1] = 0x1f;\r\n            else\
    \ if (r < 23) prime_number[SIZE - 1] = 0x3f;\r\n            else if (r < 29) prime_number[SIZE\
    \ - 1] = 0x7f;\r\n        }\r\n        const std::uint64_t sqrt_x = std::ceil(std::sqrt(N)\
    \ + 0.1);\r\n        const std::uint64_t sqrt_xi = sqrt_x / 30 + 1;\r\n      \
    \  for (std::uint64_t i = 0; i < sqrt_xi; ++i) {\r\n            for (std::uint8_t\
    \ flags = prime_number[i]; flags; flags &= flags - 1) {\r\n                std::uint8_t\
    \ lsb = flags & (-flags);\r\n                const int ibit = __builtin_ctz(lsb);\r\
    \n                const int m = kMod30[ibit];\r\n                const int pm\
    \ = 30 * i + 2 * m;\r\n                for (std::uint64_t j = i * pm + (m * m)\
    \ / 30, k = ibit; j < SIZE;\r\n                     j += i * C1[k] + C0[ibit][k],\
    \ k = (k + 1) & 7) {\r\n                    prime_number[j] &= kMask[ibit][k];\r\
    \n                }\r\n            }\r\n        }\r\n    }\r\n\r\n    /**\r\n\
    \     * @brief \u7D20\u6570\u5224\u5B9A\r\n     *\r\n     * @param x\r\n     *\
    \ @return bool\r\n     */\r\n    bool is_prime(int x) const {\r\n        switch\
    \ (x % 30) {\r\n            case 1:\r\n                return prime_number[x /\
    \ 30] >> 0 & 1;\r\n            case 7:\r\n                return prime_number[x\
    \ / 30] >> 1 & 1;\r\n            case 11:\r\n                return prime_number[x\
    \ / 30] >> 2 & 1;\r\n            case 13:\r\n                return prime_number[x\
    \ / 30] >> 3 & 1;\r\n            case 17:\r\n                return prime_number[x\
    \ / 30] >> 4 & 1;\r\n            case 19:\r\n                return prime_number[x\
    \ / 30] >> 5 & 1;\r\n            case 23:\r\n                return prime_number[x\
    \ / 30] >> 6 & 1;\r\n            case 29:\r\n                return prime_number[x\
    \ / 30] >> 7 & 1;\r\n        }\r\n        if (x < 6) {\r\n            if (x ==\
    \ 2) return true;\r\n            if (x == 3) return true;\r\n            if (x\
    \ == 5) return true;\r\n        }\r\n        return false;\r\n    }\r\n\r\n  \
    \  std::vector<int> prime_numbers(int x) const {\r\n        if (x < 2) return\
    \ std::vector<int>();\r\n        std::vector<int> res = {2};\r\n        for (int\
    \ i = 3; i <= x; i += 2) {\r\n            if (this->is_prime(i)) res.emplace_back(i);\r\
    \n        }\r\n        return res;\r\n    }\r\n\r\n  private:\r\n    std::array<std::uint8_t,\
    \ SIZE> prime_number;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/eratosthenes.hpp
  requiredBy: []
  timestamp: '2023-01-10 05:02:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/eratosthenes.hpp
layout: document
redirect_from:
- /library/lib/math/eratosthenes.hpp
- /library/lib/math/eratosthenes.hpp.html
title: "\u7D20\u6570\u5224\u5B9A"
---
