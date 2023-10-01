---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
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
  code: "#include \"segment_tree/monoid.hpp\"\n#include \"template/template.hpp\"\n\
    \n/**\n * @brief \u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\n *\n * @tparam\
    \ Monoid \u30E2\u30CE\u30A4\u30C9\n */\ntemplate <class Monoid>\nstruct persistent_segment_tree\
    \ {\n  private:\n    using T = typename Monoid::value_type;\n\n    struct _node\
    \ {\n        using pointer = _node *;\n        T val;\n        pointer left, right;\n\
    \n        constexpr _node(T _val) : val(_val), left(), right() {}\n        constexpr\
    \ _node(T _val, pointer _left, pointer _right)\n            : val(_val), left(_left),\
    \ right(_right) {}\n    };\n\n  public:\n    using node_pointer = typename _node::pointer;\n\
    \n    constexpr persistent_segment_tree() : _size(), _root() {}\n    constexpr\
    \ persistent_segment_tree(int n, node_pointer _root) : _size(n), _root(_root)\
    \ {}\n    persistent_segment_tree(int n, T e = Monoid::id) : _size(n), _root(build(0,\
    \ n, e)) {}\n    template <class U>\n    persistent_segment_tree(const std::vector<U>\
    \ &v)\n        : _size(v.size()), _root(build(0, v.size(), v)) {}\n\n    T operator[](int\
    \ i) const { return prod(i, i + 1); }\n    T at(int k) const { return operator[](k);\
    \ }\n    T get(int k) const { return operator[](k); }\n\n    persistent_segment_tree\
    \ set(int k, T val) {\n        assert(0 <= k && k < _size);\n        return persistent_segment_tree(_size,\
    \ set(0, _size, k, val, _root));\n    }\n    persistent_segment_tree reset(int\
    \ k) { return set(k, Monoid::id); }\n\n    T all_prod() const { return _root->val;\
    \ }\n    T prod(int a, int b) const {\n        assert(0 <= a && b <= _size);\n\
    \        return prod(0, _size, a, b, _root);\n    }\n\n  private:\n    int _size;\n\
    \    node_pointer _root;\n\n    static node_pointer merge(node_pointer left, node_pointer\
    \ right) {\n        return new _node(Monoid::op(left->val, right->val), left,\
    \ right);\n    }\n\n    node_pointer build(int l, int r, T val) const {\n    \
    \    if (l + 1 == r) return new _node(val);\n        int m = (l + r) >> 1;\n \
    \       return merge(build(l, m, val), build(m, r, val));\n    }\n    template\
    \ <class U>\n    node_pointer build(int l, int r, const std::vector<U> &v) const\
    \ {\n        if (l + 1 == r) return new _node(v[l]);\n        int m = (l + r)\
    \ >> 1;\n        return merge(build(l, m, v), build(m, r, v));\n    }\n\n    node_pointer\
    \ set(int l, int r, int k, T val, node_pointer node) const {\n        if (l +\
    \ 1 == r) return new _node(val);\n        int m = (l + r) >> 1;\n        if (k\
    \ < m) return merge(set(l, m, k, val, node->left), node->right);\n        else\
    \ return merge(node->left, set(m, r, k, val, node->right));\n    }\n\n    T prod(int\
    \ l, int r, int a, int b, node_pointer node) const {\n        if (a <= l && r\
    \ <= b) return node->val;\n        if (b <= l || r <= a) return Monoid::id;\n\
    \        int m = (l + r) >> 1;\n        return Monoid::op(prod(l, m, a, b, node->left),\
    \ prod(m, r, a, b, node->right));\n    }\n};\n"
  dependsOn:
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/persistent_segment_tree.hpp
  requiredBy: []
  timestamp: '2023-10-01 20:21:13+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/segment_tree/persistent_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/persistent_segment_tree.hpp
- /library/lib/segment_tree/persistent_segment_tree.hpp.html
title: "\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
