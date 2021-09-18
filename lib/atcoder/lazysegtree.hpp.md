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
  bundledCode: "#line 1 \"lib/atcoder/lazysegtree.hpp\"\n\n\n\r\n#include <algorithm>\r\
    \n#include <atcoder/internal_bit>\r\n#include <cassert>\r\n#include <iostream>\r\
    \n#include <vector>\r\nnamespace atcoder {\r\n\r\ntemplate <class S,\r\n     \
    \     S (*op)(S, S),\r\n          S (*e)(),\r\n          class F,\r\n        \
    \  S (*mapping)(F, S),\r\n          F (*composition)(F, F),\r\n          F (*id)()>\r\
    \nstruct lazy_segtree {\r\n  public:\r\n    lazy_segtree() : lazy_segtree(0) {}\r\
    \n    lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}\r\n    lazy_segtree(const\
    \ std::vector<S>& v) : _n(int(v.size())) {\r\n        log = internal::ceil_pow2(_n);\r\
    \n        size = 1 << log;\r\n        d = std::vector<S>(2 * size, e());\r\n \
    \       lz = std::vector<F>(size, id());\r\n        for (int i = 0; i < _n; i++)\
    \ d[size + i] = v[i];\r\n        for (int i = size - 1; i >= 1; i--) {\r\n   \
    \         update(i);\r\n        }\r\n    }\r\n\r\n    void set(int p, S x) {\r\
    \n        assert(0 <= p && p < _n);\r\n        p += size;\r\n        for (int\
    \ i = log; i >= 1; i--) push(p >> i);\r\n        d[p] = x;\r\n        for (int\
    \ i = 1; i <= log; i++) update(p >> i);\r\n    }\r\n\r\n    S get(int p) {\r\n\
    \        assert(0 <= p && p < _n);\r\n        p += size;\r\n        for (int i\
    \ = log; i >= 1; i--) push(p >> i);\r\n        return d[p];\r\n    }\r\n\r\n \
    \   S prod(int l, int r) {\r\n        assert(0 <= l && l <= r && r <= _n);\r\n\
    \        if (l == r) return e();\r\n\r\n        l += size;\r\n        r += size;\r\
    \n\r\n        for (int i = log; i >= 1; i--) {\r\n            if (((l >> i) <<\
    \ i) != l) push(l >> i);\r\n            if (((r >> i) << i) != r) push(r >> i);\r\
    \n        }\r\n\r\n        S sml = e(), smr = e();\r\n        while (l < r) {\r\
    \n            if (l & 1) sml = op(sml, d[l++]);\r\n            if (r & 1) smr\
    \ = op(d[--r], smr);\r\n            l >>= 1;\r\n            r >>= 1;\r\n     \
    \   }\r\n\r\n        return op(sml, smr);\r\n    }\r\n\r\n    S all_prod() { return\
    \ d[1]; }\r\n\r\n    void apply(int p, F f) {\r\n        assert(0 <= p && p <\
    \ _n);\r\n        p += size;\r\n        for (int i = log; i >= 1; i--) push(p\
    \ >> i);\r\n        d[p] = mapping(f, d[p]);\r\n        for (int i = 1; i <= log;\
    \ i++) update(p >> i);\r\n    }\r\n    void apply(int l, int r, F f) {\r\n   \
    \     assert(0 <= l && l <= r && r <= _n);\r\n        if (l == r) return;\r\n\r\
    \n        l += size;\r\n        r += size;\r\n\r\n        for (int i = log; i\
    \ >= 1; i--) {\r\n            if (((l >> i) << i) != l) push(l >> i);\r\n    \
    \        if (((r >> i) << i) != r) push((r - 1) >> i);\r\n        }\r\n\r\n  \
    \      {\r\n            int l2 = l, r2 = r;\r\n            while (l < r) {\r\n\
    \                if (l & 1) all_apply(l++, f);\r\n                if (r & 1) all_apply(--r,\
    \ f);\r\n                l >>= 1;\r\n                r >>= 1;\r\n            }\r\
    \n            l = l2;\r\n            r = r2;\r\n        }\r\n\r\n        for (int\
    \ i = 1; i <= log; i++) {\r\n            if (((l >> i) << i) != l) update(l >>\
    \ i);\r\n            if (((r >> i) << i) != r) update((r - 1) >> i);\r\n     \
    \   }\r\n    }\r\n\r\n    template <bool (*g)(S)> int max_right(int l) {\r\n \
    \       return max_right(l, [](S x) { return g(x); });\r\n    }\r\n    template\
    \ <class G> int max_right(int l, G g) {\r\n        assert(0 <= l && l <= _n);\r\
    \n        assert(g(e()));\r\n        if (l == _n) return _n;\r\n        l += size;\r\
    \n        for (int i = log; i >= 1; i--) push(l >> i);\r\n        S sm = e();\r\
    \n        do {\r\n            while (l % 2 == 0) l >>= 1;\r\n            if (!g(op(sm,\
    \ d[l]))) {\r\n                while (l < size) {\r\n                    push(l);\r\
    \n                    l = (2 * l);\r\n                    if (g(op(sm, d[l])))\
    \ {\r\n                        sm = op(sm, d[l]);\r\n                        l++;\r\
    \n                    }\r\n                }\r\n                return l - size;\r\
    \n            }\r\n            sm = op(sm, d[l]);\r\n            l++;\r\n    \
    \    } while ((l & -l) != l);\r\n        return _n;\r\n    }\r\n\r\n    template\
    \ <bool (*g)(S)> int min_left(int r) {\r\n        return min_left(r, [](S x) {\
    \ return g(x); });\r\n    }\r\n    template <class G> int min_left(int r, G g)\
    \ {\r\n        assert(0 <= r && r <= _n);\r\n        assert(g(e()));\r\n     \
    \   if (r == 0) return 0;\r\n        r += size;\r\n        for (int i = log; i\
    \ >= 1; i--) push((r - 1) >> i);\r\n        S sm = e();\r\n        do {\r\n  \
    \          r--;\r\n            while (r > 1 && (r % 2)) r >>= 1;\r\n         \
    \   if (!g(op(d[r], sm))) {\r\n                while (r < size) {\r\n        \
    \            push(r);\r\n                    r = (2 * r + 1);\r\n            \
    \        if (g(op(d[r], sm))) {\r\n                        sm = op(d[r], sm);\r\
    \n                        r--;\r\n                    }\r\n                }\r\
    \n                return r + 1 - size;\r\n            }\r\n            sm = op(d[r],\
    \ sm);\r\n        } while ((r & -r) != r);\r\n        return 0;\r\n    }\r\n\r\
    \n  private:\r\n    int _n, size, log;\r\n    std::vector<S> d;\r\n    std::vector<F>\
    \ lz;\r\n\r\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\r\n\
    \    void all_apply(int k, F f) {\r\n        d[k] = mapping(f, d[k]);\r\n    \
    \    if (k < size) lz[k] = composition(f, lz[k]);\r\n    }\r\n    void push(int\
    \ k) {\r\n        all_apply(2 * k, lz[k]);\r\n        all_apply(2 * k + 1, lz[k]);\r\
    \n        lz[k] = id();\r\n    }\r\n};\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_LAZYSEGTREE_HPP\r\n#define ATCODER_LAZYSEGTREE_HPP 1\r\n\r\
    \n#include <algorithm>\r\n#include <atcoder/internal_bit>\r\n#include <cassert>\r\
    \n#include <iostream>\r\n#include <vector>\r\nnamespace atcoder {\r\n\r\ntemplate\
    \ <class S,\r\n          S (*op)(S, S),\r\n          S (*e)(),\r\n          class\
    \ F,\r\n          S (*mapping)(F, S),\r\n          F (*composition)(F, F),\r\n\
    \          F (*id)()>\r\nstruct lazy_segtree {\r\n  public:\r\n    lazy_segtree()\
    \ : lazy_segtree(0) {}\r\n    lazy_segtree(int n) : lazy_segtree(std::vector<S>(n,\
    \ e())) {}\r\n    lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {\r\
    \n        log = internal::ceil_pow2(_n);\r\n        size = 1 << log;\r\n     \
    \   d = std::vector<S>(2 * size, e());\r\n        lz = std::vector<F>(size, id());\r\
    \n        for (int i = 0; i < _n; i++) d[size + i] = v[i];\r\n        for (int\
    \ i = size - 1; i >= 1; i--) {\r\n            update(i);\r\n        }\r\n    }\r\
    \n\r\n    void set(int p, S x) {\r\n        assert(0 <= p && p < _n);\r\n    \
    \    p += size;\r\n        for (int i = log; i >= 1; i--) push(p >> i);\r\n  \
    \      d[p] = x;\r\n        for (int i = 1; i <= log; i++) update(p >> i);\r\n\
    \    }\r\n\r\n    S get(int p) {\r\n        assert(0 <= p && p < _n);\r\n    \
    \    p += size;\r\n        for (int i = log; i >= 1; i--) push(p >> i);\r\n  \
    \      return d[p];\r\n    }\r\n\r\n    S prod(int l, int r) {\r\n        assert(0\
    \ <= l && l <= r && r <= _n);\r\n        if (l == r) return e();\r\n\r\n     \
    \   l += size;\r\n        r += size;\r\n\r\n        for (int i = log; i >= 1;\
    \ i--) {\r\n            if (((l >> i) << i) != l) push(l >> i);\r\n          \
    \  if (((r >> i) << i) != r) push(r >> i);\r\n        }\r\n\r\n        S sml =\
    \ e(), smr = e();\r\n        while (l < r) {\r\n            if (l & 1) sml = op(sml,\
    \ d[l++]);\r\n            if (r & 1) smr = op(d[--r], smr);\r\n            l >>=\
    \ 1;\r\n            r >>= 1;\r\n        }\r\n\r\n        return op(sml, smr);\r\
    \n    }\r\n\r\n    S all_prod() { return d[1]; }\r\n\r\n    void apply(int p,\
    \ F f) {\r\n        assert(0 <= p && p < _n);\r\n        p += size;\r\n      \
    \  for (int i = log; i >= 1; i--) push(p >> i);\r\n        d[p] = mapping(f, d[p]);\r\
    \n        for (int i = 1; i <= log; i++) update(p >> i);\r\n    }\r\n    void\
    \ apply(int l, int r, F f) {\r\n        assert(0 <= l && l <= r && r <= _n);\r\
    \n        if (l == r) return;\r\n\r\n        l += size;\r\n        r += size;\r\
    \n\r\n        for (int i = log; i >= 1; i--) {\r\n            if (((l >> i) <<\
    \ i) != l) push(l >> i);\r\n            if (((r >> i) << i) != r) push((r - 1)\
    \ >> i);\r\n        }\r\n\r\n        {\r\n            int l2 = l, r2 = r;\r\n\
    \            while (l < r) {\r\n                if (l & 1) all_apply(l++, f);\r\
    \n                if (r & 1) all_apply(--r, f);\r\n                l >>= 1;\r\n\
    \                r >>= 1;\r\n            }\r\n            l = l2;\r\n        \
    \    r = r2;\r\n        }\r\n\r\n        for (int i = 1; i <= log; i++) {\r\n\
    \            if (((l >> i) << i) != l) update(l >> i);\r\n            if (((r\
    \ >> i) << i) != r) update((r - 1) >> i);\r\n        }\r\n    }\r\n\r\n    template\
    \ <bool (*g)(S)> int max_right(int l) {\r\n        return max_right(l, [](S x)\
    \ { return g(x); });\r\n    }\r\n    template <class G> int max_right(int l, G\
    \ g) {\r\n        assert(0 <= l && l <= _n);\r\n        assert(g(e()));\r\n  \
    \      if (l == _n) return _n;\r\n        l += size;\r\n        for (int i = log;\
    \ i >= 1; i--) push(l >> i);\r\n        S sm = e();\r\n        do {\r\n      \
    \      while (l % 2 == 0) l >>= 1;\r\n            if (!g(op(sm, d[l]))) {\r\n\
    \                while (l < size) {\r\n                    push(l);\r\n      \
    \              l = (2 * l);\r\n                    if (g(op(sm, d[l]))) {\r\n\
    \                        sm = op(sm, d[l]);\r\n                        l++;\r\n\
    \                    }\r\n                }\r\n                return l - size;\r\
    \n            }\r\n            sm = op(sm, d[l]);\r\n            l++;\r\n    \
    \    } while ((l & -l) != l);\r\n        return _n;\r\n    }\r\n\r\n    template\
    \ <bool (*g)(S)> int min_left(int r) {\r\n        return min_left(r, [](S x) {\
    \ return g(x); });\r\n    }\r\n    template <class G> int min_left(int r, G g)\
    \ {\r\n        assert(0 <= r && r <= _n);\r\n        assert(g(e()));\r\n     \
    \   if (r == 0) return 0;\r\n        r += size;\r\n        for (int i = log; i\
    \ >= 1; i--) push((r - 1) >> i);\r\n        S sm = e();\r\n        do {\r\n  \
    \          r--;\r\n            while (r > 1 && (r % 2)) r >>= 1;\r\n         \
    \   if (!g(op(d[r], sm))) {\r\n                while (r < size) {\r\n        \
    \            push(r);\r\n                    r = (2 * r + 1);\r\n            \
    \        if (g(op(d[r], sm))) {\r\n                        sm = op(d[r], sm);\r\
    \n                        r--;\r\n                    }\r\n                }\r\
    \n                return r + 1 - size;\r\n            }\r\n            sm = op(d[r],\
    \ sm);\r\n        } while ((r & -r) != r);\r\n        return 0;\r\n    }\r\n\r\
    \n  private:\r\n    int _n, size, log;\r\n    std::vector<S> d;\r\n    std::vector<F>\
    \ lz;\r\n\r\n    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }\r\n\
    \    void all_apply(int k, F f) {\r\n        d[k] = mapping(f, d[k]);\r\n    \
    \    if (k < size) lz[k] = composition(f, lz[k]);\r\n    }\r\n    void push(int\
    \ k) {\r\n        all_apply(2 * k, lz[k]);\r\n        all_apply(2 * k + 1, lz[k]);\r\
    \n        lz[k] = id();\r\n    }\r\n};\r\n\r\n}  // namespace atcoder\r\n\r\n\
    #endif  // ATCODER_LAZYSEGTREE_HPP\r\n"
  dependsOn:
  - lib/atcoder/internal_bit.hpp
  isVerificationFile: false
  path: lib/atcoder/lazysegtree.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/lazysegtree.hpp
layout: document
redirect_from:
- /library/lib/atcoder/lazysegtree.hpp
- /library/lib/atcoder/lazysegtree.hpp.html
title: lib/atcoder/lazysegtree.hpp
---
