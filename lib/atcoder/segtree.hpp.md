---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/atcoder/internal_bit.hpp
    title: lib/atcoder/internal_bit.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/segtree.hpp\"\n\n\n\r\n#include <algorithm>\r\
    \n#include <atcoder/internal_bit>\r\n#include <cassert>\r\n#include <vector>\r\
    \n\r\nnamespace atcoder {\r\n\r\ntemplate <class S, S (*op)(S, S), S (*e)()> struct\
    \ segtree {\r\n  public:\r\n    segtree() : segtree(0) {}\r\n    segtree(int n)\
    \ : segtree(std::vector<S>(n, e())) {}\r\n    segtree(const std::vector<S>& v)\
    \ : _n(int(v.size())) {\r\n        log = internal::ceil_pow2(_n);\r\n        size\
    \ = 1 << log;\r\n        d = std::vector<S>(2 * size, e());\r\n        for (int\
    \ i = 0; i < _n; i++) d[size + i] = v[i];\r\n        for (int i = size - 1; i\
    \ >= 1; i--) {\r\n            update(i);\r\n        }\r\n    }\r\n\r\n    void\
    \ set(int p, S x) {\r\n        assert(0 <= p && p < _n);\r\n        p += size;\r\
    \n        d[p] = x;\r\n        for (int i = 1; i <= log; i++) update(p >> i);\r\
    \n    }\r\n\r\n    S get(int p) {\r\n        assert(0 <= p && p < _n);\r\n   \
    \     return d[p + size];\r\n    }\r\n\r\n    S prod(int l, int r) {\r\n     \
    \   assert(0 <= l && l <= r && r <= _n);\r\n        S sml = e(), smr = e();\r\n\
    \        l += size;\r\n        r += size;\r\n\r\n        while (l < r) {\r\n \
    \           if (l & 1) sml = op(sml, d[l++]);\r\n            if (r & 1) smr =\
    \ op(d[--r], smr);\r\n            l >>= 1;\r\n            r >>= 1;\r\n       \
    \ }\r\n        return op(sml, smr);\r\n    }\r\n\r\n    S all_prod() { return\
    \ d[1]; }\r\n\r\n    template <bool (*f)(S)> int max_right(int l) {\r\n      \
    \  return max_right(l, [](S x) { return f(x); });\r\n    }\r\n    template <class\
    \ F> int max_right(int l, F f) {\r\n        assert(0 <= l && l <= _n);\r\n   \
    \     assert(f(e()));\r\n        if (l == _n) return _n;\r\n        l += size;\r\
    \n        S sm = e();\r\n        do {\r\n            while (l % 2 == 0) l >>=\
    \ 1;\r\n            if (!f(op(sm, d[l]))) {\r\n                while (l < size)\
    \ {\r\n                    l = (2 * l);\r\n                    if (f(op(sm, d[l])))\
    \ {\r\n                        sm = op(sm, d[l]);\r\n                        l++;\r\
    \n                    }\r\n                }\r\n                return l - size;\r\
    \n            }\r\n            sm = op(sm, d[l]);\r\n            l++;\r\n    \
    \    } while ((l & -l) != l);\r\n        return _n;\r\n    }\r\n\r\n    template\
    \ <bool (*f)(S)> int min_left(int r) {\r\n        return min_left(r, [](S x) {\
    \ return f(x); });\r\n    }\r\n    template <class F> int min_left(int r, F f)\
    \ {\r\n        assert(0 <= r && r <= _n);\r\n        assert(f(e()));\r\n     \
    \   if (r == 0) return 0;\r\n        r += size;\r\n        S sm = e();\r\n   \
    \     do {\r\n            r--;\r\n            while (r > 1 && (r % 2)) r >>= 1;\r\
    \n            if (!f(op(d[r], sm))) {\r\n                while (r < size) {\r\n\
    \                    r = (2 * r + 1);\r\n                    if (f(op(d[r], sm)))\
    \ {\r\n                        sm = op(d[r], sm);\r\n                        r--;\r\
    \n                    }\r\n                }\r\n                return r + 1 -\
    \ size;\r\n            }\r\n            sm = op(d[r], sm);\r\n        } while\
    \ ((r & -r) != r);\r\n        return 0;\r\n    }\r\n\r\n  private:\r\n    int\
    \ _n, size, log;\r\n    std::vector<S> d;\r\n\r\n    void update(int k) { d[k]\
    \ = op(d[2 * k], d[2 * k + 1]); }\r\n};\r\n\r\n}  // namespace atcoder\r\n\r\n\
    \n"
  code: "#ifndef ATCODER_SEGTREE_HPP\r\n#define ATCODER_SEGTREE_HPP 1\r\n\r\n#include\
    \ <algorithm>\r\n#include <atcoder/internal_bit>\r\n#include <cassert>\r\n#include\
    \ <vector>\r\n\r\nnamespace atcoder {\r\n\r\ntemplate <class S, S (*op)(S, S),\
    \ S (*e)()> struct segtree {\r\n  public:\r\n    segtree() : segtree(0) {}\r\n\
    \    segtree(int n) : segtree(std::vector<S>(n, e())) {}\r\n    segtree(const\
    \ std::vector<S>& v) : _n(int(v.size())) {\r\n        log = internal::ceil_pow2(_n);\r\
    \n        size = 1 << log;\r\n        d = std::vector<S>(2 * size, e());\r\n \
    \       for (int i = 0; i < _n; i++) d[size + i] = v[i];\r\n        for (int i\
    \ = size - 1; i >= 1; i--) {\r\n            update(i);\r\n        }\r\n    }\r\
    \n\r\n    void set(int p, S x) {\r\n        assert(0 <= p && p < _n);\r\n    \
    \    p += size;\r\n        d[p] = x;\r\n        for (int i = 1; i <= log; i++)\
    \ update(p >> i);\r\n    }\r\n\r\n    S get(int p) {\r\n        assert(0 <= p\
    \ && p < _n);\r\n        return d[p + size];\r\n    }\r\n\r\n    S prod(int l,\
    \ int r) {\r\n        assert(0 <= l && l <= r && r <= _n);\r\n        S sml =\
    \ e(), smr = e();\r\n        l += size;\r\n        r += size;\r\n\r\n        while\
    \ (l < r) {\r\n            if (l & 1) sml = op(sml, d[l++]);\r\n            if\
    \ (r & 1) smr = op(d[--r], smr);\r\n            l >>= 1;\r\n            r >>=\
    \ 1;\r\n        }\r\n        return op(sml, smr);\r\n    }\r\n\r\n    S all_prod()\
    \ { return d[1]; }\r\n\r\n    template <bool (*f)(S)> int max_right(int l) {\r\
    \n        return max_right(l, [](S x) { return f(x); });\r\n    }\r\n    template\
    \ <class F> int max_right(int l, F f) {\r\n        assert(0 <= l && l <= _n);\r\
    \n        assert(f(e()));\r\n        if (l == _n) return _n;\r\n        l += size;\r\
    \n        S sm = e();\r\n        do {\r\n            while (l % 2 == 0) l >>=\
    \ 1;\r\n            if (!f(op(sm, d[l]))) {\r\n                while (l < size)\
    \ {\r\n                    l = (2 * l);\r\n                    if (f(op(sm, d[l])))\
    \ {\r\n                        sm = op(sm, d[l]);\r\n                        l++;\r\
    \n                    }\r\n                }\r\n                return l - size;\r\
    \n            }\r\n            sm = op(sm, d[l]);\r\n            l++;\r\n    \
    \    } while ((l & -l) != l);\r\n        return _n;\r\n    }\r\n\r\n    template\
    \ <bool (*f)(S)> int min_left(int r) {\r\n        return min_left(r, [](S x) {\
    \ return f(x); });\r\n    }\r\n    template <class F> int min_left(int r, F f)\
    \ {\r\n        assert(0 <= r && r <= _n);\r\n        assert(f(e()));\r\n     \
    \   if (r == 0) return 0;\r\n        r += size;\r\n        S sm = e();\r\n   \
    \     do {\r\n            r--;\r\n            while (r > 1 && (r % 2)) r >>= 1;\r\
    \n            if (!f(op(d[r], sm))) {\r\n                while (r < size) {\r\n\
    \                    r = (2 * r + 1);\r\n                    if (f(op(d[r], sm)))\
    \ {\r\n                        sm = op(d[r], sm);\r\n                        r--;\r\
    \n                    }\r\n                }\r\n                return r + 1 -\
    \ size;\r\n            }\r\n            sm = op(d[r], sm);\r\n        } while\
    \ ((r & -r) != r);\r\n        return 0;\r\n    }\r\n\r\n  private:\r\n    int\
    \ _n, size, log;\r\n    std::vector<S> d;\r\n\r\n    void update(int k) { d[k]\
    \ = op(d[2 * k], d[2 * k + 1]); }\r\n};\r\n\r\n}  // namespace atcoder\r\n\r\n\
    #endif  // ATCODER_SEGTREE_HPP\r\n"
  dependsOn:
  - lib/atcoder/internal_bit.hpp
  isVerificationFile: false
  path: lib/atcoder/segtree.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/segtree.hpp
layout: document
redirect_from:
- /library/lib/atcoder/segtree.hpp
- /library/lib/atcoder/segtree.hpp.html
title: lib/atcoder/segtree.hpp
---
