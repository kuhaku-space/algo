---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/compress.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/BIT.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/inversion_number.test.cpp
    title: test/aoj/alds1/inversion_number.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/compress.hpp:\
    \ line -1: no such header\n"
  code: "#include \"algorithm/compress.hpp\"\n#include \"binary_tree/BIT.hpp\"\n#include\
    \ \"template/template.hpp\"\n\n/**\n * @brief \u8EE2\u5012\u6570\u3092\u6C42\u3081\
    \u308B\n *\n * @tparam T \u914D\u5217\u306E\u65B9\n * @param v \u914D\u5217\n\
    \ * @return int64_t \u8EE2\u5012\u6570\n */\ntemplate <class T>\nint64_t inversion_number(const\
    \ vector<T> &v) {\n    Compress<T> cps(v);\n    BIT<T> bit(cps.size());\n\n  \
    \  int64_t res = 0;\n    for (int i = v.size() - 1; i >= 0; --i) {\n        res\
    \ += bit.sum(cps.get(v[i]));\n        bit.add(cps.get(v[i]), 1);\n    }\n    return\
    \ res;\n}\n"
  dependsOn:
  - lib/algorithm/compress.hpp
  - lib/template/template.hpp
  - lib/binary_tree/BIT.hpp
  isVerificationFile: false
  path: lib/algorithm/inversion_number.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/alds1/inversion_number.test.cpp
documentation_of: lib/algorithm/inversion_number.hpp
layout: document
redirect_from:
- /library/lib/algorithm/inversion_number.hpp
- /library/lib/algorithm/inversion_number.hpp.html
title: "\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B"
---
