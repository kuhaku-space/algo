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
    path: test/yosupo/new/longest_increasing_subsequence.test.cpp
    title: test/yosupo/new/longest_increasing_subsequence.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u6700\u9577\u5897\u52A0\
    \u90E8\u5206\u5217\n *\n * @tparam T \u914D\u5217\u306E\u578B\n * @param v \u914D\
    \u5217\n * @retval int \u6700\u9577\u5897\u52A0\u90E8\u5206\u5217\u306E\u9577\u3055\
    \n */\ntemplate <class T>\nint LIS(const std::vector<T> &v) {\n    int n = v.size();\n\
    \    std::vector<T> dp;\n    for (auto x : v) {\n        auto it = std::lower_bound(dp.begin(),\
    \ dp.end(), x);\n        if (it == dp.end()) dp.emplace_back(x);\n        else\
    \ *it = x;\n    }\n    return dp.size();\n}\n\n/**\n * @brief \u6700\u9577\u5897\
    \u52A0\u90E8\u5206\u5217\n *\n * @tparam T \u914D\u5217\u306E\u578B\n * @param\
    \ v \u914D\u5217\n * @retval std::vector<int> \u6700\u9577\u5897\u52A0\u90E8\u5206\
    \u5217\u306E\u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\n */\ntemplate <class T>\nstd::vector<int>\
    \ make_LIS(const std::vector<T> &v) {\n    int n = v.size();\n    std::vector<std::pair<T,\
    \ int>> dp;\n    std::vector<int> pr(n, -1);\n    for (int i = 0; i < n; ++i)\
    \ {\n        std::pair<T, int> p(v[i], -i);\n        auto it = std::lower_bound(dp.begin(),\
    \ dp.end(), p);\n        if (it != dp.begin()) pr[i] = -std::prev(it)->second;\n\
    \        if (it == dp.end()) dp.emplace_back(p);\n        else *it = p;\n    }\n\
    \n    std::vector<int> res;\n    for (int x = -dp.back().second; x != -1; x =\
    \ pr[x]) {\n        res.emplace_back(x);\n    }\n    std::reverse(res.begin(),\
    \ res.end());\n    return res;\n}\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/lis.hpp
  requiredBy: []
  timestamp: '2022-07-29 05:36:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/new/longest_increasing_subsequence.test.cpp
  - test/aoj/dpl/longest_increasing_subsequense.test.cpp
documentation_of: lib/algorithm/lis.hpp
layout: document
redirect_from:
- /library/lib/algorithm/lis.hpp
- /library/lib/algorithm/lis.hpp.html
title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
---
