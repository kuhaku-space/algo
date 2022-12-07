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
    document_title: Add line ($ax+b$)
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\nstruct li_chao_tree {\n  private:\n\
    \    struct _line {\n        std::int64_t a, b;\n\n        constexpr _line(std::int64_t\
    \ _a, std::int64_t _b) : a(_a), b(_b) {}\n        constexpr std::int64_t operator()(std::int64_t\
    \ x) const { return a * x + b; }\n    };\n\n    const _line inf_line = {0, inf};\n\
    \n    struct _node {\n        using pointer = _node *;\n        pointer left,\
    \ right;\n        _line line;\n\n        constexpr _node(_line line) : left(nullptr),\
    \ right(nullptr), line(line) {}\n    };\n\n  public:\n    using line_type = _line;\n\
    \    using node_ptr = typename _node::pointer;\n\n    static constexpr std::int64_t\
    \ inf = std::numeric_limits<std::int64_t>::max();\n\n    constexpr li_chao_tree(std::int64_t\
    \ _xr) : root(nullptr), xl(0), xr(_xr) {}\n    constexpr li_chao_tree(std::int64_t\
    \ _xl, std::int64_t _xr) : root(nullptr), xl(_xl), xr(_xr) {}\n\n    /**\n   \
    \  * @brief Add line ($ax+b$)\n     *\n     * @param a\n     * @param b\n    \
    \ */\n    void add_line(std::int64_t a, std::int64_t b) {\n        _line line\
    \ = _line{a, b};\n        this->root = this->add_line(this->root, line, this->xl,\
    \ this->xr);\n    }\n\n    /**\n     * @brief Add segment ($ax+b$)\n     *\n \
    \    * @param a\n     * @param b\n     * @param l\n     * @param r\n     */\n\
    \    void add_segment(std::int64_t a, std::int64_t b, std::int64_t l, std::int64_t\
    \ r) {\n        assert(this->xl <= l && l < r && r <= this->xr);\n        _line\
    \ line = _line{a, b};\n        this->root = this->add_segment(l, r, this->root,\
    \ line, this->xl, this->xr);\n    }\n\n    std::int64_t query(std::int64_t x)\
    \ {\n        assert(this->xl <= x && x < this->xr);\n        return this->query(x,\
    \ this->xl, this->xr);\n    }\n\n  private:\n    node_ptr root;\n    std::int64_t\
    \ xl, xr;\n\n    node_ptr add_line(node_ptr node, _line line, std::int64_t l,\
    \ std::int64_t r) {\n        if (node == nullptr) return new _node(line);\n  \
    \      if (l + 1 == r) {\n            if (line(l) < node->line(l)) node->line\
    \ = line;\n            return node;\n        }\n        std::int64_t m = (l +\
    \ r) >> 1;\n        bool left = (line(l) < node->line(l));\n        bool right\
    \ = (line(r) < node->line(r));\n        if (left && right) {\n            node->line\
    \ = line;\n            return node;\n        }\n        if (!left && !right) return\
    \ node;\n        bool mid = (line(m) < node->line(m));\n        if (mid) swap(node->line,\
    \ line);\n        if (left != mid) node->left = this->add_line(node->left, line,\
    \ l, m);\n        else node->right = this->add_line(node->right, line, m, r);\n\
    \        return node;\n    }\n\n    node_ptr add_segment(std::int64_t a, std::int64_t\
    \ b, node_ptr node, _line line, std::int64_t l,\n                         std::int64_t\
    \ r) {\n        if (r <= a || b <= l) return node;\n        if (a <= l && r <=\
    \ b) return this->add_line(node, line, l, r);\n        if (node == nullptr) node\
    \ = new _node(inf_line);\n        std::int64_t m = (l + r) >> 1;\n        node->left\
    \ = this->add_segment(a, b, node->left, line, l, m);\n        node->right = this->add_segment(a,\
    \ b, node->right, line, m, r);\n        return node;\n    }\n\n    std::int64_t\
    \ query(std::int64_t k, std::int64_t l, std::int64_t r) {\n        node_ptr node\
    \ = this->root;\n        std::int64_t s = inf;\n        while (node != nullptr)\
    \ {\n            std::int64_t m = (l + r) >> 1;\n            chmin(s, node->line(k));\n\
    \            if (k < m) r = m, node = node->left;\n            else l = m, node\
    \ = node->right;\n        }\n        return s;\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/li_chao_tree.hpp
  requiredBy: []
  timestamp: '2022-08-02 13:12:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/line_add_get_min.test.cpp
  - test/yosupo/data_structure/segment_add_get_min.test.cpp
documentation_of: lib/data_structure/li_chao_tree.hpp
layout: document
redirect_from:
- /library/lib/data_structure/li_chao_tree.hpp
- /library/lib/data_structure/li_chao_tree.hpp.html
title: Add line ($ax+b$)
---
