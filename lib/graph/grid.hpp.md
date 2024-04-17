---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/doubling.test.cpp
    title: test/aoj/jag/doubling.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/graph/grid.hpp\"\n#include <cstdint>\n#include <utility>\n\
    \nnamespace internal {\n\ntemplate <int Idx>\nstruct grid_impl {\n    template\
    \ <class Head, class... Tail>\n    constexpr grid_impl(Head &&head, Tail &&...tail)\n\
    \        : limit(head), impl(std::forward<Tail>(tail)...) {}\n\n    template <class\
    \ Head, class... Tail>\n    constexpr bool in_field(Head x, Tail &&...tail) const\
    \ {\n        return 0 <= x && x < limit && impl.in_field(std::forward<Tail>(tail)...);\n\
    \    }\n\n    template <class Head, class... Tail>\n    constexpr std::int64_t\
    \ flatten(Head x, Tail &&...tail) const {\n        return x + limit * impl.flatten(std::forward<Tail>(tail)...);\n\
    \    }\n\n  private:\n    std::int64_t limit;\n    grid_impl<Idx - 1> impl;\n\
    };\n\ntemplate <>\nstruct grid_impl<0> {\n    constexpr grid_impl() {}\n\n   \
    \ constexpr bool in_field() const { return true; }\n\n    constexpr std::int64_t\
    \ flatten() const { return 0; }\n};\n\n}  // namespace internal\n\ntemplate <int\
    \ Idx>\nstruct Grid {\n    template <class... Args, std::enable_if_t<(sizeof...(Args)\
    \ == Idx)> * = nullptr>\n    constexpr Grid(Args &&...args) : entity(std::forward<Args>(args)...)\
    \ {}\n\n    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)>\
    \ * = nullptr>\n    constexpr bool in_field(Args &&...args) const {\n        return\
    \ entity.in_field(std::forward<Args>(args)...);\n    }\n\n    template <class...\
    \ Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>\n    constexpr\
    \ std::int64_t flatten(Args &&...args) const {\n        return entity.flatten(std::forward<Args>(args)...);\n\
    \    }\n\n  private:\n    internal::grid_impl<Idx> entity;\n};\n"
  code: "#include <cstdint>\n#include <utility>\n\nnamespace internal {\n\ntemplate\
    \ <int Idx>\nstruct grid_impl {\n    template <class Head, class... Tail>\n  \
    \  constexpr grid_impl(Head &&head, Tail &&...tail)\n        : limit(head), impl(std::forward<Tail>(tail)...)\
    \ {}\n\n    template <class Head, class... Tail>\n    constexpr bool in_field(Head\
    \ x, Tail &&...tail) const {\n        return 0 <= x && x < limit && impl.in_field(std::forward<Tail>(tail)...);\n\
    \    }\n\n    template <class Head, class... Tail>\n    constexpr std::int64_t\
    \ flatten(Head x, Tail &&...tail) const {\n        return x + limit * impl.flatten(std::forward<Tail>(tail)...);\n\
    \    }\n\n  private:\n    std::int64_t limit;\n    grid_impl<Idx - 1> impl;\n\
    };\n\ntemplate <>\nstruct grid_impl<0> {\n    constexpr grid_impl() {}\n\n   \
    \ constexpr bool in_field() const { return true; }\n\n    constexpr std::int64_t\
    \ flatten() const { return 0; }\n};\n\n}  // namespace internal\n\ntemplate <int\
    \ Idx>\nstruct Grid {\n    template <class... Args, std::enable_if_t<(sizeof...(Args)\
    \ == Idx)> * = nullptr>\n    constexpr Grid(Args &&...args) : entity(std::forward<Args>(args)...)\
    \ {}\n\n    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)>\
    \ * = nullptr>\n    constexpr bool in_field(Args &&...args) const {\n        return\
    \ entity.in_field(std::forward<Args>(args)...);\n    }\n\n    template <class...\
    \ Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>\n    constexpr\
    \ std::int64_t flatten(Args &&...args) const {\n        return entity.flatten(std::forward<Args>(args)...);\n\
    \    }\n\n  private:\n    internal::grid_impl<Idx> entity;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/graph/grid.hpp
  requiredBy: []
  timestamp: '2024-02-22 18:28:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/jag/doubling.test.cpp
documentation_of: lib/graph/grid.hpp
layout: document
redirect_from:
- /library/lib/graph/grid.hpp
- /library/lib/graph/grid.hpp.html
title: lib/graph/grid.hpp
---
