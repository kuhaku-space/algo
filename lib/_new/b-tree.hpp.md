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
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <int M>\r\nstruct b_tree\
    \ {\r\n    struct node {\r\n        int sz = 0;\r\n        int data[M + 1];\r\n\
    \        node* ptr[M + 1];\r\n\r\n        void insert(int x) {\r\n           \
    \ node* p = ptr[0];\r\n            for (int i = 0; i < M; ++i) {\r\n         \
    \       if (x < data[i]) break;\r\n                p = ptr[i + 1];\r\n       \
    \     }\r\n\r\n            if (p != NULL) {\r\n                p->insert(x);\r\
    \n            } else {\r\n                data[sz++] = x;\r\n                int\
    \ idx = sz - 1;\r\n                while (idx > 0) {\r\n                    if\
    \ (data[idx - 1] < data[idx]) break;\r\n                    swap(data[idx - 1],\
    \ data[idx]);\r\n                    --idx;\r\n                }\r\n         \
    \   }\r\n        }\r\n    };\r\n    node* root;\r\n\r\n    void insert(int x)\
    \ { data[] }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/b-tree.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/b-tree.hpp
layout: document
redirect_from:
- /library/lib/_new/b-tree.hpp
- /library/lib/_new/b-tree.hpp.html
title: lib/_new/b-tree.hpp
---
