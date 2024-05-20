---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/line_add_get_min.test.cpp
    title: test/yosupo/data_structure/line_add_get_min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/segment_add_get_min.test.cpp
    title: test/yosupo/data_structure/segment_add_get_min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Li Chao Tree
    links: []
  bundledCode: "#line 2 \"lib/data_structure/li_chao_tree.hpp\"\n#include <cassert>\n\
    #include <cstdint>\n#include <functional>\n#include <limits>\n\n/**\n * @brief\
    \ Li Chao Tree\n *\n * @tparam Comp \u6BD4\u8F03\u95A2\u6570\n * @tparam Inf\n\
    \ */\ntemplate <class Comp = std::less<>, std::int64_t Inf = std::numeric_limits<std::int64_t>::max()>\n\
    struct li_chao_tree {\n  private:\n    struct _line {\n        std::int64_t a,\
    \ b;\n\n        constexpr _line(std::int64_t _a, std::int64_t _b) : a(_a), b(_b)\
    \ {}\n        constexpr std::int64_t operator()(std::int64_t x) const { return\
    \ a * x + b; }\n    };\n\n    const _line inf_line = {0, Inf};\n\n    struct _node\
    \ {\n        using pointer = _node *;\n        pointer left, right;\n        _line\
    \ line;\n\n        constexpr _node(_line line) : left(nullptr), right(nullptr),\
    \ line(line) {}\n    };\n\n  public:\n    using line_type = _line;\n    using\
    \ node_ptr = typename _node::pointer;\n\n    static constexpr std::int64_t inf\
    \ = Inf;\n\n    constexpr li_chao_tree(std::int64_t _xr) : root(nullptr), xl(0),\
    \ xr(_xr) {}\n    constexpr li_chao_tree(std::int64_t _xl, std::int64_t _xr) :\
    \ root(nullptr), xl(_xl), xr(_xr) {}\n\n    /**\n     * @brief Add line ($ax+b$)\n\
    \     *\n     * @param a\n     * @param b\n     */\n    void add_line(std::int64_t\
    \ a, std::int64_t b) {\n        line_type line = line_type{a, b};\n        root\
    \ = add_line(root, line, xl, xr);\n    }\n\n    /**\n     * @brief Add segment\
    \ ($ax+b$)\n     *\n     * @param a\n     * @param b\n     * @param l\n     *\
    \ @param r\n     */\n    void add_segment(std::int64_t a, std::int64_t b, std::int64_t\
    \ l, std::int64_t r) {\n        assert(xl <= l && l < r && r <= xr);\n       \
    \ line_type line = line_type{a, b};\n        root = add_segment(l, r, root, line,\
    \ xl, xr);\n    }\n\n    std::int64_t query(std::int64_t x) {\n        assert(xl\
    \ <= x && x < xr);\n        return query(x, xl, xr);\n    }\n\n  private:\n  \
    \  node_ptr root;\n    std::int64_t xl, xr;\n    Comp comp;\n\n    node_ptr add_line(node_ptr\
    \ node, line_type line, std::int64_t l, std::int64_t r) {\n        if (node ==\
    \ nullptr) return new _node(line);\n        if (l + 1 == r) {\n            if\
    \ (comp(line(l), node->line(l))) node->line = line;\n            return node;\n\
    \        }\n        std::int64_t m = (l + r) >> 1;\n        bool left = comp(line(l),\
    \ node->line(l));\n        bool right = comp(line(r), node->line(r));\n      \
    \  if (left && right) {\n            node->line = line;\n            return node;\n\
    \        }\n        if (!left && !right) return node;\n        bool mid = comp(line(m),\
    \ node->line(m));\n        if (mid) std::swap(node->line, line);\n        if (left\
    \ != mid) node->left = add_line(node->left, line, l, m);\n        else node->right\
    \ = add_line(node->right, line, m, r);\n        return node;\n    }\n\n    node_ptr\
    \ add_segment(std::int64_t a, std::int64_t b, node_ptr node, line_type line,\n\
    \                         std::int64_t l, std::int64_t r) {\n        if (r <=\
    \ a || b <= l) return node;\n        if (a <= l && r <= b) return add_line(node,\
    \ line, l, r);\n        if (node == nullptr) node = new _node(inf_line);\n   \
    \     std::int64_t m = (l + r) >> 1;\n        node->left = add_segment(a, b, node->left,\
    \ line, l, m);\n        node->right = add_segment(a, b, node->right, line, m,\
    \ r);\n        return node;\n    }\n\n    std::int64_t query(std::int64_t k, std::int64_t\
    \ l, std::int64_t r) {\n        node_ptr node = root;\n        std::int64_t s\
    \ = Inf;\n        while (node != nullptr) {\n            std::int64_t m = (l +\
    \ r) >> 1;\n            if (comp(node->line(k), s)) s = node->line(k);\n     \
    \       if (k < m) r = m, node = node->left;\n            else l = m, node = node->right;\n\
    \        }\n        return s;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <cstdint>\n#include <functional>\n\
    #include <limits>\n\n/**\n * @brief Li Chao Tree\n *\n * @tparam Comp \u6BD4\u8F03\
    \u95A2\u6570\n * @tparam Inf\n */\ntemplate <class Comp = std::less<>, std::int64_t\
    \ Inf = std::numeric_limits<std::int64_t>::max()>\nstruct li_chao_tree {\n  private:\n\
    \    struct _line {\n        std::int64_t a, b;\n\n        constexpr _line(std::int64_t\
    \ _a, std::int64_t _b) : a(_a), b(_b) {}\n        constexpr std::int64_t operator()(std::int64_t\
    \ x) const { return a * x + b; }\n    };\n\n    const _line inf_line = {0, Inf};\n\
    \n    struct _node {\n        using pointer = _node *;\n        pointer left,\
    \ right;\n        _line line;\n\n        constexpr _node(_line line) : left(nullptr),\
    \ right(nullptr), line(line) {}\n    };\n\n  public:\n    using line_type = _line;\n\
    \    using node_ptr = typename _node::pointer;\n\n    static constexpr std::int64_t\
    \ inf = Inf;\n\n    constexpr li_chao_tree(std::int64_t _xr) : root(nullptr),\
    \ xl(0), xr(_xr) {}\n    constexpr li_chao_tree(std::int64_t _xl, std::int64_t\
    \ _xr) : root(nullptr), xl(_xl), xr(_xr) {}\n\n    /**\n     * @brief Add line\
    \ ($ax+b$)\n     *\n     * @param a\n     * @param b\n     */\n    void add_line(std::int64_t\
    \ a, std::int64_t b) {\n        line_type line = line_type{a, b};\n        root\
    \ = add_line(root, line, xl, xr);\n    }\n\n    /**\n     * @brief Add segment\
    \ ($ax+b$)\n     *\n     * @param a\n     * @param b\n     * @param l\n     *\
    \ @param r\n     */\n    void add_segment(std::int64_t a, std::int64_t b, std::int64_t\
    \ l, std::int64_t r) {\n        assert(xl <= l && l < r && r <= xr);\n       \
    \ line_type line = line_type{a, b};\n        root = add_segment(l, r, root, line,\
    \ xl, xr);\n    }\n\n    std::int64_t query(std::int64_t x) {\n        assert(xl\
    \ <= x && x < xr);\n        return query(x, xl, xr);\n    }\n\n  private:\n  \
    \  node_ptr root;\n    std::int64_t xl, xr;\n    Comp comp;\n\n    node_ptr add_line(node_ptr\
    \ node, line_type line, std::int64_t l, std::int64_t r) {\n        if (node ==\
    \ nullptr) return new _node(line);\n        if (l + 1 == r) {\n            if\
    \ (comp(line(l), node->line(l))) node->line = line;\n            return node;\n\
    \        }\n        std::int64_t m = (l + r) >> 1;\n        bool left = comp(line(l),\
    \ node->line(l));\n        bool right = comp(line(r), node->line(r));\n      \
    \  if (left && right) {\n            node->line = line;\n            return node;\n\
    \        }\n        if (!left && !right) return node;\n        bool mid = comp(line(m),\
    \ node->line(m));\n        if (mid) std::swap(node->line, line);\n        if (left\
    \ != mid) node->left = add_line(node->left, line, l, m);\n        else node->right\
    \ = add_line(node->right, line, m, r);\n        return node;\n    }\n\n    node_ptr\
    \ add_segment(std::int64_t a, std::int64_t b, node_ptr node, line_type line,\n\
    \                         std::int64_t l, std::int64_t r) {\n        if (r <=\
    \ a || b <= l) return node;\n        if (a <= l && r <= b) return add_line(node,\
    \ line, l, r);\n        if (node == nullptr) node = new _node(inf_line);\n   \
    \     std::int64_t m = (l + r) >> 1;\n        node->left = add_segment(a, b, node->left,\
    \ line, l, m);\n        node->right = add_segment(a, b, node->right, line, m,\
    \ r);\n        return node;\n    }\n\n    std::int64_t query(std::int64_t k, std::int64_t\
    \ l, std::int64_t r) {\n        node_ptr node = root;\n        std::int64_t s\
    \ = Inf;\n        while (node != nullptr) {\n            std::int64_t m = (l +\
    \ r) >> 1;\n            if (comp(node->line(k), s)) s = node->line(k);\n     \
    \       if (k < m) r = m, node = node->left;\n            else l = m, node = node->right;\n\
    \        }\n        return s;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/data_structure/li_chao_tree.hpp
  requiredBy: []
  timestamp: '2024-04-19 14:46:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/line_add_get_min.test.cpp
  - test/yosupo/data_structure/segment_add_get_min.test.cpp
documentation_of: lib/data_structure/li_chao_tree.hpp
layout: document
redirect_from:
- /library/lib/data_structure/li_chao_tree.hpp
- /library/lib/data_structure/li_chao_tree.hpp.html
title: Li Chao Tree
---
