---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\nstruct link_cut_tree {\r\n    struct\
    \ node_t {\r\n        node_t *pp, *lp, *rp;\r\n\r\n        bool is_root() { return\
    \ !pp || (pp->lp != this && pp->rp != this); }\r\n\r\n        void rotr() {\r\n\
    \            node_t *q = pp, *r = q->pp;\r\n            if (q->lp = rp) rp->pp\
    \ = q;\r\n            rp = q;\r\n            q->pp = this;\r\n            if (pp\
    \ = r) {\r\n                if (r->lp == q) r->lp = this;\r\n                if\
    \ (r->rp == q) r->rp = this;\r\n            }\r\n        }\r\n\r\n        void\
    \ rotl() {\r\n            node_t *q = pp, *r = q->pp;\r\n            if (q->rp\
    \ = lp) lp->pp = q;\r\n            lp = q;\r\n            q->pp = this;\r\n  \
    \          if (pp = r) {\r\n                if (r->lp == q) r->lp = this;\r\n\
    \                if (r->rp == q) r->rp = this;\r\n            }\r\n        }\r\
    \n\r\n        void splay() {\r\n            while (!is_root()) {\r\n         \
    \       node_t *q = pp;\r\n                if (q->is_root()) {\r\n           \
    \         if (q->lp == this)\r\n                        rotr();\r\n          \
    \          else\r\n                        rotl();\r\n                } else {\r\
    \n                    node_t *r = q->pp;\r\n                    if (r->lp == q)\
    \ {\r\n                        if (q->lp == this)\r\n                        \
    \    q->rotr(), rotr();\r\n                        else\r\n                  \
    \          rotl(), rotr();\r\n\r\n                    } else {\r\n           \
    \             if (q->rp == this)\r\n                            q->rotl(), rotl();\r\
    \n                        else\r\n                            rotr(), rotl();\r\
    \n                    }\r\n                }\r\n            }\r\n        }\r\n\
    \    };\r\n\r\n    node_t *expose(node_t *x) {\r\n        node_t *rp = NULL;\r\
    \n        for (node_t *p = x; p; p = p->pp) {\r\n            p->splay();\r\n \
    \           p->rp = rp;\r\n            rp = p;\r\n        }\r\n        x->splay();\r\
    \n        return x;\r\n    }\r\n\r\n    void cut(node_t *c) {\r\n        expose(c);\r\
    \n        node_t *p = c->lp;\r\n        c->lp = NULL;\r\n        p->pp = NULL;\r\
    \n    }\r\n\r\n    void link(node_t *c, node_t *p) {\r\n        expose(c);\r\n\
    \        expose(p);\r\n        c->pp = p;\r\n        p->rp = c;\r\n    }\r\n};\r\
    \n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/link_cut_tree.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/link_cut_tree.hpp
layout: document
redirect_from:
- /library/lib/tree/link_cut_tree.hpp
- /library/lib/tree/link_cut_tree.hpp.html
title: lib/tree/link_cut_tree.hpp
---
