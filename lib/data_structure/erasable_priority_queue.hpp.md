---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u524A\u9664\u53EF\u80FD\u512A\u5148\u5EA6\u4ED8\u304D\u30AD\u30E5\
      \u30FC"
    links: []
  bundledCode: "#line 1 \"lib/data_structure/erasable_priority_queue.hpp\"\n#include\
    \ <functional>\r\n#include <queue>\r\n#include <utility>\r\n\r\n/**\r\n * @brief\
    \ \u524A\u9664\u53EF\u80FD\u512A\u5148\u5EA6\u4ED8\u304D\u30AD\u30E5\u30FC\r\n\
    \ *\r\n * @tparam T\r\n */\r\ntemplate <class T, class Comp = std::less<>>\r\n\
    struct erasable_priority_queue {\r\n    bool empty() const { return a.empty();\
    \ }\r\n    int size() const { return a.size() - b.size(); }\r\n    T top() const\
    \ { return a.top(); }\r\n\r\n    void insert(const T &x) { a.push(x); }\r\n  \
    \  void insert(T &&x) { a.push(std::move(x)); }\r\n    void push(const T &x) {\
    \ a.push(x); }\r\n    void push(T &&x) { a.push(std::move(x)); }\r\n    template\
    \ <typename... Args>\r\n    void emplace(Args &&...args) {\r\n        a.emplace(std::forward<Args>(args)...);\r\
    \n    }\r\n\r\n    void pop() { erase(a.top()); }\r\n\r\n    void erase(T x) {\r\
    \n        b.emplace(x);\r\n        while (!b.empty() && a.top() == b.top()) {\
    \ a.pop(), b.pop(); }\r\n    }\r\n\r\n  private:\r\n    std::priority_queue<T,\
    \ std::vector<T>, Comp> a, b;\r\n};\r\n"
  code: "#include <functional>\r\n#include <queue>\r\n#include <utility>\r\n\r\n/**\r\
    \n * @brief \u524A\u9664\u53EF\u80FD\u512A\u5148\u5EA6\u4ED8\u304D\u30AD\u30E5\
    \u30FC\r\n *\r\n * @tparam T\r\n */\r\ntemplate <class T, class Comp = std::less<>>\r\
    \nstruct erasable_priority_queue {\r\n    bool empty() const { return a.empty();\
    \ }\r\n    int size() const { return a.size() - b.size(); }\r\n    T top() const\
    \ { return a.top(); }\r\n\r\n    void insert(const T &x) { a.push(x); }\r\n  \
    \  void insert(T &&x) { a.push(std::move(x)); }\r\n    void push(const T &x) {\
    \ a.push(x); }\r\n    void push(T &&x) { a.push(std::move(x)); }\r\n    template\
    \ <typename... Args>\r\n    void emplace(Args &&...args) {\r\n        a.emplace(std::forward<Args>(args)...);\r\
    \n    }\r\n\r\n    void pop() { erase(a.top()); }\r\n\r\n    void erase(T x) {\r\
    \n        b.emplace(x);\r\n        while (!b.empty() && a.top() == b.top()) {\
    \ a.pop(), b.pop(); }\r\n    }\r\n\r\n  private:\r\n    std::priority_queue<T,\
    \ std::vector<T>, Comp> a, b;\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/data_structure/erasable_priority_queue.hpp
  requiredBy: []
  timestamp: '2024-04-19 14:46:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/erasable_priority_queue.hpp
layout: document
redirect_from:
- /library/lib/data_structure/erasable_priority_queue.hpp
- /library/lib/data_structure/erasable_priority_queue.hpp.html
title: "\u524A\u9664\u53EF\u80FD\u512A\u5148\u5EA6\u4ED8\u304D\u30AD\u30E5\u30FC"
---
