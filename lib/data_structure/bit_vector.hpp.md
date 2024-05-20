---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/compressed_wavelet_matrix.hpp
    title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/wavelet_matrix.hpp
    title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/wavelet_matrix_rectangle_sum.hpp
    title: lib/data_structure/wavelet_matrix_rectangle_sum.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_kth_smallest.2.test.cpp
    title: test/yosupo/data_structure/range_kth_smallest.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_kth_smallest.test.cpp
    title: test/yosupo/data_structure/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/rectangle_sum.test.cpp
    title: test/yosupo/data_structure/rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_range_frequency.test.cpp
    title: test/yosupo/data_structure/static_range_frequency.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5B8C\u5099\u8F9E\u66F8"
    links:
    - https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.hpp
  bundledCode: "#line 1 \"lib/data_structure/bit_vector.hpp\"\n#include <vector>\n\
    \n/**\n * @brief \u5B8C\u5099\u8F9E\u66F8\n *\n * @see https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.hpp\n\
    \ */\nstruct bit_vector {\n    bit_vector() = default;\n    bit_vector(unsigned\
    \ int _length)\n        : length(_length), blocks((_length + 31) >> 5), bit((_length\
    \ + 31) >> 5),\n          sum((_length + 31) >> 5) {}\n\n    void set(unsigned\
    \ int k) { bit[k >> 5] |= 1U << (k & 31); }\n\n    void build() {\n        sum[0]\
    \ = 0U;\n        for (unsigned int i = 1; i < blocks; ++i) {\n            sum[i]\
    \ = sum[i - 1] + __builtin_popcount(bit[i - 1]);\n        }\n    }\n\n    bool\
    \ operator[](unsigned int k) const { return bit[k >> 5] >> (k & 31) & 1; }\n\n\
    \    unsigned int rank(unsigned int k) const {\n        return sum[k >> 5] + __builtin_popcount(bit[k\
    \ >> 5] & ((1U << (k & 31)) - 1));\n    }\n    unsigned int rank(bool val, unsigned\
    \ int k) const { return val ? rank(k) : k - rank(k); }\n\n    unsigned int select(unsigned\
    \ int k) const {\n        unsigned int sl = 0, sr = blocks + 1;\n        while\
    \ (sr - sl > 1) {\n            unsigned int m = (sl + sr) >> 1;\n            if\
    \ (sum[m] < k) sl = m;\n            else sr = m;\n        }\n        k -= sum[sl];\n\
    \        unsigned int bl = 0, br = 32;\n        while (br - bl > 1) {\n      \
    \      unsigned int m = (bl + br) >> 1;\n            if (__builtin_popcount(bit[sl]\
    \ & ((1U << m) - 1)) < k) bl = m;\n            else br = m;\n        }\n     \
    \   return (sl << 5) + bl;\n    }\n\n  private:\n    unsigned int length, blocks;\n\
    \    std::vector<unsigned int> bit, sum;\n};\n"
  code: "#include <vector>\n\n/**\n * @brief \u5B8C\u5099\u8F9E\u66F8\n *\n * @see\
    \ https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.hpp\n\
    \ */\nstruct bit_vector {\n    bit_vector() = default;\n    bit_vector(unsigned\
    \ int _length)\n        : length(_length), blocks((_length + 31) >> 5), bit((_length\
    \ + 31) >> 5),\n          sum((_length + 31) >> 5) {}\n\n    void set(unsigned\
    \ int k) { bit[k >> 5] |= 1U << (k & 31); }\n\n    void build() {\n        sum[0]\
    \ = 0U;\n        for (unsigned int i = 1; i < blocks; ++i) {\n            sum[i]\
    \ = sum[i - 1] + __builtin_popcount(bit[i - 1]);\n        }\n    }\n\n    bool\
    \ operator[](unsigned int k) const { return bit[k >> 5] >> (k & 31) & 1; }\n\n\
    \    unsigned int rank(unsigned int k) const {\n        return sum[k >> 5] + __builtin_popcount(bit[k\
    \ >> 5] & ((1U << (k & 31)) - 1));\n    }\n    unsigned int rank(bool val, unsigned\
    \ int k) const { return val ? rank(k) : k - rank(k); }\n\n    unsigned int select(unsigned\
    \ int k) const {\n        unsigned int sl = 0, sr = blocks + 1;\n        while\
    \ (sr - sl > 1) {\n            unsigned int m = (sl + sr) >> 1;\n            if\
    \ (sum[m] < k) sl = m;\n            else sr = m;\n        }\n        k -= sum[sl];\n\
    \        unsigned int bl = 0, br = 32;\n        while (br - bl > 1) {\n      \
    \      unsigned int m = (bl + br) >> 1;\n            if (__builtin_popcount(bit[sl]\
    \ & ((1U << m) - 1)) < k) bl = m;\n            else br = m;\n        }\n     \
    \   return (sl << 5) + bl;\n    }\n\n  private:\n    unsigned int length, blocks;\n\
    \    std::vector<unsigned int> bit, sum;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/data_structure/bit_vector.hpp
  requiredBy:
  - lib/data_structure/wavelet_matrix_rectangle_sum.hpp
  - lib/data_structure/wavelet_matrix.hpp
  - lib/data_structure/compressed_wavelet_matrix.hpp
  timestamp: '2023-10-01 22:47:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/range_kth_smallest.2.test.cpp
  - test/yosupo/data_structure/static_range_frequency.test.cpp
  - test/yosupo/data_structure/rectangle_sum.test.cpp
  - test/yosupo/data_structure/range_kth_smallest.test.cpp
documentation_of: lib/data_structure/bit_vector.hpp
layout: document
redirect_from:
- /library/lib/data_structure/bit_vector.hpp
- /library/lib/data_structure/bit_vector.hpp.html
title: "\u5B8C\u5099\u8F9E\u66F8"
---
