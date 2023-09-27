---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yukicoder/0263.test.cpp
    title: test/yukicoder/0263.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: palindromic tree
    links:
    - https://math314.hateblo.jp/entry/2016/12/19/005919
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief palindromic tree\n *\
    \ @see https://math314.hateblo.jp/entry/2016/12/19/005919\n */\nstruct palindromic_tree\
    \ {\n  private:\n    struct _node {\n        using pointer = _node *;\n\n    \
    \    std::map<char, int> link;\n        int suffix_link;\n        int len;\n \
    \       int count;\n\n        _node() : link(), suffix_link(), len(), count()\
    \ {}\n        _node(int _suffix_link, int _len, int _count)\n            : link(),\
    \ suffix_link(_suffix_link), len(_len), count(_count) {}\n    };\n\n  public:\n\
    \    using node_type = _node;\n    using node_pointer = typename _node::pointer;\n\
    \n    palindromic_tree() : nodes(), str(), active_idx() {\n        create_node(0,\
    \ -1, 0);\n        create_node(0, 0, 0);\n    }\n\n    int size() const { return\
    \ nodes.size(); }\n\n    int get_active_idx() const { return active_idx; }\n\n\
    \    node_pointer get_node(int id) { return &nodes[id]; }\n\n    int add(char\
    \ ch) {\n        str.push_back(ch);\n        int a = find_prev_palindrome_idx(active_idx);\n\
    \        auto inserted_result = nodes[a].link.insert(std::make_pair(ch, int(nodes.size())));\n\
    \        active_idx = inserted_result.first->second;\n        if (!inserted_result.second)\
    \ {\n            nodes[active_idx].count++;\n            return active_idx;\n\
    \        }\n\n        node_pointer node = create_node(0, nodes[a].len + 2, 1);\n\
    \        if (node->len == 1) {\n            node->suffix_link = 1;\n        }\
    \ else {\n            int b = find_prev_palindrome_idx(nodes[a].suffix_link);\n\
    \            node->suffix_link = nodes[b].link[ch];\n        }\n        return\
    \ active_idx;\n    }\n\n    int move(char ch) {\n        str.push_back(ch);\n\
    \        while (true) {\n            active_idx = find_prev_palindrome_idx(active_idx);\n\
    \            auto it = nodes[active_idx].link.find(ch);\n            if (it !=\
    \ nodes[active_idx].link.end()) {\n                active_idx = it->second;\n\
    \                return active_idx;\n            }\n            if (active_idx\
    \ == 0) break;\n            active_idx = nodes[active_idx].suffix_link;\n    \
    \    }\n        return active_idx;\n    }\n\n    std::vector<int> build_frequency()\
    \ {\n        std::vector<int> res(nodes.size());\n        for (int i = int(nodes.size())\
    \ - 1; i > 0; --i) {\n            res[i] += nodes[i].count;\n            res[nodes[i].suffix_link]\
    \ += res[i];\n        }\n        return res;\n    }\n\n    void clear() {\n  \
    \      str.clear();\n        active_idx = 0;\n    }\n\n  private:\n    std::vector<node_type>\
    \ nodes;\n    std::string str;\n    int active_idx;\n\n    node_pointer create_node(int\
    \ suffix_link, int len, int count) {\n        nodes.emplace_back(suffix_link,\
    \ len, count);\n        return &nodes.back();\n    }\n\n    int find_prev_palindrome_idx(int\
    \ node_id) {\n        int pos = int(str.size()) - 1;\n        while (true) {\n\
    \            int opposite_side_idx = pos - 1 - nodes[node_id].len;\n         \
    \   if (opposite_side_idx >= 0 && str[opposite_side_idx] == str.back()) break;\n\
    \            node_id = nodes[node_id].suffix_link;\n        }\n        return\
    \ node_id;\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/palindromic_tree.hpp
  requiredBy: []
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yukicoder/0263.test.cpp
documentation_of: lib/tree/palindromic_tree.hpp
layout: document
redirect_from:
- /library/lib/tree/palindromic_tree.hpp
- /library/lib/tree/palindromic_tree.hpp.html
title: palindromic tree
---
