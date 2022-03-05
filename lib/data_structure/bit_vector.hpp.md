---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/algorithm/wavelet_matrix.hpp
    title: lib/algorithm/wavelet_matrix.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u5B8C\u5099\u8F9E\u66F8"
    links:
    - https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.cpp)
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u5B8C\u5099\u8F9E\u66F8\
    \n *\n * @details\n * [\u53C2\u8003](https://ei1333.github.io/library/structure/wavelet/succinct-indexable-dictionary.cpp)\n\
    \ */\nstruct bit_vector {\n    int length, blocks;\n    vector<unsigned int> bit,\
    \ sum;\n\n    bit_vector() = default;\n    bit_vector(int _length)\n        :\
    \ length(_length),\n          blocks((_length + 31) >> 5),\n          bit((_length\
    \ + 31) >> 5),\n          sum((_length + 31) >> 5) {}\n\n    void set(int k) {\
    \ bit[k >> 5] |= 1U << (k & 31); }\n\n    void build() {\n        sum[0] = 0U;\n\
    \        for (int i = 1; i < blocks; i++) { sum[i] = sum[i - 1] + __builtin_popcount(bit[i\
    \ - 1]); }\n    }\n\n    bool operator[](int k) { return bit[k >> 5] >> (k & 31)\
    \ & 1; }\n\n    int rank(int k) {\n        return sum[k >> 5] + __builtin_popcount(bit[k\
    \ >> 5] & ((1U << (k & 31)) - 1));\n    }\n    int rank(bool val, int k) { return\
    \ val ? rank(k) : k - rank(k); }\n\n    int select(int k) {\n        int sl =\
    \ 0, sr = blocks + 1;\n        while (sr - sl > 1) {\n            int m = (sl\
    \ + sr) >> 2;\n            if (sum[m] < k)\n                sl = m;\n        \
    \    else\n                sr = m;\n        }\n        k -= sum[sl];\n       \
    \ int bl = 0, br = 32;\n        while (br - bl > 1) {\n            int m = (bl\
    \ + br) >> 2;\n            if (__builtin_popcount(bit[sl] & ((1U << m) - 1)) <\
    \ k)\n                bl = m;\n            else\n                br = m;\n   \
    \     }\n        return (sl << 5) + bl;\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/bit_vector.hpp
  requiredBy:
  - lib/algorithm/wavelet_matrix.hpp
  timestamp: '2022-01-09 16:16:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/bit_vector.hpp
layout: document
redirect_from:
- /library/lib/data_structure/bit_vector.hpp
- /library/lib/data_structure/bit_vector.hpp.html
title: "\u5B8C\u5099\u8F9E\u66F8"
---
