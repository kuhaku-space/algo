---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree_2d.hpp
    title: "\u4E8C\u6B21\u5143\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/dynamic_rmq.test.cpp
    title: test/aoj/dsl/dynamic_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_add_rectangle_sum.2.test.cpp
    title: test/yosupo/data_structure/point_add_rectangle_sum.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/monoid.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"segment_tree/monoid.hpp\"\n#include \"template/template.hpp\"\
    \n\n/**\n * @brief \u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n *\n * @tparam\
    \ M \u30E2\u30CE\u30A4\u30C9\n */\ntemplate <class M>\nstruct dynamic_segment_tree\
    \ {\n  private:\n    using T = typename M::value_type;\n\n    struct _node {\n\
    \        using pointer = _node *;\n        std::int64_t index;\n        pointer\
    \ left, right;\n        T value, product;\n\n        constexpr _node(std::int64_t\
    \ _index, T _value)\n            : index(_index), left(nullptr), right(nullptr),\
    \ value(_value), product(_value) {}\n    };\n\n  public:\n    using node_ptr =\
    \ typename _node::pointer;\n\n    dynamic_segment_tree(std::int64_t n) : root(),\
    \ _size(n) {}\n\n    T operator[](std::int64_t k) const {\n        node_ptr node\
    \ = root;\n        std::int64_t l = 0, r = _size;\n        while (node) {\n  \
    \          if (k == node->index) return node->value;\n            std::int64_t\
    \ m = (l + r) >> 1;\n            if (k < m) r = m, node = node->left;\n      \
    \      else l = m, node = node->right;\n        }\n        return M::id;\n   \
    \ }\n    T at(std::int64_t k) const { return operator[](k); }\n    T get(std::int64_t\
    \ k) const { return operator[](k); }\n\n    void set(std::int64_t k, T x) {\n\
    \        assert(0 <= k && k < _size);\n        if (!root) {\n            root\
    \ = new _node(k, x);\n            return;\n        }\n        node_ptr node =\
    \ root;\n        std::vector<node_ptr> nodes;\n        std::int64_t l = 0, r =\
    \ _size;\n        while (true) {\n            nodes.emplace_back(node);\n    \
    \        if (k == node->index) {\n                node->value = x;\n         \
    \       break;\n            }\n            std::int64_t m = (l + r) >> 1;\n  \
    \          if (k < m) {\n                if (node->index < k) std::swap(k, node->index),\
    \ std::swap(x, node->value);\n                if (!node->left) {\n           \
    \         node->left = new _node(k, x);\n                    break;\n        \
    \        }\n                r = m, node = node->left;\n            } else {\n\
    \                if (k < node->index) std::swap(k, node->index), std::swap(x,\
    \ node->value);\n                if (!node->right) {\n                    node->right\
    \ = new _node(k, x);\n                    break;\n                }\n        \
    \        l = m, node = node->right;\n            }\n        }\n\n        std::reverse(std::begin(nodes),\
    \ std::end(nodes));\n        for (auto node : nodes) {\n            node->product\
    \ = M::op(M::op(node->left ? node->left->product : M::id, node->value),\n    \
    \                              node->right ? node->right->product : M::id);\n\
    \        }\n    }\n    void reset(std::int64_t k) { set(k, M::id); }\n\n    T\
    \ all_prod() const { return root ? root->product : M::id; }\n    T prod(std::int64_t\
    \ a, std::int64_t b) const {\n        assert(0 <= a && a <= _size);\n        assert(0\
    \ <= b && b <= _size);\n        return prod(a, b, root, 0, _size);\n    }\n\n\
    \    template <class F>\n    std::int64_t max_right(F f) const {\n        assert(f(M::id));\n\
    \        if (root == nullptr || f(root->value)) return _size;\n        node_ptr\
    \ node = root;\n        T sm = M::id;\n        std::int64_t l = 0, r = _size;\n\
    \        while (r - l > 1) {\n            std::int64_t m = (l + r) >> 1;\n   \
    \         if (node->left == nullptr || f(M::op(sm, node->left->value))) {\n  \
    \              if (node->left != nullptr) sm = M::op(sm, node->left->value);\n\
    \                l = m;\n                node = node->right;\n            } else\
    \ {\n                r = m;\n                node = node->left;\n            }\n\
    \        }\n        return f(M::op(sm, node->value)) ? r : l;\n    }\n\n    template\
    \ <class F>\n    std::int64_t min_left(F f) const {\n        assert(f(M::id));\n\
    \        if (root == nullptr || f(root->value)) return 0;\n        node_ptr node\
    \ = root;\n        T sm = M::id;\n        std::int64_t l = 0, r = _size;\n   \
    \     while (r - l > 1) {\n            std::int64_t m = (l + r) >> 1;\n      \
    \      if (node->right == nullptr || f(M::op(node->right->value, sm))) {\n   \
    \             if (node->right != nullptr) sm = M::op(node->right->value, sm);\n\
    \                r = m;\n                node = node->left;\n            } else\
    \ {\n                l = m;\n                node = node->right;\n           \
    \ }\n        }\n        return f(M::op(node->value, sm)) ? l : r;\n    }\n\n \
    \ private:\n    node_ptr root;\n    std::int64_t _size;\n\n    T prod(std::int64_t\
    \ a, std::int64_t b, node_ptr node, std::int64_t l, std::int64_t r) const {\n\
    \        if (!node || r <= a || b <= l) return M::id;\n        if (a <= l && r\
    \ <= b) return node->product;\n\n        return M::op(M::op(prod(a, b, node->left,\
    \ l, (l + r) >> 1),\n                           a <= node->index && node->index\
    \ < b ? node->value : M::id),\n                     prod(a, b, node->right, (l\
    \ + r) >> 1, r));\n    }\n};\n"
  dependsOn:
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/dynamic_segment_tree.hpp
  requiredBy:
  - lib/segment_tree/segment_tree_2d.hpp
  timestamp: '2023-07-18 06:23:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dsl/dynamic_rmq.test.cpp
  - test/yosupo/data_structure/point_add_rectangle_sum.2.test.cpp
documentation_of: lib/segment_tree/dynamic_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/dynamic_segment_tree.hpp
- /library/lib/segment_tree/dynamic_segment_tree.hpp.html
title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
