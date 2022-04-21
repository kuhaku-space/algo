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
    document_title: skew heap
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
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief skew heap\n *\n * @tparam\
    \ T \u8981\u7D20\u306E\u578B\n */\ntemplate <class T>\nstruct skew_heap {\n  private:\n\
    \    struct _node {\n        using pointer = _node *;\n\n        pointer l, r;\n\
    \        T val;\n\n        constexpr _node() : l(), r(), val() {}\n        constexpr\
    \ _node(T _val) : l(), r(), val(_val) {}\n    };\n\n  public:\n    using node_pointer\
    \ = _node::pointer;\n\n    constexpr auto top() const { return this->root->val;\
    \ }\n    constexpr bool empty() const { return this->root == nullptr; }\n\n  \
    \  void push(T val) {\n        auto node = new _node(val);\n        this->meld(this->root,\
    \ node);\n    }\n\n    void pop() { this->root = this->meld(this->root->l, this->root->r);\
    \ }\n\n    node_pointer meld(node_pointer a, node_pointer b) {\n        if (a\
    \ == nullptr) return b;\n        if (b == nullptr) return a;\n        if (a.val\
    \ > b.val) swap(a, b);\n        a.r = this->meld(a.r, b);\n        swap(a.l, a.r);\n\
    \        return a;\n    }\n\n  private:\n    node_pointer root;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/heap/skew_heap.hpp
  requiredBy: []
  timestamp: '2022-04-16 04:10:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/heap/skew_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/skew_heap.hpp
- /library/lib/heap/skew_heap.hpp.html
title: skew heap
---
