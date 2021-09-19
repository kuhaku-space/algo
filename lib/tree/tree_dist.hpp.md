---
data:
  _extendedDependsOn:
  - icon: ':warning:'
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph.hpp\"\r\n\r\n\
    vector<int> tree_dist(const Graph<void> &g, int r = 0) {\r\n    struct S {\r\n\
    \        int idx, p, d;\r\n    };\r\n    vector<int> res(g.size());\r\n    stack<S>\
    \ st;\r\n    st.push({r, -1, 0});\r\n    while (!st.empty()) {\r\n        auto\
    \ [idx, p, d] = st.top();\r\n        st.pop();\r\n        res[idx] = d;\r\n  \
    \      for (auto i : g[idx]) {\r\n            if (i == p) continue;\r\n      \
    \      st.push({i, idx, d + 1});\r\n        }\r\n    }\r\n    return res;\r\n\
    }\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/tree/tree_dist.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/tree_dist.hpp
layout: document
redirect_from:
- /library/lib/tree/tree_dist.hpp
- /library/lib/tree/tree_dist.hpp.html
title: lib/tree/tree_dist.hpp
---
