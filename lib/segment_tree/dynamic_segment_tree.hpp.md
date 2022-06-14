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
    document_title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u52D5\u7684\u30BB\u30B0\
    \u30E1\u30F3\u30C8\u6728\n *\n * @tparam T\n * @tparam F\n */\ntemplate <class\
    \ T, class F>\nstruct dynamic_segment_tree {\n    struct Node {\n        Node\
    \ *parent, *left, *right;\n        T value;\n\n        Node(Node *ptr) : parent(ptr),\
    \ left(nullptr), right(nullptr), value() {}\n    };\n\n    Node *root;\n    int64_t\
    \ N;\n    const T e;\n    const F op;\n\n    dynamic_segment_tree(int64_t _n,\
    \ T _e, F &&_op) : e(_e), op(_op) { init(_n); }\n    dynamic_segment_tree(int64_t\
    \ _n, T _e, const F &_op) : e(_e), op(_op) { init(_n); }\n\n    void init(int64_t\
    \ n) {\n        for (this->N = 1; N < n; this->N <<= 1) {}\n        this->root\
    \ = new Node(nullptr);\n    }\n\n    void update(int64_t k, T x) {\n        assert(0\
    \ <= k && k < N);\n        Node *node = this->root;\n        int64_t l = 0, r\
    \ = this->N;\n        while (r - l > 1) {\n            int64_t m = (l + r) >>\
    \ 1;\n            if (k < m) {\n                if (!node->left) node->left =\
    \ new Node(node);\n                node = node->left;\n                r = m;\n\
    \            } else {\n                if (!node->right) node->right = new Node(node);\n\
    \                node = node->right;\n                l = m;\n            }\n\
    \        }\n\n        node->value = x;\n        while (node->parent) {\n     \
    \       node = node->parent;\n            node->value =\n                op(node->left\
    \ ? node->left->value : e, node->right ? node->right->value : e);\n        }\n\
    \    }\n\n    T query() const { return this->root->value; }\n    T query(int64_t\
    \ a, int64_t b) const {\n        assert(0 <= a && a <= N);\n        assert(0 <=\
    \ b && b <= N);\n        return this->query(a, b, this->root, 0, this->N);\n \
    \   }\n    T query(int64_t a, int64_t b, Node *node, int64_t l, int64_t r) const\
    \ {\n        if (a <= l && r <= b) return node->value;\n        if (r <= a ||\
    \ b <= l) return e;\n\n        return op(node->left ? this->query(a, b, node->left,\
    \ l, (l + r) >> 1) : e,\n                  node->right ? this->query(a, b, node->right,\
    \ (l + r) >> 1, r) : e);\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/dynamic_segment_tree.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/segment_tree/dynamic_segment_tree.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/dynamic_segment_tree.hpp
- /library/lib/segment_tree/dynamic_segment_tree.hpp.html
title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
