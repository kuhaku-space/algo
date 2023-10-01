---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
    title: test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9818\u57DF\u6728"
    links:
    - https://hitonanode.github.io/cplib-cpp/segmenttree/rangetree.hpp.html
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/segment_tree.hpp:\
    \ line -1: no such header\n"
  code: "#include \"segment_tree/segment_tree.hpp\"\n#include \"template/template.hpp\"\
    \n\n/**\n * @brief \u9818\u57DF\u6728\n *\n * @tparam M\n * @tparam T\n *\n *\
    \ @see https://hitonanode.github.io/cplib-cpp/segmenttree/rangetree.hpp.html\n\
    \ */\ntemplate <class M, class T = int>\nstruct range_tree {\n  private:\n   \
    \ using Pt = std::pair<T, T>;\n    using value_type = typename M::value_type;\n\
    \n  public:\n    range_tree() = default;\n\n    void add(T x, T y) noexcept {\
    \ _pts.emplace_back(x, y); }\n\n    void build() {\n        std::sort(_pts.begin(),\
    \ _pts.end());\n        _pts.erase(std::unique(_pts.begin(), _pts.end()), _pts.end());\n\
    \        _size = _pts.size();\n\n        _range2yxs.resize(_size * 2);\n     \
    \   for (int i = 0; i < _size; i++) _range2yxs[_size + i] = {{_pts[i].second,\
    \ _pts[i].first}};\n        for (int i = _size - 1; i > 0; i--) {\n          \
    \  auto &lch = _range2yxs[i * 2];\n            auto &rch = _range2yxs[i * 2 +\
    \ 1];\n            std::merge(lch.begin(), lch.end(), rch.begin(), rch.end(),\n\
    \                       std::back_inserter(_range2yxs[i]));\n            _range2yxs[i].erase(std::unique(_range2yxs[i].begin(),\
    \ _range2yxs[i].end()),\n                                _range2yxs[i].end());\n\
    \        }\n        for (const auto &v : _range2yxs) segtrees.emplace_back(v.size());\n\
    \    }\n\n    void set(T x, T y, value_type val) {\n        int i = std::distance(_pts.begin(),\
    \ std::lower_bound(_pts.begin(), _pts.end(), Pt{x, y}));\n        assert(i < _size\
    \ && _pts[i] == std::make_pair(x, y));\n        for (i += _size; i; i >>= 1) set(i,\
    \ {x, y}, val);\n    }\n\n    value_type prod(T xl, T yl, T xr, T yr) const {\n\
    \        auto comp = [](const Pt &l, const Pt &r) {\n            return l.first\
    \ < r.first;\n        };\n        int l = _size + std::distance(_pts.begin(),\n\
    \                                      std::lower_bound(_pts.begin(), _pts.end(),\
    \ Pt{xl, yr}, comp));\n        int r = _size + std::distance(_pts.begin(),\n \
    \                                     std::lower_bound(_pts.begin(), _pts.end(),\
    \ Pt{xr, yr}, comp));\n        value_type res = M::id;\n        while (l < r)\
    \ {\n            if (l & 1) res = M::op(res, prod(l++, yl, yr));\n           \
    \ if (r & 1) res = M::op(res, prod(--r, yl, yr));\n            l >>= 1, r >>=\
    \ 1;\n        }\n        return res;\n    }\n    value_type get(T x, T y) const\
    \ {\n        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(),\
    \ _pts.end(), Pt{x, y}));\n        return i < _size && _pts[i] == std::make_pair(x,\
    \ y) ? segtrees[_size + i].get(0) : M::id;\n    }\n\n  private:\n    int _size;\n\
    \    std::vector<Pt> _pts;\n    std::vector<std::vector<Pt>> _range2yxs;\n   \
    \ std::vector<segment_tree<M>> segtrees;\n\n    void set(int v, Pt p, value_type\
    \ val) {\n        auto i = std::distance(\n            _range2yxs[v].begin(),\n\
    \            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{p.second,\
    \ p.first}));\n        segtrees[v].set(i, val);\n    }\n\n    value_type prod(int\
    \ v, T yl, T yr) const {\n        auto comp = [&](const Pt &l, const Pt &r) {\n\
    \            return l.first < r.first;\n        };\n        auto il = std::distance(\n\
    \            _range2yxs[v].begin(),\n            std::lower_bound(_range2yxs[v].begin(),\
    \ _range2yxs[v].end(), Pt{yl, yl}, comp));\n        auto ir = std::distance(\n\
    \            _range2yxs[v].begin(),\n            std::lower_bound(_range2yxs[v].begin(),\
    \ _range2yxs[v].end(), Pt{yr, yr}, comp));\n        return segtrees[v].prod(il,\
    \ ir);\n    }\n};\n"
  dependsOn:
  - lib/segment_tree/segment_tree.hpp
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/range_tree.hpp
  requiredBy: []
  timestamp: '2023-10-01 20:21:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
documentation_of: lib/binary_tree/range_tree.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/range_tree.hpp
- /library/lib/binary_tree/range_tree.hpp.html
title: "\u9818\u57DF\u6728"
---
