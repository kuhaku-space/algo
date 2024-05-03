---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/patricia_binary_trie.test.cpp
    title: test/yosupo/data_structure/patricia_binary_trie.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "2\u5206\u30D1\u30C8\u30EA\u30B7\u30A2\u6728"
    links:
    - https://kyokkounoite.hatenablog.jp/entry/2021/05/17/170000
  bundledCode: "#line 1 \"lib/binary_tree/patricia_binary_trie.hpp\"\n#include <cassert>\n\
    \n/**\n * @brief 2\u5206\u30D1\u30C8\u30EA\u30B7\u30A2\u6728\n * @see https://kyokkounoite.hatenablog.jp/entry/2021/05/17/170000\n\
    \ *\n * @tparam T\n * @tparam B \u30D3\u30C3\u30C8\u30B5\u30A4\u30BA\n */\ntemplate\
    \ <class T, int B = 31>\nstruct patricia_binary_trie {\n  private:\n    struct\
    \ _node {\n        using pointer = _node *;\n        T val;\n        int len,\
    \ count;\n        pointer ch[2];\n        _node(T _val, int _len, int _count =\
    \ 0)\n            : val(_val), len(_len), count(_count), ch{nullptr, nullptr}\
    \ {}\n    };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n \
    \   patricia_binary_trie() : root(nullptr) {}\n\n    T operator[](int k) const\
    \ {\n        assert(0 <= k && k < size());\n        return get(root, k);\n   \
    \ }\n    T at(int k) const { return operator[](k); }\n    T get(int k) const {\
    \ return operator[](k); }\n    T kth_element(int k) const { return operator[](k);\
    \ }\n\n    constexpr int size() const { return root ? root->count : 0; }\n   \
    \ constexpr bool empty() const { return !root; }\n\n    void insert(T val) {\n\
    \        if (!count(val)) root = insert(root, val);\n    }\n    void erase(T val)\
    \ {\n        if (count(val)) root = erase(root, val);\n    }\n    T max_element(T\
    \ bias = 0) const { return get_min(root, ~bias); }\n    T min_element(T bias =\
    \ 0) const { return get_min(root, bias); }\n    int lower_bound(T val) { return\
    \ count_lower(root, val); }\n    int upper_bound(T val) { return count_lower(root,\
    \ val + 1); }\n    int count(T val) const {\n        if (!root) return 0;\n  \
    \      node_ptr node = root;\n        int rest = node->len;\n        for (int\
    \ i = B - 1; i >= 0; --i) {\n            if (!rest) {\n                node =\
    \ node->ch[val >> i & 1];\n                if (!node) return 0;\n            \
    \    rest += node->len;\n            }\n            if ((val ^ node->val) >> i\
    \ & 1) return 0;\n            --rest;\n        }\n        return node->count;\n\
    \    }\n\n  private:\n    node_ptr root;\n\n    node_ptr insert(node_ptr node,\
    \ T val, int b = B - 1) {\n        if (!node) node = new _node(val, b + 1);\n\
    \        ++node->count;\n        if (b < 0) return node;\n        int len = node->len;\n\
    \        for (int i = 0; i < node->len; ++i) {\n            if (((val ^ node->val)\
    \ >> (b - i) & 1)) {\n                len = i;\n                break;\n     \
    \       }\n        }\n        if (len == b + 1) return node;\n        b -= len;\n\
    \        node_ptr itr = node;\n        if (len != node->len) {\n            itr\
    \ = new _node(val, len, node->count);\n            node->len -= len;\n       \
    \     --node->count;\n            itr->ch[node->val >> b & 1] = node;\n      \
    \  }\n        bool f = val >> b & 1;\n        itr->ch[f] = insert(itr->ch[f],\
    \ val, b);\n        return itr;\n    }\n    node_ptr erase(node_ptr node, T val,\
    \ int b = B - 1) {\n        assert(node);\n        --node->count;\n        if\
    \ (!node->count) return nullptr;\n        b -= node->len;\n        if (b < 0)\
    \ return node;\n        bool f = val >> b & 1;\n        node->ch[f] = erase(node->ch[f],\
    \ val, b);\n        return node;\n    }\n    T get_min(node_ptr node, T val, int\
    \ b = B - 1) const {\n        assert(node);\n        b -= node->len;\n       \
    \ if (b < 0) return node->val;\n        bool f = val >> b & 1;\n        f ^= !node->ch[f];\n\
    \        return get_min(node->ch[f], val, b);\n    }\n    T get(node_ptr node,\
    \ int k, int b = B - 1) const {\n        b -= node->len;\n        if (b < 0) return\
    \ node->val;\n        int m = node->ch[0] ? node->ch[0]->count : 0;\n        return\
    \ k < m ? get(node->ch[0], k, b) : get(node->ch[1], k - m, b);\n    }\n    int\
    \ count_lower(node_ptr node, T val, int b = B - 1) {\n        if (!node || b <\
    \ 0) return 0;\n        b -= node->len;\n        bool f = val >> b & 1;\n    \
    \    return (f && node->ch[0] ? node->ch[0]->count : 0) + count_lower(node->ch[f],\
    \ val, b - 1);\n    }\n};\n\n/**\n * @brief \u591A\u91CD2\u5206\u30D1\u30C8\u30EA\
    \u30B7\u30A2\u6728\n * @see https://kyokkounoite.hatenablog.jp/entry/2021/05/17/170000\n\
    \ *\n * @tparam T\n * @tparam B \u30D3\u30C3\u30C8\u30B5\u30A4\u30BA\n */\ntemplate\
    \ <class T, int B = 31>\nstruct multi_patricia_binary_trie {\n  private:\n   \
    \ struct _node {\n        using pointer = _node *;\n        T val;\n        int\
    \ len, count;\n        pointer ch[2];\n        _node(T _val, int _len, int _count\
    \ = 0)\n            : val(_val), len(_len), count(_count), ch{nullptr, nullptr}\
    \ {}\n    };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n \
    \   multi_patricia_binary_trie() : root(nullptr) {}\n\n    T operator[](int k)\
    \ const {\n        assert(0 <= k && k < size());\n        return get(root, k);\n\
    \    }\n    T at(int k) const { return operator[](k); }\n    T get(int k) const\
    \ { return operator[](k); }\n    T kth_element(int k) const { return operator[](k);\
    \ }\n\n    constexpr int size() const { return root ? root->count : 0; }\n   \
    \ constexpr bool empty() const { return !root; }\n\n    void insert(T val) { root\
    \ = insert(root, val); }\n    void erase(T val) {\n        if (count(val)) root\
    \ = erase(root, val);\n    }\n\n    T max_element(T bias = 0) const { return get_min(root,\
    \ ~bias); }\n    T min_element(T bias = 0) const { return get_min(root, bias);\
    \ }\n    int lower_bound(T val) { return count_lower(root, val); }\n    int upper_bound(T\
    \ val) { return count_lower(root, val + 1); }\n    int count(T val) const {\n\
    \        if (!root) return 0;\n        node_ptr node = root;\n        int rest\
    \ = node->len;\n        for (int i = B - 1; i >= 0; i--) {\n            if (!rest)\
    \ {\n                node = node->ch[val >> i & 1];\n                if (!node)\
    \ return 0;\n                rest += node->len;\n            }\n            if\
    \ ((val ^ node->val) >> i & 1) return 0;\n            --rest;\n        }\n   \
    \     return node->count;\n    }\n\n  private:\n    node_ptr root;\n\n    node_ptr\
    \ insert(node_ptr node, T val, int b = B - 1) {\n        if (!node) node = new\
    \ _node(val, b + 1);\n        ++node->count;\n        if (b < 0) return node;\n\
    \        int len = node->len;\n        for (int i = 0; i < node->len; ++i) {\n\
    \            if (((val ^ node->val) >> (b - i) & 1)) {\n                len =\
    \ i;\n                break;\n            }\n        }\n        if (len == b +\
    \ 1) return node;\n        b -= len;\n        node_ptr itr = node;\n        if\
    \ (len != node->len) {\n            itr = new _node(val, len, node->count);\n\
    \            node->len -= len;\n            --node->count;\n            itr->ch[node->val\
    \ >> b & 1] = node;\n        }\n        bool f = val >> b & 1;\n        itr->ch[f]\
    \ = insert(itr->ch[f], val, b);\n        return itr;\n    }\n    node_ptr erase(node_ptr\
    \ node, T val, int b = B - 1) {\n        assert(node);\n        --node->count;\n\
    \        if (!node->count) return nullptr;\n        b -= node->len;\n        if\
    \ (b < 0) return node;\n        bool f = val >> b & 1;\n        node->ch[f] =\
    \ erase(node->ch[f], val, b);\n        return node;\n    }\n    T get_min(node_ptr\
    \ node, T val, int b = B - 1) const {\n        assert(node);\n        b -= node->len;\n\
    \        if (b < 0) return node->val;\n        bool f = val >> b & 1;\n      \
    \  f ^= !node->ch[f];\n        return get_min(node->ch[f], val, b);\n    }\n \
    \   T get(node_ptr node, int k, int b = B - 1) const {\n        b -= node->len;\n\
    \        if (b < 0) return node->val;\n        int m = node->ch[0] ? node->ch[0]->count\
    \ : 0;\n        return k < m ? get(node->ch[0], k, b) : get(node->ch[1], k - m,\
    \ b);\n    }\n    int count_lower(node_ptr node, T val, int b = B - 1) {\n   \
    \     if (!node || b < 0) return 0;\n        b -= node->len;\n        bool f =\
    \ val >> b & 1;\n        return (f && node->ch[0] ? node->ch[0]->count : 0) +\
    \ count_lower(node->ch[f], val, b - 1);\n    }\n};\n"
  code: "#include <cassert>\n\n/**\n * @brief 2\u5206\u30D1\u30C8\u30EA\u30B7\u30A2\
    \u6728\n * @see https://kyokkounoite.hatenablog.jp/entry/2021/05/17/170000\n *\n\
    \ * @tparam T\n * @tparam B \u30D3\u30C3\u30C8\u30B5\u30A4\u30BA\n */\ntemplate\
    \ <class T, int B = 31>\nstruct patricia_binary_trie {\n  private:\n    struct\
    \ _node {\n        using pointer = _node *;\n        T val;\n        int len,\
    \ count;\n        pointer ch[2];\n        _node(T _val, int _len, int _count =\
    \ 0)\n            : val(_val), len(_len), count(_count), ch{nullptr, nullptr}\
    \ {}\n    };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n \
    \   patricia_binary_trie() : root(nullptr) {}\n\n    T operator[](int k) const\
    \ {\n        assert(0 <= k && k < size());\n        return get(root, k);\n   \
    \ }\n    T at(int k) const { return operator[](k); }\n    T get(int k) const {\
    \ return operator[](k); }\n    T kth_element(int k) const { return operator[](k);\
    \ }\n\n    constexpr int size() const { return root ? root->count : 0; }\n   \
    \ constexpr bool empty() const { return !root; }\n\n    void insert(T val) {\n\
    \        if (!count(val)) root = insert(root, val);\n    }\n    void erase(T val)\
    \ {\n        if (count(val)) root = erase(root, val);\n    }\n    T max_element(T\
    \ bias = 0) const { return get_min(root, ~bias); }\n    T min_element(T bias =\
    \ 0) const { return get_min(root, bias); }\n    int lower_bound(T val) { return\
    \ count_lower(root, val); }\n    int upper_bound(T val) { return count_lower(root,\
    \ val + 1); }\n    int count(T val) const {\n        if (!root) return 0;\n  \
    \      node_ptr node = root;\n        int rest = node->len;\n        for (int\
    \ i = B - 1; i >= 0; --i) {\n            if (!rest) {\n                node =\
    \ node->ch[val >> i & 1];\n                if (!node) return 0;\n            \
    \    rest += node->len;\n            }\n            if ((val ^ node->val) >> i\
    \ & 1) return 0;\n            --rest;\n        }\n        return node->count;\n\
    \    }\n\n  private:\n    node_ptr root;\n\n    node_ptr insert(node_ptr node,\
    \ T val, int b = B - 1) {\n        if (!node) node = new _node(val, b + 1);\n\
    \        ++node->count;\n        if (b < 0) return node;\n        int len = node->len;\n\
    \        for (int i = 0; i < node->len; ++i) {\n            if (((val ^ node->val)\
    \ >> (b - i) & 1)) {\n                len = i;\n                break;\n     \
    \       }\n        }\n        if (len == b + 1) return node;\n        b -= len;\n\
    \        node_ptr itr = node;\n        if (len != node->len) {\n            itr\
    \ = new _node(val, len, node->count);\n            node->len -= len;\n       \
    \     --node->count;\n            itr->ch[node->val >> b & 1] = node;\n      \
    \  }\n        bool f = val >> b & 1;\n        itr->ch[f] = insert(itr->ch[f],\
    \ val, b);\n        return itr;\n    }\n    node_ptr erase(node_ptr node, T val,\
    \ int b = B - 1) {\n        assert(node);\n        --node->count;\n        if\
    \ (!node->count) return nullptr;\n        b -= node->len;\n        if (b < 0)\
    \ return node;\n        bool f = val >> b & 1;\n        node->ch[f] = erase(node->ch[f],\
    \ val, b);\n        return node;\n    }\n    T get_min(node_ptr node, T val, int\
    \ b = B - 1) const {\n        assert(node);\n        b -= node->len;\n       \
    \ if (b < 0) return node->val;\n        bool f = val >> b & 1;\n        f ^= !node->ch[f];\n\
    \        return get_min(node->ch[f], val, b);\n    }\n    T get(node_ptr node,\
    \ int k, int b = B - 1) const {\n        b -= node->len;\n        if (b < 0) return\
    \ node->val;\n        int m = node->ch[0] ? node->ch[0]->count : 0;\n        return\
    \ k < m ? get(node->ch[0], k, b) : get(node->ch[1], k - m, b);\n    }\n    int\
    \ count_lower(node_ptr node, T val, int b = B - 1) {\n        if (!node || b <\
    \ 0) return 0;\n        b -= node->len;\n        bool f = val >> b & 1;\n    \
    \    return (f && node->ch[0] ? node->ch[0]->count : 0) + count_lower(node->ch[f],\
    \ val, b - 1);\n    }\n};\n\n/**\n * @brief \u591A\u91CD2\u5206\u30D1\u30C8\u30EA\
    \u30B7\u30A2\u6728\n * @see https://kyokkounoite.hatenablog.jp/entry/2021/05/17/170000\n\
    \ *\n * @tparam T\n * @tparam B \u30D3\u30C3\u30C8\u30B5\u30A4\u30BA\n */\ntemplate\
    \ <class T, int B = 31>\nstruct multi_patricia_binary_trie {\n  private:\n   \
    \ struct _node {\n        using pointer = _node *;\n        T val;\n        int\
    \ len, count;\n        pointer ch[2];\n        _node(T _val, int _len, int _count\
    \ = 0)\n            : val(_val), len(_len), count(_count), ch{nullptr, nullptr}\
    \ {}\n    };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n \
    \   multi_patricia_binary_trie() : root(nullptr) {}\n\n    T operator[](int k)\
    \ const {\n        assert(0 <= k && k < size());\n        return get(root, k);\n\
    \    }\n    T at(int k) const { return operator[](k); }\n    T get(int k) const\
    \ { return operator[](k); }\n    T kth_element(int k) const { return operator[](k);\
    \ }\n\n    constexpr int size() const { return root ? root->count : 0; }\n   \
    \ constexpr bool empty() const { return !root; }\n\n    void insert(T val) { root\
    \ = insert(root, val); }\n    void erase(T val) {\n        if (count(val)) root\
    \ = erase(root, val);\n    }\n\n    T max_element(T bias = 0) const { return get_min(root,\
    \ ~bias); }\n    T min_element(T bias = 0) const { return get_min(root, bias);\
    \ }\n    int lower_bound(T val) { return count_lower(root, val); }\n    int upper_bound(T\
    \ val) { return count_lower(root, val + 1); }\n    int count(T val) const {\n\
    \        if (!root) return 0;\n        node_ptr node = root;\n        int rest\
    \ = node->len;\n        for (int i = B - 1; i >= 0; i--) {\n            if (!rest)\
    \ {\n                node = node->ch[val >> i & 1];\n                if (!node)\
    \ return 0;\n                rest += node->len;\n            }\n            if\
    \ ((val ^ node->val) >> i & 1) return 0;\n            --rest;\n        }\n   \
    \     return node->count;\n    }\n\n  private:\n    node_ptr root;\n\n    node_ptr\
    \ insert(node_ptr node, T val, int b = B - 1) {\n        if (!node) node = new\
    \ _node(val, b + 1);\n        ++node->count;\n        if (b < 0) return node;\n\
    \        int len = node->len;\n        for (int i = 0; i < node->len; ++i) {\n\
    \            if (((val ^ node->val) >> (b - i) & 1)) {\n                len =\
    \ i;\n                break;\n            }\n        }\n        if (len == b +\
    \ 1) return node;\n        b -= len;\n        node_ptr itr = node;\n        if\
    \ (len != node->len) {\n            itr = new _node(val, len, node->count);\n\
    \            node->len -= len;\n            --node->count;\n            itr->ch[node->val\
    \ >> b & 1] = node;\n        }\n        bool f = val >> b & 1;\n        itr->ch[f]\
    \ = insert(itr->ch[f], val, b);\n        return itr;\n    }\n    node_ptr erase(node_ptr\
    \ node, T val, int b = B - 1) {\n        assert(node);\n        --node->count;\n\
    \        if (!node->count) return nullptr;\n        b -= node->len;\n        if\
    \ (b < 0) return node;\n        bool f = val >> b & 1;\n        node->ch[f] =\
    \ erase(node->ch[f], val, b);\n        return node;\n    }\n    T get_min(node_ptr\
    \ node, T val, int b = B - 1) const {\n        assert(node);\n        b -= node->len;\n\
    \        if (b < 0) return node->val;\n        bool f = val >> b & 1;\n      \
    \  f ^= !node->ch[f];\n        return get_min(node->ch[f], val, b);\n    }\n \
    \   T get(node_ptr node, int k, int b = B - 1) const {\n        b -= node->len;\n\
    \        if (b < 0) return node->val;\n        int m = node->ch[0] ? node->ch[0]->count\
    \ : 0;\n        return k < m ? get(node->ch[0], k, b) : get(node->ch[1], k - m,\
    \ b);\n    }\n    int count_lower(node_ptr node, T val, int b = B - 1) {\n   \
    \     if (!node || b < 0) return 0;\n        b -= node->len;\n        bool f =\
    \ val >> b & 1;\n        return (f && node->ch[0] ? node->ch[0]->count : 0) +\
    \ count_lower(node->ch[f], val, b - 1);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/binary_tree/patricia_binary_trie.hpp
  requiredBy: []
  timestamp: '2024-04-19 12:27:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/patricia_binary_trie.test.cpp
documentation_of: lib/binary_tree/patricia_binary_trie.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/patricia_binary_trie.hpp
- /library/lib/binary_tree/patricia_binary_trie.hpp.html
title: "2\u5206\u30D1\u30C8\u30EA\u30B7\u30A2\u6728"
---
