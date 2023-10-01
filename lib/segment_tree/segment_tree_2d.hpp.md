---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/dynamic_segment_tree.hpp
    title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_add_rectangle_sum.2.test.cpp
    title: test/yosupo/data_structure/point_add_rectangle_sum.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E8C\u6B21\u5143\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/dynamic_segment_tree.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"segment_tree/dynamic_segment_tree.hpp\"\n#include\
    \ \"template/template.hpp\"\n\n/**\n * @brief \u4E8C\u6B21\u5143\u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\n *\n * @tparam M \u30E2\u30CE\u30A4\u30C9\n */\ntemplate <class\
    \ M>\nstruct segment_tree_2d {\n  private:\n    using T = typename M::value_type;\n\
    \n    struct _node {\n        using pointer = _node *;\n        pointer left,\
    \ right;\n        dynamic_segment_tree<M> segtree;\n\n        _node(std::int64_t\
    \ w) : left(nullptr), right(nullptr), segtree(w) {}\n    };\n\n  public:\n   \
    \ using node_ptr = typename _node::pointer;\n\n    segment_tree_2d(std::int64_t\
    \ h, std::int64_t w) : root(new _node(w)), _h(h), _w(w) {}\n\n    T at(std::int64_t\
    \ x, std::int64_t y) const {\n        node_ptr node = root;\n        std::int64_t\
    \ l = 0, r = _h;\n        while (r - l > 1) {\n            if (!node) return M::id;\n\
    \            std::int64_t m = (l + r) >> 1;\n            if (x < m) r = m, node\
    \ = node->left;\n            else l = m, node = node->right;\n        }\n    \
    \    return node ? node->segtree.get(y) : M::id;\n    }\n    T get(std::int64_t\
    \ x, std::int64_t y) const { return at(x, y); }\n\n    void set(std::int64_t x,\
    \ std::int64_t y, T val) {\n        assert(0 <= x && x < _h);\n        assert(0\
    \ <= y && y < _w);\n        node_ptr node = root;\n        std::vector<node_ptr>\
    \ nodes;\n        std::int64_t l = 0, r = _h;\n        while (r - l > 1) {\n \
    \           std::int64_t m = (l + r) >> 1;\n            nodes.emplace_back(node);\n\
    \            if (x < m) {\n                if (!node->left) node->left = new _node(_w);\n\
    \                r = m, node = node->left;\n            } else {\n           \
    \     if (!node->right) node->right = new _node(_w);\n                l = m, node\
    \ = node->right;\n            }\n        }\n        node->segtree.set(y, val);\n\
    \n        std::reverse(std::begin(nodes), std::end(nodes));\n        for (auto\
    \ node : nodes) {\n            node->segtree.set(y, M::op(node->left ? node->left->segtree.get(y)\
    \ : M::id,\n                                       node->right ? node->right->segtree.get(y)\
    \ : M::id));\n        }\n    }\n    void reset(std::int64_t x, std::int64_t y)\
    \ { set(x, y, M::id); }\n\n    T all_prod() const { return root ? root->segtree.all_prod()\
    \ : M::id; }\n    T prod(std::int64_t l, std::int64_t r, std::int64_t d, std::int64_t\
    \ u) const {\n        assert(0 <= l && l <= r && r <= _h);\n        assert(0 <=\
    \ d && d <= u && u <= _w);\n        return prod(l, r, d, u, root, 0, _h);\n  \
    \  }\n\n  private:\n    node_ptr root;\n    std::int64_t _h, _w;\n\n    T prod(std::int64_t\
    \ l, std::int64_t r, std::int64_t d, std::int64_t u, node_ptr node,\n        \
    \   std::int64_t x, std::int64_t y) const {\n        if (!node || y <= l || r\
    \ <= x) return M::id;\n        if (l <= x && y <= r) return node->segtree.prod(d,\
    \ u);\n\n        return M::op(prod(l, r, d, u, node->left, x, (x + y) >> 1),\n\
    \                     prod(l, r, d, u, node->right, (x + y) >> 1, y));\n    }\n\
    };\n"
  dependsOn:
  - lib/segment_tree/dynamic_segment_tree.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/segment_tree_2d.hpp
  requiredBy: []
  timestamp: '2023-10-01 20:21:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/point_add_rectangle_sum.2.test.cpp
documentation_of: lib/segment_tree/segment_tree_2d.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/segment_tree_2d.hpp
- /library/lib/segment_tree/segment_tree_2d.hpp.html
title: "\u4E8C\u6B21\u5143\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
