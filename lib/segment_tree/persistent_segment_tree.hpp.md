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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/monoid.hpp:\
    \ line -1: no such header\n"
  code: "#include \"segment_tree/monoid.hpp\"\n#include \"template/template.hpp\"\n\
    \ntemplate <class M>\nstruct persistent_segment_tree {\n  private:\n    using\
    \ T = typename M::value_type;\n\n    struct Node {\n        using pointer = Node\
    \ *;\n        T val;\n        pointer left, right;\n\n        constexpr Node(T\
    \ _val) : val(_val), left(), right() {}\n        constexpr Node(T _val, pointer\
    \ _left, pointer _right)\n            : val(_val), left(_left), right(_right)\
    \ {}\n    };\n\n  public:\n    using node_pointer = typename Node::pointer;\n\n\
    \    constexpr persistent_segment_tree() : _size(), root() {}\n    constexpr persistent_segment_tree(int\
    \ n, node_pointer _root) : _size(n), root(_root) {}\n    persistent_segment_tree(int\
    \ n, T e = M::id) : _size(n), root(this->build(0, n, e)) {}\n    template <class\
    \ U>\n    persistent_segment_tree(const std::vector<U> &v)\n        : _size(v.size()),\
    \ root(this->build(0, v.size(), v)) {}\n\n    T operator[](int i) const { return\
    \ this->prod(i, i + 1); }\n    T at(int k) const { return this->operator[](k);\
    \ }\n    T get(int k) const { return this->operator[](k); }\n\n    persistent_segment_tree\
    \ set(int k, T val) {\n        assert(0 <= k && k < this->_size);\n        return\
    \ persistent_segment_tree(this->_size, this->set(0, this->_size, k, val, this->root));\n\
    \    }\n    persistent_segment_tree reset(int k) { return this->set(k, M::id);\
    \ }\n\n    T all_prod() const { return this->root->val; }\n    T prod(int a, int\
    \ b) const {\n        assert(0 <= a && b <= this->_size);\n        return this->prod(0,\
    \ this->_size, a, b, this->root);\n    }\n\n  private:\n    int _size;\n    node_pointer\
    \ root;\n\n    static node_pointer merge(node_pointer left, node_pointer right)\
    \ {\n        return new Node(M::op(left->val, right->val), left, right);\n   \
    \ }\n\n    node_pointer build(int l, int r, T val) const {\n        if (l + 1\
    \ == r) return new Node(val);\n        int m = (l + r) >> 1;\n        return this->merge(this->build(l,\
    \ m, val), this->build(m, r, val));\n    }\n    template <class U>\n    node_pointer\
    \ build(int l, int r, const std::vector<U> &v) const {\n        if (l + 1 == r)\
    \ return new Node(v[l]);\n        int m = (l + r) >> 1;\n        return this->merge(this->build(l,\
    \ m, v), this->build(m, r, v));\n    }\n\n    node_pointer set(int l, int r, int\
    \ k, T val, node_pointer node) const {\n        if (l + 1 == r) return new Node(val);\n\
    \        int m = (l + r) >> 1;\n        if (k < m) return this->merge(this->set(l,\
    \ m, k, val, node->left), node->right);\n        else return this->merge(node->left,\
    \ this->set(m, r, k, val, node->right));\n    }\n\n    T prod(int l, int r, int\
    \ a, int b, node_pointer node) const {\n        if (a <= l && r <= b) return node->val;\n\
    \        if (b <= l || r <= a) return M::id;\n        int m = (l + r) >> 1;\n\
    \        return M::op(this->prod(l, m, a, b, node->left), this->prod(m, r, a,\
    \ b, node->right));\n    }\n};\n"
  dependsOn:
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/persistent_segment_tree.hpp
  requiredBy: []
  timestamp: '2023-05-07 20:09:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/segment_tree/persistent_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/persistent_segment_tree.hpp
- /library/lib/segment_tree/persistent_segment_tree.hpp.html
title: lib/segment_tree/persistent_segment_tree.hpp
---
