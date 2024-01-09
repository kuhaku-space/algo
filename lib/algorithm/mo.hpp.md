---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_range_inversions.test.cpp
    title: test/yosupo/data_structure/static_range_inversions.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Mo's algorithm
    links:
    - https://ei1333.hateblo.jp/entry/2017/09/11/211011
    - https://snuke.hatenablog.com/entry/2016/07/01/000000
  bundledCode: "#line 1 \"lib/algorithm/mo.hpp\"\n#include <algorithm>\r\n#include\
    \ <cmath>\r\n#include <iostream>\r\n#include <numeric>\r\n#include <vector>\r\n\
    \r\n/**\r\n * @brief Mo's algorithm\r\n * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011\r\
    \n * @see https://snuke.hatenablog.com/entry/2016/07/01/000000\r\n */\r\nstruct\
    \ Mo {\r\n    Mo(int n) : _left(), _right(), _order(), _size(n), _nl(0), _nr(0),\
    \ _ptr(0) {}\r\n\r\n    void input(int q, int bias = 1, int closed = 0) {\r\n\
    \        for (int i = 0; i < q; ++i) {\r\n            int l, r;\r\n          \
    \  std::cin >> l >> r;\r\n            add(l - bias, r - bias + closed);\r\n  \
    \      }\r\n    }\r\n\r\n    void add(int l, int r) {\r\n        _left.emplace_back(l);\r\
    \n        _right.emplace_back(r);\r\n    }\r\n    void emplace(int l, int r) {\
    \ return add(l, r); }\r\n    void insert(int l, int r) { return add(l, r); }\r\
    \n\r\n    void build() {\r\n        int q = _left.size();\r\n        int width\
    \ = std::max(1, int(_size / std::sqrt(q)));\r\n        _order.resize(q);\r\n \
    \       std::iota(_order.begin(), _order.end(), 0);\r\n        std::sort(_order.begin(),\
    \ _order.end(), [&](int a, int b) -> bool {\r\n            if (_left[a] / width\
    \ != _left[b] / width) return _left[a] < _left[b];\r\n            return (_left[a]\
    \ / width % 2 == 0) ? (_right[a] < _right[b]) : (_right[b] < _right[a]);\r\n \
    \       });\r\n    }\r\n\r\n    template <class F, class G>\r\n    int process(F\
    \ add, G del) {\r\n        if (_ptr == (int)_order.size()) return -1;\r\n    \
    \    const auto id = _order[_ptr];\r\n        while (_nl > _left[id]) add(--_nl);\r\
    \n        while (_nr < _right[id]) add(_nr++);\r\n        while (_nl < _left[id])\
    \ del(_nl++);\r\n        while (_nr > _right[id]) del(--_nr);\r\n        return\
    \ _order[_ptr++];\r\n    }\r\n\r\n    template <class F, class G, class H, class\
    \ I>\r\n    int process(F addl, G addr, H dell, I delr) {\r\n        if (_ptr\
    \ == (int)_order.size()) return -1;\r\n        const auto id = _order[_ptr];\r\
    \n        while (_nl > _left[id]) addl(--_nl);\r\n        while (_nr < _right[id])\
    \ addr(_nr++);\r\n        while (_nl < _left[id]) dell(_nl++);\r\n        while\
    \ (_nr > _right[id]) delr(--_nr);\r\n        return _order[_ptr++];\r\n    }\r\
    \n\r\n  private:\r\n    std::vector<int> _left, _right, _order;\r\n    int _size,\
    \ _nl, _nr, _ptr;\r\n};\r\n"
  code: "#include <algorithm>\r\n#include <cmath>\r\n#include <iostream>\r\n#include\
    \ <numeric>\r\n#include <vector>\r\n\r\n/**\r\n * @brief Mo's algorithm\r\n *\
    \ @see https://ei1333.hateblo.jp/entry/2017/09/11/211011\r\n * @see https://snuke.hatenablog.com/entry/2016/07/01/000000\r\
    \n */\r\nstruct Mo {\r\n    Mo(int n) : _left(), _right(), _order(), _size(n),\
    \ _nl(0), _nr(0), _ptr(0) {}\r\n\r\n    void input(int q, int bias = 1, int closed\
    \ = 0) {\r\n        for (int i = 0; i < q; ++i) {\r\n            int l, r;\r\n\
    \            std::cin >> l >> r;\r\n            add(l - bias, r - bias + closed);\r\
    \n        }\r\n    }\r\n\r\n    void add(int l, int r) {\r\n        _left.emplace_back(l);\r\
    \n        _right.emplace_back(r);\r\n    }\r\n    void emplace(int l, int r) {\
    \ return add(l, r); }\r\n    void insert(int l, int r) { return add(l, r); }\r\
    \n\r\n    void build() {\r\n        int q = _left.size();\r\n        int width\
    \ = std::max(1, int(_size / std::sqrt(q)));\r\n        _order.resize(q);\r\n \
    \       std::iota(_order.begin(), _order.end(), 0);\r\n        std::sort(_order.begin(),\
    \ _order.end(), [&](int a, int b) -> bool {\r\n            if (_left[a] / width\
    \ != _left[b] / width) return _left[a] < _left[b];\r\n            return (_left[a]\
    \ / width % 2 == 0) ? (_right[a] < _right[b]) : (_right[b] < _right[a]);\r\n \
    \       });\r\n    }\r\n\r\n    template <class F, class G>\r\n    int process(F\
    \ add, G del) {\r\n        if (_ptr == (int)_order.size()) return -1;\r\n    \
    \    const auto id = _order[_ptr];\r\n        while (_nl > _left[id]) add(--_nl);\r\
    \n        while (_nr < _right[id]) add(_nr++);\r\n        while (_nl < _left[id])\
    \ del(_nl++);\r\n        while (_nr > _right[id]) del(--_nr);\r\n        return\
    \ _order[_ptr++];\r\n    }\r\n\r\n    template <class F, class G, class H, class\
    \ I>\r\n    int process(F addl, G addr, H dell, I delr) {\r\n        if (_ptr\
    \ == (int)_order.size()) return -1;\r\n        const auto id = _order[_ptr];\r\
    \n        while (_nl > _left[id]) addl(--_nl);\r\n        while (_nr < _right[id])\
    \ addr(_nr++);\r\n        while (_nl < _left[id]) dell(_nl++);\r\n        while\
    \ (_nr > _right[id]) delr(--_nr);\r\n        return _order[_ptr++];\r\n    }\r\
    \n\r\n  private:\r\n    std::vector<int> _left, _right, _order;\r\n    int _size,\
    \ _nl, _nr, _ptr;\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/algorithm/mo.hpp
  requiredBy: []
  timestamp: '2023-11-16 06:37:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/static_range_inversions.test.cpp
documentation_of: lib/algorithm/mo.hpp
layout: document
redirect_from:
- /library/lib/algorithm/mo.hpp
- /library/lib/algorithm/mo.hpp.html
title: Mo's algorithm
---
