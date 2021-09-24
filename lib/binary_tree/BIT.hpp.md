---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/binary_tree/BIT_RSQ.hpp
    title: lib/binary_tree/BIT_RSQ.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/the_number_of_inversions.test.cpp
    title: test/aoj/the_number_of_inversions.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_add_range_sum.test.cpp
    title: test/yosupo/data_structure/point_add_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Binary Indexed Tree
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief Binary Indexed\
    \ Tree\r\n */\r\ntemplate <class T>\r\nstruct BIT {\r\n    int N;\r\n    vector<T>\
    \ data;\r\n\r\n    BIT() : N(), data() {}\r\n    BIT(int n, T e = T(0)) : N(n\
    \ + 1), data(n + 1, e) {}\r\n    BIT(const vector<T> &v) : N(v.size() + 1), data(v.size()\
    \ + 1) { this->build(v); }\r\n\r\n    const T &operator[](int i) const { return\
    \ this->at(i); }\r\n    const T at(int k) const { return this->sum(k + 1) - this->sum(k);\
    \ }\r\n    const T get(int k) const { return this->sum(k + 1) - this->sum(k);\
    \ }\r\n\r\n    template <class U>\r\n    void build(const vector<U> &v) {\r\n\
    \        int n = v.size();\r\n        for (int i = 0; i < n; ++i) this->add(i,\
    \ v[i]);\r\n    }\r\n\r\n    /**\r\n     * @brief v[k] = x\r\n     *\r\n     *\
    \ @param k index\r\n     * @param x data\r\n     * @return void\r\n     */\r\n\
    \    void update(int k, T x) { this->add(k, x - this->at(k)); }\r\n    /**\r\n\
    \     * @brief v[k] += x\r\n     *\r\n     * @param k index\r\n     * @param x\
    \ data\r\n     * @return void\r\n     */\r\n    void add(int k, T x) {\r\n   \
    \     assert(0 <= k && k < N);\r\n        for (++k; k < N; k += k & -k) data[k]\
    \ += x;\r\n    }\r\n    /**\r\n     * @brief chmax(v[k], x)\r\n     *\r\n    \
    \ * @param k index\r\n     * @param x data\r\n     * @return bool\r\n     */\r\
    \n    bool chmax(int k, T x) {\r\n        if (this->at(k) >= x) return false;\r\
    \n        this->update(k, x);\r\n        return true;\r\n    }\r\n    /**\r\n\
    \     * @brief chmin(v[k], x)\r\n     *\r\n     * @param k index\r\n     * @param\
    \ x data\r\n     * @return bool\r\n     */\r\n    bool chmin(int k, T x) {\r\n\
    \        if (this->at(k) <= x) return false;\r\n        this->update(k, x);\r\n\
    \        return true;\r\n    }\r\n\r\n    /**\r\n     * @brief v[0] + ... + v[k\
    \ - 1]\r\n     *\r\n     * @param k index\r\n     * @return T\r\n     */\r\n \
    \   T sum(int k) const {\r\n        assert(0 <= k && k <= N);\r\n        T res\
    \ = 0;\r\n        for (; k > 0; k -= k & -k) res += data[k];\r\n        return\
    \ res;\r\n    }\r\n    /**\r\n     * @brief v[a] + ... + v[a - 1]\r\n     *\r\n\
    \     * @param a first index\r\n     * @param b last index\r\n     * @return T\r\
    \n     */\r\n    T sum(int a, int b) const { return this->sum(b) - this->sum(a);\
    \ }\r\n\r\n    /**\r\n     * @brief lower_bound(v.begin(), v.end(), x)\r\n   \
    \  *\r\n     * @param x data\r\n     * @return int\r\n     */\r\n    int lower_bound(T\
    \ x) const {\r\n        if (x <= 0) return 0;\r\n        int k = 0;\r\n      \
    \  while (k < N) k <<= 1;\r\n        int res = 0;\r\n        for (; k > 0; k >>=\
    \ 1) {\r\n            if (res + k < N && data[res + k] < x) x -= data[res += k];\r\
    \n        }\r\n        return res;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/BIT.hpp
  requiredBy:
  - lib/binary_tree/BIT_RSQ.hpp
  timestamp: '2021-09-25 01:24:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/the_number_of_inversions.test.cpp
  - test/yosupo/data_structure/point_add_range_sum.test.cpp
documentation_of: lib/binary_tree/BIT.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/BIT.hpp
- /library/lib/binary_tree/BIT.hpp.html
title: Binary Indexed Tree
---
