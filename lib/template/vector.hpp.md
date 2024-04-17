---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/joi/rle.test.cpp
    title: test/aoj/joi/rle.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/string/enumerate_palindromes.test.cpp
    title: test/yosupo/string/enumerate_palindromes.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\nstruct increment_impl\
    \ {\n    template <class T>\n    const increment_impl &operator>>(std::vector<T>\
    \ &v) const {\n        for (auto &x : v) ++x;\n        return *this;\n    }\n\
    } Inc;\n\nstruct decrement_impl {\n    template <class T>\n    const decrement_impl\
    \ &operator>>(std::vector<T> &v) const {\n        for (auto &x : v) --x;\n   \
    \     return *this;\n    }\n} Dec;\n\nstruct sort_impl {\n    template <class\
    \ T>\n    const sort_impl &operator>>(std::vector<T> &v) const {\n        std::sort(v.begin(),\
    \ v.end());\n        return *this;\n    }\n} Sort;\n\nstruct unique_impl {\n \
    \   template <class T>\n    const unique_impl &operator>>(std::vector<T> &v) const\
    \ {\n        std::sort(v.begin(), v.end());\n        v.erase(std::unique(v.begin(),\
    \ v.end()), v.end());\n        return *this;\n    }\n} Uniq;\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/template/vector.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/joi/rle.test.cpp
  - test/yosupo/string/enumerate_palindromes.test.cpp
documentation_of: lib/template/vector.hpp
layout: document
redirect_from:
- /library/lib/template/vector.hpp
- /library/lib/template/vector.hpp.html
title: lib/template/vector.hpp
---
