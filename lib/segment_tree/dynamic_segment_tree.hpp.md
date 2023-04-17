---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/pow.hpp
    title: lib/math/pow.hpp
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
    document_title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/pow.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"math/pow.hpp\"\n#include \"segment_tree/monoid.hpp\"\
    \n#include \"template/template.hpp\"\n\n/**\n * @brief \u52D5\u7684\u30BB\u30B0\
    \u30E1\u30F3\u30C8\u6728\n *\n * @tparam M \u30E2\u30CE\u30A4\u30C9\n */\ntemplate\
    \ <class M>\nstruct dynamic_segment_tree {\n  private:\n    using T = typename\
    \ M::value_type;\n\n    struct _node {\n        using pointer = _node *;\n   \
    \     pointer parent, left, right;\n        T value;\n\n        _node(pointer\
    \ ptr) : parent(ptr), left(nullptr), right(nullptr), value(M::id) {}\n    };\n\
    \n  public:\n    using node_ptr = typename _node::pointer;\n\n    dynamic_segment_tree(std::int64_t\
    \ n) : root(), _size(), _log() { this->init(n); }\n\n    T operator[](int k) const\
    \ {\n        node_ptr node = this->root;\n        for (int i = this->_log - 1;\
    \ i >= 0; --i) {\n            if (k >> i & 1) {\n                if (!node->right)\
    \ return M::id;\n                node = node->right;\n            } else {\n \
    \               if (!node->left) return M::id;\n                node = node->left;\n\
    \            }\n        }\n        return node->value;\n    }\n    T at(int k)\
    \ const { return this->operator[](k); }\n    T get(int k) const { return this->operator[](k);\
    \ }\n\n    void init(std::int64_t n) {\n        this->_log = ceil_pow2(n);\n \
    \       this->_size = 1LL << this->_log;\n        this->root = new _node(nullptr);\n\
    \    }\n\n    void set(std::int64_t k, T x) {\n        assert(0 <= k && k < this->_size);\n\
    \        node_ptr node = this->root;\n        for (int i = this->_log - 1; i >=\
    \ 0; --i) {\n            if (k >> i & 1) {\n                if (!node->right)\
    \ node->right = new _node(node);\n                node = node->right;\n      \
    \      } else {\n                if (!node->left) node->left = new _node(node);\n\
    \                node = node->left;\n            }\n        }\n\n        node->value\
    \ = x;\n        while (node->parent) {\n            node = node->parent;\n   \
    \         node->value = M::op(node->left ? node->left->value : M::id,\n      \
    \                          node->right ? node->right->value : M::id);\n      \
    \  }\n    }\n    void reset(std::int64_t k) { this->set(k, M::id); }\n\n    T\
    \ all_prod() const { return this->root ? this->root->value : M::id; }\n    T prod(std::int64_t\
    \ a, std::int64_t b) const {\n        assert(0 <= a && a <= this->_size);\n  \
    \      assert(0 <= b && b <= this->_size);\n        return this->prod(a, b, this->root,\
    \ 0, this->_size);\n    }\n\n    template <class F>\n    std::int64_t max_right(F\
    \ f) const {\n        assert(f(M::id));\n        if (this->root == nullptr ||\
    \ f(this->root->value)) return this->_size;\n        node_ptr node = this->root;\n\
    \        T sm = M::id;\n        std::int64_t l = 0, r = this->_size;\n       \
    \ while (r - l > 1) {\n            std::int64_t m = (l + r) >> 1;\n          \
    \  if (node->left == nullptr || f(M::op(sm, node->left->value))) {\n         \
    \       if (node->left != nullptr) sm = M::op(sm, node->left->value);\n      \
    \          l = m;\n                node = node->right;\n            } else {\n\
    \                r = m;\n                node = node->left;\n            }\n \
    \       }\n        return f(M::op(sm, node->value)) ? r : l;\n    }\n\n    template\
    \ <class F>\n    std::int64_t min_left(F f) const {\n        assert(f(M::id));\n\
    \        if (this->root == nullptr || f(this->root->value)) return 0;\n      \
    \  node_ptr node = this->root;\n        T sm = M::id;\n        std::int64_t l\
    \ = 0, r = this->_size;\n        while (r - l > 1) {\n            std::int64_t\
    \ m = (l + r) >> 1;\n            if (node->right == nullptr || f(M::op(node->right->value,\
    \ sm))) {\n                if (node->right != nullptr) sm = M::op(node->right->value,\
    \ sm);\n                r = m;\n                node = node->left;\n         \
    \   } else {\n                l = m;\n                node = node->right;\n  \
    \          }\n        }\n        return f(M::op(node->value, sm)) ? l : r;\n \
    \   }\n\n  private:\n    node_ptr root;\n    std::int64_t _size, _log;\n\n   \
    \ T prod(std::int64_t a, std::int64_t b, node_ptr node, std::int64_t l, std::int64_t\
    \ r) const {\n        if (a <= l && r <= b) return node->value;\n        if (r\
    \ <= a || b <= l) return M::id;\n\n        return M::op(node->left ? this->prod(a,\
    \ b, node->left, l, (l + r) >> 1) : M::id,\n                     node->right ?\
    \ this->prod(a, b, node->right, (l + r) >> 1, r) : M::id);\n    }\n};\n"
  dependsOn:
  - lib/math/pow.hpp
  - lib/template/template.hpp
  - lib/segment_tree/monoid.hpp
  isVerificationFile: false
  path: lib/segment_tree/dynamic_segment_tree.hpp
  requiredBy: []
  timestamp: '2023-04-17 09:43:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/segment_tree/dynamic_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/dynamic_segment_tree.hpp
- /library/lib/segment_tree/dynamic_segment_tree.hpp.html
title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
