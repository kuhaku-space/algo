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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T>\r\nstruct heap\
    \ {\r\n    vector<T> data;\r\n    int sz;\r\n\r\n    heap() : data(1), sz(0) {}\r\
    \n\r\n    void push(T x) {\r\n        data.emplace_back(x);\r\n        for (int\
    \ it = ++sz; it > 1 && data[it] > data[it >> 1]; it >>= 1) {\r\n            swap(data[it],\
    \ data[it >> 1]);\r\n        }\r\n    }\r\n\r\n    auto top() const { return data[1];\
    \ }\r\n\r\n    void pop() {\r\n        data[1] = data[sz--];\r\n        data.pop_back();\r\
    \n        for (int it = 1; data[it] < min(data[it << 1], data[(it << 1) | 1]);)\
    \ {\r\n            it <<= 1;\r\n            if (data[it] < data[it | 1]) ++it;\r\
    \n            swap(data[it], data[it >> 1]);\r\n        }\r\n    }\r\n\r\n   \
    \ int size() const { return sz; }\r\n    bool empty() const { return sz == 0;\
    \ }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/heap.hpp
  requiredBy: []
  timestamp: '2021-10-01 05:33:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/heap.hpp
layout: document
redirect_from:
- /library/lib/data_structure/heap.hpp
- /library/lib/data_structure/heap.hpp.html
title: lib/data_structure/heap.hpp
---
