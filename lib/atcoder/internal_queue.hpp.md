---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/atcoder/maxflow.hpp
    title: lib/atcoder/maxflow.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/internal_queue.hpp\"\n\n\n\r\n#include <vector>\r\
    \n\r\nnamespace atcoder {\r\n\r\nnamespace internal {\r\n\r\ntemplate <class T>\
    \ struct simple_queue {\r\n    std::vector<T> payload;\r\n    int pos = 0;\r\n\
    \    void reserve(int n) { payload.reserve(n); }\r\n    int size() const { return\
    \ int(payload.size()) - pos; }\r\n    bool empty() const { return pos == int(payload.size());\
    \ }\r\n    void push(const T& t) { payload.push_back(t); }\r\n    T& front() {\
    \ return payload[pos]; }\r\n    void clear() {\r\n        payload.clear();\r\n\
    \        pos = 0;\r\n    }\r\n    void pop() { pos++; }\r\n};\r\n\r\n}  // namespace\
    \ internal\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_INTERNAL_QUEUE_HPP\r\n#define ATCODER_INTERNAL_QUEUE_HPP\
    \ 1\r\n\r\n#include <vector>\r\n\r\nnamespace atcoder {\r\n\r\nnamespace internal\
    \ {\r\n\r\ntemplate <class T> struct simple_queue {\r\n    std::vector<T> payload;\r\
    \n    int pos = 0;\r\n    void reserve(int n) { payload.reserve(n); }\r\n    int\
    \ size() const { return int(payload.size()) - pos; }\r\n    bool empty() const\
    \ { return pos == int(payload.size()); }\r\n    void push(const T& t) { payload.push_back(t);\
    \ }\r\n    T& front() { return payload[pos]; }\r\n    void clear() {\r\n     \
    \   payload.clear();\r\n        pos = 0;\r\n    }\r\n    void pop() { pos++; }\r\
    \n};\r\n\r\n}  // namespace internal\r\n\r\n}  // namespace atcoder\r\n\r\n#endif\
    \  // ATCODER_INTERNAL_QUEUE_HPP\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/atcoder/internal_queue.hpp
  requiredBy:
  - lib/atcoder/maxflow.hpp
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/internal_queue.hpp
layout: document
redirect_from:
- /library/lib/atcoder/internal_queue.hpp
- /library/lib/atcoder/internal_queue.hpp.html
title: lib/atcoder/internal_queue.hpp
---
