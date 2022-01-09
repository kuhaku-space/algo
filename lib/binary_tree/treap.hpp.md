---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/algorithm/xorshift.hpp
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
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/xorshift.hpp:\
    \ line -1: no such header\n"
  code: "#include \"algorithm/xorshift.hpp\"\n#include \"template/template.hpp\"\n\
    \ntemplate <class T>\nstruct Treap {\n    struct Node {\n        T val;\n    \
    \    Xorshift::result_type priority;\n        Node *left, *right;\n\n        Node(T\
    \ _val, Xorshift::result_type _priority)\n            : val(_val), priority(_priority),\
    \ left(nullptr), right(nullptr) {}\n    };\n\n    Treap() : root(nullptr) {}\n\
    \n    void insert(T val) { this->root = this->insert(this->root, val); }\n\n \
    \   void erase(T val) { this->root = this->erase(this->root, val); }\n\n    bool\
    \ contains(T val) const {\n        Node *node = this->root;\n        while (node\
    \ && node->val != val) {\n            if (val < node->val)\n                node\
    \ = node->left;\n            else\n                node = node->right;\n     \
    \   }\n        return node != nullptr;\n    }\n\n    int count(T val) const {\
    \ return this->count(this->root, val); }\n\n    void dump(T l, T r) const { return\
    \ this->dump(this->root, l, r); }\n\n  private:\n    Xorshift xor128;\n    Node\
    \ *root;\n\n    constexpr T get_min_val(Node *node) const {\n        assert(node);\n\
    \        while (node->left) { node = node->left; }\n        return node->val;\n\
    \    }\n\n    constexpr Node *rotl(Node *node) {\n        assert(node);\n    \
    \    Node *pivot = node->right;\n        assert(pivot);\n        node->right =\
    \ pivot->left;\n        pivot->left = node;\n        return pivot;\n    }\n\n\
    \    constexpr Node *rotr(Node *node) {\n        assert(node);\n        Node *pivot\
    \ = node->left;\n        assert(pivot);\n        node->left = pivot->right;\n\
    \        pivot->right = node;\n        return pivot;\n    }\n\n    constexpr Node\
    \ *rotate(Node *node) {\n        if (node->right && node->priority < node->right->priority)\
    \ {\n            node = this->rotl(node);\n        } else if (node->left && node->priority\
    \ < node->left->priority) {\n            node = this->rotr(node);\n        }\n\
    \        return node;\n    }\n\n    constexpr Node *insert(Node *node, T val)\
    \ {\n        if (node == nullptr) return new Node(val, this->xor128());\n    \
    \    if (val < node->val)\n            node->left = this->insert(node->left, val);\n\
    \        else\n            node->right = this->insert(node->right, val);\n\n \
    \       return this->rotate(node);\n    }\n\n    constexpr Node *erase(Node *node,\
    \ T val) {\n        if (node == nullptr) return nullptr;\n        if (val < node->val)\
    \ {\n            node->left = this->erase(node->left, val);\n        } else if\
    \ (node->val < val) {\n            node->right = this->erase(node->right, val);\n\
    \        } else {\n            if (node->right == nullptr) {\n               \
    \ return node->left;\n            } else {\n                node->val = this->get_min_val(node->right);\n\
    \                node->right = this->erase_min(node->right);\n            }\n\
    \        }\n        return this->rotate(node);\n    }\n\n    constexpr Node *erase_min(Node\
    \ *node) {\n        if (node->left == nullptr) return node->right;\n        node->left\
    \ = this->erase_min(node->left);\n        return this->rotate(node);\n    }\n\n\
    \    int count(Node *node, T val) const {\n        if (node == nullptr) return\
    \ 0;\n        int res = node->val == val;\n        if (!(node->val < val)) res\
    \ += this->count(node->left, val);\n        if (!(val < node->val)) res += this->count(node->right,\
    \ val);\n        return res;\n    }\n\n    void dump(Node *node, T l, T r) const\
    \ {\n        if (node == nullptr) return;\n        if (!(node->val < l)) this->dump(node->left,\
    \ l, r);\n        if (!(node->val < l) && !(r < node->val)) cout << node->val\
    \ << '\\n';\n        if (!(r < node->val)) this->dump(node->right, l, r);\n  \
    \  }\n};\n"
  dependsOn:
  - lib/algorithm/xorshift.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/treap.hpp
  requiredBy: []
  timestamp: '2022-01-09 16:16:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/binary_tree/treap.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/treap.hpp
- /library/lib/binary_tree/treap.hpp.html
title: lib/binary_tree/treap.hpp
---
