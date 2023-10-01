---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\n/**\n * @brief Li Chao\
    \ Tree\n *\n * @tparam Comp \u6BD4\u8F03\u95A2\u6570\n * @tparam Inf\n */\ntemplate\
    \ <class Comp = std::less<>, std::int64_t Inf = std::numeric_limits<std::int64_t>::max()>\n\
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
    \ a, std::int64_t b) {\n        line_type line = line_type{a, b};\n        this->root\
    \ = this->add_line(this->root, line, this->xl, this->xr);\n    }\n\n    /**\n\
    \     * @brief Add segment ($ax+b$)\n     *\n     * @param a\n     * @param b\n\
    \     * @param l\n     * @param r\n     */\n    void add_segment(std::int64_t\
    \ a, std::int64_t b, std::int64_t l, std::int64_t r) {\n        assert(this->xl\
    \ <= l && l < r && r <= this->xr);\n        line_type line = line_type{a, b};\n\
    \        this->root = this->add_segment(l, r, this->root, line, this->xl, this->xr);\n\
    \    }\n\n    std::int64_t query(std::int64_t x) {\n        assert(this->xl <=\
    \ x && x < this->xr);\n        return this->query(x, this->xl, this->xr);\n  \
    \  }\n\n  private:\n    node_ptr root;\n    std::int64_t xl, xr;\n    Comp comp;\n\
    \n    node_ptr add_line(node_ptr node, line_type line, std::int64_t l, std::int64_t\
    \ r) {\n        if (node == nullptr) return new _node(line);\n        if (l +\
    \ 1 == r) {\n            if (comp(line(l), node->line(l))) node->line = line;\n\
    \            return node;\n        }\n        std::int64_t m = (l + r) >> 1;\n\
    \        bool left = comp(line(l), node->line(l));\n        bool right = comp(line(r),\
    \ node->line(r));\n        if (left && right) {\n            node->line = line;\n\
    \            return node;\n        }\n        if (!left && !right) return node;\n\
    \        bool mid = comp(line(m), node->line(m));\n        if (mid) std::swap(node->line,\
    \ line);\n        if (left != mid) node->left = this->add_line(node->left, line,\
    \ l, m);\n        else node->right = this->add_line(node->right, line, m, r);\n\
    \        return node;\n    }\n\n    node_ptr add_segment(std::int64_t a, std::int64_t\
    \ b, node_ptr node, line_type line,\n                         std::int64_t l,\
    \ std::int64_t r) {\n        if (r <= a || b <= l) return node;\n        if (a\
    \ <= l && r <= b) return this->add_line(node, line, l, r);\n        if (node ==\
    \ nullptr) node = new _node(inf_line);\n        std::int64_t m = (l + r) >> 1;\n\
    \        node->left = this->add_segment(a, b, node->left, line, l, m);\n     \
    \   node->right = this->add_segment(a, b, node->right, line, m, r);\n        return\
    \ node;\n    }\n\n    std::int64_t query(std::int64_t k, std::int64_t l, std::int64_t\
    \ r) {\n        node_ptr node = this->root;\n        std::int64_t s = Inf;\n \
    \       while (node != nullptr) {\n            std::int64_t m = (l + r) >> 1;\n\
    \            if (comp(node->line(k), s)) s = node->line(k);\n            if (k\
    \ < m) r = m, node = node->left;\n            else l = m, node = node->right;\n\
    \        }\n        return s;\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/li_chao_tree.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/segment_add_get_min.test.cpp
  - test/yosupo/data_structure/line_add_get_min.test.cpp
documentation_of: lib/data_structure/li_chao_tree.hpp
layout: document
redirect_from:
- /library/lib/data_structure/li_chao_tree.hpp
- /library/lib/data_structure/li_chao_tree.hpp.html
title: Li Chao Tree
---
