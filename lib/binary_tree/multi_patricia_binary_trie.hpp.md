---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "2\u5206\u30D1\u30C8\u30EA\u30B7\u30A2\u6728(\u91CD\u8907\u3042\
      \u308A)"
    links:
    - https://kyokkounoite.hatenablog.jp/entry/2021/05/17/170000
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief 2\u5206\u30D1\u30C8\u30EA\
    \u30B7\u30A2\u6728(\u91CD\u8907\u3042\u308A)\n * @ref https://kyokkounoite.hatenablog.jp/entry/2021/05/17/170000\
    \ \"\u53C2\u8003\"\n *\n * @tparam T\n * @tparam B \u30D3\u30C3\u30C8\u30B5\u30A4\
    \u30BA\n */\ntemplate <class T, int B = 31>\nstruct multi_patricia_binary_trie\
    \ {\n    struct Node {\n        T val;\n        int len, count;\n        Node*\
    \ ch[2];\n        Node(T _val, int _len, int _count = 0)\n            : val(_val),\
    \ len(_len), count(_count), ch{nullptr, nullptr} {}\n    };\n\n    Node* root;\n\
    \n    multi_patricia_binary_trie() : root(nullptr) {}\n\n    T operator[](int\
    \ k) const {\n        assert(0 <= k && k < this->size());\n        return this->get(root,\
    \ k);\n    }\n\n    int size() const { return this->root ? this->root->count :\
    \ 0; }\n    bool empty() const { return !this->root; }\n    void insert(T val)\
    \ { this->root = this->add(this->root, val); }\n    void erase(T val) {\n    \
    \    if (this->count(val)) this->root = this->sub(this->root, val);\n    }\n \
    \   T kth_element(int k) const {\n        assert(0 <= k && k < this->size());\n\
    \        return this->get(this->root, k);\n    }\n    T max_element(T bias = 0)\
    \ const { return this->get_min(this->root, ~bias); }\n    T min_element(T bias\
    \ = 0) const { return this->get_min(this->root, bias); }\n    int lower_bound(T\
    \ val) { return this->count_lower(this->root, val); }\n    int upper_bound(T val)\
    \ { return this->count_lower(this->root, val + 1); }\n    int count(T val) const\
    \ {\n        if (!this->root) return 0;\n        Node* node = this->root;\n  \
    \      int rest = node->len;\n        for (int i = B - 1; i >= 0; i--) {\n   \
    \         if (!rest) {\n                node = node->ch[val >> i & 1];\n     \
    \           if (!node) return 0;\n                rest += node->len;\n       \
    \     }\n            if ((val ^ node->val) >> i & 1) return 0;\n            --rest;\n\
    \        }\n        return node->count;\n    }\n\n  private:\n    Node* add(Node*\
    \ node, T val, int b = B - 1) {\n        if (!node) node = new Node(val, b + 1);\n\
    \        ++node->count;\n        if (b < 0) return node;\n        int len = node->len;\n\
    \        for (int i = 0; i < node->len; ++i) {\n            if (((val ^ node->val)\
    \ >> (b - i) & 1)) {\n                len = i;\n                break;\n     \
    \       }\n        }\n        if (len == b + 1) return node;\n        b -= len;\n\
    \        Node* itr = node;\n        if (len != node->len) {\n            itr =\
    \ new Node(val, len, node->count);\n            node->len -= len;\n          \
    \  --node->count;\n            itr->ch[node->val >> b & 1] = node;\n        }\n\
    \        bool f = val >> b & 1;\n        itr->ch[f] = this->add(itr->ch[f], val,\
    \ b);\n        return itr;\n    }\n    Node* sub(Node* node, T val, int b = B\
    \ - 1) {\n        assert(node);\n        --node->count;\n        if (!node->count)\
    \ return nullptr;\n        b -= node->len;\n        if (b < 0) return node;\n\
    \        bool f = val >> b & 1;\n        node->ch[f] = this->sub(node->ch[f],\
    \ val, b);\n        return node;\n    }\n    T get_min(Node* node, T val, int\
    \ b = B - 1) const {\n        assert(node);\n        b -= node->len;\n       \
    \ if (b < 0) return node->val;\n        bool f = val >> b & 1;\n        f ^= !node->ch[f];\n\
    \        return this->get_min(node->ch[f], val, b);\n    }\n    T get(Node* node,\
    \ int k, int b = B - 1) const {\n        b -= node->len;\n        if (b < 0) return\
    \ node->val;\n        int m = node->ch[0] ? node->ch[0]->count : 0;\n        return\
    \ k < m ? this->get(node->ch[0], k, b) : this->get(node->ch[1], k - m, b);\n \
    \   }\n    int count_lower(Node* node, T val, int b = B - 1) {\n        if (!node\
    \ || b < 0) return 0;\n        b -= node->len;\n        bool f = val >> b & 1;\n\
    \        return (f && node->ch[0] ? node->ch[0]->count : 0) +\n              \
    \ this->count_lower(node->ch[f], val, b - 1);\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/multi_patricia_binary_trie.hpp
  requiredBy: []
  timestamp: '2021-10-02 20:25:15+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/binary_tree/multi_patricia_binary_trie.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/multi_patricia_binary_trie.hpp
- /library/lib/binary_tree/multi_patricia_binary_trie.hpp.html
title: "2\u5206\u30D1\u30C8\u30EA\u30B7\u30A2\u6728(\u91CD\u8907\u3042\u308A)"
---
