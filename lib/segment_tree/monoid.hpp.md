---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/sparse_table.hpp
    title: "\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB"
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/swag.hpp
    title: lib/data_structure/swag.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':warning:'
    path: lib/segment_tree/dynamic_segment_tree.hpp
    title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/lazy_segment_tree.hpp
    title: "\u9045\u5EF6\u8A55\u4FA1\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':warning:'
    path: lib/segment_tree/persistent_dual_segment_tree.hpp
    title: lib/segment_tree/persistent_dual_segment_tree.hpp
  - icon: ':warning:'
    path: lib/segment_tree/persistent_segment_tree.hpp
    title: lib/segment_tree/persistent_segment_tree.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree_raq.hpp
    title: lib/segment_tree/segment_tree_raq.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/link_cut_tree.hpp
    title: Link-Cut Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/raq_rmq.test.cpp
    title: test/aoj/dsl/raq_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/rmq.test.cpp
    title: test/aoj/dsl/rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/rmq_ruq.test.cpp
    title: test/aoj/dsl/rmq_ruq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/rsq_ruq.test.cpp
    title: test/aoj/dsl/rsq_ruq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/ruq.test.cpp
    title: test/aoj/dsl/ruq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
    title: test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_set_range_composite.test.cpp
    title: test/yosupo/data_structure/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
    title: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_affine_range_sum.test.cpp
    title: test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_rmq.test.cpp
    title: test/yosupo/data_structure/static_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
    title: test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
    title: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\ntemplate <class T>\n\
    struct Add {\n    using value_type = T;\n    static constexpr T id = T(0);\n \
    \   static constexpr T op(const T &lhs, const T &rhs) { return lhs + rhs; }\n\n\
    \    template <class U>\n    static constexpr U f(T lhs, U rhs) {\n        return\
    \ lhs + rhs;\n    }\n};\n\ntemplate <class T>\nstruct And {\n    using value_type\
    \ = T;\n    static constexpr T id = T(0);\n    static constexpr T op(const T &lhs,\
    \ const T &rhs) { return lhs & rhs; }\n\n    template <class U>\n    static constexpr\
    \ U f(T lhs, U rhs) {\n        return lhs & rhs;\n    }\n};\n\ntemplate <class\
    \ T>\nstruct Or {\n    using value_type = T;\n    static constexpr T id = T(0);\n\
    \    static constexpr T op(const T &lhs, const T &rhs) { return lhs | rhs; }\n\
    \n    template <class U>\n    static constexpr U f(T lhs, U rhs) {\n        return\
    \ lhs | rhs;\n    }\n};\n\ntemplate <class T>\nstruct Xor {\n    using value_type\
    \ = T;\n    static constexpr T id = T(0);\n    static constexpr T op(const T &lhs,\
    \ const T &rhs) { return lhs ^ rhs; }\n\n    template <class U>\n    static constexpr\
    \ U f(T lhs, U rhs) {\n        return lhs ^ rhs;\n    }\n};\n\ntemplate <class\
    \ T>\nstruct Min {\n    using value_type = T;\n    static constexpr T id = numeric_limits<T>::max();\n\
    \    static constexpr T op(const T &lhs, const T &rhs) { return min(lhs, rhs);\
    \ }\n\n    template <class U>\n    static constexpr U f(T lhs, U rhs) {\n    \
    \    return min((U)lhs, rhs);\n    }\n};\n\ntemplate <class T>\nstruct Max {\n\
    \    using value_type = T;\n    static constexpr T id = numeric_limits<T>::min();\n\
    \    static constexpr T op(const T &lhs, const T &rhs) { return max(lhs, rhs);\
    \ }\n\n    template <class U>\n    static constexpr U f(T lhs, U rhs) {\n    \
    \    return max((U)lhs, rhs);\n    }\n};\n\ntemplate <class T>\nstruct Update\
    \ {\n    using value_type = T;\n    static constexpr T id = numeric_limits<T>::max();\n\
    \    static constexpr T op(const T &lhs, const T &rhs) { return lhs == Update::id\
    \ ? rhs : lhs; }\n\n    template <class U>\n    static constexpr U f(T lhs, U\
    \ rhs) {\n        return lhs == Update::id ? rhs : lhs;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct Affine {\n    using value_type = std::pair<T, T>;\n    static\
    \ constexpr std::pair<T, T> id = std::pair<T, T>(1, 0);\n    static constexpr\
    \ std::pair<T, T> op(std::pair<T, T> lhs, std::pair<T, T> rhs) {\n        return\
    \ {lhs.first * rhs.first, lhs.first * rhs.second + lhs.second};\n    }\n};\n\n\
    template <class M>\nstruct Rev {\n    using T = typename M::value_type;\n    using\
    \ value_type = T;\n    static constexpr T id = M::id;\n    static constexpr T\
    \ op(T lhs, T rhs) { return M::op(rhs, lhs); }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/monoid.hpp
  requiredBy:
  - lib/segment_tree/dynamic_segment_tree.hpp
  - lib/segment_tree/persistent_dual_segment_tree.hpp
  - lib/segment_tree/dual_segment_tree.hpp
  - lib/segment_tree/segment_tree.hpp
  - lib/segment_tree/persistent_segment_tree.hpp
  - lib/segment_tree/segment_tree_raq.hpp
  - lib/segment_tree/lazy_segment_tree.hpp
  - lib/tree/link_cut_tree.hpp
  - lib/data_structure/swag.hpp
  - lib/data_structure/sparse_table.hpp
  timestamp: '2022-07-19 05:54:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/point_set_range_composite.test.cpp
  - test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - test/yosupo/data_structure/vertex_add_subtree_sum.test.cpp
  - test/yosupo/data_structure/static_rmq.test.cpp
  - test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - test/aoj/dsl/rmq.test.cpp
  - test/aoj/dsl/rsq_ruq.test.cpp
  - test/aoj/dsl/ruq.test.cpp
  - test/aoj/dsl/raq_rmq.test.cpp
  - test/aoj/dsl/rmq_ruq.test.cpp
documentation_of: lib/segment_tree/monoid.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/monoid.hpp
- /library/lib/segment_tree/monoid.hpp.html
title: lib/segment_tree/monoid.hpp
---
