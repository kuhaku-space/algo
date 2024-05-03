---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/random/xorshift.hpp
    title: "\u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/itp2/treap.test.cpp
    title: test/aoj/itp2/treap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Treap
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: random/xorshift.hpp:\
    \ line -1: no such header\n"
  code: "#include <cassert>\n#include \"random/xorshift.hpp\"\n\n/**\n * @brief Treap\n\
    \ *\n * @tparam T \u8981\u7D20\u306E\u578B\n * @tparam UniformRandomBitGenerator\
    \ \u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668\n */\ntemplate <class T, class UniformRandomBitGenerator\
    \ = Xorshift>\nstruct Treap {\n  private:\n    struct _node {\n        using pointer\
    \ = _node *;\n        T val;\n        typename UniformRandomBitGenerator::result_type\
    \ priority;\n        pointer left, right;\n\n        _node(T _val, typename UniformRandomBitGenerator::result_type\
    \ _priority)\n            : val(_val), priority(_priority), left(nullptr), right(nullptr)\
    \ {}\n    };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n \
    \   constexpr Treap() : root(nullptr) {}\n\n    void insert(T val) { root = insert(root,\
    \ val); }\n\n    void erase(T val) { root = erase(root, val); }\n\n    bool contains(T\
    \ val) const {\n        node_ptr node = root;\n        while (node && node->val\
    \ != val) {\n            if (val < node->val) node = node->left;\n           \
    \ else node = node->right;\n        }\n        return node != nullptr;\n    }\n\
    \n    int count(T val) const { return count(root, val); }\n\n  private:\n    UniformRandomBitGenerator\
    \ gen;\n    node_ptr root;\n\n    constexpr T get_min_val(node_ptr node) const\
    \ {\n        assert(node);\n        while (node->left) { node = node->left; }\n\
    \        return node->val;\n    }\n\n    constexpr node_ptr rotl(node_ptr node)\
    \ {\n        assert(node);\n        node_ptr pivot = node->right;\n        assert(pivot);\n\
    \        node->right = pivot->left;\n        pivot->left = node;\n        return\
    \ pivot;\n    }\n\n    constexpr node_ptr rotr(node_ptr node) {\n        assert(node);\n\
    \        node_ptr pivot = node->left;\n        assert(pivot);\n        node->left\
    \ = pivot->right;\n        pivot->right = node;\n        return pivot;\n    }\n\
    \n    constexpr node_ptr rotate(node_ptr node) {\n        if (node->right && node->priority\
    \ < node->right->priority) node = rotl(node);\n        else if (node->left &&\
    \ node->priority < node->left->priority) node = rotr(node);\n        return node;\n\
    \    }\n\n    constexpr node_ptr insert(node_ptr node, T val) {\n        if (node\
    \ == nullptr) return new _node(val, gen());\n        if (val < node->val) node->left\
    \ = insert(node->left, val);\n        else node->right = insert(node->right, val);\n\
    \        return rotate(node);\n    }\n\n    constexpr node_ptr erase(node_ptr\
    \ node, T val) {\n        if (node == nullptr) return nullptr;\n        if (val\
    \ < node->val) {\n            node->left = erase(node->left, val);\n        }\
    \ else if (node->val < val) {\n            node->right = erase(node->right, val);\n\
    \        } else {\n            if (node->right == nullptr) {\n               \
    \ return node->left;\n            } else {\n                node->val = get_min_val(node->right);\n\
    \                node->right = erase_min(node->right);\n            }\n      \
    \  }\n        return rotate(node);\n    }\n\n    constexpr node_ptr erase_min(node_ptr\
    \ node) {\n        if (node->left == nullptr) return node->right;\n        node->left\
    \ = erase_min(node->left);\n        return rotate(node);\n    }\n\n    int count(node_ptr\
    \ node, T val) const {\n        if (node == nullptr) return 0;\n        int res\
    \ = node->val == val;\n        if (!(node->val < val)) res += count(node->left,\
    \ val);\n        if (!(val < node->val)) res += count(node->right, val);\n   \
    \     return res;\n    }\n};\n"
  dependsOn:
  - lib/random/xorshift.hpp
  isVerificationFile: false
  path: lib/binary_tree/treap.hpp
  requiredBy: []
  timestamp: '2024-04-19 12:27:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/itp2/treap.test.cpp
documentation_of: lib/binary_tree/treap.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/treap.hpp
- /library/lib/binary_tree/treap.hpp.html
title: Treap
---
