---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Mo's algorithm (rollback)
    links:
    - https://ei1333.hateblo.jp/entry/2017/09/11/211011
    - https://snuke.hatenablog.com/entry/2016/07/01/000000
  bundledCode: "#line 1 \"lib/algorithm/rollback_mo.hpp\"\n#include <algorithm>\r\n\
    #include <cmath>\r\n#include <iostream>\r\n#include <numeric>\r\n#include <vector>\r\
    \n\r\n/**\r\n * @brief Mo's algorithm (rollback)\r\n * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011\r\
    \n * @see https://snuke.hatenablog.com/entry/2016/07/01/000000\r\n */\r\nstruct\
    \ rollback_mo {\r\n    rollback_mo(int n) : _left(), _right(), _order(), _size(n)\
    \ {}\r\n\r\n    void input(int q, int bias = 1, int closed = 0) {\r\n        for\
    \ (int i = 0; i < q; ++i) {\r\n            int l, r;\r\n            std::cin >>\
    \ l >> r;\r\n            add(l - bias, r - bias + closed);\r\n        }\r\n  \
    \  }\r\n\r\n    void add(int l, int r) {\r\n        _left.emplace_back(l);\r\n\
    \        _right.emplace_back(r);\r\n    }\r\n    void emplace(int l, int r) {\
    \ return add(l, r); }\r\n    void insert(int l, int r) { return add(l, r); }\r\
    \n\r\n    template <class F, class G, class H, class I>\r\n    void solve(F rem,\
    \ G save, H load, I add) {\r\n        return solve(rem, save, load, add, add);\r\
    \n    }\r\n    template <class F, class G, class H, class I, class J>\r\n    void\
    \ solve(F rem, G save, H load, I addl, J addr) {\r\n        int q = _left.size();\r\
    \n        int width = std::max(1, int(_size / std::sqrt(q)));\r\n        _order.resize(q);\r\
    \n        std::iota(_order.begin(), _order.end(), 0);\r\n        std::sort(_order.begin(),\
    \ _order.end(), [&](int a, int b) -> bool {\r\n            if (_left[a] / width\
    \ != _left[b] / width) return _left[a] < _left[b];\r\n            return _right[a]\
    \ < _right[b];\r\n        });\r\n\r\n        auto reset = save();\r\n        for\
    \ (auto &&idx : _order) {\r\n            if (_right[idx] - _left[idx] < width)\
    \ {\r\n                for (int i = _left[idx]; i < _right[idx]; i++) addr(i);\r\
    \n                rem(idx);\r\n                load(reset);\r\n            }\r\
    \n        }\r\n\r\n        int right = 0, last_block = -1;\r\n        for (auto\
    \ idx : _order) {\r\n            if (_right[idx] - _left[idx] < width) continue;\r\
    \n            int block = _left[idx] / width;\r\n            if (block != last_block)\
    \ {\r\n                load(reset);\r\n                last_block = block;\r\n\
    \                right = (block + 1) * width;\r\n            }\r\n           \
    \ while (right < _right[idx]) addr(right++);\r\n            auto snapshot = save();\r\
    \n            for (int j = (block + 1) * width - 1; j >= _left[idx]; --j) addl(j);\r\
    \n            rem(idx);\r\n            load(snapshot);\r\n        }\r\n    }\r\
    \n\r\n  private:\r\n    std::vector<int> _left, _right, _order;\r\n    int _size;\r\
    \n};\r\n"
  code: "#include <algorithm>\r\n#include <cmath>\r\n#include <iostream>\r\n#include\
    \ <numeric>\r\n#include <vector>\r\n\r\n/**\r\n * @brief Mo's algorithm (rollback)\r\
    \n * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011\r\n * @see https://snuke.hatenablog.com/entry/2016/07/01/000000\r\
    \n */\r\nstruct rollback_mo {\r\n    rollback_mo(int n) : _left(), _right(), _order(),\
    \ _size(n) {}\r\n\r\n    void input(int q, int bias = 1, int closed = 0) {\r\n\
    \        for (int i = 0; i < q; ++i) {\r\n            int l, r;\r\n          \
    \  std::cin >> l >> r;\r\n            add(l - bias, r - bias + closed);\r\n  \
    \      }\r\n    }\r\n\r\n    void add(int l, int r) {\r\n        _left.emplace_back(l);\r\
    \n        _right.emplace_back(r);\r\n    }\r\n    void emplace(int l, int r) {\
    \ return add(l, r); }\r\n    void insert(int l, int r) { return add(l, r); }\r\
    \n\r\n    template <class F, class G, class H, class I>\r\n    void solve(F rem,\
    \ G save, H load, I add) {\r\n        return solve(rem, save, load, add, add);\r\
    \n    }\r\n    template <class F, class G, class H, class I, class J>\r\n    void\
    \ solve(F rem, G save, H load, I addl, J addr) {\r\n        int q = _left.size();\r\
    \n        int width = std::max(1, int(_size / std::sqrt(q)));\r\n        _order.resize(q);\r\
    \n        std::iota(_order.begin(), _order.end(), 0);\r\n        std::sort(_order.begin(),\
    \ _order.end(), [&](int a, int b) -> bool {\r\n            if (_left[a] / width\
    \ != _left[b] / width) return _left[a] < _left[b];\r\n            return _right[a]\
    \ < _right[b];\r\n        });\r\n\r\n        auto reset = save();\r\n        for\
    \ (auto &&idx : _order) {\r\n            if (_right[idx] - _left[idx] < width)\
    \ {\r\n                for (int i = _left[idx]; i < _right[idx]; i++) addr(i);\r\
    \n                rem(idx);\r\n                load(reset);\r\n            }\r\
    \n        }\r\n\r\n        int right = 0, last_block = -1;\r\n        for (auto\
    \ idx : _order) {\r\n            if (_right[idx] - _left[idx] < width) continue;\r\
    \n            int block = _left[idx] / width;\r\n            if (block != last_block)\
    \ {\r\n                load(reset);\r\n                last_block = block;\r\n\
    \                right = (block + 1) * width;\r\n            }\r\n           \
    \ while (right < _right[idx]) addr(right++);\r\n            auto snapshot = save();\r\
    \n            for (int j = (block + 1) * width - 1; j >= _left[idx]; --j) addl(j);\r\
    \n            rem(idx);\r\n            load(snapshot);\r\n        }\r\n    }\r\
    \n\r\n  private:\r\n    std::vector<int> _left, _right, _order;\r\n    int _size;\r\
    \n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/algorithm/rollback_mo.hpp
  requiredBy: []
  timestamp: '2023-12-20 19:20:23+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/rollback_mo.hpp
layout: document
redirect_from:
- /library/lib/algorithm/rollback_mo.hpp
- /library/lib/algorithm/rollback_mo.hpp.html
title: Mo's algorithm (rollback)
---
