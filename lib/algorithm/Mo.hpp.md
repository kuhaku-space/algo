---
data:
  _extendedDependsOn:
  - icon: ':question:'
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
    struct Mo {\r\n    vector<int> left, right, order;\r\n    vector<bool> contains;\r\
    \n    int width, nl, nr, ptr;\r\n    const F add;\r\n    const G del;\r\n\r\n\
    \    Mo(int n, const F &f, const G &g)\r\n        : add(f), del(g), width((int)sqrt(n)),\
    \ nl(0), nr(0), ptr(0), contains(n) {}\r\n\r\n    void insert(int l, int r) {\r\
    \n        this->left.emplace_back(l);\r\n        this->right.emplace_back(r);\r\
    \n    }\r\n\r\n    void build() {\r\n        this->order.resize(this->left.size());\r\
    \n        iota(this->order.begin(), this->order.end(), 0);\r\n        sort(this->order.begin(),\
    \ this->order.end(), [&](int a, int b) {\r\n            if (this->left[a] / this->width\
    \ != this->left[b] / this->width)\r\n                return this->left[a] < this->left[b];\r\
    \n            return this->right[a] < this->right[b];\r\n        });\r\n    }\r\
    \n\r\n    int process() {\r\n        if (this->ptr == this->order.size()) return\
    \ -1;\r\n        const auto id = this->order[this->ptr];\r\n        while (this->nl\
    \ > this->left[id]) this->distribute(--this->nl);\r\n        while (this->nr <\
    \ this->right[id]) this->distribute(this->nr++);\r\n        while (this->nl <\
    \ this->left[id]) this->distribute(this->nl++);\r\n        while (this->nr > this->right[id])\
    \ this->distribute(--this->nr);\r\n        return this->order[this->ptr++];\r\n\
    \    }\r\n\r\n    void distribute(int idx) {\r\n        this->contains[idx] =\
    \ !this->contains[idx];\r\n        if (this->contains[idx])\r\n            this->add(idx);\r\
    \n        else\r\n            this->del(idx);\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/Mo.hpp
  requiredBy: []
  timestamp: '2021-10-01 05:33:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/Mo.hpp
layout: document
redirect_from:
- /library/lib/algorithm/Mo.hpp
- /library/lib/algorithm/Mo.hpp.html
title: lib/algorithm/Mo.hpp
---
