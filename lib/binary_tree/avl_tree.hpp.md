---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/itp2/avl_tree.test.cpp
    title: test/aoj/itp2/avl_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "AVL\u6728"
    links:
    - https://tjkendev.github.io/procon-library/cpp/binary_search_tree/avl-tree.html
  bundledCode: "#line 1 \"lib/binary_tree/avl_tree.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n\n/**\n * @brief AVL\u6728\n * @see https://tjkendev.github.io/procon-library/cpp/binary_search_tree/avl-tree.html\n\
    \ *\n * @tparam T \u8981\u7D20\u306E\u578B\n */\ntemplate <class T>\nstruct avl_tree\
    \ {\n  private:\n    struct _node {\n        using pointer = _node *;\n      \
    \  T val;\n        int height;\n        pointer left, right;\n\n        constexpr\
    \ _node(T _val) : val(_val), height(1), left(nullptr), right(nullptr) {}\n\n \
    \       static constexpr int get_height(pointer node) { return node == nullptr\
    \ ? 0 : node->height; }\n        static constexpr int get_balance_factor(pointer\
    \ node) {\n            return node == nullptr ? 0\n                          \
    \         : _node::get_height(node->left) - _node::get_height(node->right);\n\
    \        }\n\n        constexpr void set_height() {\n            height = std::max(_node::get_height(left),\
    \ _node::get_height(right)) + 1;\n        }\n        constexpr bool is_leaf()\
    \ const { return left == nullptr && right == nullptr; }\n    };\n\n  public:\n\
    \    using node_type = _node;\n    using node_ptr = typename _node::pointer;\n\
    \n    constexpr avl_tree() : root(nullptr) {}\n\n    void insert(T val) { root\
    \ = insert(root, val); }\n\n    void erase(T val) { root = erase(root, val); }\n\
    \n    bool contains(T val) const {\n        node_ptr node = root;\n        while\
    \ (node && node->val != val) {\n            if (val < node->val) node = node->left;\n\
    \            else node = node->right;\n        }\n        return node != nullptr;\n\
    \    }\n\n    int count(T val) const { return count(root, val); }\n\n    node_ptr\
    \ lower_bound(T val) const {\n        node_ptr res = nullptr, node = root;\n \
    \       while (node) {\n            if (!(node->val < val)) {\n              \
    \  res = node;\n                node = node->left;\n            } else {\n   \
    \             node = node->right;\n            }\n        }\n        return res;\n\
    \    }\n\n    node_ptr upper_bound(T val) const {\n        node_ptr res = nullptr,\
    \ node = root;\n        while (node) {\n            if (val < node->val) {\n \
    \               res = node;\n                node = node->left;\n            }\
    \ else {\n                node = node->right;\n            }\n        }\n    \
    \    return res;\n    }\n\n  private:\n    node_ptr root;\n\n    constexpr T get_min_val(node_ptr\
    \ node) const {\n        assert(node);\n        while (node->left) node = node->left;\n\
    \        return node->val;\n    }\n\n    constexpr node_ptr rotl(node_ptr node)\
    \ {\n        assert(node);\n        node_ptr pivot = node->right;\n        assert(pivot);\n\
    \        node->right = pivot->left;\n        pivot->left = node;\n        node->set_height();\n\
    \        pivot->set_height();\n        return pivot;\n    }\n\n    constexpr node_ptr\
    \ rotr(node_ptr node) {\n        assert(node);\n        node_ptr pivot = node->left;\n\
    \        assert(pivot);\n        node->left = pivot->right;\n        pivot->right\
    \ = node;\n        node->set_height();\n        pivot->set_height();\n       \
    \ return pivot;\n    }\n\n    constexpr node_ptr rotlr(node_ptr node) {\n    \
    \    node->left = rotl(node->left);\n        node = rotr(node);\n        return\
    \ node;\n    }\n\n    constexpr node_ptr rotrl(node_ptr node) {\n        node->right\
    \ = rotr(node->right);\n        node = rotl(node);\n        return node;\n   \
    \ }\n\n    constexpr node_ptr rotate(node_ptr node) {\n        int bf = node_type::get_balance_factor(node);\n\
    \        if (bf < -1) {\n            if (node_type::get_balance_factor(node->right)\
    \ >= 1) node = rotrl(node);\n            else node = rotl(node);\n        } else\
    \ if (bf > 1) {\n            if (node_type::get_balance_factor(node->left) <=\
    \ -1) node = rotlr(node);\n            else node = rotr(node);\n        } else\
    \ {\n            node->set_height();\n        }\n        return node;\n    }\n\
    \n    constexpr node_ptr insert(node_ptr node, T val) {\n        if (node == nullptr)\
    \ return new _node(val);\n        if (val < node->val) node->left = insert(node->left,\
    \ val);\n        else node->right = insert(node->right, val);\n\n        return\
    \ rotate(node);\n    }\n\n    constexpr node_ptr erase(node_ptr node, T val) {\n\
    \        if (node == nullptr) return nullptr;\n        if (val < node->val) {\n\
    \            node->left = erase(node->left, val);\n        } else if (node->val\
    \ < val) {\n            node->right = erase(node->right, val);\n        } else\
    \ {\n            if (node->right == nullptr) {\n                return node->left;\n\
    \            } else {\n                node->val = get_min_val(node->right);\n\
    \                node->right = erase_min(node->right);\n            }\n      \
    \  }\n        return rotate(node);\n    }\n\n    constexpr node_ptr erase_min(node_ptr\
    \ node) {\n        if (node->left == nullptr) return node->right;\n        node->left\
    \ = erase_min(node->left);\n        return rotate(node);\n    }\n\n    int count(node_ptr\
    \ node, T val) const {\n        if (node == nullptr) return 0;\n        int res\
    \ = node->val == val;\n        if (!(node->val < val)) res += count(node->left,\
    \ val);\n        if (!(val < node->val)) res += count(node->right, val);\n   \
    \     return res;\n    }\n};\n"
  code: "#include <algorithm>\n#include <cassert>\n\n/**\n * @brief AVL\u6728\n *\
    \ @see https://tjkendev.github.io/procon-library/cpp/binary_search_tree/avl-tree.html\n\
    \ *\n * @tparam T \u8981\u7D20\u306E\u578B\n */\ntemplate <class T>\nstruct avl_tree\
    \ {\n  private:\n    struct _node {\n        using pointer = _node *;\n      \
    \  T val;\n        int height;\n        pointer left, right;\n\n        constexpr\
    \ _node(T _val) : val(_val), height(1), left(nullptr), right(nullptr) {}\n\n \
    \       static constexpr int get_height(pointer node) { return node == nullptr\
    \ ? 0 : node->height; }\n        static constexpr int get_balance_factor(pointer\
    \ node) {\n            return node == nullptr ? 0\n                          \
    \         : _node::get_height(node->left) - _node::get_height(node->right);\n\
    \        }\n\n        constexpr void set_height() {\n            height = std::max(_node::get_height(left),\
    \ _node::get_height(right)) + 1;\n        }\n        constexpr bool is_leaf()\
    \ const { return left == nullptr && right == nullptr; }\n    };\n\n  public:\n\
    \    using node_type = _node;\n    using node_ptr = typename _node::pointer;\n\
    \n    constexpr avl_tree() : root(nullptr) {}\n\n    void insert(T val) { root\
    \ = insert(root, val); }\n\n    void erase(T val) { root = erase(root, val); }\n\
    \n    bool contains(T val) const {\n        node_ptr node = root;\n        while\
    \ (node && node->val != val) {\n            if (val < node->val) node = node->left;\n\
    \            else node = node->right;\n        }\n        return node != nullptr;\n\
    \    }\n\n    int count(T val) const { return count(root, val); }\n\n    node_ptr\
    \ lower_bound(T val) const {\n        node_ptr res = nullptr, node = root;\n \
    \       while (node) {\n            if (!(node->val < val)) {\n              \
    \  res = node;\n                node = node->left;\n            } else {\n   \
    \             node = node->right;\n            }\n        }\n        return res;\n\
    \    }\n\n    node_ptr upper_bound(T val) const {\n        node_ptr res = nullptr,\
    \ node = root;\n        while (node) {\n            if (val < node->val) {\n \
    \               res = node;\n                node = node->left;\n            }\
    \ else {\n                node = node->right;\n            }\n        }\n    \
    \    return res;\n    }\n\n  private:\n    node_ptr root;\n\n    constexpr T get_min_val(node_ptr\
    \ node) const {\n        assert(node);\n        while (node->left) node = node->left;\n\
    \        return node->val;\n    }\n\n    constexpr node_ptr rotl(node_ptr node)\
    \ {\n        assert(node);\n        node_ptr pivot = node->right;\n        assert(pivot);\n\
    \        node->right = pivot->left;\n        pivot->left = node;\n        node->set_height();\n\
    \        pivot->set_height();\n        return pivot;\n    }\n\n    constexpr node_ptr\
    \ rotr(node_ptr node) {\n        assert(node);\n        node_ptr pivot = node->left;\n\
    \        assert(pivot);\n        node->left = pivot->right;\n        pivot->right\
    \ = node;\n        node->set_height();\n        pivot->set_height();\n       \
    \ return pivot;\n    }\n\n    constexpr node_ptr rotlr(node_ptr node) {\n    \
    \    node->left = rotl(node->left);\n        node = rotr(node);\n        return\
    \ node;\n    }\n\n    constexpr node_ptr rotrl(node_ptr node) {\n        node->right\
    \ = rotr(node->right);\n        node = rotl(node);\n        return node;\n   \
    \ }\n\n    constexpr node_ptr rotate(node_ptr node) {\n        int bf = node_type::get_balance_factor(node);\n\
    \        if (bf < -1) {\n            if (node_type::get_balance_factor(node->right)\
    \ >= 1) node = rotrl(node);\n            else node = rotl(node);\n        } else\
    \ if (bf > 1) {\n            if (node_type::get_balance_factor(node->left) <=\
    \ -1) node = rotlr(node);\n            else node = rotr(node);\n        } else\
    \ {\n            node->set_height();\n        }\n        return node;\n    }\n\
    \n    constexpr node_ptr insert(node_ptr node, T val) {\n        if (node == nullptr)\
    \ return new _node(val);\n        if (val < node->val) node->left = insert(node->left,\
    \ val);\n        else node->right = insert(node->right, val);\n\n        return\
    \ rotate(node);\n    }\n\n    constexpr node_ptr erase(node_ptr node, T val) {\n\
    \        if (node == nullptr) return nullptr;\n        if (val < node->val) {\n\
    \            node->left = erase(node->left, val);\n        } else if (node->val\
    \ < val) {\n            node->right = erase(node->right, val);\n        } else\
    \ {\n            if (node->right == nullptr) {\n                return node->left;\n\
    \            } else {\n                node->val = get_min_val(node->right);\n\
    \                node->right = erase_min(node->right);\n            }\n      \
    \  }\n        return rotate(node);\n    }\n\n    constexpr node_ptr erase_min(node_ptr\
    \ node) {\n        if (node->left == nullptr) return node->right;\n        node->left\
    \ = erase_min(node->left);\n        return rotate(node);\n    }\n\n    int count(node_ptr\
    \ node, T val) const {\n        if (node == nullptr) return 0;\n        int res\
    \ = node->val == val;\n        if (!(node->val < val)) res += count(node->left,\
    \ val);\n        if (!(val < node->val)) res += count(node->right, val);\n   \
    \     return res;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/binary_tree/avl_tree.hpp
  requiredBy: []
  timestamp: '2023-11-16 06:51:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/itp2/avl_tree.test.cpp
documentation_of: lib/binary_tree/avl_tree.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/avl_tree.hpp
- /library/lib/binary_tree/avl_tree.hpp.html
title: "AVL\u6728"
---
