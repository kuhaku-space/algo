---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/data_structure/bit_vector.hpp
    title: "\u5B8C\u5099\u8F9E\u66F8"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/bit_vector.hpp:\
    \ line -1: no such header\n"
  code: "#include \"data_structure/bit_vector.hpp\"\n#include \"template/template.hpp\"\
    \n\ntemplate <typename T, int MAXLOG>\nstruct wavelet_matrix {\n    int length;\n\
    \    bit_vector matrix[MAXLOG];\n    int mid[MAXLOG];\n\n    wavelet_matrix()\
    \ = default;\n\n    wavelet_matrix(vector<T> v) : length(v.size()) {\n       \
    \ vector<T> l(length), r(length);\n        for (int level = MAXLOG - 1; level\
    \ >= 0; level--) {\n            matrix[level] = bit_vector(length + 1);\n    \
    \        int left = 0, right = 0;\n            for (int i = 0; i < length; i++)\
    \ {\n                if (v[i] >> level & 1) {\n                    matrix[level].set(i);\n\
    \                    r[right++] = v[i];\n                } else {\n          \
    \          l[left++] = v[i];\n                }\n            }\n            mid[level]\
    \ = left;\n            matrix[level].build();\n            v.swap(l);\n      \
    \      for (int i = 0; i < right; i++) { v[left + i] = r[i]; }\n        }\n  \
    \  }\n\n    pair<int, int> succ(bool f, int l, int r, int level) {\n        return\
    \ {matrix[level].rank(f, l) + mid[level] * f,\n                matrix[level].rank(f,\
    \ r) + mid[level] * f};\n    }\n\n    T access(int k) {\n        T ret = 0;\n\
    \        for (int level = MAXLOG - 1; level >= 0; level--) {\n            bool\
    \ f = matrix[level][k];\n            if (f) ret |= T(1) << level;\n          \
    \  k = matrix[level].rank(f, k) + mid[level] * f;\n        }\n        return ret;\n\
    \    }\n\n    T operator[](const int &k) { return access(k); }\n\n    int rank(const\
    \ T &x, int r) {\n        int l = 0;\n        for (int level = MAXLOG - 1; level\
    \ >= 0; level--) {\n            tie(l, r) = succ((x >> level) & 1, l, r, level);\n\
    \        }\n        return r - l;\n    }\n\n    T kth_smallest(int l, int r, int\
    \ k) {\n        assert(0 <= k && k < r - l);\n        T ret = 0;\n        for\
    \ (int level = MAXLOG - 1; level >= 0; level--) {\n            int cnt = matrix[level].rank(false,\
    \ r) - matrix[level].rank(false, l);\n            bool f = cnt <= k;\n       \
    \     if (f) {\n                ret |= T(1) << level;\n                k -= cnt;\n\
    \            }\n            tie(l, r) = succ(f, l, r, level);\n        }\n   \
    \     return ret;\n    }\n\n    T kth_largest(int l, int r, int k) { return kth_smallest(l,\
    \ r, r - l - k - 1); }\n\n    int range_freq(int l, int r, T upper) {\n      \
    \  int ret = 0;\n        for (int level = MAXLOG - 1; level >= 0; level--) {\n\
    \            bool f = ((upper >> level) & 1);\n            if (f) ret += matrix[level].rank(false,\
    \ r) - matrix[level].rank(false, l);\n            tie(l, r) = succ(f, l, r, level);\n\
    \        }\n        return ret;\n    }\n\n    int range_freq(int l, int r, T lower,\
    \ T upper) {\n        return range_freq(l, r, upper) - range_freq(l, r, lower);\n\
    \    }\n\n    T prev_value(int l, int r, T upper) {\n        int cnt = range_freq(l,\
    \ r, upper);\n        return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);\n\
    \    }\n\n    T next_value(int l, int r, T lower) {\n        int cnt = range_freq(l,\
    \ r, lower);\n        return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);\n\
    \    }\n};\n"
  dependsOn:
  - lib/data_structure/bit_vector.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/wavelet_matrix.hpp
  requiredBy: []
  timestamp: '2021-10-01 05:33:08+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/wavelet_matrix.hpp
layout: document
redirect_from:
- /library/lib/algorithm/wavelet_matrix.hpp
- /library/lib/algorithm/wavelet_matrix.hpp.html
title: lib/algorithm/wavelet_matrix.hpp
---
