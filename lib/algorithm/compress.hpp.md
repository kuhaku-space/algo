---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/inversion_number.hpp
    title: "\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B"
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/compressed_wavelet_matrix.hpp
    title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/inversion_number.test.cpp
    title: test/aoj/alds1/inversion_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_kth_smallest.test.cpp
    title: test/yosupo/data_structure/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/rectangle_sum.test.cpp
    title: test/yosupo/data_structure/rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_range_frequency.test.cpp
    title: test/yosupo/data_structure/static_range_frequency.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_range_inversions.test.cpp
    title: test/yosupo/data_structure/static_range_inversions.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/number_of_subsequences.test.cpp
    title: test/yosupo/math/number_of_subsequences.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5EA7\u6A19\u5727\u7E2E"
    links: []
  bundledCode: "#line 2 \"lib/algorithm/compress.hpp\"\n#include <algorithm>\r\n#include\
    \ <iterator>\r\n#include <vector>\r\n\r\n/**\r\n * @brief \u5EA7\u6A19\u5727\u7E2E\
    \r\n *\r\n * @tparam T \u8981\u7D20\u306E\u578B\r\n */\r\ntemplate <class T>\r\
    \nstruct coordinate_compression {\r\n    coordinate_compression() = default;\r\
    \n    coordinate_compression(const std::vector<T> &_data) : data(_data) { build();\
    \ }\r\n\r\n    const T &operator[](int i) const { return data[i]; }\r\n    T &operator[](int\
    \ i) { return data[i]; }\r\n\r\n    void add(T x) { data.emplace_back(x); }\r\n\
    \r\n    void build() {\r\n        std::sort(std::begin(data), std::end(data));\r\
    \n        data.erase(std::unique(std::begin(data), std::end(data)), std::end(data));\r\
    \n    }\r\n\r\n    bool exists(T x) const {\r\n        auto it = std::lower_bound(std::begin(data),\
    \ std::end(data), x);\r\n        return it != std::end(data) && *it == x;\r\n\
    \    }\r\n\r\n    int get(T x) const {\r\n        auto it = std::lower_bound(std::begin(data),\
    \ std::end(data), x);\r\n        return std::distance(std::begin(data), it);\r\
    \n    }\r\n\r\n    int size() const { return std::size(data); }\r\n\r\n  private:\r\
    \n    std::vector<T> data;\r\n};\r\n\r\n/**\r\n * @brief \u5EA7\u6A19\u5727\u7E2E\
    \r\n *\r\n * @tparam T \u8981\u7D20\u306E\u578B\r\n * @param v \u914D\u5217\r\n\
    \ * @return std::vector<T>\r\n */\r\ntemplate <class T>\r\nstd::vector<T> compress(const\
    \ std::vector<T> &v) {\r\n    coordinate_compression cps(v);\r\n    std::vector<T>\
    \ res;\r\n    res.reserve(std::size(v));\r\n    for (auto &&x : v) res.emplace_back(cps.get(x));\r\
    \n    return res;\r\n}\r\n"
  code: "#pragma once\r\n#include <algorithm>\r\n#include <iterator>\r\n#include <vector>\r\
    \n\r\n/**\r\n * @brief \u5EA7\u6A19\u5727\u7E2E\r\n *\r\n * @tparam T \u8981\u7D20\
    \u306E\u578B\r\n */\r\ntemplate <class T>\r\nstruct coordinate_compression {\r\
    \n    coordinate_compression() = default;\r\n    coordinate_compression(const\
    \ std::vector<T> &_data) : data(_data) { build(); }\r\n\r\n    const T &operator[](int\
    \ i) const { return data[i]; }\r\n    T &operator[](int i) { return data[i]; }\r\
    \n\r\n    void add(T x) { data.emplace_back(x); }\r\n\r\n    void build() {\r\n\
    \        std::sort(std::begin(data), std::end(data));\r\n        data.erase(std::unique(std::begin(data),\
    \ std::end(data)), std::end(data));\r\n    }\r\n\r\n    bool exists(T x) const\
    \ {\r\n        auto it = std::lower_bound(std::begin(data), std::end(data), x);\r\
    \n        return it != std::end(data) && *it == x;\r\n    }\r\n\r\n    int get(T\
    \ x) const {\r\n        auto it = std::lower_bound(std::begin(data), std::end(data),\
    \ x);\r\n        return std::distance(std::begin(data), it);\r\n    }\r\n\r\n\
    \    int size() const { return std::size(data); }\r\n\r\n  private:\r\n    std::vector<T>\
    \ data;\r\n};\r\n\r\n/**\r\n * @brief \u5EA7\u6A19\u5727\u7E2E\r\n *\r\n * @tparam\
    \ T \u8981\u7D20\u306E\u578B\r\n * @param v \u914D\u5217\r\n * @return std::vector<T>\r\
    \n */\r\ntemplate <class T>\r\nstd::vector<T> compress(const std::vector<T> &v)\
    \ {\r\n    coordinate_compression cps(v);\r\n    std::vector<T> res;\r\n    res.reserve(std::size(v));\r\
    \n    for (auto &&x : v) res.emplace_back(cps.get(x));\r\n    return res;\r\n\
    }\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/algorithm/compress.hpp
  requiredBy:
  - lib/algorithm/inversion_number.hpp
  - lib/data_structure/compressed_wavelet_matrix.hpp
  timestamp: '2023-10-01 19:53:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/math/number_of_subsequences.test.cpp
  - test/yosupo/data_structure/range_kth_smallest.test.cpp
  - test/yosupo/data_structure/static_range_frequency.test.cpp
  - test/yosupo/data_structure/static_range_inversions.test.cpp
  - test/yosupo/data_structure/rectangle_sum.test.cpp
  - test/aoj/alds1/inversion_number.test.cpp
documentation_of: lib/algorithm/compress.hpp
layout: document
redirect_from:
- /library/lib/algorithm/compress.hpp
- /library/lib/algorithm/compress.hpp.html
title: "\u5EA7\u6A19\u5727\u7E2E"
---
