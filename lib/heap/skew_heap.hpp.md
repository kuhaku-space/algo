---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/skew_heap.test.cpp
    title: test/aoj/alds1/skew_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: skew heap
    links:
    - http://hos.ac/blog/#blog0001
  bundledCode: "#line 1 \"lib/heap/skew_heap.hpp\"\n#include <functional>\n#include\
    \ <utility>\n\n/**\n * @brief skew heap\n *\n * @tparam T \u8981\u7D20\u306E\u578B\
    \n *\n * @see http://hos.ac/blog/#blog0001\n */\ntemplate <class T, class Comp\
    \ = std::less<>>\nstruct skew_heap {\n  private:\n    struct _node {\n       \
    \ using pointer = _node *;\n\n        pointer _left, _right;\n        T _val;\n\
    \n        constexpr _node() : _left(), _right(), _val() {}\n        constexpr\
    \ _node(const T &_val) : _left(), _right(), _val(_val) {}\n        constexpr _node(T\
    \ &&_val) : _left(), _right(), _val(std::move(_val)) {}\n        template <typename...\
    \ Args>\n        constexpr _node(Args &&...args) : _left(), _right(), _val(std::forward<Args>(args)...)\
    \ {}\n    };\n\n  public:\n    using value_type = T;\n    using node_pointer =\
    \ typename _node::pointer;\n\n    constexpr skew_heap() : _root() {}\n\n    constexpr\
    \ bool empty() const { return !_root; }\n    constexpr T top() const { return\
    \ _root->_val; }\n\n    constexpr void push(const T &val) {\n        auto node\
    \ = new _node(val);\n        _root = meld(_root, node);\n    }\n    constexpr\
    \ void push(T &&val) {\n        auto node = new _node(std::move(val));\n     \
    \   _root = meld(_root, node);\n    }\n    template <typename... Args>\n    constexpr\
    \ void emplace(Args &&...args) {\n        auto node = new _node(std::forward<Args>(args)...);\n\
    \        _root = meld(_root, node);\n    }\n\n    constexpr void pop() { _root\
    \ = meld(_root->_left, _root->_right); }\n\n    constexpr void meld(const skew_heap<T,\
    \ Comp> &rhs) { _root = meld(_root, rhs->_root); }\n\n  private:\n    node_pointer\
    \ _root;\n    Comp _comp;\n\n    constexpr node_pointer meld(node_pointer a, node_pointer\
    \ b) {\n        if (!a) return b;\n        if (!b) return a;\n        if (_comp(a->_val,\
    \ b->_val)) std::swap(a, b);\n        a->_right = meld(a->_right, b);\n      \
    \  std::swap(a->_left, a->_right);\n        return a;\n    }\n};\n"
  code: "#include <functional>\n#include <utility>\n\n/**\n * @brief skew heap\n *\n\
    \ * @tparam T \u8981\u7D20\u306E\u578B\n *\n * @see http://hos.ac/blog/#blog0001\n\
    \ */\ntemplate <class T, class Comp = std::less<>>\nstruct skew_heap {\n  private:\n\
    \    struct _node {\n        using pointer = _node *;\n\n        pointer _left,\
    \ _right;\n        T _val;\n\n        constexpr _node() : _left(), _right(), _val()\
    \ {}\n        constexpr _node(const T &_val) : _left(), _right(), _val(_val) {}\n\
    \        constexpr _node(T &&_val) : _left(), _right(), _val(std::move(_val))\
    \ {}\n        template <typename... Args>\n        constexpr _node(Args &&...args)\
    \ : _left(), _right(), _val(std::forward<Args>(args)...) {}\n    };\n\n  public:\n\
    \    using value_type = T;\n    using node_pointer = typename _node::pointer;\n\
    \n    constexpr skew_heap() : _root() {}\n\n    constexpr bool empty() const {\
    \ return !_root; }\n    constexpr T top() const { return _root->_val; }\n\n  \
    \  constexpr void push(const T &val) {\n        auto node = new _node(val);\n\
    \        _root = meld(_root, node);\n    }\n    constexpr void push(T &&val) {\n\
    \        auto node = new _node(std::move(val));\n        _root = meld(_root, node);\n\
    \    }\n    template <typename... Args>\n    constexpr void emplace(Args &&...args)\
    \ {\n        auto node = new _node(std::forward<Args>(args)...);\n        _root\
    \ = meld(_root, node);\n    }\n\n    constexpr void pop() { _root = meld(_root->_left,\
    \ _root->_right); }\n\n    constexpr void meld(const skew_heap<T, Comp> &rhs)\
    \ { _root = meld(_root, rhs->_root); }\n\n  private:\n    node_pointer _root;\n\
    \    Comp _comp;\n\n    constexpr node_pointer meld(node_pointer a, node_pointer\
    \ b) {\n        if (!a) return b;\n        if (!b) return a;\n        if (_comp(a->_val,\
    \ b->_val)) std::swap(a, b);\n        a->_right = meld(a->_right, b);\n      \
    \  std::swap(a->_left, a->_right);\n        return a;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/heap/skew_heap.hpp
  requiredBy: []
  timestamp: '2023-10-01 21:10:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/alds1/skew_heap.test.cpp
documentation_of: lib/heap/skew_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/skew_heap.hpp
- /library/lib/heap/skew_heap.hpp.html
title: skew heap
---
