---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/binary_trie.test.cpp
    title: test/yosupo/data_structure/binary_trie.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "2\u5206\u30C8\u30E9\u30A4\u6728"
    links:
    - https://kazuma8128.hatenablog.com/entry/2018/05/06/022654
  bundledCode: "#line 1 \"lib/binary_tree/binary_trie.hpp\"\n#include <cassert>\n\n\
    /**\n * @brief 2\u5206\u30C8\u30E9\u30A4\u6728\n * @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654\n\
    \ *\n * @tparam T \u8981\u7D20\u306E\u578B\n * @tparam B \u30D3\u30C3\u30C8\u30B5\
    \u30A4\u30BA\n */\ntemplate <class T, int B = 31>\nstruct binary_trie {\n  private:\n\
    \    struct _node {\n        using pointer = _node *;\n        int count;\n  \
    \      pointer ch[2];\n        _node() : count(), ch{nullptr, nullptr} {}\n  \
    \  };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n    constexpr\
    \ binary_trie() : root(nullptr) {}\n\n    T operator[](int k) const {\n      \
    \  assert(0 <= k && k < size());\n        return get(root, k);\n    }\n    T at(int\
    \ k) const { return operator[](k); }\n    T get(int k) const { return operator[](k);\
    \ }\n    T kth_element(int k) const { return operator[](k); }\n\n    constexpr\
    \ bool empty() const { return !root; }\n    constexpr int size() const { return\
    \ empty() ? 0 : root->count; }\n\n    void insert(T val) {\n        if (!count(val))\
    \ root = insert(root, val);\n    }\n    void erase(T val) {\n        if (count(val))\
    \ root = erase(root, val);\n    }\n\n    T max_element(T bias = 0) const { return\
    \ get_min(root, ~bias); }\n    T min_element(T bias = 0) const { return get_min(root,\
    \ bias); }\n    int lower_bound(T val) const { return count_lower(root, val);\
    \ }\n    int upper_bound(T val) const { return count_lower(root, val + 1); }\n\
    \    int count(T val) const {\n        if (!root) return 0;\n        node_ptr\
    \ node = root;\n        for (int i = B - 1; i >= 0; i--) {\n            node =\
    \ node->ch[val >> i & 1];\n            if (!node) return 0;\n        }\n     \
    \   return node->count;\n    }\n\n  private:\n    node_ptr root;\n\n    node_ptr\
    \ insert(node_ptr node, T val, int b = B - 1) {\n        if (!node) node = new\
    \ _node();\n        ++node->count;\n        if (b < 0) return node;\n        bool\
    \ f = val >> b & (T)1;\n        node->ch[f] = insert(node->ch[f], val, b - 1);\n\
    \        return node;\n    }\n    node_ptr erase(node_ptr node, T val, int b =\
    \ B - 1) {\n        assert(node);\n        --node->count;\n        if (!node->count)\
    \ return nullptr;\n        if (b < 0) return node;\n        bool f = val >> b\
    \ & (T)1;\n        node->ch[f] = erase(node->ch[f], val, b - 1);\n        return\
    \ node;\n    }\n    T get_min(node_ptr node, T val, int b = B - 1) const {\n \
    \       assert(node);\n        if (b < 0) return 0;\n        bool f = val >> b\
    \ & (T)1;\n        f ^= !node->ch[f];\n        return get_min(node->ch[f], val,\
    \ b - 1) | ((T)f << (T)b);\n    }\n    T get(node_ptr node, int k, int b = B -\
    \ 1) const {\n        if (b < 0) return 0;\n        int m = node->ch[0] ? node->ch[0]->count\
    \ : 0;\n        return k < m ? get(node->ch[0], k, b - 1) : get(node->ch[1], k\
    \ - m, b - 1) | ((T)1 << b);\n    }\n    int count_lower(node_ptr node, T val,\
    \ int b = B - 1) const {\n        if (!node || b < 0) return 0;\n        bool\
    \ f = val >> b & 1;\n        return (f && node->ch[0] ? node->ch[0]->count : 0)\
    \ + count_lower(node->ch[f], val, b - 1);\n    }\n};\n\n/**\n * @brief \u591A\u91CD\
    2\u5206\u30C8\u30E9\u30A4\u6728\n * @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654\n\
    \ *\n * @tparam T \u8981\u7D20\u306E\u578B\n * @tparam B \u30D3\u30C3\u30C8\u30B5\
    \u30A4\u30BA\n */\ntemplate <class T, int B = 31>\nstruct multi_binary_trie {\n\
    \  private:\n    struct _node {\n        using pointer = _node *;\n        int\
    \ count;\n        pointer ch[2];\n        _node() : count(), ch{nullptr, nullptr}\
    \ {}\n    };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n \
    \   multi_binary_trie() : root(nullptr) {}\n\n    T operator[](int k) const {\n\
    \        assert(0 <= k && k < size());\n        return get(root, k);\n    }\n\
    \    T at(int k) const { return operator[](k); }\n    T get(int k) const { return\
    \ operator[](k); }\n    T kth_element(int k) const { return operator[](k); }\n\
    \n    constexpr int size() const { return root ? root->count : 0; }\n    constexpr\
    \ bool empty() const { return !root; }\n\n    void insert(T val) { root = insert(root,\
    \ val); }\n    void erase(T val) {\n        if (count(val)) root = erase(root,\
    \ val);\n    }\n\n    T max_element(T bias = 0) const { return get_min(root, ~bias);\
    \ }\n    T min_element(T bias = 0) const { return get_min(root, bias); }\n   \
    \ int lower_bound(T val) { return count_lower(root, val); }\n    int upper_bound(T\
    \ val) { return count_lower(root, val + 1); }\n    int count(T val) const {\n\
    \        if (!root) return 0;\n        node_ptr node = root;\n        for (int\
    \ i = B - 1; i >= 0; i--) {\n            node = node->ch[val >> i & (T)1];\n \
    \           if (!node) return 0;\n        }\n        return node->count;\n   \
    \ }\n\n  private:\n    node_ptr root;\n\n    node_ptr insert(node_ptr node, T\
    \ val, int b = B - 1) {\n        if (!node) node = new _node();\n        ++node->count;\n\
    \        if (b < 0) return node;\n        bool f = val >> b & (T)1;\n        node->ch[f]\
    \ = insert(node->ch[f], val, b - 1);\n        return node;\n    }\n    node_ptr\
    \ erase(node_ptr node, T val, int b = B - 1) {\n        assert(node);\n      \
    \  --node->count;\n        if (!node->count) return nullptr;\n        if (b <\
    \ 0) return node;\n        bool f = val >> b & (T)1;\n        node->ch[f] = erase(node->ch[f],\
    \ val, b - 1);\n        return node;\n    }\n    T get_min(node_ptr node, T val,\
    \ int b = B - 1) const {\n        assert(node);\n        if (b < 0) return 0;\n\
    \        bool f = val >> b & (T)1;\n        f ^= !node->ch[f];\n        return\
    \ get_min(node->ch[f], val, b - 1) | ((T)f << (T)b);\n    }\n    T get(node_ptr\
    \ node, int k, int b = B - 1) const {\n        if (b < 0) return 0;\n        int\
    \ m = node->ch[0] ? node->ch[0]->count : 0;\n        return k < m ? get(node->ch[0],\
    \ k, b - 1) : get(node->ch[1], k - m, b - 1) | ((T)1 << b);\n    }\n    int count_lower(node_ptr\
    \ node, T val, int b = B - 1) {\n        if (!node || b < 0) return 0;\n     \
    \   bool f = val >> b & (T)1;\n        return (f && node->ch[0] ? node->ch[0]->count\
    \ : 0) + count_lower(node->ch[f], val, b - 1);\n    }\n};\n"
  code: "#include <cassert>\n\n/**\n * @brief 2\u5206\u30C8\u30E9\u30A4\u6728\n *\
    \ @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654\n *\n * @tparam\
    \ T \u8981\u7D20\u306E\u578B\n * @tparam B \u30D3\u30C3\u30C8\u30B5\u30A4\u30BA\
    \n */\ntemplate <class T, int B = 31>\nstruct binary_trie {\n  private:\n    struct\
    \ _node {\n        using pointer = _node *;\n        int count;\n        pointer\
    \ ch[2];\n        _node() : count(), ch{nullptr, nullptr} {}\n    };\n\n  public:\n\
    \    using node_ptr = typename _node::pointer;\n\n    constexpr binary_trie()\
    \ : root(nullptr) {}\n\n    T operator[](int k) const {\n        assert(0 <= k\
    \ && k < size());\n        return get(root, k);\n    }\n    T at(int k) const\
    \ { return operator[](k); }\n    T get(int k) const { return operator[](k); }\n\
    \    T kth_element(int k) const { return operator[](k); }\n\n    constexpr bool\
    \ empty() const { return !root; }\n    constexpr int size() const { return empty()\
    \ ? 0 : root->count; }\n\n    void insert(T val) {\n        if (!count(val)) root\
    \ = insert(root, val);\n    }\n    void erase(T val) {\n        if (count(val))\
    \ root = erase(root, val);\n    }\n\n    T max_element(T bias = 0) const { return\
    \ get_min(root, ~bias); }\n    T min_element(T bias = 0) const { return get_min(root,\
    \ bias); }\n    int lower_bound(T val) const { return count_lower(root, val);\
    \ }\n    int upper_bound(T val) const { return count_lower(root, val + 1); }\n\
    \    int count(T val) const {\n        if (!root) return 0;\n        node_ptr\
    \ node = root;\n        for (int i = B - 1; i >= 0; i--) {\n            node =\
    \ node->ch[val >> i & 1];\n            if (!node) return 0;\n        }\n     \
    \   return node->count;\n    }\n\n  private:\n    node_ptr root;\n\n    node_ptr\
    \ insert(node_ptr node, T val, int b = B - 1) {\n        if (!node) node = new\
    \ _node();\n        ++node->count;\n        if (b < 0) return node;\n        bool\
    \ f = val >> b & (T)1;\n        node->ch[f] = insert(node->ch[f], val, b - 1);\n\
    \        return node;\n    }\n    node_ptr erase(node_ptr node, T val, int b =\
    \ B - 1) {\n        assert(node);\n        --node->count;\n        if (!node->count)\
    \ return nullptr;\n        if (b < 0) return node;\n        bool f = val >> b\
    \ & (T)1;\n        node->ch[f] = erase(node->ch[f], val, b - 1);\n        return\
    \ node;\n    }\n    T get_min(node_ptr node, T val, int b = B - 1) const {\n \
    \       assert(node);\n        if (b < 0) return 0;\n        bool f = val >> b\
    \ & (T)1;\n        f ^= !node->ch[f];\n        return get_min(node->ch[f], val,\
    \ b - 1) | ((T)f << (T)b);\n    }\n    T get(node_ptr node, int k, int b = B -\
    \ 1) const {\n        if (b < 0) return 0;\n        int m = node->ch[0] ? node->ch[0]->count\
    \ : 0;\n        return k < m ? get(node->ch[0], k, b - 1) : get(node->ch[1], k\
    \ - m, b - 1) | ((T)1 << b);\n    }\n    int count_lower(node_ptr node, T val,\
    \ int b = B - 1) const {\n        if (!node || b < 0) return 0;\n        bool\
    \ f = val >> b & 1;\n        return (f && node->ch[0] ? node->ch[0]->count : 0)\
    \ + count_lower(node->ch[f], val, b - 1);\n    }\n};\n\n/**\n * @brief \u591A\u91CD\
    2\u5206\u30C8\u30E9\u30A4\u6728\n * @see https://kazuma8128.hatenablog.com/entry/2018/05/06/022654\n\
    \ *\n * @tparam T \u8981\u7D20\u306E\u578B\n * @tparam B \u30D3\u30C3\u30C8\u30B5\
    \u30A4\u30BA\n */\ntemplate <class T, int B = 31>\nstruct multi_binary_trie {\n\
    \  private:\n    struct _node {\n        using pointer = _node *;\n        int\
    \ count;\n        pointer ch[2];\n        _node() : count(), ch{nullptr, nullptr}\
    \ {}\n    };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n \
    \   multi_binary_trie() : root(nullptr) {}\n\n    T operator[](int k) const {\n\
    \        assert(0 <= k && k < size());\n        return get(root, k);\n    }\n\
    \    T at(int k) const { return operator[](k); }\n    T get(int k) const { return\
    \ operator[](k); }\n    T kth_element(int k) const { return operator[](k); }\n\
    \n    constexpr int size() const { return root ? root->count : 0; }\n    constexpr\
    \ bool empty() const { return !root; }\n\n    void insert(T val) { root = insert(root,\
    \ val); }\n    void erase(T val) {\n        if (count(val)) root = erase(root,\
    \ val);\n    }\n\n    T max_element(T bias = 0) const { return get_min(root, ~bias);\
    \ }\n    T min_element(T bias = 0) const { return get_min(root, bias); }\n   \
    \ int lower_bound(T val) { return count_lower(root, val); }\n    int upper_bound(T\
    \ val) { return count_lower(root, val + 1); }\n    int count(T val) const {\n\
    \        if (!root) return 0;\n        node_ptr node = root;\n        for (int\
    \ i = B - 1; i >= 0; i--) {\n            node = node->ch[val >> i & (T)1];\n \
    \           if (!node) return 0;\n        }\n        return node->count;\n   \
    \ }\n\n  private:\n    node_ptr root;\n\n    node_ptr insert(node_ptr node, T\
    \ val, int b = B - 1) {\n        if (!node) node = new _node();\n        ++node->count;\n\
    \        if (b < 0) return node;\n        bool f = val >> b & (T)1;\n        node->ch[f]\
    \ = insert(node->ch[f], val, b - 1);\n        return node;\n    }\n    node_ptr\
    \ erase(node_ptr node, T val, int b = B - 1) {\n        assert(node);\n      \
    \  --node->count;\n        if (!node->count) return nullptr;\n        if (b <\
    \ 0) return node;\n        bool f = val >> b & (T)1;\n        node->ch[f] = erase(node->ch[f],\
    \ val, b - 1);\n        return node;\n    }\n    T get_min(node_ptr node, T val,\
    \ int b = B - 1) const {\n        assert(node);\n        if (b < 0) return 0;\n\
    \        bool f = val >> b & (T)1;\n        f ^= !node->ch[f];\n        return\
    \ get_min(node->ch[f], val, b - 1) | ((T)f << (T)b);\n    }\n    T get(node_ptr\
    \ node, int k, int b = B - 1) const {\n        if (b < 0) return 0;\n        int\
    \ m = node->ch[0] ? node->ch[0]->count : 0;\n        return k < m ? get(node->ch[0],\
    \ k, b - 1) : get(node->ch[1], k - m, b - 1) | ((T)1 << b);\n    }\n    int count_lower(node_ptr\
    \ node, T val, int b = B - 1) {\n        if (!node || b < 0) return 0;\n     \
    \   bool f = val >> b & (T)1;\n        return (f && node->ch[0] ? node->ch[0]->count\
    \ : 0) + count_lower(node->ch[f], val, b - 1);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/binary_tree/binary_trie.hpp
  requiredBy: []
  timestamp: '2023-11-16 20:49:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/binary_trie.test.cpp
documentation_of: lib/binary_tree/binary_trie.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/binary_trie.hpp
- /library/lib/binary_tree/binary_trie.hpp.html
title: "2\u5206\u30C8\u30E9\u30A4\u6728"
---
