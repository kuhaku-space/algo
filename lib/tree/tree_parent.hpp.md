---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u6728\u306E\u9802\u70B9\u306E\u89AA\u3092\u6C42\u3081\u308B"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\r\n#include \"template/template.hpp\"\r\n\r\n\
    /**\r\n * @brief \u6728\u306E\u9802\u70B9\u306E\u89AA\u3092\u6C42\u3081\u308B\r\
    \n * \r\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\r\n * @param g \u6728\
    \r\n * @param r \u6839\r\n * @return std::vector<int> \r\n */\r\ntemplate <class\
    \ T>\r\nstd::vector<int> tree_parent(const Graph<T> &g, int r = 0) {\r\n    std::vector<int>\
    \ res(g.size());\r\n    std::stack<std::pair<int, int>> st;\r\n    res[r] = -1;\r\
    \n    st.emplace(r, -1);\r\n    while (!st.empty()) {\r\n        auto [index,\
    \ parent] = st.top();\r\n        st.pop();\r\n        for (auto &e : g[index])\
    \ {\r\n            if (e.to() == parent) continue;\r\n            res[e.to()]\
    \ = index;\r\n            st.emplace(e.to(), index);\r\n        }\r\n    }\r\n\
    \    return res;\r\n}\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/tree_parent.hpp
  requiredBy: []
  timestamp: '2022-03-25 03:25:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/tree_parent.hpp
layout: document
redirect_from:
- /library/lib/tree/tree_parent.hpp
- /library/lib/tree/tree_parent.hpp.html
title: "\u6728\u306E\u9802\u70B9\u306E\u89AA\u3092\u6C42\u3081\u308B"
---
