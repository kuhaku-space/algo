---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/dynamic_union_find.test.cpp
    title: test/aoj/jag/dynamic_union_find.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u52D5\u7684Union-Find"
    links: []
  bundledCode: "#line 1 \"lib/tree/dynamic_union_find.hpp\"\n#include <cstdint>\n\
    #include <unordered_map>\n#include <utility>\n\n/**\n * @brief \u52D5\u7684Union-Find\n\
    \ *\n */\nstruct dynamic_union_find {\n    dynamic_union_find() : data() {}\n\n\
    \    std::int64_t root(std::int64_t x) {\n        if (!data.count(x)) data[x]\
    \ = -1;\n        return data[x] < 0 ? x : data[x] = root(data[x]);\n    }\n  \
    \  std::int64_t get_root(std::int64_t x) { return root(x); }\n\n    bool is_root(std::int64_t\
    \ x) { return data.count(x) && data[x] < 0; }\n\n    bool same(std::int64_t x,\
    \ std::int64_t y) { return root(x) == root(y); }\n    bool is_same(std::int64_t\
    \ x, std::int64_t y) { return same(x, y); }\n\n    int size(std::int64_t x) {\
    \ return -data[root(x)]; }\n    int get_size(std::int64_t x) { return size(x);\
    \ }\n\n    void clear() { data.clear(); }\n\n    bool unite(std::int64_t x, std::int64_t\
    \ y) {\n        x = root(x), y = root(y);\n        if (x == y) return false;\n\
    \        if (data[x] > data[y]) std::swap(x, y);\n        data[x] += data[y];\n\
    \        data[y] = x;\n        return true;\n    }\n\n    template <class F>\n\
    \    bool unite(std::int64_t x, std::int64_t y, F f) {\n        x = root(x), y\
    \ = root(y);\n        if (x != y) {\n            if (data[x] > data[y]) std::swap(x,\
    \ y);\n            data[x] += data[y];\n            data[y] = x;\n        }\n\
    \        f(x, y);\n        return x != y;\n    }\n\n  private:\n    std::unordered_map<std::int64_t,\
    \ std::int64_t> data;\n};\n"
  code: "#include <cstdint>\n#include <unordered_map>\n#include <utility>\n\n/**\n\
    \ * @brief \u52D5\u7684Union-Find\n *\n */\nstruct dynamic_union_find {\n    dynamic_union_find()\
    \ : data() {}\n\n    std::int64_t root(std::int64_t x) {\n        if (!data.count(x))\
    \ data[x] = -1;\n        return data[x] < 0 ? x : data[x] = root(data[x]);\n \
    \   }\n    std::int64_t get_root(std::int64_t x) { return root(x); }\n\n    bool\
    \ is_root(std::int64_t x) { return data.count(x) && data[x] < 0; }\n\n    bool\
    \ same(std::int64_t x, std::int64_t y) { return root(x) == root(y); }\n    bool\
    \ is_same(std::int64_t x, std::int64_t y) { return same(x, y); }\n\n    int size(std::int64_t\
    \ x) { return -data[root(x)]; }\n    int get_size(std::int64_t x) { return size(x);\
    \ }\n\n    void clear() { data.clear(); }\n\n    bool unite(std::int64_t x, std::int64_t\
    \ y) {\n        x = root(x), y = root(y);\n        if (x == y) return false;\n\
    \        if (data[x] > data[y]) std::swap(x, y);\n        data[x] += data[y];\n\
    \        data[y] = x;\n        return true;\n    }\n\n    template <class F>\n\
    \    bool unite(std::int64_t x, std::int64_t y, F f) {\n        x = root(x), y\
    \ = root(y);\n        if (x != y) {\n            if (data[x] > data[y]) std::swap(x,\
    \ y);\n            data[x] += data[y];\n            data[y] = x;\n        }\n\
    \        f(x, y);\n        return x != y;\n    }\n\n  private:\n    std::unordered_map<std::int64_t,\
    \ std::int64_t> data;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/tree/dynamic_union_find.hpp
  requiredBy: []
  timestamp: '2024-04-27 16:43:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/jag/dynamic_union_find.test.cpp
documentation_of: lib/tree/dynamic_union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/dynamic_union_find.hpp
- /library/lib/tree/dynamic_union_find.hpp.html
title: "\u52D5\u7684Union-Find"
---
