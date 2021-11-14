---
data:
  _extendedDependsOn:
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T, class U>\r\n\
    struct slope_trick {\r\n    U min_f;\r\n    priority_queue<T> l;\r\n    priority_queue<T,\
    \ vector<T>, greater> r;\r\n\r\n    slope_trick() : min_f(), l(), r() {}\r\n\r\
    \n    U get() { return min_f; }\r\n\r\n    // Add f(x) = a\r\n    void add(U a)\
    \ { min_f += a; }\r\n\r\n    // Add f(x) = max(0, x - a)\r\n    void add_f(T a)\
    \ {\r\n        min_f += max(U(), l.top() - a);\r\n        l.push(a);\r\n     \
    \   auto x = l.top();\r\n        l.pop();\r\n        r.push(x);\r\n    }\r\n\r\
    \n    // Add f(x) = max(0, a - x)\r\n    void add_g(U a) {\r\n        min_f +=\
    \ max(U(), a - r.top());\r\n        r.push(a);\r\n        auto x = r.top();\r\n\
    \        r.pop();\r\n        l.push(x);\r\n    }\r\n\r\n    // Add f(x) = abs(x\
    \ - a)\r\n    void add_abs(U a) {\r\n        add_f(a);\r\n        add_g(a);\r\n\
    \    }\r\n\r\n    void min_l() { r = priority_queue<T, vector<T>, greater>();\
    \ }\r\n    void min_r() { l = priority_queue<T>(); }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/slope_trick.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/slope_trick.hpp
layout: document
redirect_from:
- /library/lib/_new/slope_trick.hpp
- /library/lib/_new/slope_trick.hpp.html
title: lib/_new/slope_trick.hpp
---
