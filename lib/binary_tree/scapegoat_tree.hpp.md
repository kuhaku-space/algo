---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/itp2/scapegoat_tree.test.cpp
    title: test/aoj/itp2/scapegoat_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30B9\u30B1\u30FC\u30D7\u30B4\u30FC\u30C8\u6728"
    links:
    - https://kopricky.github.io/code/BinarySearchTree/scapegoat_tree.html
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u30B9\u30B1\u30FC\u30D7\
    \u30B4\u30FC\u30C8\u6728\n * @see https://kopricky.github.io/code/BinarySearchTree/scapegoat_tree.html\n\
    \ *\n * @tparam T \u8981\u7D20\u306E\u578B\n */\ntemplate <class T>\nstruct scapegoat_tree\
    \ {\n  private:\n    struct Node {\n        using pointer = Node *;\n\n      \
    \  T val;\n        unsigned int size;\n        pointer left, right;\n\n      \
    \  Node(T _val) : val(_val), size(1), left(nullptr), right(nullptr) {}\n\n   \
    \     static constexpr int get_size(pointer node) { return node ? node->size :\
    \ 0; }\n\n        void eval() { this->size = 1 + Node::get_size(left) + Node::get_size(right);\
    \ }\n    };\n\n  public:\n    using node_ptr = typename Node::pointer;\n\n   \
    \ scapegoat_tree(const double _alpha = 2.0 / 3.0)\n        : root(nullptr), alpha(_alpha),\
    \ log_val(-1.0 / std::log2(_alpha)), max_element_size(0) {}\n\n    constexpr bool\
    \ empty() const { return !(this->root); }\n\n    constexpr int size() const {\
    \ return this->empty() ? 0 : this->root->size; }\n\n    constexpr bool contains(T\
    \ val) const {\n        node_ptr node = this->root;\n        while (node) {\n\
    \            if (node->val == val) return true;\n            node = (val < node->val\
    \ ? node->left : node->right);\n        }\n        return false;\n    }\n\n  \
    \  constexpr T index(int k) const {\n        assert(k < this->size());\n     \
    \   node_ptr node = this->root;\n        while (node) {\n            if (Node::get_size(node->left)\
    \ == k) {\n                break;\n            } else if (k < Node::get_size(node->left))\
    \ {\n                node = node->left;\n            } else {\n              \
    \  k -= Node::get_size(node->left) + 1;\n                node = node->right;\n\
    \            }\n        }\n        return node->val;\n    }\n    constexpr T kth_element(int\
    \ k) const { return this->index(k); }\n\n    void insert(T val) {\n        this->max_element_size\
    \ = std::max(this->max_element_size, this->size() + 1);\n        bool balanced\
    \ = true;\n        this->root = this->insert(this->root, val, 0, balanced);\n\
    \        assert(balanced);\n    }\n\n    void erase(T val) {\n        this->root\
    \ = this->erase(this->root, val);\n        this->check();\n    }\n\n  private:\n\
    \    node_ptr root;\n    double alpha, log_val;\n    int max_element_size;\n\n\
    \    void subtree_dfs(node_ptr node, std::vector<node_ptr> &nodes) const {\n \
    \       if (node->left) this->subtree_dfs(node->left, nodes);\n        nodes.emplace_back(node);\n\
    \        if (node->right) this->subtree_dfs(node->right, nodes);\n    }\n    node_ptr\
    \ build_pbbt_rec(int l, int r, const std::vector<node_ptr> &nodes) {\n       \
    \ if (r - l == 0) {\n            return nullptr;\n        } else if (r - l ==\
    \ 1) {\n            node_ptr node = nodes[l];\n            node->left = node->right\
    \ = nullptr;\n            node->eval();\n            return node;\n        }\n\
    \        int mid = (l + r) >> 1;\n        node_ptr node = nodes[mid];\n      \
    \  node->left = this->build_pbbt_rec(l, mid, nodes);\n        node->right = this->build_pbbt_rec(mid\
    \ + 1, r, nodes);\n        node->eval();\n        return node;\n    }\n    node_ptr\
    \ build_pbbt(node_ptr node) {\n        if (!node) return nullptr;\n        std::vector<node_ptr>\
    \ nodes;\n        this->subtree_dfs(node, nodes);\n        return this->build_pbbt_rec(0,\
    \ nodes.size(), nodes);\n    }\n\n    node_ptr insert(node_ptr node, T val, int\
    \ depth, bool &balanced) {\n        if (!node) {\n            balanced = (depth\
    \ <= std::floor(log_val * std::log2(max_element_size)));\n            return new\
    \ Node(val);\n        } else if (val < node->val) {\n            node->left =\
    \ this->insert(node->left, val, depth + 1, balanced);\n            node->eval();\n\
    \            if (balanced || node->left->size <= alpha * node->size) return node;\n\
    \        } else {\n            node->right = this->insert(node->right, val, depth\
    \ + 1, balanced);\n            node->eval();\n            if (balanced || node->right->size\
    \ <= alpha * node->size) return node;\n        }\n        balanced = true;\n \
    \       return this->build_pbbt(node);\n    }\n\n    node_ptr join(node_ptr left,\
    \ node_ptr right) {\n        if (!left || !right) {\n            return left ?\
    \ left : right;\n        } else if (left->size < right->size) {\n            right->left\
    \ = this->join(left, right->left);\n            right->eval();\n            return\
    \ right;\n        } else {\n            left->right = this->join(left->right,\
    \ right);\n            left->eval();\n            return left;\n        }\n  \
    \  }\n\n    node_ptr erase(node_ptr node, T val) {\n        if (!node) {\n   \
    \         return nullptr;\n        } else if (node->val == val) {\n          \
    \  return this->join(node->left, node->right);\n        } else if (val < node->val)\
    \ {\n            node->left = this->erase(node->left, val);\n            node->eval();\n\
    \            return node;\n        } else {\n            node->right = this->erase(node->right,\
    \ val);\n            node->eval();\n            return node;\n        }\n    }\n\
    \n    void check() {\n        if (this->size() >= alpha * max_element_size) return;\n\
    \        this->root = this->build_pbbt(this->root);\n        this->max_element_size\
    \ = this->size();\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/scapegoat_tree.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/itp2/scapegoat_tree.test.cpp
documentation_of: lib/binary_tree/scapegoat_tree.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/scapegoat_tree.hpp
- /library/lib/binary_tree/scapegoat_tree.hpp.html
title: "\u30B9\u30B1\u30FC\u30D7\u30B4\u30FC\u30C8\u6728"
---
