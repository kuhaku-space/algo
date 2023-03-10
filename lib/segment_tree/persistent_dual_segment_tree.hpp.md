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
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/monoid.hpp:\
    \ line -1: no such header\n"
  code: "#include \"segment_tree/monoid.hpp\"\n#include \"template/template.hpp\"\n\
    \ntemplate <class M>\nstruct persistent_dual_segment_tree {\n  private:\n    using\
    \ T = typename M::value_type;\n\n    struct Node {\n        using pointer = Node\
    \ *;\n        T val;\n        pointer left, right;\n\n        constexpr Node(T\
    \ _val) : val(_val), left(), right() {}\n        constexpr Node(T _val, pointer\
    \ _left, pointer _right)\n            : val(_val), left(_left), right(_right)\
    \ {}\n    };\n\n  public:\n    using node_pointer = typename Node::pointer;\n\n\
    \    constexpr persistent_dual_segment_tree() : _size(), root() {}\n    constexpr\
    \ persistent_dual_segment_tree(int n, node_pointer _root) : _size(n), root(_root)\
    \ {}\n    persistent_dual_segment_tree(int n, T e = M::id) : _size(n), root(this->build(0,\
    \ n, e)) {}\n    template <class U>\n    persistent_dual_segment_tree(const vector<U>\
    \ &v)\n        : _size(v.size()), root(this->build(0, v.size(), v)) {}\n\n   \
    \ T operator[](int i) const { return this->get(0, this->_size, i, this->root);\
    \ }\n    T at(int k) const { return this->operator[](k); }\n    T get(int k) const\
    \ { return this->operator[](k); }\n\n    persistent_dual_segment_tree apply(int\
    \ a, T val) const { return this->apply(a, a + 1, val); }\n    persistent_dual_segment_tree\
    \ apply(int a, int b, T val) const {\n        assert(0 <= a && b <= this->_size);\n\
    \        return persistent_dual_segment_tree(\n            this->_size, this->apply(0,\
    \ this->_size, a, b, val, M::id, this->root));\n    }\n\n  private:\n    int _size;\n\
    \    node_pointer root;\n\n    static node_pointer merge(node_pointer left, node_pointer\
    \ right) {\n        return new Node(M::op(left->val, right->val), left, right);\n\
    \    }\n\n    node_pointer build(int l, int r, T val) const {\n        if (l +\
    \ 1 == r) return new Node(val);\n        int m = (l + r) >> 1;\n        return\
    \ this->merge(this->build(l, m, val), this->build(m, r, val));\n    }\n    template\
    \ <class U>\n    node_pointer build(int l, int r, const vector<U> &v) const {\n\
    \        if (l + 1 == r) return new Node(v[l]);\n        int m = (l + r) >> 1;\n\
    \        return this->merge(this->build(l, m, v), this->build(m, r, v));\n   \
    \ }\n\n    T get(int l, int r, int k, node_pointer node) const {\n        if (l\
    \ + 1 == r) return node->val;\n        int m = (l + r) >> 1;\n        if (k <\
    \ m) return M::op(node->val, this->get(l, m, k, node->left));\n        else return\
    \ M::op(node->val, this->get(m, r, k, node->right));\n    }\n\n    node_pointer\
    \ apply(int l, int r, int a, int b, T val, T prop, node_pointer node) const {\n\
    \        if (a <= l && r <= b)\n            return new Node(M::op(val, M::op(prop,\
    \ node->val)), node->left, node->right);\n        if (b <= l || r <= a) return\
    \ new Node(M::op(prop, node->val), node->left, node->right);\n        int m =\
    \ (l + r) >> 1;\n        return new Node(M::id, this->apply(l, m, a, b, val, M::op(prop,\
    \ node->val), node->left),\n                        this->apply(m, r, a, b, val,\
    \ M::op(prop, node->val), node->right));\n    }\n};\n"
  dependsOn:
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/persistent_dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2023-02-04 18:39:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/segment_tree/persistent_dual_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/persistent_dual_segment_tree.hpp
- /library/lib/segment_tree/persistent_dual_segment_tree.hpp.html
title: lib/segment_tree/persistent_dual_segment_tree.hpp
---
