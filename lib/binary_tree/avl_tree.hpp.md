---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "AVL\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief AVL\u6728\n * \n * @tparam\
    \ T \n */\ntemplate <class T>\nstruct avl_tree {\n    struct Node {\n        T\
    \ val;\n        int height;\n        Node *left, *right;\n\n        constexpr\
    \ Node(T _val) : val(_val), height(1), left(nullptr), right(nullptr) {}\n\n  \
    \      constexpr bool is_leaf() const { return this->left == nullptr && this->right\
    \ == nullptr; }\n    };\n\n    constexpr avl_tree() : root(nullptr) {}\n\n   \
    \ int get_height() const { return this->root == nullptr ? 0 : this->root->height;\
    \ }\n\n    void insert(T val) { this->root = this->insert(this->root, val); }\n\
    \n    void erase(T val) { this->root = this->erase(this->root, val); }\n\n   \
    \ bool contains(T val) const {\n        Node *node = this->root;\n        while\
    \ (node && node->val != val) {\n            if (val < node->val)\n           \
    \     node = node->left;\n            else\n                node = node->right;\n\
    \        }\n        return node != nullptr;\n    }\n\n    int count(T val) const\
    \ { return this->count(this->root, val); }\n\n    void dump(T l, T r) const {\
    \ return this->dump(this->root, l, r); }\n\n  private:\n    Node *root;\n\n  \
    \  constexpr int get_height(Node *node) const { return node == nullptr ? 0 : node->height;\
    \ }\n    constexpr int get_balance_factor(Node *node) const {\n        return\
    \ node == nullptr ? 0 : this->get_height(node->left) - this->get_height(node->right);\n\
    \    }\n\n    constexpr T get_min_val(Node *node) const {\n        assert(node);\n\
    \        while (node->left) { node = node->left; }\n        return node->val;\n\
    \    }\n\n    constexpr Node *rotl(Node *node) {\n        assert(node);\n    \
    \    Node *pivot = node->right;\n        assert(pivot);\n        node->right =\
    \ pivot->left;\n        pivot->left = node;\n        node->height = max(this->get_height(node->left),\
    \ this->get_height(node->right)) + 1;\n        pivot->height = max(this->get_height(pivot->left),\
    \ this->get_height(pivot->right)) + 1;\n        return pivot;\n    }\n\n    constexpr\
    \ Node *rotr(Node *node) {\n        assert(node);\n        Node *pivot = node->left;\n\
    \        assert(pivot);\n        node->left = pivot->right;\n        pivot->right\
    \ = node;\n        node->height = max(this->get_height(node->left), this->get_height(node->right))\
    \ + 1;\n        pivot->height = max(this->get_height(pivot->left), this->get_height(pivot->right))\
    \ + 1;\n        return pivot;\n    }\n\n    constexpr Node *rotlr(Node *node)\
    \ {\n        node->left = this->rotl(node->left);\n        node = this->rotr(node);\n\
    \        return node;\n    }\n\n    constexpr Node *rotrl(Node *node) {\n    \
    \    node->right = this->rotr(node->right);\n        node = this->rotl(node);\n\
    \        return node;\n    }\n\n    constexpr Node *rotate(Node *node) {\n   \
    \     int bf = this->get_balance_factor(node);\n        if (bf < -1) {\n     \
    \       if (this->get_balance_factor(node->right) >= 1)\n                node\
    \ = this->rotrl(node);\n            else\n                node = this->rotl(node);\n\
    \        } else if (bf > 1) {\n            if (this->get_balance_factor(node->left)\
    \ <= -1)\n                node = this->rotlr(node);\n            else\n      \
    \          node = this->rotr(node);\n        } else {\n            node->height\
    \ = max(this->get_height(node->left), this->get_height(node->right)) + 1;\n  \
    \      }\n        return node;\n    }\n\n    constexpr Node *insert(Node *node,\
    \ T val) {\n        if (node == nullptr) return new Node(val);\n        if (val\
    \ < node->val)\n            node->left = this->insert(node->left, val);\n    \
    \    else\n            node->right = this->insert(node->right, val);\n\n     \
    \   return this->rotate(node);\n    }\n\n    constexpr Node *erase(Node *node,\
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
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/avl_tree.hpp
  requiredBy: []
  timestamp: '2022-01-09 16:16:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/binary_tree/avl_tree.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/avl_tree.hpp
- /library/lib/binary_tree/avl_tree.hpp.html
title: "AVL\u6728"
---
