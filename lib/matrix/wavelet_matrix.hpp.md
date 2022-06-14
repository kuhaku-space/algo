---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bit_vector.hpp
    title: "\u5B8C\u5099\u8F9E\u66F8"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/matrix/compressed_wavelet_matrix.hpp
    title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_kth_smallest.test.cpp
    title: test/yosupo/data_structure/range_kth_smallest.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_kth_smallest_2.test.cpp
    title: test/yosupo/data_structure/range_kth_smallest_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
    links:
    - https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.cpp.html)
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/bit_vector.hpp:\
    \ line -1: no such header\n"
  code: "#include \"data_structure/bit_vector.hpp\"\n#include \"template/template.hpp\"\
    \n\n/**\n * @brief \u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217\n *\
    \ @details [\u53C2\u8003](https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.cpp.html)\n\
    \ *\n * @tparam T\n * @tparam L\n */\ntemplate <class T, int L = 20>\nstruct wavelet_matrix\
    \ {\n    wavelet_matrix() = default;\n    wavelet_matrix(std::vector<T> v) : length(v.size())\
    \ {\n        std::vector<T> l(length), r(length);\n        for (int level = L\
    \ - 1; level >= 0; --level) {\n            this->matrix[level] = bit_vector(this->length\
    \ + 1);\n            int left = 0, right = 0;\n            for (int i = 0; i <\
    \ this->length; ++i) {\n                if (v[i] >> level & 1) {\n           \
    \         this->matrix[level].set(i);\n                    r[right++] = v[i];\n\
    \                } else {\n                    l[left++] = v[i];\n           \
    \     }\n            }\n            this->mid[level] = left;\n            this->matrix[level].build();\n\
    \            v.swap(l);\n            for (int i = 0; i < right; ++i) { v[left\
    \ + i] = r[i]; }\n        }\n    }\n\n    T access(int k) const {\n        T res\
    \ = 0;\n        for (int level = L - 1; level >= 0; --level) {\n            bool\
    \ f = this->matrix[level][k];\n            if (f) res |= T(1) << level;\n    \
    \        k = this->matrix[level].rank(f, k) + this->mid[level] * f;\n        }\n\
    \        return res;\n    }\n    T operator[](int k) const { return this->access(k);\
    \ }\n\n    /**\n     * @brief count i s.t. (0 <= i < r) && v[i] == x\n     *\n\
    \     * @param x\n     * @param r\n     * @return int\n     */\n    int rank(int\
    \ r, T x) const {\n        int l = 0;\n        for (int level = L - 1; level >=\
    \ 0; --level) {\n            std::tie(l, r) = this->succ((x >> level) & 1, l,\
    \ r, level);\n        }\n        return r - l;\n    }\n\n    /**\n     * @brief\
    \ count i s.t. (l <= i < r) && v[i] == x\n     *\n     * @param l\n     * @param\
    \ r\n     * @param x\n     * @return int\n     */\n    int rank(int l, int r,\
    \ T x) const { return this->rank(r, x) - this->rank(l, x); }\n\n    /**\n    \
    \ * @brief k-th smallest number in v[l ... r-1]\n     *\n     * @param l\n   \
    \  * @param r\n     * @param k\n     * @return T\n     */\n    T kth_smallest(int\
    \ l, int r, int k) const {\n        assert(0 <= k && k < r - l);\n        T res\
    \ = 0;\n        for (int level = L - 1; level >= 0; --level) {\n            int\
    \ cnt = this->matrix[level].rank(false, r) - this->matrix[level].rank(false, l);\n\
    \            bool f = cnt <= k;\n            if (f) {\n                res |=\
    \ T(1) << level;\n                k -= cnt;\n            }\n            std::tie(l,\
    \ r) = succ(f, l, r, level);\n        }\n        return res;\n    }\n\n    /**\n\
    \     * @brief k-th largest number in v[l ... r-1]\n     *\n     * @param l\n\
    \     * @param r\n     * @param k\n     * @return T\n     */\n    T kth_largest(int\
    \ l, int r, int k) const { return this->kth_smallest(l, r, r - l - k - 1); }\n\
    \n    /**\n     * @brief count i s.t. (l <= i < r) && (v[i] < upper)\n     *\n\
    \     * @param l\n     * @param r\n     * @param upper\n     * @return int\n \
    \    */\n    int range_freq(int l, int r, T upper) const {\n        int res =\
    \ 0;\n        for (int level = L - 1; level >= 0; --level) {\n            bool\
    \ f = ((upper >> level) & 1);\n            if (f) res += this->matrix[level].rank(false,\
    \ r) - this->matrix[level].rank(false, l);\n            tie(l, r) = this->succ(f,\
    \ l, r, level);\n        }\n        return res;\n    }\n\n    /**\n     * @brief\
    \ count i s.t. (l <= i < r) && (lower <= v[i] < upper)\n     *\n     * @param\
    \ l\n     * @param r\n     * @param lower\n     * @param upper\n     * @return\
    \ int\n     */\n    int range_freq(int l, int r, T lower, T upper) const {\n \
    \       return this->range_freq(l, r, upper) - this->range_freq(l, r, lower);\n\
    \    }\n\n    /**\n     * @brief max v[i] s.t. (l <= i < r) && (v[i] < upper)\n\
    \     *\n     * @param l\n     * @param r\n     * @param upper\n     * @return\
    \ T\n     */\n    T prev_value(int l, int r, T upper) const {\n        int cnt\
    \ = this->range_freq(l, r, upper);\n        return cnt == 0 ? T(-1) : this->kth_smallest(l,\
    \ r, cnt - 1);\n    }\n\n    /**\n     * @brief min v[i] s.t. (l <= i < r) &&\
    \ (lower <= v[i])\n     *\n     * @param l\n     * @param r\n     * @param lower\n\
    \     * @return T\n     */\n    T next_value(int l, int r, T lower) const {\n\
    \        int cnt = this->range_freq(l, r, lower);\n        return cnt == r - l\
    \ ? T(-1) : this->kth_smallest(l, r, cnt);\n    }\n\n  private:\n    int length;\n\
    \    bit_vector matrix[L];\n    int mid[L];\n\n    std::pair<int, int> succ(bool\
    \ f, int l, int r, int level) const {\n        return {this->matrix[level].rank(f,\
    \ l) + this->mid[level] * f,\n                this->matrix[level].rank(f, r) +\
    \ this->mid[level] * f};\n    }\n};\n"
  dependsOn:
  - lib/data_structure/bit_vector.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/matrix/wavelet_matrix.hpp
  requiredBy:
  - lib/matrix/compressed_wavelet_matrix.hpp
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/range_kth_smallest_2.test.cpp
  - test/yosupo/data_structure/range_kth_smallest.test.cpp
documentation_of: lib/matrix/wavelet_matrix.hpp
layout: document
redirect_from:
- /library/lib/matrix/wavelet_matrix.hpp
- /library/lib/matrix/wavelet_matrix.hpp.html
title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
---
