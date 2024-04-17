---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/treap.hpp
    title: Treap
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/skip_list.hpp
    title: "\u30B9\u30AD\u30C3\u30D7\u30EA\u30B9\u30C8"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/itp2/skip_list.test.cpp
    title: test/aoj/itp2/skip_list.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/itp2/treap.test.cpp
    title: test/aoj/itp2/treap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668"
    links: []
  bundledCode: "#line 2 \"lib/random/xorshift.hpp\"\n#include <array>\n#include <cstdint>\n\
    #include <limits>\n#include <utility>\n\n/**\n * @brief \u64EC\u4F3C\u4E71\u6570\
    \u751F\u6210\u5668\n * @details \u5468\u671F\uFF1A$2^128-1$\n */\nstruct Xorshift\
    \ {\n    using state_type = std::array<std::uint32_t, 4>;\n    using result_type\
    \ = std::uint32_t;\n    constexpr Xorshift() : state{123456789, 362436069, 521288629,\
    \ 88675123} {}\n\n    static constexpr result_type min() { return std::numeric_limits<result_type>::min();\
    \ }\n    static constexpr result_type max() { return std::numeric_limits<result_type>::max();\
    \ }\n    result_type operator()() {\n        std::uint32_t t = (state[0] ^ (state[0]\
    \ << 11));\n        state[0] = state[1], state[1] = state[2], state[2] = state[3];\n\
    \        return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));\n \
    \   }\n    bool operator==(const Xorshift &rhs) noexcept { return (state == rhs.state);\
    \ }\n    bool operator!=(const Xorshift &rhs) noexcept { return (state != rhs.state);\
    \ }\n\n    constexpr state_type serialize() const noexcept { return state; }\n\
    \    constexpr void deserialize(const state_type &data) noexcept { state = data;\
    \ }\n    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data);\
    \ }\n\n    /**\n     * @brief a\u4EE5\u4E0Ab\u4EE5\u4E0B\u306E\u6574\u6570\u3092\
    \u751F\u6210\n     *\n     * @param a\n     * @param b\n     * @return int [a,\
    \ b]\n     */\n    int rand_range(int a, int b) { return a + operator()() % (b\
    \ - a + 1); }\n\n    /**\n     * @brief 0.0\u4EE5\u4E0A1.0\u672A\u6E80\u306E\u6D6E\
    \u52D5\u5C0F\u6570\u70B9\u6570\u3092\u751F\u6210\n     *\n     * @return double\
    \ [0.0, 1.0)\n     */\n    double random() { return (double)operator()() / max();\
    \ }\n\n  private:\n    state_type state;\n};\n"
  code: "#pragma once\n#include <array>\n#include <cstdint>\n#include <limits>\n#include\
    \ <utility>\n\n/**\n * @brief \u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668\n * @details\
    \ \u5468\u671F\uFF1A$2^128-1$\n */\nstruct Xorshift {\n    using state_type =\
    \ std::array<std::uint32_t, 4>;\n    using result_type = std::uint32_t;\n    constexpr\
    \ Xorshift() : state{123456789, 362436069, 521288629, 88675123} {}\n\n    static\
    \ constexpr result_type min() { return std::numeric_limits<result_type>::min();\
    \ }\n    static constexpr result_type max() { return std::numeric_limits<result_type>::max();\
    \ }\n    result_type operator()() {\n        std::uint32_t t = (state[0] ^ (state[0]\
    \ << 11));\n        state[0] = state[1], state[1] = state[2], state[2] = state[3];\n\
    \        return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));\n \
    \   }\n    bool operator==(const Xorshift &rhs) noexcept { return (state == rhs.state);\
    \ }\n    bool operator!=(const Xorshift &rhs) noexcept { return (state != rhs.state);\
    \ }\n\n    constexpr state_type serialize() const noexcept { return state; }\n\
    \    constexpr void deserialize(const state_type &data) noexcept { state = data;\
    \ }\n    constexpr void deserialize(state_type &&data) noexcept { state = std::move(data);\
    \ }\n\n    /**\n     * @brief a\u4EE5\u4E0Ab\u4EE5\u4E0B\u306E\u6574\u6570\u3092\
    \u751F\u6210\n     *\n     * @param a\n     * @param b\n     * @return int [a,\
    \ b]\n     */\n    int rand_range(int a, int b) { return a + operator()() % (b\
    \ - a + 1); }\n\n    /**\n     * @brief 0.0\u4EE5\u4E0A1.0\u672A\u6E80\u306E\u6D6E\
    \u52D5\u5C0F\u6570\u70B9\u6570\u3092\u751F\u6210\n     *\n     * @return double\
    \ [0.0, 1.0)\n     */\n    double random() { return (double)operator()() / max();\
    \ }\n\n  private:\n    state_type state;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/random/xorshift.hpp
  requiredBy:
  - lib/data_structure/skip_list.hpp
  - lib/binary_tree/treap.hpp
  timestamp: '2023-10-02 03:03:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/itp2/treap.test.cpp
  - test/aoj/itp2/skip_list.test.cpp
documentation_of: lib/random/xorshift.hpp
layout: document
redirect_from:
- /library/lib/random/xorshift.hpp
- /library/lib/random/xorshift.hpp.html
title: "\u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668"
---
