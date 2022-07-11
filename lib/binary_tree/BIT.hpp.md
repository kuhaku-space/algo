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
    path: lib/binary_tree/BIT_RAQ.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728\uFF08\u533A\u9593\u52A0\u7B97\u3001\
      \u533A\u9593\u7DCF\u548C\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/inversion_number.test.cpp
    title: test/aoj/alds1/inversion_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/raq_rsq.test.cpp
    title: test/aoj/dsl/raq_rsq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_add_range_sum.test.cpp
    title: test/yosupo/data_structure/point_add_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
    links:
    - http://hos.ac/slides/20140319_bit.pdf
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u30D5\u30A7\u30CB\
    \u30C3\u30AF\u6728\r\n * @see http://hos.ac/slides/20140319_bit.pdf\r\n *\r\n\
    \ * @tparam T\r\n */\r\ntemplate <class T>\r\nstruct BIT {\r\n    BIT() : _size(),\
    \ data() {}\r\n    BIT(int n) : _size(n + 1), data(n + 1) {}\r\n    BIT(const\
    \ std::vector<T> &v) : _size((int)v.size() + 1), data((int)v.size() + 1) {\r\n\
    \        this->build(v);\r\n    }\r\n    template <class U>\r\n    BIT(const std::vector<U>\
    \ &v) : _size((int)v.size() + 1), data((int)v.size() + 1) {\r\n        this->build(v);\r\
    \n    }\r\n\r\n    T operator[](int i) const { return this->sum(i + 1) - this->sum(i);\
    \ }\r\n    T at(int k) const { return this->operator[](k); }\r\n    T get(int\
    \ k) const { return this->operator[](k); }\r\n\r\n    template <class U>\r\n \
    \   void build(const std::vector<U> &v) {\r\n        for (int i = 0, n = v.size();\
    \ i < n; ++i) this->add(i, v[i]);\r\n    }\r\n\r\n    /**\r\n     * @brief v[k]\
    \ = val\r\n     *\r\n     * @param k index of array\r\n     * @param val new value\r\
    \n     * @return void\r\n     */\r\n    void update(int k, T val) { this->add(k,\
    \ val - this->at(k)); }\r\n    /**\r\n     * @brief v[k] += val\r\n     *\r\n\
    \     * @param k index of array\r\n     * @param val new value\r\n     * @return\
    \ void\r\n     */\r\n    void add(int k, T val) {\r\n        assert(0 <= k &&\
    \ k < this->_size);\r\n        for (++k; k < this->_size; k += k & -k) this->data[k]\
    \ += val;\r\n    }\r\n    /**\r\n     * @brief chmax(v[k], val)\r\n     *\r\n\
    \     * @param k index of array\r\n     * @param val new value\r\n     * @return\
    \ bool\r\n     */\r\n    bool chmax(int k, T val) {\r\n        if (this->at(k)\
    \ >= val) return false;\r\n        this->update(k, val);\r\n        return true;\r\
    \n    }\r\n    /**\r\n     * @brief chmin(v[k], val)\r\n     *\r\n     * @param\
    \ k index of value\r\n     * @param val new value\r\n     * @return bool\r\n \
    \    */\r\n    bool chmin(int k, T val) {\r\n        if (this->at(k) <= val) return\
    \ false;\r\n        this->update(k, val);\r\n        return true;\r\n    }\r\n\
    \r\n    /**\r\n     * @brief v[0] + ... + v[n - 1]\r\n     *\r\n     * @return\
    \ T\r\n     */\r\n    T all_sum() const { return this->sum(this->_size); }\r\n\
    \    /**\r\n     * @brief v[0] + ... + v[k - 1]\r\n     *\r\n     * @param k index\
    \ of array\r\n     * @return T\r\n     */\r\n    T sum(int k) const {\r\n    \
    \    assert(0 <= k && k <= this->_size);\r\n        T res = 0;\r\n        for\
    \ (; k > 0; k -= k & -k) res += this->data[k];\r\n        return res;\r\n    }\r\
    \n    /**\r\n     * @brief v[a] + ... + v[b - 1]\r\n     *\r\n     * @param a\
    \ first index of array\r\n     * @param b last index of array\r\n     * @return\
    \ T\r\n     */\r\n    T sum(int a, int b) const { return a < b ? this->sum(b)\
    \ - this->sum(a) : 0; }\r\n\r\n    /**\r\n     * @brief binary search on BIT\r\
    \n     *\r\n     * @param val target value\r\n     * @return int\r\n     */\r\n\
    \    int lower_bound(T val) const {\r\n        if (val <= 0) return 0;\r\n   \
    \     int k = 1;\r\n        while (k < this->_size) k <<= 1;\r\n        int res\
    \ = 0;\r\n        for (; k > 0; k >>= 1) {\r\n            if (res + k < this->_size\
    \ && this->data[res + k] < val) val -= this->data[res += k];\r\n        }\r\n\
    \        return res;\r\n    }\r\n\r\n  private:\r\n    int _size;\r\n    std::vector<T>\
    \ data;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/BIT.hpp
  requiredBy:
  - lib/algorithm/inversion_number.hpp
  - lib/binary_tree/BIT_RAQ.hpp
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/point_add_range_sum.test.cpp
  - test/aoj/alds1/inversion_number.test.cpp
  - test/aoj/dsl/raq_rsq.test.cpp
documentation_of: lib/binary_tree/BIT.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/BIT.hpp
- /library/lib/binary_tree/BIT.hpp.html
title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
---
