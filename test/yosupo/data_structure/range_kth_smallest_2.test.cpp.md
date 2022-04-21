---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/compress.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bit_vector.hpp
    title: "\u5B8C\u5099\u8F9E\u66F8"
  - icon: ':heavy_check_mark:'
    path: lib/matrix/compressed_wavelet_matrix.hpp
    title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
  - icon: ':heavy_check_mark:'
    path: lib/matrix/wavelet_matrix.hpp
    title: "\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217"
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: matrix/compressed_wavelet_matrix.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\
    #include \"matrix/compressed_wavelet_matrix.hpp\"\n#include \"template/atcoder.hpp\"\
    \n\nint main(void) {\n    sonic();\n    int n, q;\n    cin >> n >> q;\n    vector<int>\
    \ a(n);\n    cin >> a;\n    wavelet_matrix<int, 30> wm(a);\n\n    while (q--)\
    \ {\n        int l, r, k;\n        cin >> l >> r >> k;\n        co(wm.kth_smallest(l,\
    \ r, k));\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/matrix/compressed_wavelet_matrix.hpp
  - lib/algorithm/compress.hpp
  - lib/template/template.hpp
  - lib/matrix/wavelet_matrix.hpp
  - lib/data_structure/bit_vector.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/range_kth_smallest_2.test.cpp
  requiredBy: []
  timestamp: '2022-04-16 04:10:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/range_kth_smallest_2.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/range_kth_smallest_2.test.cpp
- /verify/test/yosupo/data_structure/range_kth_smallest_2.test.cpp.html
title: test/yosupo/data_structure/range_kth_smallest_2.test.cpp
---
