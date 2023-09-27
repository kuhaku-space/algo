---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/random/xoroshiro128.hpp
    title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 xoroshiro128++"
  - icon: ':warning:'
    path: lib/random/xoshiro128.hpp
    title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 xoshiro128++"
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 SplitMix64"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\n/**\n * @brief \u7591\
    \u4F3C\u4E71\u6570\u751F\u6210\u5668 SplitMix64\n * @details \u5468\u671F\uFF1A\
    $2^64-1$\n */\nstruct split_mix_64 {\n    using state_type = std::uint64_t;\n\
    \    using result_type = std::uint64_t;\n\n    constexpr split_mix_64() noexcept\
    \ : state(1234567890) {}\n    constexpr split_mix_64(std::uint64_t seed) noexcept\
    \ : state(seed) {}\n\n    static constexpr result_type min() noexcept { return\
    \ std::numeric_limits<result_type>::min(); }\n    static constexpr result_type\
    \ max() noexcept { return std::numeric_limits<result_type>::max(); }\n    constexpr\
    \ result_type operator()() {\n        std::uint64_t z = (state += 0x9e3779b97f4a7c15);\n\
    \        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n        z = (z ^ (z >> 27))\
    \ * 0x94d049bb133111eb;\n        return z ^ (z >> 31);\n    }\n\n    constexpr\
    \ state_type serialize() const noexcept { return state; }\n    constexpr void\
    \ deserialize(const state_type &data) noexcept { state = data; }\n    constexpr\
    \ void deserialize(state_type &&data) noexcept { state = std::move(data); }\n\n\
    \    template <std::size_t N>\n    constexpr std::array<std::uint64_t, N> generate_seed_sequence()\
    \ noexcept {\n        std::array<std::uint64_t, N> seeds = {};\n        for (auto\
    \ &seed : seeds) seed = operator()();\n        return seeds;\n    }\n\n    /**\n\
    \     * @brief a\u4EE5\u4E0Ab\u4EE5\u4E0B\u306E\u6574\u6570\u3092\u751F\u6210\n\
    \     *\n     * @param a\n     * @param b\n     * @return int [a, b]\n     */\n\
    \    int rand_range(int a, int b) { return a + operator()() % (b - a + 1); }\n\
    \n    /**\n     * @brief 0.0\u4EE5\u4E0A1.0\u672A\u6E80\u306E\u6D6E\u52D5\u5C0F\
    \u6570\u70B9\u6570\u3092\u751F\u6210\n     *\n     * @return double [0, 1)\n \
    \    */\n    double random() { return (double)operator()() / max(); }\n\n  private:\n\
    \    state_type state;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/random/split_mix_64.hpp
  requiredBy:
  - lib/random/xoshiro128.hpp
  - lib/random/xoroshiro128.hpp
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/random/split_mix_64.hpp
layout: document
redirect_from:
- /library/lib/random/split_mix_64.hpp
- /library/lib/random/split_mix_64.hpp.html
title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 SplitMix64"
---
