---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bit_vector.hpp
    title: "\u5B8C\u5099\u8F9E\u66F8"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/rectangle_sum.test.cpp
    title: test/yosupo/data_structure/rectangle_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/bit_vector.hpp:\
    \ line -1: no such header\n"
  code: "#include <cassert>\n#include <numeric>\n#include <tuple>\n#include <vector>\n\
    #include \"data_structure/bit_vector.hpp\"\n\ntemplate <class T, class U = T,\
    \ int L = 30>\nstruct wavelet_matrix_rectangle_sum {\n    wavelet_matrix_rectangle_sum()\
    \ = default;\n    template <class Value>\n    wavelet_matrix_rectangle_sum(const\
    \ std::vector<T> &v, const std::vector<Value> &u)\n        : length(v.size())\
    \ {\n        assert(v.size() == u.size());\n        std::vector<int> l(length),\
    \ r(length), ord(length);\n        std::iota(ord.begin(), ord.end(), 0);\n   \
    \     for (int level = L - 1; level >= 0; level--) {\n            matrix[level]\
    \ = bit_vector(length + 1);\n            int left = 0, right = 0;\n          \
    \  for (int i = 0; i < length; i++) {\n                if ((v[ord[i]] >> level)\
    \ & 1) {\n                    matrix[level].set(i);\n                    r[right++]\
    \ = ord[i];\n                } else {\n                    l[left++] = ord[i];\n\
    \                }\n            }\n            mid[level] = left;\n          \
    \  matrix[level].build();\n            ord.swap(l);\n            for (int i =\
    \ 0; i < right; i++) ord[left + i] = r[i];\n            cs[level].resize(length\
    \ + 1);\n            cs[level][0] = U(0);\n            for (int i = 0; i < length;\
    \ i++) cs[level][i + 1] = cs[level][i] + u[ord[i]];\n        }\n    }\n\n    U\
    \ range_sum(int r, T x) const { return range_sum(0, r, x); }\n\n    U range_sum(int\
    \ l, int r, T x) const {\n        for (int level = L - 1; level >= 0; level--)\n\
    \            std::tie(l, r) = succ((x >> level) & 1, l, r, level);\n        return\
    \ cs[0][matrix[0].rank(false, r)] - cs[0][matrix[0].rank(false, l)];\n    }\n\n\
    \    U rect_sum(int l, int r, T upper) const {\n        U res = 0;\n        for\
    \ (int level = L - 1; level >= 0; level--) {\n            bool f = (upper >> level)\
    \ & 1;\n            if (f)\n                res += cs[level][matrix[level].rank(false,\
    \ r)] -\n                       cs[level][matrix[level].rank(false, l)];\n   \
    \         std::tie(l, r) = succ(f, l, r, level);\n        }\n        return res;\n\
    \    }\n\n    U rect_sum(int l, int r, T lower, T upper) const {\n        return\
    \ rect_sum(l, r, upper) - rect_sum(l, r, lower);\n    }\n\n  private:\n    int\
    \ length;\n    bit_vector matrix[L];\n    int mid[L];\n    std::vector<U> cs[L];\n\
    \n    std::pair<int, int> succ(bool f, int l, int r, int level) const {\n    \
    \    return {matrix[level].rank(f, l) + mid[level] * f,\n                matrix[level].rank(f,\
    \ r) + mid[level] * f};\n    }\n};\n"
  dependsOn:
  - lib/data_structure/bit_vector.hpp
  isVerificationFile: false
  path: lib/data_structure/wavelet_matrix_rectangle_sum.hpp
  requiredBy: []
  timestamp: '2024-02-04 15:22:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/rectangle_sum.test.cpp
documentation_of: lib/data_structure/wavelet_matrix_rectangle_sum.hpp
layout: document
redirect_from:
- /library/lib/data_structure/wavelet_matrix_rectangle_sum.hpp
- /library/lib/data_structure/wavelet_matrix_rectangle_sum.hpp.html
title: lib/data_structure/wavelet_matrix_rectangle_sum.hpp
---
