---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/rupc/range_set.test.cpp
    title: test/aoj/rupc/range_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/binary_tree/range_set.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <set>\n#include <utility>\n\n\
    template <class T>\nstruct range_set {\n    range_set() = default;\n\n    std::pair<T,\
    \ T> get(T x) const {\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        if (it == intervals.end() || !contains(x, *it)) return std::make_pair(inf,\
    \ inf);\n        return std::make_pair(it->second, it->first);\n    }\n\n    bool\
    \ contains(T x) const {\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        return it != intervals.end() && contains(x, *it);\n    }\n\n \
    \   bool same(T x, T y) const {\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        return it != intervals.end() && contains(x, *it) && contains(y,\
    \ *it);\n    }\n\n    std::pair<T, T> insert(T x, T y) {\n        assert(x < y);\n\
    \        auto it = intervals.lower_bound(std::make_pair(x, std::numeric_limits<T>::lowest()));\n\
    \        while (it != intervals.end() && it->second <= y) {\n            x = std::min(x,\
    \ it->second);\n            y = std::max(y, it->first);\n            it = intervals.erase(it);\n\
    \        }\n        intervals.emplace(y, x);\n        return std::make_pair(x,\
    \ y);\n    }\n\n    std::pair<T, T> insert(T x) { return insert(x, x + 1); }\n\
    \n    void erase(T x, T y) {\n        assert(x < y);\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        if (it == intervals.end()) return;\n        if (it->second !=\
    \ x) {\n            T l = it->second, r = it->first;\n            intervals.erase(it);\n\
    \            intervals.emplace(x, l);\n            intervals.emplace(r, x);\n\
    \        }\n        it = intervals.lower_bound(std::make_pair(x, x));\n      \
    \  while (it != intervals.end()) {\n            if (y <= it->second) break;\n\
    \            if (y < it->first) {\n                T r = it->first;\n        \
    \        intervals.erase(it);\n                intervals.emplace(r, y);\n    \
    \            break;\n            }\n            it = intervals.erase(it);\n  \
    \      }\n    }\n\n    void erase(T x) { erase(x, x + 1); }\n\n  private:\n  \
    \  static constexpr T inf = std::numeric_limits<T>::max();\n    std::set<std::pair<T,\
    \ T>> intervals;\n\n    static bool contains(T x, const std::pair<T, T> &p) {\
    \ return p.second <= x && x < p.first; }\n};\n"
  code: "#include <algorithm>\n#include <cassert>\n#include <limits>\n#include <set>\n\
    #include <utility>\n\ntemplate <class T>\nstruct range_set {\n    range_set()\
    \ = default;\n\n    std::pair<T, T> get(T x) const {\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        if (it == intervals.end() || !contains(x, *it)) return std::make_pair(inf,\
    \ inf);\n        return std::make_pair(it->second, it->first);\n    }\n\n    bool\
    \ contains(T x) const {\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        return it != intervals.end() && contains(x, *it);\n    }\n\n \
    \   bool same(T x, T y) const {\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        return it != intervals.end() && contains(x, *it) && contains(y,\
    \ *it);\n    }\n\n    std::pair<T, T> insert(T x, T y) {\n        assert(x < y);\n\
    \        auto it = intervals.lower_bound(std::make_pair(x, std::numeric_limits<T>::lowest()));\n\
    \        while (it != intervals.end() && it->second <= y) {\n            x = std::min(x,\
    \ it->second);\n            y = std::max(y, it->first);\n            it = intervals.erase(it);\n\
    \        }\n        intervals.emplace(y, x);\n        return std::make_pair(x,\
    \ y);\n    }\n\n    std::pair<T, T> insert(T x) { return insert(x, x + 1); }\n\
    \n    void erase(T x, T y) {\n        assert(x < y);\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        if (it == intervals.end()) return;\n        if (it->second !=\
    \ x) {\n            T l = it->second, r = it->first;\n            intervals.erase(it);\n\
    \            intervals.emplace(x, l);\n            intervals.emplace(r, x);\n\
    \        }\n        it = intervals.lower_bound(std::make_pair(x, x));\n      \
    \  while (it != intervals.end()) {\n            if (y <= it->second) break;\n\
    \            if (y < it->first) {\n                T r = it->first;\n        \
    \        intervals.erase(it);\n                intervals.emplace(r, y);\n    \
    \            break;\n            }\n            it = intervals.erase(it);\n  \
    \      }\n    }\n\n    void erase(T x) { erase(x, x + 1); }\n\n  private:\n  \
    \  static constexpr T inf = std::numeric_limits<T>::max();\n    std::set<std::pair<T,\
    \ T>> intervals;\n\n    static bool contains(T x, const std::pair<T, T> &p) {\
    \ return p.second <= x && x < p.first; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/binary_tree/range_set.hpp
  requiredBy: []
  timestamp: '2024-04-19 12:27:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/rupc/range_set.test.cpp
documentation_of: lib/binary_tree/range_set.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/range_set.hpp
- /library/lib/binary_tree/range_set.hpp.html
title: lib/binary_tree/range_set.hpp
---
