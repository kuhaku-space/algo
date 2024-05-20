---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/range_tree.hpp
    title: "\u9818\u57DF\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree_raq.hpp
    title: lib/segment_tree/segment_tree_raq.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/raq_rmq.test.cpp
    title: test/aoj/dsl/raq_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/rmq.2.test.cpp
    title: test/aoj/dsl/rmq.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/rmq.test.cpp
    title: test/aoj/dsl/rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
    title: test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: internal/internal_bit.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include <cassert>\r\n#include <vector>\r\n#include \"internal/internal_bit.hpp\"\
    \r\n#include \"segment_tree/monoid.hpp\"\r\n\r\n/**\r\n * @brief \u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\r\n * @see https://noshi91.hatenablog.com/entry/2020/04/22/212649\r\
    \n *\r\n * @tparam M \u30E2\u30CE\u30A4\u30C9\r\n */\r\ntemplate <class M>\r\n\
    struct segment_tree {\r\n  private:\r\n    using T = typename M::value_type;\r\
    \n\r\n    struct _segment_tree_reference {\r\n      private:\r\n        segment_tree<M>\
    \ &self;\r\n        int k;\r\n\r\n      public:\r\n        _segment_tree_reference(segment_tree<M>\
    \ &self, int k) : self(self), k(k) {}\r\n        _segment_tree_reference &operator=(const\
    \ T &x) {\r\n            self.set(k, x);\r\n            return *this;\r\n    \
    \    }\r\n        operator T() const { return self.get(k); }\r\n    };\r\n\r\n\
    \  public:\r\n    segment_tree() : segment_tree(0) {}\r\n    explicit segment_tree(int\
    \ n, T e = M::id) : segment_tree(std::vector<T>(n, e)) {}\r\n    template <class\
    \ U>\r\n    explicit segment_tree(const std::vector<U> &v) : _n(v.size()) {\r\n\
    \        _size = internal::bit_ceil(_n);\r\n        _log = internal::countr_zero(_size);\r\
    \n        data = std::vector<T>(_size << 1, M::id);\r\n        for (int i = 0;\
    \ i < _n; ++i) data[_size + i] = T(v[i]);\r\n        for (int i = _size - 1; i\
    \ >= 1; --i) update(i);\r\n    }\r\n\r\n    const T &operator[](int k) const {\
    \ return data[k + _size]; }\r\n    _segment_tree_reference operator[](int k) {\
    \ return _segment_tree_reference(*this, k); }\r\n    T at(int k) const { return\
    \ data[k + _size]; }\r\n    T get(int k) const { return data[k + _size]; }\r\n\
    \r\n    void set(int k, T val) {\r\n        assert(0 <= k && k < _n);\r\n    \
    \    k += _size;\r\n        data[k] = val;\r\n        for (int i = 1; i <= _log;\
    \ ++i) update(k >> i);\r\n    }\r\n    void reset(int k) { set(k, M::id); }\r\n\
    \r\n    T all_prod() const { return data[1]; }\r\n    T prod(int a, int b) const\
    \ {\r\n        assert(0 <= a && b <= _n);\r\n        T l = M::id, r = M::id;\r\
    \n        for (a += _size, b += _size; a < b; a >>= 1, b >>= 1) {\r\n        \
    \    if (a & 1) l = M::op(l, data[a++]);\r\n            if (b & 1) r = M::op(data[--b],\
    \ r);\r\n        }\r\n        return M::op(l, r);\r\n    }\r\n\r\n    template\
    \ <class F>\r\n    int max_right(F f) const {\r\n        return max_right(0, f);\r\
    \n    }\r\n\r\n    template <class F>\r\n    int max_right(int l, F f) const {\r\
    \n        assert(0 <= l && l <= _n);\r\n        assert(f(M::id));\r\n        if\
    \ (l == _n) return _n;\r\n        l += _size;\r\n        T sm = M::id;\r\n   \
    \     do {\r\n            while (l % 2 == 0) l >>= 1;\r\n            if (!f(M::op(sm,\
    \ data[l]))) {\r\n                while (l < _size) {\r\n                    l\
    \ = (2 * l);\r\n                    if (f(M::op(sm, data[l]))) {\r\n         \
    \               sm = M::op(sm, data[l]);\r\n                        l++;\r\n \
    \                   }\r\n                }\r\n                return l - _size;\r\
    \n            }\r\n            sm = M::op(sm, data[l]);\r\n            l++;\r\n\
    \        } while ((l & -l) != l);\r\n        return _n;\r\n    }\r\n\r\n    template\
    \ <class F>\r\n    int min_left(F f) const {\r\n        return min_left(_n, f);\r\
    \n    }\r\n\r\n    template <class F>\r\n    int min_left(int r, F f) const {\r\
    \n        assert(0 <= r && r <= _n);\r\n        assert(f(M::id));\r\n        if\
    \ (r == 0) return 0;\r\n        r += _size;\r\n        T sm = M::id;\r\n     \
    \   do {\r\n            r--;\r\n            while (r > 1 && (r % 2)) r >>= 1;\r\
    \n            if (!f(M::op(data[r], sm))) {\r\n                while (r < _size)\
    \ {\r\n                    r = (2 * r + 1);\r\n                    if (f(M::op(data[r],\
    \ sm))) {\r\n                        sm = M::op(data[r], sm);\r\n            \
    \            r--;\r\n                    }\r\n                }\r\n          \
    \      return r + 1 - _size;\r\n            }\r\n            sm = M::op(data[r],\
    \ sm);\r\n        } while ((r & -r) != r);\r\n        return 0;\r\n    }\r\n\r\
    \n  private:\r\n    int _n, _size, _log;\r\n    std::vector<T> data;\r\n\r\n \
    \   void update(int k) { data[k] = M::op(data[2 * k], data[2 * k + 1]); }\r\n\
    };\r\n"
  dependsOn:
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  isVerificationFile: false
  path: lib/segment_tree/segment_tree.hpp
  requiredBy:
  - lib/binary_tree/range_tree.hpp
  - lib/segment_tree/segment_tree_raq.hpp
  timestamp: '2024-05-06 21:20:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dsl/raq_rmq.test.cpp
  - test/aoj/dsl/rmq.2.test.cpp
  - test/aoj/dsl/rmq.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
  - test/yosupo/data_structure/point_set_range_composite.test.cpp
  - test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
documentation_of: lib/segment_tree/segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/segment_tree.hpp
- /library/lib/segment_tree/segment_tree.hpp.html
title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
