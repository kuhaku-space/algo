---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/pow.hpp
    title: lib/math/pow.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree_raq.hpp
    title: lib/segment_tree/segment_tree_raq.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/raq_rmq.test.cpp
    title: test/aoj/dsl/raq_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/rmq.test.cpp
    title: test/aoj/dsl/rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_set_range_composite.test.cpp
    title: test/yosupo/data_structure/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
    title: test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
    title: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links:
    - https://noshi91.hatenablog.com/entry/2020/04/22/212649
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/pow.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"math/pow.hpp\"\r\n#include \"segment_tree/monoid.hpp\"\
    \r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\r\n * @see https://noshi91.hatenablog.com/entry/2020/04/22/212649\r\
    \n *\r\n * @tparam M \u30E2\u30CE\u30A4\u30C9\r\n */\r\ntemplate <class M>\r\n\
    struct segment_tree {\r\n  private:\r\n    using T = typename M::value_type;\r\
    \n\r\n  public:\r\n    segment_tree() : segment_tree(0) {}\r\n    explicit segment_tree(int\
    \ n, T e = M::id) : segment_tree(std::vector<T>(n, e)) {}\r\n    template <class\
    \ U>\r\n    explicit segment_tree(const std::vector<U> &v) : _n(v.size()) {\r\n\
    \        this->_log = ceil_pow2(this->_n);\r\n        this->_size = 1 << this->_log;\r\
    \n        this->data = std::vector<T>(this->_size << 1, M::id);\r\n        for\
    \ (int i = 0; i < this->_n; ++i) this->data[this->_size + i] = T(v[i]);\r\n  \
    \      for (int i = this->_size - 1; i >= 1; --i) this->update(i);\r\n    }\r\n\
    \r\n    const T &operator[](int k) const { return this->data[k + this->_size];\
    \ }\r\n    T at(int k) const { return this->operator[](k); }\r\n    T get(int\
    \ k) const { return this->operator[](k); }\r\n\r\n    void set(int k, T val) {\r\
    \n        assert(0 <= k && k < this->_n);\r\n        k += this->_size;\r\n   \
    \     this->data[k] = val;\r\n        for (int i = 1; i <= this->_log; ++i) this->update(k\
    \ >> i);\r\n    }\r\n    void reset(int k) { this->set(k, M::id); }\r\n\r\n  \
    \  T all_prod() const { return this->data[1]; }\r\n    T prod(int a, int b) const\
    \ {\r\n        assert(0 <= a && b <= this->_n);\r\n        T l = M::id, r = M::id;\r\
    \n        for (a += this->_size, b += this->_size; a < b; a >>= 1, b >>= 1) {\r\
    \n            if (a & 1) l = M::op(l, this->data[a++]);\r\n            if (b &\
    \ 1) r = M::op(this->data[--b], r);\r\n        }\r\n        return M::op(l, r);\r\
    \n    }\r\n\r\n  private:\r\n    int _n, _size, _log;\r\n    std::vector<T> data;\r\
    \n\r\n    void update(int k) { this->data[k] = M::op(this->data[2 * k], this->data[2\
    \ * k + 1]); }\r\n};\r\n"
  dependsOn:
  - lib/math/pow.hpp
  - lib/template/template.hpp
  - lib/segment_tree/monoid.hpp
  isVerificationFile: false
  path: lib/segment_tree/segment_tree.hpp
  requiredBy:
  - lib/segment_tree/segment_tree_raq.hpp
  timestamp: '2022-07-19 05:54:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dsl/raq_rmq.test.cpp
  - test/aoj/dsl/rmq.test.cpp
  - test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/data_structure/point_set_range_composite.test.cpp
documentation_of: lib/segment_tree/segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/segment_tree.hpp
- /library/lib/segment_tree/segment_tree.hpp.html
title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
