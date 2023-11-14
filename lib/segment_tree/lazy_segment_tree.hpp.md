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
    path: test/aoj/dsl/rmq_ruq.test.cpp
    title: test/aoj/dsl/rmq_ruq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/rsq_ruq.test.cpp
    title: test/aoj/dsl/rsq_ruq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/rupc/lazy_segment_tree.test.cpp
    title: test/aoj/rupc/lazy_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_affine_range_sum.test.cpp
    title: test/yosupo/data_structure/range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9045\u5EF6\u8A55\u4FA1\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links:
    - https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: internal/internal_bit.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"internal/internal_bit.hpp\"\r\n#include \"segment_tree/monoid.hpp\"\
    \r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u9045\u5EF6\u8A55\
    \u4FA1\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\r\n * @see https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp\r\
    \n *\r\n * @tparam S \u30E2\u30CE\u30A4\u30C9\r\n * @tparam F \u30E2\u30CE\u30A4\
    \u30C9\r\n */\r\ntemplate <class S, class F>\r\nstruct lazy_segment_tree {\r\n\
    \  private:\r\n    using T = typename S::value_type;\r\n    using U = typename\
    \ F::value_type;\r\n\r\n  public:\r\n    lazy_segment_tree() : lazy_segment_tree(0)\
    \ {}\r\n    explicit lazy_segment_tree(int n, T e = S::id) : lazy_segment_tree(std::vector<T>(n,\
    \ e)) {}\r\n    explicit lazy_segment_tree(const std::vector<T> &v) : _n(int(v.size()))\
    \ {\r\n        _size = internal::bit_ceil(_n);\r\n        _log = internal::countr_zero(_size);\r\
    \n        data = std::vector<T>(2 * _size, S::id);\r\n        lazy = std::vector<U>(_size,\
    \ F::id);\r\n        for (int i = 0; i < _n; i++) data[_size + i] = v[i];\r\n\
    \        for (int i = _size - 1; i >= 1; --i) update(i);\r\n    }\r\n\r\n    void\
    \ set(int p, T x) {\r\n        assert(0 <= p && p < _n);\r\n        p += _size;\r\
    \n        for (int i = _log; i >= 1; --i) push(p >> i);\r\n        data[p] = x;\r\
    \n        for (int i = 1; i <= _log; ++i) update(p >> i);\r\n    }\r\n\r\n   \
    \ T at(int p) { return get(p); }\r\n    T get(int p) {\r\n        assert(0 <=\
    \ p && p < _n);\r\n        p += _size;\r\n        for (int i = _log; i >= 1; --i)\
    \ push(p >> i);\r\n        return data[p];\r\n    }\r\n\r\n    void apply(int\
    \ p, U f) {\r\n        assert(0 <= p && p < _n);\r\n        p += _size;\r\n  \
    \      for (int i = _log; i >= 1; --i) push(p >> i);\r\n        data[p] = F::f(f,\
    \ data[p]);\r\n        for (int i = 1; i <= _log; ++i) update(p >> i);\r\n   \
    \ }\r\n    void apply(int l, int r, U f) {\r\n        assert(0 <= l && l <= r\
    \ && r <= _n);\r\n        if (l == r) return;\r\n\r\n        l += _size, r +=\
    \ _size;\r\n\r\n        for (int i = _log; i >= 1; --i) {\r\n            if (((l\
    \ >> i) << i) != l) push(l >> i);\r\n            if (((r >> i) << i) != r) push((r\
    \ - 1) >> i);\r\n        }\r\n\r\n        int l2 = l, r2 = r;\r\n        while\
    \ (l < r) {\r\n            if (l & 1) all_apply(l++, f);\r\n            if (r\
    \ & 1) all_apply(--r, f);\r\n            l >>= 1, r >>= 1;\r\n        }\r\n  \
    \      l = l2, r = r2;\r\n\r\n        for (int i = 1; i <= _log; i++) {\r\n  \
    \          if (((l >> i) << i) != l) update(l >> i);\r\n            if (((r >>\
    \ i) << i) != r) update((r - 1) >> i);\r\n        }\r\n    }\r\n\r\n    T prod(int\
    \ l, int r) {\r\n        assert(0 <= l && l <= r && r <= _n);\r\n        if (l\
    \ == r) return S::id;\r\n\r\n        l += _size, r += _size;\r\n\r\n        for\
    \ (int i = _log; i >= 1; --i) {\r\n            if (((l >> i) << i) != l) push(l\
    \ >> i);\r\n            if (((r >> i) << i) != r) push((r - 1) >> i);\r\n    \
    \    }\r\n\r\n        T sml = S::id, smr = S::id;\r\n        while (l < r) {\r\
    \n            if (l & 1) sml = S::op(sml, data[l++]);\r\n            if (r & 1)\
    \ smr = S::op(data[--r], smr);\r\n            l >>= 1, r >>= 1;\r\n        }\r\
    \n\r\n        return S::op(sml, smr);\r\n    }\r\n\r\n    T all_prod() const {\
    \ return data[1]; }\r\n\r\n  private:\r\n    int _n, _size, _log;\r\n    std::vector<T>\
    \ data;\r\n    std::vector<U> lazy;\r\n\r\n    void update(int k) { data[k] =\
    \ S::op(data[2 * k], data[2 * k + 1]); }\r\n    void all_apply(int k, U f) {\r\
    \n        data[k] = F::f(f, data[k]);\r\n        if (k < _size) lazy[k] = F::op(f,\
    \ lazy[k]);\r\n    }\r\n    void push(int k) {\r\n        all_apply(2 * k, lazy[k]);\r\
    \n        all_apply(2 * k + 1, lazy[k]);\r\n        lazy[k] = F::id;\r\n    }\r\
    \n};\r\n"
  dependsOn:
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/lazy_segment_tree.hpp
  requiredBy: []
  timestamp: '2023-10-01 20:21:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - test/aoj/dsl/rsq_ruq.test.cpp
  - test/aoj/dsl/rmq_ruq.test.cpp
  - test/aoj/rupc/lazy_segment_tree.test.cpp
documentation_of: lib/segment_tree/lazy_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/lazy_segment_tree.hpp
- /library/lib/segment_tree/lazy_segment_tree.hpp.html
title: "\u9045\u5EF6\u8A55\u4FA1\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
