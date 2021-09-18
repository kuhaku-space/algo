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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class F, class G>\r\n\
    struct Mo {\r\n    vector<int> left, right, order;\r\n    bitset<1 << 20> v;\r\
    \n    int width, nl, nr, ptr;\r\n    const F add;\r\n    const G del;\r\n\r\n\
    \    Mo(int n, const F &f, const G &g)\r\n        : add(f), del(g), width((int)sqrt(n)),\
    \ nl(0), nr(0), ptr(0), v() {}\r\n\r\n    void insert(int l, int r) {\r\n    \
    \    left.emplace_back(l);\r\n        right.emplace_back(r);\r\n    }\r\n\r\n\
    \    void build() {\r\n        order.resize(left.size());\r\n        iota(order.begin(),\
    \ order.end(), 0);\r\n        sort(order.begin(), order.end(), [&](int a, int\
    \ b) {\r\n            if (left[a] / width != left[b] / width) return left[a] <\
    \ left[b];\r\n            return right[a] < right[b];\r\n        });\r\n    }\r\
    \n\r\n    int process() {\r\n        if (ptr == order.size()) return -1;\r\n \
    \       const auto id = order[ptr];\r\n        while (nl > left[id]) this->distribute(--nl);\r\
    \n        while (nr < right[id]) this->distribute(nr++);\r\n        while (nl\
    \ < left[id]) this->distribute(nl++);\r\n        while (nr > right[id]) this->distribute(--nr);\r\
    \n        return order[ptr++];\r\n    }\r\n\r\n    inline void distribute(int\
    \ idx) {\r\n        v.flip(idx);\r\n        if (v[idx])\r\n            add(idx);\r\
    \n        else\r\n            del(idx);\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_struct/Mo.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_struct/Mo.hpp
layout: document
redirect_from:
- /library/lib/data_struct/Mo.hpp
- /library/lib/data_struct/Mo.hpp.html
title: lib/data_struct/Mo.hpp
---
