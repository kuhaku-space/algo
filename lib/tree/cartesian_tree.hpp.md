---
data:
  _extendedDependsOn: []
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
  bundledCode: "#line 1 \"lib/tree/cartesian_tree.hpp\"\n#include <stack>\n#include\
    \ <vector>\n\n/**\n * @brief Cartesian Tree\n *\n * @tparam T \u914D\u5217\u306E\
    \u578B\n * @param v \u914D\u5217\n * @return std::vector<int>\n */\ntemplate <typename\
    \ T>\nstd::vector<int> cartesian_tree(const std::vector<T> &v) {\n    int n =\
    \ v.size();\n    std::vector<int> res(n, -1);\n    std::stack<T> st;\n    for\
    \ (int i = 0; i < n; ++i) {\n        int p = -1;\n        while (!st.empty() &&\
    \ v[i] < v[st.top()]) {\n            p = st.top();\n            st.pop();\n  \
    \      }\n        if (p != -1) res[p] = i;\n        if (!st.empty()) res[i] =\
    \ st.top();\n        st.emplace(i);\n    }\n    return res;\n}\n"
  code: "#include <stack>\n#include <vector>\n\n/**\n * @brief Cartesian Tree\n *\n\
    \ * @tparam T \u914D\u5217\u306E\u578B\n * @param v \u914D\u5217\n * @return std::vector<int>\n\
    \ */\ntemplate <typename T>\nstd::vector<int> cartesian_tree(const std::vector<T>\
    \ &v) {\n    int n = v.size();\n    std::vector<int> res(n, -1);\n    std::stack<T>\
    \ st;\n    for (int i = 0; i < n; ++i) {\n        int p = -1;\n        while (!st.empty()\
    \ && v[i] < v[st.top()]) {\n            p = st.top();\n            st.pop();\n\
    \        }\n        if (p != -1) res[p] = i;\n        if (!st.empty()) res[i]\
    \ = st.top();\n        st.emplace(i);\n    }\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/tree/cartesian_tree.hpp
  requiredBy: []
  timestamp: '2024-01-23 17:27:36+09:00'
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
