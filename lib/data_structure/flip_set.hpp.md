---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/data_structure/flip_set.hpp\"\n#include <set>\n\ntemplate\
    \ <class T>\nstruct flip_set {\n    flip_set() : data() {}\n\n    bool empty()\
    \ const {\n        return data.empty();\n    }\n    int size() const {\n     \
    \   return data.size();\n    }\n\n    bool contains(const T &x) const {\n    \
    \    return data.count(x);\n    }\n    bool contains(T &&x) const {\n        return\
    \ data.count(std::move(x));\n    }\n\n    bool flip(const T &x) {\n        if\
    \ (data.count(x))\n            return data.erase(x), false;\n        else\n  \
    \          return data.emplace(x), true;\n    }\n    bool flip(T &&x) {\n    \
    \    if (data.count(x))\n            return data.erase(std::move(x)), false;\n\
    \        else\n            return data.emplace(x), true;\n    }\n\n  private:\n\
    \    std::set<T> data;\n};\n"
  code: "#include <set>\n\ntemplate <class T>\nstruct flip_set {\n    flip_set() :\
    \ data() {}\n\n    bool empty() const {\n        return data.empty();\n    }\n\
    \    int size() const {\n        return data.size();\n    }\n\n    bool contains(const\
    \ T &x) const {\n        return data.count(x);\n    }\n    bool contains(T &&x)\
    \ const {\n        return data.count(std::move(x));\n    }\n\n    bool flip(const\
    \ T &x) {\n        if (data.count(x))\n            return data.erase(x), false;\n\
    \        else\n            return data.emplace(x), true;\n    }\n    bool flip(T\
    \ &&x) {\n        if (data.count(x))\n            return data.erase(std::move(x)),\
    \ false;\n        else\n            return data.emplace(x), true;\n    }\n\n \
    \ private:\n    std::set<T> data;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/data_structure/flip_set.hpp
  requiredBy: []
  timestamp: '2024-02-09 11:05:37+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/flip_set.hpp
layout: document
redirect_from:
- /library/lib/data_structure/flip_set.hpp
- /library/lib/data_structure/flip_set.hpp.html
title: lib/data_structure/flip_set.hpp
---
