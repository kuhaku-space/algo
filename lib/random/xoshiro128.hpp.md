---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/random/split_mix_64.hpp
    title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 SplitMix64"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 xoshiro128++"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: random/split_mix_64.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include <array>\n#include <cstdint>\n#include <limits>\n#include\
    \ <utility>\n#include \"random/split_mix_64.hpp\"\n\n/**\n * @brief \u7591\u4F3C\
    \u4E71\u6570\u751F\u6210\u5668 xoshiro128++\n * @details \u5468\u671F\uFF1A$2^128-1$\n\
    \ */\nstruct xoshiro128 {\n    using state_type = std::array<std::uint32_t, 4>;\n\
    \    using result_type = std::uint32_t;\n\n    constexpr xoshiro128() : state()\
    \ {\n        split_mix_64 split_mix{};\n        for (auto &s : state) s = static_cast<std::uint32_t>(split_mix());\n\
    \    }\n    constexpr xoshiro128(std::int64_t seed) noexcept : state() {\n   \
    \     split_mix_64 split_mix{seed};\n        for (auto &s : state) s = static_cast<std::uint32_t>(split_mix());\n\
    \    }\n\n    static constexpr result_type min() noexcept { return std::numeric_limits<result_type>::min();\
    \ }\n    static constexpr result_type max() noexcept { return std::numeric_limits<result_type>::max();\
    \ }\n    constexpr result_type operator()() {\n        const std::uint32_t result\
    \ = rotl(state[0] + state[3], 7) + state[0];\n        const std::uint32_t t =\
    \ state[1] << 9;\n        state[2] ^= state[0];\n        state[3] ^= state[1];\n\
    \        state[1] ^= state[2];\n        state[0] ^= state[3];\n        state[2]\
    \ ^= t;\n        state[3] = rotl(state[3], 11);\n        return result;\n    }\n\
    \    bool operator==(const xoshiro128 &rhs) noexcept { return (state == rhs.state);\
    \ }\n    bool operator!=(const xoshiro128 &rhs) noexcept { return (state != rhs.state);\
    \ }\n\n    constexpr state_type serialize() const noexcept { return state; }\n\
    \    constexpr void deserialize(const state_type &data) noexcept { state = data;\
    \ }\n    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data);\
    \ }\n\n    /**\n     * @brief a\u4EE5\u4E0Ab\u4EE5\u4E0B\u306E\u6574\u6570\u3092\
    \u751F\u6210\n     *\n     * @param a\n     * @param b\n     * @return int [a,\
    \ b]\n     */\n    int rand_range(int a, int b) { return a + operator()() % (b\
    \ - a + 1); }\n\n    /**\n     * @brief 0.0\u4EE5\u4E0A1.0\u672A\u6E80\u306E\u6D6E\
    \u52D5\u5C0F\u6570\u70B9\u6570\u3092\u751F\u6210\n     *\n     * @return double\
    \ [0, 1)\n     */\n    double random() { return (double)operator()() / max();\
    \ }\n\n  private:\n    state_type state;\n\n    static constexpr std::uint32_t\
    \ rotl(const std::uint32_t x, const int s) noexcept {\n        return (x << s)\
    \ | (x >> (32 - s));\n    }\n};\n"
  dependsOn:
  - lib/random/split_mix_64.hpp
  isVerificationFile: false
  path: lib/random/xoshiro128.hpp
  requiredBy: []
  timestamp: '2023-10-02 03:03:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/random/xoshiro128.hpp
layout: document
redirect_from:
- /library/lib/random/xoshiro128.hpp
- /library/lib/random/xoshiro128.hpp.html
title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 xoshiro128++"
---
