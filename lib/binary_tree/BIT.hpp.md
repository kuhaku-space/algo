---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/binary_tree/BIT_RSQ.hpp
    title: v[k] = val
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj/the_number_of_inversions.test.cpp
    title: test/aoj/the_number_of_inversions.test.cpp
  - icon: ':x:'
    path: test/yosupo/data_structure/point_add_range_sum.test.cpp
    title: test/yosupo/data_structure/point_add_range_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Binary Indexed Tree
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief Binary Indexed\
    \ Tree\r\n */\r\ntemplate <class T>\r\nstruct BIT {\r\n    int N;\r\n    vector<T>\
    \ data;\r\n\r\n    BIT() : N(), data() {}\r\n    BIT(int n, T e = T(0)) : N(n\
    \ + 1), data(n + 1, e) {}\r\n    BIT(const vector<T> &v) : N(v.size() + 1), data(v.size()\
    \ + 1) { this->build(v); }\r\n\r\n    const T at(int k) const { return this->sum(k\
    \ + 1) - this->sum(k); }\r\n    const T get(int k) const { return this->operator[](k);\
    \ }\r\n\r\n    template <class U>\r\n    void build(const vector<U> &v) {\r\n\
    \        int n = v.size();\r\n        for (int i = 0; i < n; ++i) this->add(i,\
    \ v[i]);\r\n    }\r\n\r\n    /**\r\n     * @brief v[k] = val\r\n     *\r\n   \
    \  * @param k index of array\r\n     * @param val new value\r\n     * @return\
    \ void\r\n     */\r\n    void update(int k, T val) { this->add(k, val - this->at(k));\
    \ }\r\n    /**\r\n     * @brief v[k] += val\r\n     *\r\n     * @param k index\
    \ of array\r\n     * @param val new value\r\n     * @return void\r\n     */\r\n\
    \    void add(int k, T val) {\r\n        assert(0 <= k && k < this->N);\r\n  \
    \      for (++k; k < N; k += k & -k) this->data[k] += val;\r\n    }\r\n    /**\r\
    \n     * @brief chmax(v[k], val)\r\n     *\r\n     * @param k index of array\r\
    \n     * @param val new value\r\n     * @return bool\r\n     */\r\n    bool chmax(int\
    \ k, T val) {\r\n        if (this->at(k) >= val) return false;\r\n        this->update(k,\
    \ val);\r\n        return true;\r\n    }\r\n    /**\r\n     * @brief chmin(v[k],\
    \ val)\r\n     *\r\n     * @param k index of value\r\n     * @param val new value\r\
    \n     * @return bool\r\n     */\r\n    bool chmin(int k, T val) {\r\n       \
    \ if (this->at(k) <= val) return false;\r\n        this->update(k, val);\r\n \
    \       return true;\r\n    }\r\n\r\n    /**\r\n     * @brief v[0] + ... + v[n\
    \ - 1]\r\n     *\r\n     * @return T\r\n     */\r\n    T all_sum() const { return\
    \ this->sum(this->N); }\r\n    /**\r\n     * @brief v[0] + ... + v[k - 1]\r\n\
    \     *\r\n     * @param k index of array\r\n     * @return T\r\n     */\r\n \
    \   T sum(int k) const {\r\n        assert(0 <= k && k <= this->N);\r\n      \
    \  T res = 0;\r\n        for (; k > 0; k -= k & -k) res += this->data[k];\r\n\
    \        return res;\r\n    }\r\n    /**\r\n     * @brief v[a] + ... + v[b - 1]\r\
    \n     *\r\n     * @param a first index of array\r\n     * @param b last index\
    \ of array\r\n     * @return T\r\n     */\r\n    T sum(int a, int b) const { return\
    \ this->sum(b) - this->sum(a); }\r\n\r\n    /**\r\n     * @brief binary search\
    \ on BIT\r\n     *\r\n     * @param val target value\r\n     * @return int\r\n\
    \     */\r\n    int lower_bound(T val) const {\r\n        if (val <= 0) return\
    \ 0;\r\n        int k = 1;\r\n        while (k < this->N) k <<= 1;\r\n       \
    \ int res = 0;\r\n        for (; k > 0; k >>= 1) {\r\n            if (res + k\
    \ < N && this->data[res + k] < val) val -= this->data[res += k];\r\n        }\r\
    \n        return res;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/BIT.hpp
  requiredBy:
  - lib/binary_tree/BIT_RSQ.hpp
  timestamp: '2021-11-06 08:05:28+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo/data_structure/point_add_range_sum.test.cpp
  - test/aoj/the_number_of_inversions.test.cpp
documentation_of: lib/binary_tree/BIT.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/BIT.hpp
- /library/lib/binary_tree/BIT.hpp.html
title: Binary Indexed Tree
---
