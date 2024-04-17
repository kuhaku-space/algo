---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/macro.hpp
    title: lib/template/macro.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/sonic.hpp
    title: lib/template/sonic.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/sample/many_a+b.test.cpp
    title: test/yosupo/sample/many_a+b.test.cpp
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/macro.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/macro.hpp\"\n#include \"template/sonic.hpp\"\
    \n#include \"template/template.hpp\"\nusing namespace std;\nusing ll = std::int64_t;\n\
    using ld = long double;\ntemplate <class T, class U>\nstd::istream &operator>>(std::istream\
    \ &is, std::pair<T, U> &p) {\n    return is >> p.first >> p.second;\n}\ntemplate\
    \ <class T>\nstd::istream &operator>>(std::istream &is, std::vector<T> &v) {\n\
    \    for (T &i : v) is >> i;\n    return is;\n}\ntemplate <class T, class U>\n\
    std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {\n    return\
    \ os << '(' << p.first << ',' << p.second << ')';\n}\ntemplate <class T>\nstd::ostream\
    \ &operator<<(std::ostream &os, const std::vector<T> &v) {\n    for (auto it =\
    \ v.begin(); it != v.end(); ++it) {\n        os << (it == v.begin() ? \"\" : \"\
    \ \") << *it;\n    }\n    return os;\n}\ntemplate <class Head, class... Tail>\n\
    void co(Head &&head, Tail &&...tail) {\n    if constexpr (sizeof...(tail) == 0)\
    \ std::cout << head << '\\n';\n    else std::cout << head << ' ', co(std::forward<Tail>(tail)...);\n\
    }\ntemplate <class Head, class... Tail>\nvoid ce(Head &&head, Tail &&...tail)\
    \ {\n    if constexpr (sizeof...(tail) == 0) std::cerr << head << '\\n';\n   \
    \ else std::cerr << head << ' ', ce(std::forward<Tail>(tail)...);\n}\ntemplate\
    \ <typename T, typename... Args>\nauto make_vector(T x, int arg, Args... args)\
    \ {\n    if constexpr (sizeof...(args) == 0) return std::vector<T>(arg, x);\n\
    \    else return std::vector(arg, make_vector<T>(x, args...));\n}\nvoid Yes(bool\
    \ is_correct = true) {\n    std::cout << (is_correct ? \"Yes\" : \"No\") << '\\\
    n';\n}\nvoid No(bool is_not_correct = true) {\n    Yes(!is_not_correct);\n}\n\
    void YES(bool is_correct = true) {\n    std::cout << (is_correct ? \"YES\" : \"\
    NO\") << '\\n';\n}\nvoid NO(bool is_not_correct = true) {\n    YES(!is_not_correct);\n\
    }\nvoid Takahashi(bool is_correct = true) {\n    std::cout << (is_correct ? \"\
    Takahashi\" : \"Aoki\") << '\\n';\n}\nvoid Aoki(bool is_not_correct = true) {\n\
    \    Takahashi(!is_not_correct);\n}\n"
  dependsOn:
  - lib/template/macro.hpp
  - lib/template/template.hpp
  - lib/template/sonic.hpp
  isVerificationFile: false
  path: lib/template/atcoder.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/sample/many_a+b.test.cpp
documentation_of: lib/template/atcoder.hpp
layout: document
redirect_from:
- /library/lib/template/atcoder.hpp
- /library/lib/template/atcoder.hpp.html
title: lib/template/atcoder.hpp
---
