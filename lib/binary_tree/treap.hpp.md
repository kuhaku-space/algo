---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/random/split_mix_64.hpp
    title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 SplitMix64"
  - icon: ':warning:'
    path: lib/random/xorshift.hpp
    title: "\u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Treap
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: random/xorshift.hpp:\
    \ line -1: no such header\n"
  code: "#include \"random/xorshift.hpp\"\n#include \"template/template.hpp\"\n\n\
    /**\n * @brief Treap\n *\n * @tparam T \u8981\u7D20\u306E\u578B\n * @tparam UniformRandomBitGenerator\
    \ \u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668\n */\ntemplate <class T, class UniformRandomBitGenerator\
    \ = Xorshift>\nstruct Treap {\n  private:\n    struct Node {\n        using pointer\
    \ = Node *;\n        T val;\n        UniformRandomBitGenerator::result_type priority;\n\
    \        pointer left, right;\n\n        Node(T _val, UniformRandomBitGenerator::result_type\
    \ _priority)\n            : val(_val), priority(_priority), left(nullptr), right(nullptr)\
    \ {}\n    };\n\n  public:\n    using node_pointer = typename Node::pointer;\n\n\
    \    constexpr Treap() : root(nullptr) {}\n\n    void insert(T val) { this->root\
    \ = this->insert(this->root, val); }\n\n    void erase(T val) { this->root = this->erase(this->root,\
    \ val); }\n\n    bool contains(T val) const {\n        node_pointer node = this->root;\n\
    \        while (node && node->val != val) {\n            if (val < node->val)\
    \ node = node->left;\n            else node = node->right;\n        }\n      \
    \  return node != nullptr;\n    }\n\n    int count(T val) const { return this->count(this->root,\
    \ val); }\n\n  private:\n    UniformRandomBitGenerator gen;\n    node_pointer\
    \ root;\n\n    constexpr T get_min_val(node_pointer node) const {\n        assert(node);\n\
    \        while (node->left) { node = node->left; }\n        return node->val;\n\
    \    }\n\n    constexpr node_pointer rotl(node_pointer node) {\n        assert(node);\n\
    \        node_pointer pivot = node->right;\n        assert(pivot);\n        node->right\
    \ = pivot->left;\n        pivot->left = node;\n        return pivot;\n    }\n\n\
    \    constexpr node_pointer rotr(node_pointer node) {\n        assert(node);\n\
    \        node_pointer pivot = node->left;\n        assert(pivot);\n        node->left\
    \ = pivot->right;\n        pivot->right = node;\n        return pivot;\n    }\n\
    \n    constexpr node_pointer rotate(node_pointer node) {\n        if (node->right\
    \ && node->priority < node->right->priority) {\n            node = this->rotl(node);\n\
    \        } else if (node->left && node->priority < node->left->priority) {\n \
    \           node = this->rotr(node);\n        }\n        return node;\n    }\n\
    \n    constexpr node_pointer insert(node_pointer node, T val) {\n        if (node\
    \ == nullptr) return new Node(val, this->gen());\n        if (val < node->val)\
    \ node->left = this->insert(node->left, val);\n        else node->right = this->insert(node->right,\
    \ val);\n        return this->rotate(node);\n    }\n\n    constexpr node_pointer\
    \ erase(node_pointer node, T val) {\n        if (node == nullptr) return nullptr;\n\
    \        if (val < node->val) {\n            node->left = this->erase(node->left,\
    \ val);\n        } else if (node->val < val) {\n            node->right = this->erase(node->right,\
    \ val);\n        } else {\n            if (node->right == nullptr) {\n       \
    \         return node->left;\n            } else {\n                node->val\
    \ = this->get_min_val(node->right);\n                node->right = this->erase_min(node->right);\n\
    \            }\n        }\n        return this->rotate(node);\n    }\n\n    constexpr\
    \ node_pointer erase_min(node_pointer node) {\n        if (node->left == nullptr)\
    \ return node->right;\n        node->left = this->erase_min(node->left);\n   \
    \     return this->rotate(node);\n    }\n\n    int count(node_pointer node, T\
    \ val) const {\n        if (node == nullptr) return 0;\n        int res = node->val\
    \ == val;\n        if (!(node->val < val)) res += this->count(node->left, val);\n\
    \        if (!(val < node->val)) res += this->count(node->right, val);\n     \
    \   return res;\n    }\n};\n"
  dependsOn:
  - lib/random/xorshift.hpp
  - lib/random/split_mix_64.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/treap.hpp
  requiredBy: []
  timestamp: '2022-05-13 04:24:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/binary_tree/treap.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/treap.hpp
- /library/lib/binary_tree/treap.hpp.html
title: Treap
---
