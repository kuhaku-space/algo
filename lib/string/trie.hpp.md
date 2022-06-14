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
    links:
    - https://algo-logic.info/trie-tree/#:~:text=Trie%E6%9C%A8%E3%81%AF%E3%80%81%E5%8A%B9%E7%8E%87%E7%9A%84,%E3%81%95%E3%82%92M%20%E3%81%A8%E3%81%97%E3%81%BE%E3%81%97%E3%81%9F%E3%80%82%EF%BC%89
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n// https://algo-logic.info/trie-tree/#:~:text=Trie%E6%9C%A8%E3%81%AF%E3%80%81%E5%8A%B9%E7%8E%87%E7%9A%84,%E3%81%95%E3%82%92M%20%E3%81%A8%E3%81%97%E3%81%BE%E3%81%97%E3%81%9F%E3%80%82%EF%BC%89\r\
    \n\r\n/*\r\n * Usage:\r\n * Trie<26, 'a'> trie;\r\n * Trie<96, ' '> trie;\r\n\
    \ */\r\ntemplate <int char_size, int base>\r\nstruct Trie {\r\n    struct Node\
    \ {\r\n        vector<int> next_node, accept;\r\n        int c, common;\r\n  \
    \      Node(int _c) : c(_c), common(0), next_node(char_size, -1) {}\r\n    };\r\
    \n    vector<Node> nodes;\r\n    int root;\r\n    Trie() : root(0) { nodes.emplace_back(Node(root));\
    \ }\r\n\r\n    void insert(const string &word) { insert(word, nodes[0].common);\
    \ }\r\n    void insert(const string &word, int word_id) {\r\n        int node_id\
    \ = 0;\r\n        for (int i = 0; i < word.size(); ++i) {\r\n            int c\
    \ = word[i] - base;\r\n            int &next_id = nodes[node_id].next_node[c];\r\
    \n            if (next_id == -1) {\r\n                next_id = nodes.size();\r\
    \n                nodes.emplace_back(Node(c));\r\n            }\r\n          \
    \  ++nodes[node_id].common;\r\n            node_id = next_id;\r\n        }\r\n\
    \        ++nodes[node_id].common;\r\n        nodes[node_id].accept.emplace_back(word_id);\r\
    \n    }\r\n\r\n    bool search(const string &word, bool prefix = false) {\r\n\
    \        int node_id = 0;\r\n        for (int i = 0; i < word.size(); i++) {\r\
    \n            int c = word[i] - base;\r\n            int &next_id = nodes[node_id].next_node[c];\r\
    \n            if (next_id == -1) return false;\r\n            node_id = next_id;\r\
    \n        }\r\n        return (prefix) ? true : nodes[node_id].accept.size() >\
    \ 0;\r\n    }\r\n\r\n    int search_id(const string &word) {\r\n        int node_id\
    \ = 0;\r\n        for (int i = 0; i < word.size(); i++) {\r\n            int c\
    \ = word[i] - base;\r\n            int &next_id = nodes[node_id].next_node[c];\r\
    \n            if (next_id == -1) return -1;\r\n            node_id = next_id;\r\
    \n        }\r\n        return node_id;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/trie.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/trie.hpp
layout: document
redirect_from:
- /library/lib/string/trie.hpp
- /library/lib/string/trie.hpp.html
title: lib/string/trie.hpp
---
