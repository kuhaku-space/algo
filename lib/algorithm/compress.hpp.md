---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/inversion_number.hpp
    title: "\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B"
  - icon: ':heavy_check_mark:'
    path: lib/matrix/compressed_wavelet_matrix.hpp
    title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/inversion_number.test.cpp
    title: test/aoj/alds1/inversion_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_kth_smallest.test.cpp
    title: test/yosupo/data_structure/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_kth_smallest_2.test.cpp
    title: test/yosupo/data_structure/range_kth_smallest_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_range_frequency.test.cpp
    title: test/yosupo/data_structure/static_range_frequency.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_range_inversions.test.cpp
    title: test/yosupo/data_structure/static_range_inversions.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/new/number_of_subsequences.test.cpp
    title: test/yosupo/new/number_of_subsequences.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5EA7\u6A19\u5727\u7E2E"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief\
    \ \u5EA7\u6A19\u5727\u7E2E\r\n *\r\n * @tparam T \u8981\u7D20\u306E\u578B\r\n\
    \ */\r\ntemplate <class T>\r\nstruct coordinate_compression {\r\n    coordinate_compression()\
    \ = default;\r\n    coordinate_compression(const std::vector<T> &_data) : data(_data)\
    \ { this->build(); }\r\n\r\n    const T &operator[](int i) const { return this->data[i];\
    \ }\r\n    T &operator[](int i) { return this->data[i]; }\r\n\r\n    void add(T\
    \ x) { this->data.emplace_back(x); }\r\n\r\n    void build() {\r\n        std::sort(this->data.begin(),\
    \ this->data.end());\r\n        this->data.erase(std::unique(this->data.begin(),\
    \ this->data.end()), this->data.end());\r\n    }\r\n    void build(const std::vector<T>\
    \ &v) {\r\n        this->data = v;\r\n        std::sort(this->data.begin(), this->data.end());\r\
    \n        this->data.erase(std::unique(this->data.begin(), this->data.end()),\
    \ this->data.end());\r\n    }\r\n\r\n    bool exist(T x) const {\r\n        auto\
    \ it = std::lower_bound(this->data.begin(), this->data.end(), x);\r\n        return\
    \ it != this->data.end() && *it == x;\r\n    }\r\n\r\n    int get(T x) const {\r\
    \n        auto it = std::lower_bound(this->data.begin(), this->data.end(), x);\r\
    \n        return it - this->data.begin();\r\n    }\r\n\r\n    int size() const\
    \ { return this->data.size(); }\r\n\r\n  private:\r\n    std::vector<T> data;\r\
    \n};\r\n\r\n/**\r\n * @brief \u5EA7\u6A19\u5727\u7E2E\r\n *\r\n * @tparam T \u8981\
    \u7D20\u306E\u578B\r\n * @param v\r\n * @return std::vector<T>\r\n */\r\ntemplate\
    \ <class T>\r\nstd::vector<T> compress(const std::vector<T> &v) {\r\n    coordinate_compression\
    \ cps(v);\r\n    std::vector<T> res;\r\n    for (auto x : v) res.emplace_back(cps.get(x));\r\
    \n    return res;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/compress.hpp
  requiredBy:
  - lib/matrix/compressed_wavelet_matrix.hpp
  - lib/algorithm/inversion_number.hpp
  timestamp: '2023-05-07 20:09:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/range_kth_smallest.test.cpp
  - test/yosupo/data_structure/static_range_inversions.test.cpp
  - test/yosupo/data_structure/range_kth_smallest_2.test.cpp
  - test/yosupo/data_structure/static_range_frequency.test.cpp
  - test/yosupo/new/number_of_subsequences.test.cpp
  - test/aoj/alds1/inversion_number.test.cpp
documentation_of: lib/algorithm/compress.hpp
layout: document
redirect_from:
- /library/lib/algorithm/compress.hpp
- /library/lib/algorithm/compress.hpp.html
title: "\u5EA7\u6A19\u5727\u7E2E"
---
