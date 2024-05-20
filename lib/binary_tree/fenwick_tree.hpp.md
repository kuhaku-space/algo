---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/inversion_number.hpp
    title: "\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B"
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/fenwick_tree_raq.hpp
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
    path: test/aoj/dsl/rsq.test.cpp
    title: test/aoj/dsl/rsq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/range_query_on_tree.test.cpp
    title: test/aoj/grl/range_query_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/range_query_on_tree_2.test.cpp
    title: test/aoj/grl/range_query_on_tree_2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_add_range_sum.test.cpp
    title: test/yosupo/data_structure/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_range_inversions.test.cpp
    title: test/yosupo/data_structure/static_range_inversions.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
    title: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
    title: test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
    links:
    - http://hos.ac/slides/20140319_bit.pdf
  bundledCode: "#line 2 \"lib/binary_tree/fenwick_tree.hpp\"\n#include <cassert>\r\
    \n#include <vector>\r\n\r\n/**\r\n * @brief \u30D5\u30A7\u30CB\u30C3\u30AF\u6728\
    \r\n * @see http://hos.ac/slides/20140319_bit.pdf\r\n *\r\n * @tparam T\r\n */\r\
    \ntemplate <class T>\r\nstruct fenwick_tree {\r\n    fenwick_tree() : _size(),\
    \ data() {}\r\n    fenwick_tree(int n) : _size(n + 1), data(n + 1) {}\r\n    template\
    \ <class U>\r\n    fenwick_tree(const std::vector<U> &v) : _size((int)v.size()\
    \ + 1), data((int)v.size() + 1) {\r\n        build(v);\r\n    }\r\n\r\n    T operator[](int\
    \ i) const { return sum(i + 1) - sum(i); }\r\n    T at(int k) const { return operator[](k);\
    \ }\r\n    T get(int k) const { return operator[](k); }\r\n\r\n    template <class\
    \ U>\r\n    void build(const std::vector<U> &v) {\r\n        for (int i = 0, n\
    \ = v.size(); i < n; ++i) add(i, v[i]);\r\n    }\r\n\r\n    /**\r\n     * @brief\
    \ v[k] = val\r\n     *\r\n     * @param k index of array\r\n     * @param val\
    \ new value\r\n     * @return void\r\n     */\r\n    void update(int k, T val)\
    \ { add(k, val - at(k)); }\r\n    /**\r\n     * @brief v[k] += val\r\n     *\r\
    \n     * @param k index of array\r\n     * @param val new value\r\n     * @return\
    \ void\r\n     */\r\n    void add(int k, T val) {\r\n        assert(0 <= k &&\
    \ k < _size);\r\n        for (++k; k < _size; k += k & -k) data[k] += val;\r\n\
    \    }\r\n    /**\r\n     * @brief chmax(v[k], val)\r\n     *\r\n     * @param\
    \ k index of array\r\n     * @param val new value\r\n     * @return bool\r\n \
    \    */\r\n    bool chmax(int k, T val) {\r\n        if (at(k) >= val) return\
    \ false;\r\n        update(k, val);\r\n        return true;\r\n    }\r\n    /**\r\
    \n     * @brief chmin(v[k], val)\r\n     *\r\n     * @param k index of value\r\
    \n     * @param val new value\r\n     * @return bool\r\n     */\r\n    bool chmin(int\
    \ k, T val) {\r\n        if (at(k) <= val) return false;\r\n        update(k,\
    \ val);\r\n        return true;\r\n    }\r\n\r\n    /**\r\n     * @brief v[0]\
    \ + ... + v[n - 1]\r\n     *\r\n     * @return T\r\n     */\r\n    T all_sum()\
    \ const { return sum(_size); }\r\n    /**\r\n     * @brief v[0] + ... + v[k -\
    \ 1]\r\n     *\r\n     * @param k index of array\r\n     * @return T\r\n     */\r\
    \n    T sum(int k) const {\r\n        assert(0 <= k && k <= _size);\r\n      \
    \  T res = 0;\r\n        for (; k > 0; k -= k & -k) res += data[k];\r\n      \
    \  return res;\r\n    }\r\n    /**\r\n     * @brief v[a] + ... + v[b - 1]\r\n\
    \     *\r\n     * @param a first index of array\r\n     * @param b last index\
    \ of array\r\n     * @return T\r\n     */\r\n    T sum(int a, int b) const { return\
    \ a < b ? sum(b) - sum(a) : 0; }\r\n\r\n    /**\r\n     * @brief binary search\
    \ on fenwick_tree\r\n     *\r\n     * @param val target value\r\n     * @return\
    \ int\r\n     */\r\n    int lower_bound(T val) const {\r\n        if (val <= 0)\
    \ return 0;\r\n        int k = 1;\r\n        while (k < _size) k <<= 1;\r\n  \
    \      int res = 0;\r\n        for (; k > 0; k >>= 1) {\r\n            if (res\
    \ + k < _size && data[res + k] < val) val -= data[res += k];\r\n        }\r\n\
    \        return res;\r\n    }\r\n\r\n  private:\r\n    int _size;\r\n    std::vector<T>\
    \ data;\r\n};\r\n"
  code: "#pragma once\r\n#include <cassert>\r\n#include <vector>\r\n\r\n/**\r\n *\
    \ @brief \u30D5\u30A7\u30CB\u30C3\u30AF\u6728\r\n * @see http://hos.ac/slides/20140319_bit.pdf\r\
    \n *\r\n * @tparam T\r\n */\r\ntemplate <class T>\r\nstruct fenwick_tree {\r\n\
    \    fenwick_tree() : _size(), data() {}\r\n    fenwick_tree(int n) : _size(n\
    \ + 1), data(n + 1) {}\r\n    template <class U>\r\n    fenwick_tree(const std::vector<U>\
    \ &v) : _size((int)v.size() + 1), data((int)v.size() + 1) {\r\n        build(v);\r\
    \n    }\r\n\r\n    T operator[](int i) const { return sum(i + 1) - sum(i); }\r\
    \n    T at(int k) const { return operator[](k); }\r\n    T get(int k) const {\
    \ return operator[](k); }\r\n\r\n    template <class U>\r\n    void build(const\
    \ std::vector<U> &v) {\r\n        for (int i = 0, n = v.size(); i < n; ++i) add(i,\
    \ v[i]);\r\n    }\r\n\r\n    /**\r\n     * @brief v[k] = val\r\n     *\r\n   \
    \  * @param k index of array\r\n     * @param val new value\r\n     * @return\
    \ void\r\n     */\r\n    void update(int k, T val) { add(k, val - at(k)); }\r\n\
    \    /**\r\n     * @brief v[k] += val\r\n     *\r\n     * @param k index of array\r\
    \n     * @param val new value\r\n     * @return void\r\n     */\r\n    void add(int\
    \ k, T val) {\r\n        assert(0 <= k && k < _size);\r\n        for (++k; k <\
    \ _size; k += k & -k) data[k] += val;\r\n    }\r\n    /**\r\n     * @brief chmax(v[k],\
    \ val)\r\n     *\r\n     * @param k index of array\r\n     * @param val new value\r\
    \n     * @return bool\r\n     */\r\n    bool chmax(int k, T val) {\r\n       \
    \ if (at(k) >= val) return false;\r\n        update(k, val);\r\n        return\
    \ true;\r\n    }\r\n    /**\r\n     * @brief chmin(v[k], val)\r\n     *\r\n  \
    \   * @param k index of value\r\n     * @param val new value\r\n     * @return\
    \ bool\r\n     */\r\n    bool chmin(int k, T val) {\r\n        if (at(k) <= val)\
    \ return false;\r\n        update(k, val);\r\n        return true;\r\n    }\r\n\
    \r\n    /**\r\n     * @brief v[0] + ... + v[n - 1]\r\n     *\r\n     * @return\
    \ T\r\n     */\r\n    T all_sum() const { return sum(_size); }\r\n    /**\r\n\
    \     * @brief v[0] + ... + v[k - 1]\r\n     *\r\n     * @param k index of array\r\
    \n     * @return T\r\n     */\r\n    T sum(int k) const {\r\n        assert(0\
    \ <= k && k <= _size);\r\n        T res = 0;\r\n        for (; k > 0; k -= k &\
    \ -k) res += data[k];\r\n        return res;\r\n    }\r\n    /**\r\n     * @brief\
    \ v[a] + ... + v[b - 1]\r\n     *\r\n     * @param a first index of array\r\n\
    \     * @param b last index of array\r\n     * @return T\r\n     */\r\n    T sum(int\
    \ a, int b) const { return a < b ? sum(b) - sum(a) : 0; }\r\n\r\n    /**\r\n \
    \    * @brief binary search on fenwick_tree\r\n     *\r\n     * @param val target\
    \ value\r\n     * @return int\r\n     */\r\n    int lower_bound(T val) const {\r\
    \n        if (val <= 0) return 0;\r\n        int k = 1;\r\n        while (k <\
    \ _size) k <<= 1;\r\n        int res = 0;\r\n        for (; k > 0; k >>= 1) {\r\
    \n            if (res + k < _size && data[res + k] < val) val -= data[res += k];\r\
    \n        }\r\n        return res;\r\n    }\r\n\r\n  private:\r\n    int _size;\r\
    \n    std::vector<T> data;\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/binary_tree/fenwick_tree.hpp
  requiredBy:
  - lib/binary_tree/fenwick_tree_raq.hpp
  - lib/algorithm/inversion_number.hpp
  timestamp: '2023-11-16 21:07:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/alds1/inversion_number.test.cpp
  - test/aoj/dsl/rsq.test.cpp
  - test/aoj/dsl/raq_rsq.test.cpp
  - test/aoj/grl/range_query_on_tree_2.test.cpp
  - test/aoj/grl/range_query_on_tree.test.cpp
  - test/yosupo/data_structure/point_add_range_sum.test.cpp
  - test/yosupo/data_structure/vertex_add_subtree_sum.2.test.cpp
  - test/yosupo/data_structure/static_range_inversions.test.cpp
  - test/yosupo/data_structure/vertex_add_path_sum.test.cpp
documentation_of: lib/binary_tree/fenwick_tree.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/fenwick_tree.hpp
- /library/lib/binary_tree/fenwick_tree.hpp.html
title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
---
