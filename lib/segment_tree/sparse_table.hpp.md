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
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_rmq.test.cpp
    title: test/yosupo/data_structure/static_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/pow.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"math/pow.hpp\"\n#include \"segment_tree/monoid.hpp\"\
    \n#include \"template/template.hpp\"\n\n/**\n * @brief \u30B9\u30D1\u30FC\u30B9\
    \u30C6\u30FC\u30D6\u30EB\n *\n * @tparam M \u30E2\u30CE\u30A4\u30C9\n */\ntemplate\
    \ <class M>\nstruct sparse_table {\n  private:\n    using T = typename M::value_type;\n\
    \n  public:\n    sparse_table(const std::vector<T> &v) : _size(v.size()), lookup(v.size()\
    \ + 1) {\n        int s = v.size();\n        int b = floor_pow2(s) + 1;\n    \
    \    this->data = std::vector<std::vector<T>>(b, std::vector<T>(1 << b));\n  \
    \      for (int i = 0; i < s; ++i) this->data[0][i] = v[i];\n\n        for (int\
    \ i = 1; i < b; ++i) {\n            for (int j = 0; j + (1 << i) <= (1 << b);\
    \ j++) {\n                this->data[i][j] =\n                    M::op(this->data[i\
    \ - 1][j], this->data[i - 1][j + (1 << (i - 1))]);\n            }\n        }\n\
    \n        for (int i = 2; i < s + 1; ++i) this->lookup[i] = this->lookup[i >>\
    \ 1] + 1;\n    }\n\n    T prod(int l, int r) const {\n        assert(0 <= l &&\
    \ l <= r && r <= this->_size);\n        int b = this->lookup[r - l];\n       \
    \ return M::op(this->data[b][l], this->data[b][r - (1 << b)]);\n    }\n\n  private:\n\
    \    int _size;\n    std::vector<int> lookup;\n    std::vector<std::vector<T>>\
    \ data;\n};\n"
  dependsOn:
  - lib/math/pow.hpp
  - lib/template/template.hpp
  - lib/segment_tree/monoid.hpp
  isVerificationFile: false
  path: lib/segment_tree/sparse_table.hpp
  requiredBy: []
  timestamp: '2022-07-19 05:54:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/static_rmq.test.cpp
documentation_of: lib/segment_tree/sparse_table.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/sparse_table.hpp
- /library/lib/segment_tree/sparse_table.hpp.html
title: "\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB"
---
