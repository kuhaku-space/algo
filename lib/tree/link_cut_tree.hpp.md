---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
    title: test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Link-Cut Tree
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/monoid.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"segment_tree/monoid.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\n/**\r\n * @brief Link-Cut Tree\r\n *\r\n * @tparam M \u53EF\u63DB\u30E2\
    \u30CE\u30A4\u30C9\r\n */\r\ntemplate <class M>\r\nstruct link_cut_tree {\r\n\
    \  private:\r\n    using T = typename M::value_type;\r\n\r\n    struct _node {\r\
    \n        using pointer = _node *;\r\n\r\n        pointer pp, lp, rp;\r\n    \
    \    bool flip;\r\n        T val, total;\r\n\r\n        constexpr bool is_root()\
    \ { return !pp || (pp->lp != this && pp->rp != this); }\r\n\r\n        void set(T\
    \ val) {\r\n            this->val = val;\r\n            this->update();\r\n  \
    \      }\r\n        void update() {\r\n            this->total = val;\r\n    \
    \        if (this->lp) this->total = M::op(this->lp->total, this->total);\r\n\
    \            if (this->rp) this->total = M::op(this->total, this->rp->total);\r\
    \n        }\r\n\r\n        void do_flip() {\r\n            this->flip = !this->flip;\r\
    \n            std::swap(this->lp, this->rp);\r\n        }\r\n        void propagate()\
    \ {\r\n            if (this->flip) {\r\n                this->flip = false;\r\n\
    \                if (this->lp) this->lp->do_flip();\r\n                if (this->rp)\
    \ this->rp->do_flip();\r\n            }\r\n        }\r\n        void propagate_all()\
    \ {\r\n            if (!this->is_root()) this->pp->propagate_all();\r\n      \
    \      this->propagate();\r\n        }\r\n\r\n        void rot() {\r\n       \
    \     int x = (this->pp->rp == this);\r\n            pointer pa = this->pp;\r\n\
    \            pointer ch = (x ? this->lp : this->rp);\r\n\r\n            if (!pa->is_root())\
    \ {\r\n                if (pa->pp->rp == pa) pa->pp->rp = this;\r\n          \
    \      else pa->pp->lp = this;\r\n            }\r\n            this->pp = pa->pp;\r\
    \n\r\n            (x ? this->lp : this->rp) = pa;\r\n            pa->pp = this;\r\
    \n            (!x ? pa->lp : pa->rp) = ch;\r\n            if (ch) ch->pp = pa;\r\
    \n\r\n            pa->update();\r\n            this->update();\r\n        }\r\n\
    \        void splay() {\r\n            this->propagate_all();\r\n            while\
    \ (!this->is_root()) {\r\n                if (!this->pp->is_root()) {\r\n    \
    \                if ((this->pp->rp == this) == (this->pp->pp->rp == pp)) {\r\n\
    \                        this->pp->rot();\r\n                    } else {\r\n\
    \                        this->rot();\r\n                    }\r\n           \
    \     }\r\n                this->rot();\r\n            }\r\n        }\r\n\r\n\
    \        void expose() {\r\n            this->splay();\r\n            while (this->pp)\
    \ {\r\n                this->pp->splay();\r\n                this->pp->rp = this;\r\
    \n                this->rot();\r\n            }\r\n            this->rp = nullptr;\r\
    \n            this->update();\r\n        }\r\n\r\n        void make_root() {\r\
    \n            this->expose();\r\n            this->do_flip();\r\n        }\r\n\
    \r\n        void link(pointer v) {\r\n            this->make_root();\r\n     \
    \       this->pp = v;\r\n        }\r\n\r\n        void cut() {\r\n           \
    \ this->expose();\r\n            this->lp->pp = nullptr;\r\n            this->lp\
    \ = nullptr;\r\n            this->update();\r\n        }\r\n    };\r\n\r\n  public:\r\
    \n    using node_type = _node;\r\n    using node_ptr = typename _node::pointer;\r\
    \n\r\n    link_cut_tree(int n) : nodes(n, nullptr) {\r\n        for (int i = 0;\
    \ i < n; ++i) {\r\n            this->nodes[i] = new _node();\r\n        }\r\n\
    \    }\r\n\r\n    void set(int v, T val) {\r\n        this->nodes[v]->splay();\r\
    \n        this->nodes[v]->set(val);\r\n    }\r\n    T get_val(int v) { return\
    \ this->nodes[v]->val; }\r\n    T get_total(int v) { return this->nodes[v]->total;\
    \ }\r\n    void link(int u, int v) { this->nodes[u]->link(nodes[v]); }\r\n   \
    \ void cut(int u, int v) {\r\n        this->nodes[u]->make_root();\r\n       \
    \ this->nodes[v]->cut();\r\n    }\r\n    void cut(int v) { this->nodes[v]->cut();\
    \ }\r\n    void splay(int v) { this->nodes[v]->splay(); }\r\n    void make_root(int\
    \ v) { this->nodes[v]->make_root(); }\r\n    void expose(int v) { this->nodes[v]->expose();\
    \ }\r\n\r\n  private:\r\n    std::vector<node_ptr> nodes;\r\n};\r\n"
  dependsOn:
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/link_cut_tree.hpp
  requiredBy: []
  timestamp: '2023-05-22 20:52:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/dynamic_tree_vertex_add_path_sum.test.cpp
documentation_of: lib/tree/link_cut_tree.hpp
layout: document
redirect_from:
- /library/lib/tree/link_cut_tree.hpp
- /library/lib/tree/link_cut_tree.hpp.html
title: Link-Cut Tree
---
