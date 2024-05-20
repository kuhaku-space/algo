---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/ruq.test.cpp
    title: test/aoj/dsl/ruq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: internal/internal_bit.hpp:\
    \ line -1: no such header\n"
  code: "#include <cassert>\r\n#include <vector>\r\n#include \"internal/internal_bit.hpp\"\
    \r\n#include \"segment_tree/monoid.hpp\"\r\n\r\n/**\r\n * @brief \u53CC\u5BFE\u30BB\
    \u30B0\u30E1\u30F3\u30C8\u6728\r\n *\r\n * @tparam M \u30E2\u30CE\u30A4\u30C9\r\
    \n */\r\ntemplate <class M>\r\nstruct dual_segment_tree {\r\n  private:\r\n  \
    \  using T = typename M::value_type;\r\n\r\n  public:\r\n    dual_segment_tree()\
    \ : dual_segment_tree(0) {}\r\n    explicit dual_segment_tree(int n, T e = M::id)\
    \ : dual_segment_tree(std::vector<T>(n, e)) {}\r\n    template <class U>\r\n \
    \   explicit dual_segment_tree(const std::vector<U> &v) : _n(v.size()) {\r\n \
    \       _size = internal::bit_ceil(_n);\r\n        _log = internal::countr_zero(_size);\r\
    \n        data = std::vector<T>(_size << 1, M::id);\r\n        for (int i = 0;\
    \ i < _n; ++i) data[_size + i] = T(v[i]);\r\n    }\r\n\r\n    T at(int k) { return\
    \ get(k); }\r\n    T get(int k) {\r\n        assert(0 <= k && k < _n);\r\n   \
    \     k += _size;\r\n        for (int i = _log; i >= 1; --i) push(k >> i);\r\n\
    \        return data[k];\r\n    }\r\n\r\n    void apply(int a, T val) { apply(a,\
    \ a + 1, val); }\r\n    void apply(int a, int b, T val) {\r\n        assert(0\
    \ <= a && a <= _n);\r\n        assert(0 <= b && b <= _n);\r\n        a += _size,\
    \ b += _size;\r\n        for (int i = _log; i >= 1; --i) {\r\n            if (((a\
    \ >> i) << i) != a) push(a >> i);\r\n            if (((b >> i) << i) != b) push((b\
    \ - 1) >> i);\r\n        }\r\n\r\n        for (; a < b; a >>= 1, b >>= 1) {\r\n\
    \            if (a & 1) all_apply(a++, val);\r\n            if (b & 1) all_apply(--b,\
    \ val);\r\n        }\r\n    }\r\n\r\n  private:\r\n    int _n, _size, _log;\r\n\
    \    std::vector<T> data;\r\n\r\n    void all_apply(int k, T val) { data[k] =\
    \ M::op(val, data[k]); }\r\n    void push(int k) {\r\n        all_apply(2 * k,\
    \ data[k]);\r\n        all_apply(2 * k + 1, data[k]);\r\n        data[k] = M::id;\r\
    \n    }\r\n};\r\n"
  dependsOn:
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  isVerificationFile: false
  path: lib/segment_tree/dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2024-05-06 21:20:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dsl/ruq.test.cpp
documentation_of: lib/segment_tree/dual_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/dual_segment_tree.hpp
- /library/lib/segment_tree/dual_segment_tree.hpp.html
title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
