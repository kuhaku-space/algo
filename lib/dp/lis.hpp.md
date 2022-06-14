---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/longest_increasing_subsequense.test.cpp
    title: test/aoj/dpl/longest_increasing_subsequense.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u6700\u9577\u5897\u52A0\
    \u90E8\u5206\u5217\n *\n * @tparam T \u914D\u5217\u306E\u578B\n * @param v \u914D\
    \u5217\n * @return int \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u9577\u3055\
    \n */\ntemplate <class T>\nint LIS(const std::vector<T> &v) {\n    int n = v.size();\n\
    \    std::vector<T> dp;\n    for (int i = 0; i < n; ++i) {\n        auto it =\
    \ std::lower_bound(dp.begin(), dp.end(), v[i]);\n        if (it == dp.end()) dp.emplace_back(v[i]);\n\
    \        else *it = v[i];\n    }\n    return dp.size();\n}\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/dp/lis.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dpl/longest_increasing_subsequense.test.cpp
documentation_of: lib/dp/lis.hpp
layout: document
redirect_from:
- /library/lib/dp/lis.hpp
- /library/lib/dp/lis.hpp.html
title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
---
