---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: slope trick
    links: []
  bundledCode: "#line 1 \"lib/math/slope_trick.hpp\"\n#include <algorithm>\r\n#include\
    \ <functional>\r\n#include <queue>\r\n#include <vector>\r\n\r\n/**\r\n * @brief\
    \ slope trick\r\n *\r\n * @tparam T\r\n */\r\ntemplate <class T>\r\nstruct slope_trick\
    \ {\r\n    T min_f;\r\n    std::priority_queue<T> l;\r\n    std::priority_queue<T,\
    \ std::vector<T>, std::greater<>> r;\r\n\r\n    slope_trick() : min_f(), l(),\
    \ r() {}\r\n\r\n    T get_x() { return l.top(); }\r\n    T get() { return min_f;\
    \ }\r\n    T get_y() { return get(); }\r\n\r\n    /**\r\n     * @brief Add f(x)\
    \ = a\r\n     *\r\n     * @param a\r\n     */\r\n    void add(T a) { min_f +=\
    \ a; }\r\n\r\n    /**\r\n     * @brief Add f(x) = max(0, x - a)\r\n     *\r\n\
    \     * @param a\r\n     */\r\n    void add_f(T a) {\r\n        if (!l.empty())\
    \ min_f += std::max(T(), l.top() - a);\r\n        l.emplace(a);\r\n        auto\
    \ x = l.top();\r\n        l.pop();\r\n        r.emplace(x);\r\n    }\r\n\r\n \
    \   /**\r\n     * @brief Add f(x) = max(0, a - x)\r\n     *\r\n     * @param a\r\
    \n     */\r\n    void add_g(T a) {\r\n        if (!r.empty()) min_f += std::max(T(),\
    \ a - r.top());\r\n        r.emplace(a);\r\n        auto x = r.top();\r\n    \
    \    r.pop();\r\n        l.emplace(x);\r\n    }\r\n\r\n    /**\r\n     * @brief\
    \ Add f(x) = abs(x - a) = max(0, x - a) + max(0, a - x)\r\n     *\r\n     * @param\
    \ a\r\n     */\r\n    void add_abs(T a) {\r\n        add_f(a);\r\n        add_g(a);\r\
    \n    }\r\n\r\n    void min_l() { r = std::priority_queue<T, std::vector<T>, std::greater<>>();\
    \ }\r\n    void min_r() { l = std::priority_queue<T>(); }\r\n};\r\n"
  code: "#include <algorithm>\r\n#include <functional>\r\n#include <queue>\r\n#include\
    \ <vector>\r\n\r\n/**\r\n * @brief slope trick\r\n *\r\n * @tparam T\r\n */\r\n\
    template <class T>\r\nstruct slope_trick {\r\n    T min_f;\r\n    std::priority_queue<T>\
    \ l;\r\n    std::priority_queue<T, std::vector<T>, std::greater<>> r;\r\n\r\n\
    \    slope_trick() : min_f(), l(), r() {}\r\n\r\n    T get_x() { return l.top();\
    \ }\r\n    T get() { return min_f; }\r\n    T get_y() { return get(); }\r\n\r\n\
    \    /**\r\n     * @brief Add f(x) = a\r\n     *\r\n     * @param a\r\n     */\r\
    \n    void add(T a) { min_f += a; }\r\n\r\n    /**\r\n     * @brief Add f(x) =\
    \ max(0, x - a)\r\n     *\r\n     * @param a\r\n     */\r\n    void add_f(T a)\
    \ {\r\n        if (!l.empty()) min_f += std::max(T(), l.top() - a);\r\n      \
    \  l.emplace(a);\r\n        auto x = l.top();\r\n        l.pop();\r\n        r.emplace(x);\r\
    \n    }\r\n\r\n    /**\r\n     * @brief Add f(x) = max(0, a - x)\r\n     *\r\n\
    \     * @param a\r\n     */\r\n    void add_g(T a) {\r\n        if (!r.empty())\
    \ min_f += std::max(T(), a - r.top());\r\n        r.emplace(a);\r\n        auto\
    \ x = r.top();\r\n        r.pop();\r\n        l.emplace(x);\r\n    }\r\n\r\n \
    \   /**\r\n     * @brief Add f(x) = abs(x - a) = max(0, x - a) + max(0, a - x)\r\
    \n     *\r\n     * @param a\r\n     */\r\n    void add_abs(T a) {\r\n        add_f(a);\r\
    \n        add_g(a);\r\n    }\r\n\r\n    void min_l() { r = std::priority_queue<T,\
    \ std::vector<T>, std::greater<>>(); }\r\n    void min_r() { l = std::priority_queue<T>();\
    \ }\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/math/slope_trick.hpp
  requiredBy: []
  timestamp: '2024-04-17 14:43:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/slope_trick.hpp
layout: document
redirect_from:
- /library/lib/math/slope_trick.hpp
- /library/lib/math/slope_trick.hpp.html
title: slope trick
---
