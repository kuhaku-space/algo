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
  bundledCode: "#line 1 \"lib/algorithm/in_field.hpp\"\n#include <cstdint>\n#include\
    \ <utility>\n\nnamespace internal {\n\ntemplate <int Idx>\nstruct in_field_impl\
    \ {\n    template <class Head, class... Tail>\n    constexpr in_field_impl(Head\
    \ &&head, Tail &&...tail)\n        : limit(head), impl(std::forward<Tail>(tail)...)\
    \ {}\n\n    template <class Head, class... Tail>\n    constexpr bool is_internal(Head\
    \ x, Tail &&...tail) const {\n        return 0 <= x && x < limit && impl.is_internal(std::forward<Tail>(tail)...);\n\
    \    }\n\n  private:\n    std::int64_t limit;\n    in_field_impl<Idx - 1> impl;\n\
    };\n\ntemplate <>\nstruct in_field_impl<0> {\n    constexpr in_field_impl() {}\n\
    \n    constexpr bool is_internal() const {\n        return true;\n    }\n};\n\n\
    }  // namespace internal\n\ntemplate <int Idx>\nstruct InField {\n    template\
    \ <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>\n  \
    \  constexpr InField(Args &&...args) : entity(std::forward<Args>(args)...) {}\n\
    \n    template <class... Args>\n    constexpr bool operator()(Args &&...args)\
    \ const {\n        return entity.is_internal(std::forward<Args>(args)...);\n \
    \   }\n\n  private:\n    internal::in_field_impl<Idx> entity;\n};\n"
  code: "#include <cstdint>\n#include <utility>\n\nnamespace internal {\n\ntemplate\
    \ <int Idx>\nstruct in_field_impl {\n    template <class Head, class... Tail>\n\
    \    constexpr in_field_impl(Head &&head, Tail &&...tail)\n        : limit(head),\
    \ impl(std::forward<Tail>(tail)...) {}\n\n    template <class Head, class... Tail>\n\
    \    constexpr bool is_internal(Head x, Tail &&...tail) const {\n        return\
    \ 0 <= x && x < limit && impl.is_internal(std::forward<Tail>(tail)...);\n    }\n\
    \n  private:\n    std::int64_t limit;\n    in_field_impl<Idx - 1> impl;\n};\n\n\
    template <>\nstruct in_field_impl<0> {\n    constexpr in_field_impl() {}\n\n \
    \   constexpr bool is_internal() const {\n        return true;\n    }\n};\n\n\
    }  // namespace internal\n\ntemplate <int Idx>\nstruct InField {\n    template\
    \ <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>\n  \
    \  constexpr InField(Args &&...args) : entity(std::forward<Args>(args)...) {}\n\
    \n    template <class... Args>\n    constexpr bool operator()(Args &&...args)\
    \ const {\n        return entity.is_internal(std::forward<Args>(args)...);\n \
    \   }\n\n  private:\n    internal::in_field_impl<Idx> entity;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/algorithm/in_field.hpp
  requiredBy: []
  timestamp: '2024-02-22 00:09:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/jag/doubling.test.cpp
documentation_of: lib/algorithm/in_field.hpp
layout: document
redirect_from:
- /library/lib/algorithm/in_field.hpp
- /library/lib/algorithm/in_field.hpp.html
title: lib/algorithm/in_field.hpp
---
