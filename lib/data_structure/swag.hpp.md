---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
    title: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/monoid.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include <stack>\n#include \"segment_tree/monoid.hpp\"\n\n\
    template <class M>\nstruct sliding_window_aggregation {\n  private:\n    using\
    \ T = typename M::value_type;\n\n  public:\n    sliding_window_aggregation() :\
    \ back_total(M::id), front(), back() { front.emplace(M::id); }\n\n    T top()\
    \ const { return M::op(back_total, front.top()); }\n\n    void emplace(T val)\
    \ {\n        back.emplace(val);\n        back_total = M::op(val, back_total);\n\
    \    }\n    void push(T val) { emplace(val); }\n\n    void pop() {\n        if\
    \ (front.size() == 1) {\n            while (!back.empty()) {\n               \
    \ front.emplace(M::op(front.top(), back.top()));\n                back.pop();\n\
    \            }\n            back_total = M::id;\n        }\n        front.pop();\n\
    \    }\n\n  private:\n    T back_total;\n    std::stack<T> front, back;\n};\n"
  dependsOn:
  - lib/segment_tree/monoid.hpp
  isVerificationFile: false
  path: lib/data_structure/swag.hpp
  requiredBy: []
  timestamp: '2024-05-06 21:20:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/queue_operate_all_composite.test.cpp
documentation_of: lib/data_structure/swag.hpp
layout: document
redirect_from:
- /library/lib/data_structure/swag.hpp
- /library/lib/data_structure/swag.hpp.html
title: lib/data_structure/swag.hpp
---
