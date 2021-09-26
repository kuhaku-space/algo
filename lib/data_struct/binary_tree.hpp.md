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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T>\r\nstruct binary_tree\
    \ {\r\n    struct node {\r\n        T key;\r\n        int left, right;\r\n\r\n\
    \        node() : key(numeric_limits<T>::max()), left(), right() {}\r\n      \
    \  node(T _key, int64_t _left, int64_t _right)\r\n            : key(_key), left(_left),\
    \ right(_right) {}\r\n    };\r\n\r\n    int size;\r\n    vector<node> nodes;\r\
    \n\r\n    binary_tree() : size(1), nodes(1) {}\r\n\r\n    bool operator<(const\
    \ binary_tree &rhs) const { return dfs() < rhs.dfs(); }\r\n\r\n    const int find(T\
    \ key) const {\r\n        int it = 0;\r\n        while (nodes[it].key != numeric_limits<T>::max()\
    \ &&\r\n               nodes[it].key != key) {\r\n            if (key < nodes[it].key)\r\
    \n                it = nodes[it].left;\r\n            else\r\n               \
    \ it = nodes[it].right;\r\n        }\r\n        return it;\r\n    }\r\n\r\n  \
    \  bool exist(T key) const { return nodes[find(key)].key == key; }\r\n\r\n   \
    \ void insert(T key) {\r\n        auto it = find(key);\r\n        if (nodes[it].key\
    \ == key) return;\r\n        nodes.resize(size + 2, node());\r\n        nodes[it]\
    \ = node(key, size, size + 1);\r\n        size += 2;\r\n    }\r\n\r\n    vector<int>\
    \ dfs() const {\r\n        vector<int> res;\r\n        stack<int> st;\r\n    \
    \    st.push(0);\r\n        while (!st.empty()) {\r\n            int t = st.top();\r\
    \n            st.pop();\r\n            if (nodes[t].key == numeric_limits<T>::max())\
    \ continue;\r\n            res.emplace_back(nodes[t].key);\r\n            st.push(nodes[t].right);\r\
    \n            st.push(nodes[t].left);\r\n        }\r\n        return res;\r\n\
    \    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_struct/binary_tree.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_struct/binary_tree.hpp
layout: document
redirect_from:
- /library/lib/data_struct/binary_tree.hpp
- /library/lib/data_struct/binary_tree.hpp.html
title: lib/data_struct/binary_tree.hpp
---
