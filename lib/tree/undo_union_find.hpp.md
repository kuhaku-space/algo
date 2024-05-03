---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/joi/undo_union_find.test.cpp
    title: test/aoj/joi/undo_union_find.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/undo_union_find.test.cpp
    title: test/yosupo/data_structure/undo_union_find.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Undo\u53EF\u80FDUnion-Find"
    links:
    - https://ei1333.github.io/luzhiled/snippets/structure/union-find.html
  bundledCode: "#line 1 \"lib/tree/undo_union_find.hpp\"\n#include <stack>\n#include\
    \ <utility>\n#include <vector>\n\n/**\n * @brief Undo\u53EF\u80FDUnion-Find\n\
    \ * @details Implement (union by size)\n *\n * @see https://ei1333.github.io/luzhiled/snippets/structure/union-find.html\n\
    \ */\nstruct undo_union_find {\n    undo_union_find() : data(), history() {}\n\
    \    undo_union_find(int _n) : data(_n, -1), history() {}\n\n    int root(int\
    \ x) { return data[x] < 0 ? x : root(data[x]); }\n    int get_root(int k) { return\
    \ root(k); }\n\n    bool is_root(int k) const { return data[k] < 0; }\n\n    bool\
    \ same(int x, int y) { return root(x) == root(y); }\n    bool is_same(int x, int\
    \ y) { return same(x, y); }\n\n    int size(int k) { return -data[root(k)]; }\n\
    \    int get_size(int k) { return size(k); }\n\n    bool unite(int x, int y) {\n\
    \        x = root(x), y = root(y);\n        history.emplace(x, data[x]);\n   \
    \     history.emplace(y, data[y]);\n        if (x == y) return false;\n      \
    \  if (data[x] > data[y]) std::swap(x, y);\n        data[x] += data[y];\n    \
    \    data[y] = x;\n        return true;\n    }\n\n    void undo() {\n        data[history.top().first]\
    \ = history.top().second;\n        history.pop();\n        data[history.top().first]\
    \ = history.top().second;\n        history.pop();\n    }\n\n    int snapshot()\
    \ const { return history.size(); }\n\n    void rollback(int x = 0) {\n       \
    \ while ((int)(history.size()) > x) undo();\n    }\n\n  private:\n    std::vector<int>\
    \ data;\n    std::stack<std::pair<int, int>> history;\n};\n"
  code: "#include <stack>\n#include <utility>\n#include <vector>\n\n/**\n * @brief\
    \ Undo\u53EF\u80FDUnion-Find\n * @details Implement (union by size)\n *\n * @see\
    \ https://ei1333.github.io/luzhiled/snippets/structure/union-find.html\n */\n\
    struct undo_union_find {\n    undo_union_find() : data(), history() {}\n    undo_union_find(int\
    \ _n) : data(_n, -1), history() {}\n\n    int root(int x) { return data[x] < 0\
    \ ? x : root(data[x]); }\n    int get_root(int k) { return root(k); }\n\n    bool\
    \ is_root(int k) const { return data[k] < 0; }\n\n    bool same(int x, int y)\
    \ { return root(x) == root(y); }\n    bool is_same(int x, int y) { return same(x,\
    \ y); }\n\n    int size(int k) { return -data[root(k)]; }\n    int get_size(int\
    \ k) { return size(k); }\n\n    bool unite(int x, int y) {\n        x = root(x),\
    \ y = root(y);\n        history.emplace(x, data[x]);\n        history.emplace(y,\
    \ data[y]);\n        if (x == y) return false;\n        if (data[x] > data[y])\
    \ std::swap(x, y);\n        data[x] += data[y];\n        data[y] = x;\n      \
    \  return true;\n    }\n\n    void undo() {\n        data[history.top().first]\
    \ = history.top().second;\n        history.pop();\n        data[history.top().first]\
    \ = history.top().second;\n        history.pop();\n    }\n\n    int snapshot()\
    \ const { return history.size(); }\n\n    void rollback(int x = 0) {\n       \
    \ while ((int)(history.size()) > x) undo();\n    }\n\n  private:\n    std::vector<int>\
    \ data;\n    std::stack<std::pair<int, int>> history;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/tree/undo_union_find.hpp
  requiredBy: []
  timestamp: '2024-01-14 19:57:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/undo_union_find.test.cpp
  - test/aoj/joi/undo_union_find.test.cpp
documentation_of: lib/tree/undo_union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/undo_union_find.hpp
- /library/lib/tree/undo_union_find.hpp.html
title: "Undo\u53EF\u80FDUnion-Find"
---
