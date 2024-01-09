---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/fenwick_tree.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/raq_rsq.test.cpp
    title: test/aoj/dsl/raq_rsq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/range_query_on_tree_2.test.cpp
    title: test/aoj/grl/range_query_on_tree_2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728\uFF08\u533A\u9593\u52A0\u7B97\
      \u3001\u533A\u9593\u7DCF\u548C\uFF09"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/fenwick_tree.hpp:\
    \ line -1: no such header\n"
  code: "#include \"binary_tree/fenwick_tree.hpp\"\r\n\r\n/**\r\n * @brief \u30D5\u30A7\
    \u30CB\u30C3\u30AF\u6728\uFF08\u533A\u9593\u52A0\u7B97\u3001\u533A\u9593\u7DCF\
    \u548C\uFF09\r\n *\r\n * @tparam T\r\n */\r\ntemplate <class T>\r\nstruct fenwick_tree_raq\
    \ {\r\n    fenwick_tree_raq() = default;\r\n    fenwick_tree_raq(int n) : p(n\
    \ + 1), q(n + 1) {}\r\n\r\n    auto operator[](int i) const { return sum(i + 1)\
    \ - sum(i); }\r\n    auto at(int k) const { return operator[](k); }\r\n\r\n  \
    \  template <class U>\r\n    void build(const std::vector<U> &v) {\r\n       \
    \ for (int i = 0, n = v.size(); i < n; ++i) add(i, v[i]);\r\n    }\r\n\r\n   \
    \ /**\r\n     * @brief v[k] = val\r\n     *\r\n     * @param k index of array\r\
    \n     * @param val new value\r\n     */\r\n    void update(int k, T val) { add(k,\
    \ k + 1, val - at(k)); }\r\n\r\n    /**\r\n     * @brief v[k] += val\r\n     *\r\
    \n     * @param k index of array\r\n     * @param val\r\n     */\r\n    void add(int\
    \ k, T val) { add(k, k + 1, val); }\r\n    /**\r\n     * @brief v[a ... b-1] +=\
    \ val\r\n     *\r\n     * @param a first index of array\r\n     * @param b last\
    \ index of array\r\n     * @param val\r\n     */\r\n    void add(int a, int b,\
    \ T val) {\r\n        p.add(a, -val * a);\r\n        p.add(b, val * b);\r\n  \
    \      q.add(a, val);\r\n        q.add(b, -val);\r\n    }\r\n\r\n    /**\r\n \
    \    * @brief v[0] + ... v[k - 1]\r\n     *\r\n     * @param k index of array\r\
    \n     * @return T\r\n     */\r\n    T sum(int k) const { return p.sum(k) + q.sum(k)\
    \ * k; }\r\n    /**\r\n     * @brief v[a] + ... + v[b - 1]\r\n     *\r\n     *\
    \ @param a first index of array\r\n     * @param b last index of array\r\n   \
    \  * @return T\r\n     */\r\n    T sum(int a, int b) const { return sum(b) - sum(a);\
    \ }\r\n\r\n  private:\r\n    fenwick_tree<T> p, q;\r\n};\r\n"
  dependsOn:
  - lib/binary_tree/fenwick_tree.hpp
  isVerificationFile: false
  path: lib/binary_tree/fenwick_tree_raq.hpp
  requiredBy: []
  timestamp: '2023-11-16 21:07:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/range_query_on_tree_2.test.cpp
  - test/aoj/dsl/raq_rsq.test.cpp
documentation_of: lib/binary_tree/fenwick_tree_raq.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/fenwick_tree_raq.hpp
- /library/lib/binary_tree/fenwick_tree_raq.hpp.html
title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728\uFF08\u533A\u9593\u52A0\u7B97\u3001\u533A\
  \u9593\u7DCF\u548C\uFF09"
---
