---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/monoid.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"segment_tree/monoid.hpp\"\n#include \"template/template.hpp\"\
    \n\ntemplate <class M>\nstruct sliding_window_aggregation {\n  private:\n    using\
    \ T = typename M::value_type;\n\n  public:\n    sliding_window_aggregation() :\
    \ back_total(M::id), front(), back() {\n        this->front.emplace(M::id);\n\
    \    }\n\n    T top() const { return M::op(this->back_total, this->front.top());\
    \ }\n\n    void emplace(T val) {\n        this->back.emplace(val);\n        this->back_total\
    \ = M::op(val, back_total);\n    }\n    void push(T val) { this->emplace(val);\
    \ }\n\n    void pop() {\n        if (this->front.size() == 1) {\n            while\
    \ (!this->back.empty()) {\n                this->front.emplace(M::op(this->front.top(),\
    \ this->back.top()));\n                this->back.pop();\n            }\n    \
    \        this->back_total = M::id;\n        }\n        this->front.pop();\n  \
    \  }\n\n  private:\n    T back_total;\n    std::stack<T> front, back;\n};\n"
  dependsOn:
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/swag.hpp
  requiredBy: []
  timestamp: '2023-05-22 20:52:45+09:00'
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
