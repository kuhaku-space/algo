---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/aho_corasick.test.cpp
    title: test/aoj/jag/aho_corasick.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Aho Corasick \u6CD5"
    links:
    - https://ei1333.github.io/library/string/aho-corasick.hpp.html
    - https://naoya-2.hatenadiary.org/entry/20090405/aho_corasick
  bundledCode: "#line 1 \"lib/string/aho_corasick.hpp\"\n#include <cassert>\n#include\
    \ <queue>\n#include <string>\n#include <vector>\n\n/**\n * @brief Aho Corasick\
    \ \u6CD5\n * @see https://naoya-2.hatenadiary.org/entry/20090405/aho_corasick\n\
    \ * @see https://ei1333.github.io/library/string/aho-corasick.hpp.html\n *\n *\
    \ @tparam char_size\n * @tparam base\n */\ntemplate <int char_size, int base>\n\
    struct aho_corasick {\n  private:\n    struct _node {\n        std::vector<int>\
    \ next_node;\n        _node() : next_node(char_size, -1) {}\n\n        int next(int\
    \ x) const { return next_node[x]; }\n    };\n\n  public:\n    using node_type\
    \ = _node;\n\n    aho_corasick() : nodes(), failure() { nodes.emplace_back();\
    \ }\n\n    int size() const noexcept { return nodes.size(); }\n\n    std::vector<int>\
    \ build() {\n        failure = std::vector<int>(size(), 0);\n        std::queue<int>\
    \ que;\n        for (int i = 0; i < char_size; ++i) {\n            int next_root\
    \ = nodes[0].next(i);\n            if (next_root != -1) { que.emplace(next_root);\
    \ }\n        }\n\n        while (!que.empty()) {\n            int x = que.front();\n\
    \            que.pop();\n            for (int i = 0; i < char_size; ++i) {\n \
    \               int next_x = nodes[x].next(i);\n                if (next_x !=\
    \ -1) {\n                    que.emplace(next_x);\n                    int y =\
    \ x;\n                    do {\n                        y = failure[y];\n    \
    \                    int next_y = nodes[y].next(i);\n                        if\
    \ (next_y != -1) {\n                            failure[next_x] = next_y;\n  \
    \                          break;\n                        }\n               \
    \     } while (y != 0);\n                }\n            }\n        }\n       \
    \ return failure;\n    }\n\n    std::vector<int> insert(const std::string &word)\
    \ {\n        std::vector<int> res;\n        int node_id = 0;\n        for (int\
    \ i = 0; i < (int)word.size(); ++i) {\n            int &next_id = nodes[node_id].next_node[word[i]\
    \ - base];\n            if (next_id == -1) {\n                next_id = nodes.size();\n\
    \                nodes.emplace_back();\n            }\n            node_id = next_id;\n\
    \            res.emplace_back(node_id);\n        }\n        return res;\n    }\n\
    \n    int search(const char c, int now = 0) {\n        int next_id = nodes[now].next(c\
    \ - base);\n        while (next_id == -1 && now != 0) {\n            now = failure[now];\n\
    \            next_id = nodes[now].next(c - base);\n        }\n        return next_id\
    \ != -1 ? next_id : 0;\n    }\n\n    std::vector<int> search(const std::string\
    \ &str, int now = 0) {\n        std::vector<int> res;\n        res.emplace_back(now);\n\
    \        for (auto c : str) {\n            now = search(c, now);\n           \
    \ res.emplace_back(now);\n        }\n        return res;\n    }\n\n    node_type\
    \ get_node(int node_id) const {\n        assert(0 <= node_id && node_id < (int)nodes.size());\n\
    \        return nodes[node_id];\n    }\n\n  private:\n    std::vector<node_type>\
    \ nodes;\n    std::vector<int> failure;\n};\n"
  code: "#include <cassert>\n#include <queue>\n#include <string>\n#include <vector>\n\
    \n/**\n * @brief Aho Corasick \u6CD5\n * @see https://naoya-2.hatenadiary.org/entry/20090405/aho_corasick\n\
    \ * @see https://ei1333.github.io/library/string/aho-corasick.hpp.html\n *\n *\
    \ @tparam char_size\n * @tparam base\n */\ntemplate <int char_size, int base>\n\
    struct aho_corasick {\n  private:\n    struct _node {\n        std::vector<int>\
    \ next_node;\n        _node() : next_node(char_size, -1) {}\n\n        int next(int\
    \ x) const { return next_node[x]; }\n    };\n\n  public:\n    using node_type\
    \ = _node;\n\n    aho_corasick() : nodes(), failure() { nodes.emplace_back();\
    \ }\n\n    int size() const noexcept { return nodes.size(); }\n\n    std::vector<int>\
    \ build() {\n        failure = std::vector<int>(size(), 0);\n        std::queue<int>\
    \ que;\n        for (int i = 0; i < char_size; ++i) {\n            int next_root\
    \ = nodes[0].next(i);\n            if (next_root != -1) { que.emplace(next_root);\
    \ }\n        }\n\n        while (!que.empty()) {\n            int x = que.front();\n\
    \            que.pop();\n            for (int i = 0; i < char_size; ++i) {\n \
    \               int next_x = nodes[x].next(i);\n                if (next_x !=\
    \ -1) {\n                    que.emplace(next_x);\n                    int y =\
    \ x;\n                    do {\n                        y = failure[y];\n    \
    \                    int next_y = nodes[y].next(i);\n                        if\
    \ (next_y != -1) {\n                            failure[next_x] = next_y;\n  \
    \                          break;\n                        }\n               \
    \     } while (y != 0);\n                }\n            }\n        }\n       \
    \ return failure;\n    }\n\n    std::vector<int> insert(const std::string &word)\
    \ {\n        std::vector<int> res;\n        int node_id = 0;\n        for (int\
    \ i = 0; i < (int)word.size(); ++i) {\n            int &next_id = nodes[node_id].next_node[word[i]\
    \ - base];\n            if (next_id == -1) {\n                next_id = nodes.size();\n\
    \                nodes.emplace_back();\n            }\n            node_id = next_id;\n\
    \            res.emplace_back(node_id);\n        }\n        return res;\n    }\n\
    \n    int search(const char c, int now = 0) {\n        int next_id = nodes[now].next(c\
    \ - base);\n        while (next_id == -1 && now != 0) {\n            now = failure[now];\n\
    \            next_id = nodes[now].next(c - base);\n        }\n        return next_id\
    \ != -1 ? next_id : 0;\n    }\n\n    std::vector<int> search(const std::string\
    \ &str, int now = 0) {\n        std::vector<int> res;\n        res.emplace_back(now);\n\
    \        for (auto c : str) {\n            now = search(c, now);\n           \
    \ res.emplace_back(now);\n        }\n        return res;\n    }\n\n    node_type\
    \ get_node(int node_id) const {\n        assert(0 <= node_id && node_id < (int)nodes.size());\n\
    \        return nodes[node_id];\n    }\n\n  private:\n    std::vector<node_type>\
    \ nodes;\n    std::vector<int> failure;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/string/aho_corasick.hpp
  requiredBy: []
  timestamp: '2024-01-23 17:46:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/jag/aho_corasick.test.cpp
documentation_of: lib/string/aho_corasick.hpp
layout: document
redirect_from:
- /library/lib/string/aho_corasick.hpp
- /library/lib/string/aho_corasick.hpp.html
title: "Aho Corasick \u6CD5"
---
