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
    document_title: Mo's algorithm
    links:
    - https://ei1333.hateblo.jp/entry/2017/09/11/211011
    - https://snuke.hatenablog.com/entry/2016/07/01/000000
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief Mo's algorithm\r\
    \n * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011\r\n * @see https://snuke.hatenablog.com/entry/2016/07/01/000000\r\
    \n *\r\n * @tparam F\r\n * @tparam G\r\n */\r\ntemplate <class F, class G>\r\n\
    struct Mo {\r\n    Mo(int n, const F &f, const G &g)\r\n        : _left(), _right(),\
    \ _order(), _size(n), _nl(0), _nr(0), _ptr(0), _add(f), _del(g) {}\r\n\r\n   \
    \ void add(int l, int r) {\r\n        this->_left.emplace_back(l);\r\n       \
    \ this->_right.emplace_back(r);\r\n    }\r\n    void emplace(int l, int r) { return\
    \ this->add(l, r); }\r\n    void insert(int l, int r) { return this->add(l, r);\
    \ }\r\n\r\n    void build() {\r\n        int q = this->_left.size();\r\n     \
    \   int width = std::max(1, int(this->_size / sqrt(q)));\r\n        this->_order.resize(q);\r\
    \n        std::iota(this->_order.begin(), this->_order.end(), 0);\r\n        std::sort(this->_order.begin(),\
    \ this->_order.end(), [&](int a, int b) -> bool {\r\n            if (this->_left[a]\
    \ / width != this->_left[b] / width)\r\n                return this->_left[a]\
    \ < this->_left[b];\r\n            return (this->_left[a] / width % 2) != (this->_right[a]\
    \ < this->_right[b]);\r\n        });\r\n    }\r\n\r\n    int process() {\r\n \
    \       if (this->_ptr == (int)this->_order.size()) return -1;\r\n        const\
    \ auto id = this->_order[this->_ptr];\r\n        while (this->_nl > this->_left[id])\
    \ this->_add(--this->_nl);\r\n        while (this->_nr < this->_right[id]) this->_add(this->_nr++);\r\
    \n        while (this->_nl < this->_left[id]) this->_del(this->_nl++);\r\n   \
    \     while (this->_nr > this->_right[id]) this->_del(--this->_nr);\r\n      \
    \  return this->_order[this->_ptr++];\r\n    }\r\n\r\n  private:\r\n    std::vector<int>\
    \ _left, _right, _order;\r\n    int _size, _nl, _nr, _ptr;\r\n    const F &_add;\r\
    \n    const G &_del;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/mo.hpp
  requiredBy: []
  timestamp: '2022-06-26 18:20:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/mo.hpp
layout: document
redirect_from:
- /library/lib/algorithm/mo.hpp
- /library/lib/algorithm/mo.hpp.html
title: Mo's algorithm
---
