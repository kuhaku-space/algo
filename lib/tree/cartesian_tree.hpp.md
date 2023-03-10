---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/tree/cartesian_tree.test.cpp
    title: test/yosupo/tree/cartesian_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Cartesian Tree
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief Cartesian Tree\n *\n\
    \ * @tparam T \u914D\u5217\u306E\u578B\n * @param v \u914D\u5217\n * @return std::vector<int>\n\
    \ */\ntemplate <typename T>\nstd::vector<int> cartesian_tree(const std::vector<T>\
    \ &v) {\n    int n = v.size();\n    std::vector<int> res(n, -1);\n    std::stack<T>\
    \ st;\n    for (int i = 0; i < n; ++i) {\n        int p = -1;\n        while (!st.empty()\
    \ && v[i] < v[st.top()]) {\n            p = st.top();\n            st.pop();\n\
    \        }\n        if (p != -1) res[p] = i;\n        if (!st.empty()) res[i]\
    \ = st.top();\n        st.emplace(i);\n    }\n    return res;\n}\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/cartesian_tree.hpp
  requiredBy: []
  timestamp: '2022-07-31 09:41:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/tree/cartesian_tree.test.cpp
documentation_of: lib/tree/cartesian_tree.hpp
layout: document
redirect_from:
- /library/lib/tree/cartesian_tree.hpp
- /library/lib/tree/cartesian_tree.hpp.html
title: Cartesian Tree
---
