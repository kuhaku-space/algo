---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_rmq.2.test.cpp
    title: test/yosupo/data_structure/static_rmq.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Disjoint Sparse Table
    links:
    - https://ei1333.github.io/library/structure/others/disjoint-sparse-table.hpp.html
    - https://noshi91.hatenablog.com/entry/2018/05/08/183946
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: internal/internal_bit.hpp:\
    \ line -1: no such header\n"
  code: "#include <bit>\n#include <cassert>\n#include <vector>\n#include \"internal/internal_bit.hpp\"\
    \n\n/**\n * @brief Disjoint Sparse Table\n * @see https://noshi91.hatenablog.com/entry/2018/05/08/183946\n\
    \ * @see https://ei1333.github.io/library/structure/others/disjoint-sparse-table.hpp.html\n\
    \ *\n * @tparam M\n */\ntemplate <class M>\nstruct disjoint_sparse_table {\n \
    \ private:\n    using T = typename M::value_type;\n\n  public:\n    template <class\
    \ U>\n    disjoint_sparse_table(const std::vector<U> &v) {\n        int b = 1;\n\
    \        while (1 << b < (int)v.size()) ++b;\n        data.resize(b, std::vector<T>(v.size(),\
    \ M::id));\n        for (int i = 0; i < (int)v.size(); i++) data[0][i] = v[i];\n\
    \        for (int i = 1; i < b; i++) {\n            int shift = 1 << i;\n    \
    \        for (int j = 0; j < (int)v.size(); j += shift << 1) {\n             \
    \   int t = std::min(j + shift, (int)v.size());\n                data[i][t - 1]\
    \ = v[t - 1];\n                for (int k = t - 2; k >= j; k--) data[i][k] = M::op(v[k],\
    \ data[i][k + 1]);\n                if ((int)v.size() <= t) break;\n         \
    \       data[i][t] = v[t];\n                int r = std::min(t + shift, (int)v.size());\n\
    \                for (int k = t + 1; k < r; k++) data[i][k] = M::op(data[i][k\
    \ - 1], v[k]);\n            }\n        }\n    }\n\n    T prod(int l, int r) const\
    \ {\n        assert(l <= r);\n        if (l == r) return M::id;\n        if (l\
    \ == --r) return data[0][l];\n        int p = 31 - internal::countl_zero(unsigned(l\
    \ ^ r));\n        return M::op(data[p][l], data[p][r]);\n    }\n\n  private:\n\
    \    std::vector<std::vector<T>> data;\n};\n"
  dependsOn:
  - lib/internal/internal_bit.hpp
  isVerificationFile: false
  path: lib/data_structure/disjoint_sparse_table.hpp
  requiredBy: []
  timestamp: '2024-02-21 23:45:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/static_rmq.2.test.cpp
documentation_of: lib/data_structure/disjoint_sparse_table.hpp
layout: document
redirect_from:
- /library/lib/data_structure/disjoint_sparse_table.hpp
- /library/lib/data_structure/disjoint_sparse_table.hpp.html
title: Disjoint Sparse Table
---
