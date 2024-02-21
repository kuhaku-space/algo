---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/random/xorshift.hpp
    title: "\u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668"
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/itp2/skip_list.test.cpp
    title: test/aoj/itp2/skip_list.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30B9\u30AD\u30C3\u30D7\u30EA\u30B9\u30C8"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: random/xorshift.hpp:\
    \ line -1: no such header\n"
  code: "#include \"random/xorshift.hpp\"\n#include \"template/template.hpp\"\n\n\
    /**\n * @brief \u30B9\u30AD\u30C3\u30D7\u30EA\u30B9\u30C8\n *\n * @tparam T \u8981\
    \u7D20\u306E\u578B\n * @tparam B \u30EA\u30F3\u30AF\u30B5\u30A4\u30BA\n * @tparam\
    \ UniformRandomBitGenerator \u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668\n */\n\
    template <class T, int B = 20, class UniformRandomBitGenerator = Xorshift>\nstruct\
    \ skip_list {\n  private:\n    struct _node {\n        using pointer = _node *;\n\
    \        T val;\n        pointer itr[B];\n\n        constexpr _node() : val(),\
    \ itr{} {}\n        constexpr _node(const T &_val) : val(_val), itr{} {}\n   \
    \     constexpr _node(T &&_val) : val(std::move(_val)), itr{} {}\n        template\
    \ <typename... Args>\n        constexpr _node(Args &&...args) : val(std::forward<Args>(args)...),\
    \ itr{} {}\n    };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\
    \n    skip_list() : head(), gen() { head = new _node(); }\n\n    template <typename...\
    \ Args>\n    void emplace(Args &&...args) {\n        node_ptr new_node = new _node(std::forward<Args>(args)...);\n\
    \        insert_node(new_node);\n    }\n    void insert(const T &val) {\n    \
    \    node_ptr new_node = new _node(val);\n        insert_node(new_node);\n   \
    \ }\n    void insert(T &&val) {\n        node_ptr new_node = new _node(val);\n\
    \        insert_node(new_node);\n    }\n\n    void erase(const T &val) {\n   \
    \     node_ptr delete_node = select_delete_node(val);\n        if (!delete_node)\
    \ return;\n        node_ptr node = head;\n        for (int i = B - 1; i >= 0;\
    \ --i) {\n            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];\n\
    \            if (node->itr[i] == delete_node) node->itr[i] = node->itr[i]->itr[i];\n\
    \        }\n    }\n\n    bool contains(const T &val) const {\n        node_ptr\
    \ node = head;\n        for (int i = B - 1; i >= 0; --i) {\n            while\
    \ (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];\n           \
    \ if (node->itr[i] && node->itr[i]->val == val) return true;\n        }\n    \
    \    return false;\n    }\n\n    int count(const T &val) const {\n        node_ptr\
    \ node = head;\n        for (int i = B - 1; i >= 0; --i) {\n            while\
    \ (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];\n        }\n\n\
    \        int res = 0;\n        while (node->itr[0] && node->itr[0]->val == val)\
    \ ++res, node = node->itr[0];\n        return res;\n    }\n\n  private:\n    node_ptr\
    \ head;\n    UniformRandomBitGenerator gen;\n\n    int create_height() {\n   \
    \     int height = 0;\n        int rand_num = gen();\n        for (int i = 0;\
    \ i < B - 1; ++i) {\n            if (rand_num >> i & 1) break;\n            ++height;\n\
    \        }\n        return height;\n    }\n\n    void insert_node(node_ptr new_node)\
    \ {\n        node_ptr node = head;\n        int height = create_height();\n  \
    \      for (int i = B - 1; i >= 0; --i) {\n            while (node->itr[i] &&\
    \ node->itr[i]->val < new_node->val) node = node->itr[i];\n\n            if (i\
    \ <= height) {\n                new_node->itr[i] = node->itr[i];\n           \
    \     node->itr[i] = new_node;\n            }\n        }\n    }\n\n    node_ptr\
    \ select_delete_node(const T &val) {\n        node_ptr node = head;\n        for\
    \ (int i = B - 1; i >= 0; --i) {\n            while (node->itr[i] && node->itr[i]->val\
    \ < val) node = node->itr[i];\n        }\n        return node->itr[0] && node->itr[0]->val\
    \ == val ? node->itr[0] : nullptr;\n    }\n};\n"
  dependsOn:
  - lib/random/xorshift.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/skip_list.hpp
  requiredBy: []
  timestamp: '2023-10-02 03:03:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/itp2/skip_list.test.cpp
documentation_of: lib/data_structure/skip_list.hpp
layout: document
redirect_from:
- /library/lib/data_structure/skip_list.hpp
- /library/lib/data_structure/skip_list.hpp.html
title: "\u30B9\u30AD\u30C3\u30D7\u30EA\u30B9\u30C8"
---
