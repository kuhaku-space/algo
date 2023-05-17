---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/compress.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bit_vector.hpp
    title: "\u5B8C\u5099\u8F9E\u66F8"
  - icon: ':heavy_check_mark:'
    path: lib/matrix/wavelet_matrix.hpp
    title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_kth_smallest.test.cpp
    title: test/yosupo/data_structure/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_kth_smallest_2.test.cpp
    title: test/yosupo/data_structure/range_kth_smallest_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_range_frequency.test.cpp
    title: test/yosupo/data_structure/static_range_frequency.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
    links:
    - https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.cpp.html)
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/compress.hpp:\
    \ line -1: no such header\n"
  code: "#include \"algorithm/compress.hpp\"\n#include \"matrix/wavelet_matrix.hpp\"\
    \n#include \"template/template.hpp\"\n\n/**\n * @brief \u30A6\u30A7\u30FC\u30D6\
    \u30EC\u30C3\u30C8\u884C\u5217\n * @details [\u53C2\u8003](https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.cpp.html)\n\
    \ *\n * @tparam T\n * @tparam MAXLOG\n */\ntemplate <class T, int MAXLOG = 20>\n\
    struct compressed_wavelet_matrix {\n    compressed_wavelet_matrix() = default;\n\
    \    compressed_wavelet_matrix(const std::vector<T> &v) : cps(v) {\n        int\
    \ n = v.size();\n        std::vector<int> t(n);\n        for (int i = 0; i < n;\
    \ ++i) t[i] = this->cps.get(v[i]);\n        this->mat = wavelet_matrix<int, MAXLOG>(t);\n\
    \    }\n\n    T access(int k) const { return this->cps[this->mat.access(k)]; }\n\
    \    T operator[](int k) const { return this->access(k); }\n\n    /**\n     *\
    \ @brief count i s.t. (0 <= i < r) && v[i] == x\n     *\n     * @param x\n   \
    \  * @param r\n     * @return int\n     */\n    int rank(int r, T x) const {\n\
    \        auto pos = this->cps.get(x);\n        if (pos == this->cps.size() ||\
    \ this->cps[pos] != x) return 0;\n        return this->mat.rank(r, pos);\n   \
    \ }\n\n    /**\n     * @brief count i s.t. (l <= i < r) && v[i] == x\n     *\n\
    \     * @param l\n     * @param r\n     * @param x\n     * @return int\n     */\n\
    \    int rank(int l, int r, T x) const { return this->rank(r, x) - this->rank(l,\
    \ x); }\n\n    /**\n     * @brief k-th smallest number in v[l ... r-1]\n     *\n\
    \     * @param l\n     * @param r\n     * @param k\n     * @return T\n     */\n\
    \    T kth_smallest(int l, int r, int k) const { return this->cps[this->mat.kth_smallest(l,\
    \ r, k)]; }\n\n    /**\n     * @brief k-th largest number in v[l ... r-1]\n  \
    \   *\n     * @param l\n     * @param r\n     * @param k\n     * @return T\n \
    \    */\n    T kth_largest(int l, int r, int k) const { return this->cps[this->mat.kth_largest(l,\
    \ r, k)]; }\n\n    /**\n     * @brief count i s.t. (l <= i < r) && (v[i] < upper)\n\
    \     *\n     * @param l\n     * @param r\n     * @param upper\n     * @return\
    \ int\n     */\n    int range_freq(int l, int r, T upper) const {\n        return\
    \ this->mat.range_freq(l, r, this->cps.get(upper));\n    }\n\n    /**\n     *\
    \ @brief count i s.t. (l <= i < r) && (lower <= v[i] < upper)\n     *\n     *\
    \ @param l\n     * @param r\n     * @param lower\n     * @param upper\n     *\
    \ @return int\n     */\n    int range_freq(int l, int r, T lower, T upper) const\
    \ {\n        return this->mat.range_freq(l, r, this->cps.get(lower), this->cps.get(upper));\n\
    \    }\n\n    /**\n     * @brief max v[i] s.t. (l <= i < r) && (v[i] < upper)\n\
    \     *\n     * @param l\n     * @param r\n     * @param upper\n     * @return\
    \ T\n     */\n    T prev_value(int l, int r, T upper) const {\n        auto res\
    \ = this->mat.prev_value(l, r, this->cps.get(upper));\n        return res == -1\
    \ ? T(-1) : this->cps[res];\n    }\n\n    /**\n     * @brief min v[i] s.t. (l\
    \ <= i < r) && (lower <= v[i])\n     *\n     * @param l\n     * @param r\n   \
    \  * @param lower\n     * @return T\n     */\n    T next_value(int l, int r, T\
    \ lower) const {\n        auto res = this->mat.next_value(l, r, this->cps.get(lower));\n\
    \        return res == -1 ? T(-1) : this->cps[res];\n    }\n\n  private:\n   \
    \ wavelet_matrix<int, MAXLOG> mat;\n    coordinate_compression<T> cps;\n};\n"
  dependsOn:
  - lib/algorithm/compress.hpp
  - lib/template/template.hpp
  - lib/matrix/wavelet_matrix.hpp
  - lib/data_structure/bit_vector.hpp
  isVerificationFile: false
  path: lib/matrix/compressed_wavelet_matrix.hpp
  requiredBy: []
  timestamp: '2023-05-17 13:01:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/range_kth_smallest.test.cpp
  - test/yosupo/data_structure/static_range_frequency.test.cpp
  - test/yosupo/data_structure/range_kth_smallest_2.test.cpp
documentation_of: lib/matrix/compressed_wavelet_matrix.hpp
layout: document
redirect_from:
- /library/lib/matrix/compressed_wavelet_matrix.hpp
- /library/lib/matrix/compressed_wavelet_matrix.hpp.html
title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
---
