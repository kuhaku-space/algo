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
    document_title: Trie
    links:
    - https://algo-logic.info/trie-tree/
    - https://atcoder.jp/contests/tenka1-2016-final-open/tasks/tenka1_2016_final_c
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief Trie\r\n *\r\n\
    \ * @tparam char_size \u6587\u5B57\u7A2E\r\n * @tparam base\r\n *\r\n * @see https://algo-logic.info/trie-tree/\r\
    \n * @see https://atcoder.jp/contests/tenka1-2016-final-open/tasks/tenka1_2016_final_c\r\
    \n *\r\n * Usage:\r\n * Trie<26, 'a'> trie;\r\n * Trie<96, ' '> trie;\r\n */\r\
    \ntemplate <int char_size, int base>\r\nstruct Trie {\r\n  private:\r\n    struct\
    \ _node {\r\n        std::vector<int> next_node;\r\n        _node() : next_node(char_size,\
    \ -1) {}\r\n    };\r\n\r\n  public:\r\n    using node_type = _node;\r\n\r\n  \
    \  Trie() : root(0), nodes() { this->nodes.emplace_back(); }\r\n\r\n    int size()\
    \ const noexcept { return this->nodes.size(); }\r\n\r\n    std::vector<int> insert(const\
    \ string &word) {\r\n        std::vector<int> res;\r\n        int node_id = 0;\r\
    \n        for (int i = 0; i < (int)word.size(); ++i) {\r\n            int c =\
    \ word[i] - base;\r\n            int &next_id = this->nodes[node_id].next_node[c];\r\
    \n            if (next_id == -1) {\r\n                next_id = this->nodes.size();\r\
    \n                this->nodes.emplace_back();\r\n            }\r\n           \
    \ node_id = next_id;\r\n            res.emplace_back(node_id);\r\n        }\r\n\
    \        return res;\r\n    }\r\n\r\n    int search_id(const string &word) {\r\
    \n        int node_id = 0;\r\n        for (int i = 0; i < (int)word.size(); ++i)\
    \ {\r\n            int c = word[i] - base;\r\n            int &next_id = this->nodes[node_id].next_node[c];\r\
    \n            if (next_id == -1) return -1;\r\n            node_id = next_id;\r\
    \n        }\r\n        return node_id;\r\n    }\r\n\r\n    node_type get_node(int\
    \ node_id) const {\r\n        assert(0 <= node_id && node_id < (int)this->nodes.size());\r\
    \n        return this->nodes[node_id];\r\n    }\r\n\r\n  private:\r\n    int root;\r\
    \n    std::vector<node_type> nodes;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/trie.hpp
  requiredBy: []
  timestamp: '2023-05-22 19:46:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/trie.hpp
layout: document
redirect_from:
- /library/lib/string/trie.hpp
- /library/lib/string/trie.hpp.html
title: Trie
---
