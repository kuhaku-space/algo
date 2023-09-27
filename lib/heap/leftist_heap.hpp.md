---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/leftist_heap.test.cpp
    title: test/aoj/alds1/leftist_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: leftist heap
    links:
    - http://hos.ac/blog/#blog0001
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief leftist heap\n *\n *\
    \ @tparam T \u8981\u7D20\u306E\u578B\n *\n * @see http://hos.ac/blog/#blog0001\n\
    \ */\ntemplate <class T, class Comp = std::less<>>\nstruct leftist_heap {\n  private:\n\
    \    struct _node {\n        using pointer = _node *;\n\n        pointer _left,\
    \ _right;\n        int _rank;\n        T _val;\n\n        constexpr _node() :\
    \ _left(), _right(), _rank(), _val() {}\n        constexpr _node(const T &_val)\
    \ : _left(), _right(), _rank(), _val(_val) {}\n        constexpr _node(T &&_val)\
    \ : _left(), _right(), _rank(), _val(_val) {}\n        template <typename... Args>\n\
    \        constexpr _node(Args &&...args)\n            : _left(), _right(), _rank(),\
    \ _val(std::forward<Args>(args)...) {}\n    };\n\n  public:\n    using value_type\
    \ = T;\n    using node_ptr = typename _node::pointer;\n\n    leftist_heap() :\
    \ _root() {}\n\n    constexpr bool empty() const { return !_root; }\n    constexpr\
    \ T top() const { return _root->_val; }\n\n    constexpr void push(const T &val)\
    \ {\n        auto node = new _node(val);\n        _root = meld(_root, node);\n\
    \    }\n    constexpr void push(T &&val) {\n        auto node = new _node(std::move(val));\n\
    \        _root = meld(_root, node);\n    }\n    template <typename... Args>\n\
    \    constexpr void emplace(Args &&...args) {\n        auto node = new _node(std::forward<Args>(args)...);\n\
    \        _root = meld(_root, node);\n    }\n\n    constexpr void pop() { _root\
    \ = meld(_root->_left, _root->_right); }\n\n    constexpr void meld(const leftist_heap<T,\
    \ Comp> &rhs) { _root = meld(_root, rhs._root); }\n\n  private:\n    node_ptr\
    \ _root;\n    Comp _comp;\n\n    constexpr node_ptr meld(node_ptr a, node_ptr\
    \ b) {\n        if (!a) return b;\n        if (!b) return a;\n        if (_comp(a->_val,\
    \ b->_val)) std::swap(a, b);\n        a->_right = meld(a->_right, b);\n      \
    \  if (!a->_left || a->_left->_rank < a->_right->_rank) std::swap(a->_left, a->_right);\n\
    \        a->_rank = (!a->_right ? 0 : a->_right->_rank) + 1;\n        return a;\n\
    \    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/heap/leftist_heap.hpp
  requiredBy: []
  timestamp: '2023-09-27 03:17:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/alds1/leftist_heap.test.cpp
documentation_of: lib/heap/leftist_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/leftist_heap.hpp
- /library/lib/heap/leftist_heap.hpp.html
title: leftist heap
---
