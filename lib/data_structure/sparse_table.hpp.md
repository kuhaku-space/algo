---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: internal/internal_bit.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"internal/internal_bit.hpp\"\n#include \"segment_tree/monoid.hpp\"\
    \n#include \"template/template.hpp\"\n\n/**\n * @brief \u30B9\u30D1\u30FC\u30B9\
    \u30C6\u30FC\u30D6\u30EB\n *\n * @tparam M \u30E2\u30CE\u30A4\u30C9\n */\ntemplate\
    \ <class M>\nstruct sparse_table {\n  private:\n    using T = typename M::value_type;\n\
    \n  public:\n    sparse_table(const std::vector<T> &v) : _size(v.size()), lookup(v.size()\
    \ + 1), data() {\n        int b = std::max(1, internal::countr_zero(internal::bit_ceil(_size)));\n\
    \        data.emplace_back(v);\n        for (int i = 1; i < b; ++i) data.emplace_back(_size\
    \ + 1 - (1 << i));\n        for (int i = 1; i < b; ++i) {\n            for (int\
    \ j = 0; j + (1 << i) <= _size; ++j) {\n                data[i][j] = M::op(data[i\
    \ - 1][j], data[i - 1][j + (1 << (i - 1))]);\n            }\n        }\n     \
    \   for (int i = 3; i <= _size; ++i) lookup[i] = lookup[(i + 1) >> 1] + 1;\n \
    \   }\n\n    T prod(int l, int r) const {\n        assert(0 <= l && l < r && r\
    \ <= _size);\n        int b = lookup[r - l];\n        return M::op(data[b][l],\
    \ data[b][r - (1 << b)]);\n    }\n\n  private:\n    int _size;\n    std::vector<int>\
    \ lookup;\n    std::vector<std::vector<T>> data;\n};\n"
  dependsOn:
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/sparse_table.hpp
  requiredBy: []
  timestamp: '2023-10-01 20:21:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/static_rmq.test.cpp
documentation_of: lib/data_structure/sparse_table.hpp
layout: document
redirect_from:
- /library/lib/data_structure/sparse_table.hpp
- /library/lib/data_structure/sparse_table.hpp.html
title: "\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB"
---
