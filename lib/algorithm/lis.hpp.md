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
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/longest_increasing_subsequence.test.cpp
    title: test/yosupo/math/longest_increasing_subsequence.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u6700\u9577\u5897\u52A0\
    \u90E8\u5206\u5217\n *\n * @tparam T \u914D\u5217\u306E\u578B\n * @param v \u914D\
    \u5217\n * @retval int \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u9577\u3055\
    \n */\ntemplate <class T>\nint longest_increasing_subsequence(const std::vector<T>\
    \ &v) {\n    int n = v.size();\n    std::vector<T> dp;\n    for (auto x : v) {\n\
    \        auto it = std::lower_bound(std::begin(dp), std::end(dp), x);\n      \
    \  if (it == std::end(dp)) dp.emplace_back(x);\n        else *it = x;\n    }\n\
    \    return dp.size();\n}\n\n/**\n * @brief \u6700\u9577\u5897\u52A0\u90E8\u5206\
    \u5217\n *\n * @tparam T \u914D\u5217\u306E\u578B\n * @param v \u914D\u5217\n\
    \ * @retval std::vector<int> \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u30A4\
    \u30F3\u30C7\u30C3\u30AF\u30B9\n */\ntemplate <class T>\nstd::vector<int> make_lis(const\
    \ std::vector<T> &v) {\n    int n = v.size();\n    std::vector<T> dp;\n    std::vector<int>\
    \ pos;\n    pos.reserve(n);\n    for (auto x : v) {\n        auto it = std::lower_bound(std::begin(dp),\
    \ std::end(dp), x);\n        pos.emplace_back(std::distance(std::begin(dp), it));\n\
    \        if (it == std::end(dp)) dp.emplace_back(x);\n        else *it = x;\n\
    \    }\n\n    int x = dp.size();\n    std::vector<int> res(x--);\n    for (int\
    \ i = n - 1; i >= 0; --i) {\n        if (pos[i] == x) res[x] = i, --x;\n    }\n\
    \    return res;\n}\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/lis.hpp
  requiredBy: []
  timestamp: '2023-07-23 03:53:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dpl/longest_increasing_subsequense.test.cpp
  - test/yosupo/math/longest_increasing_subsequence.test.cpp
documentation_of: lib/algorithm/lis.hpp
layout: document
redirect_from:
- /library/lib/algorithm/lis.hpp
- /library/lib/algorithm/lis.hpp.html
title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
---
