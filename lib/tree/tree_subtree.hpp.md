---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\r\n#include \"template/template.hpp\"\r\n\r\n\
    template <class T>\r\nvector<int> tree_subtree(const Graph<T> &g, int r = 0) {\r\
    \n    vector<int> res(g.size());\r\n    auto dfs = [&g, &res](auto &&self, int\
    \ idx, int par) {\r\n        res[idx] = 1;\r\n        for (auto i : g[idx]) {\r\
    \n            if (i.to == par) continue;\r\n            res[idx] += self(self,\
    \ i.to, idx);\r\n        }\r\n        return res[idx];\r\n    };\r\n    dfs(dfs,\
    \ r, -1);\r\n    return res;\r\n}\r\n\r\ntemplate <>\r\nvector<int> tree_subtree(const\
    \ Graph<void> &g, int r) {\r\n    vector<int> res(g.size());\r\n    auto dfs =\
    \ [&g, &res](auto &&self, int idx, int par) -> int {\r\n        res[idx] = 1;\r\
    \n        for (auto i : g[idx]) {\r\n            if (i == par) continue;\r\n \
    \           res[idx] += self(self, i, idx);\r\n        }\r\n        return res[idx];\r\
    \n    };\r\n    dfs(dfs, r, -1);\r\n    return res;\r\n}\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/tree_subtree.hpp
  requiredBy: []
  timestamp: '2021-11-25 21:03:15+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/tree_subtree.hpp
layout: document
redirect_from:
- /library/lib/tree/tree_subtree.hpp
- /library/lib/tree/tree_subtree.hpp.html
title: lib/tree/tree_subtree.hpp
---
