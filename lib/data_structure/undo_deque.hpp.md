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
  bundledCode: "#line 1 \"lib/data_structure/undo_deque.hpp\"\n#include <deque>\n\
    #include <stack>\n#include <utility>\n\ntemplate <class T>\nstruct undo_deque\
    \ {\n    T front() const { return data.front(); }\n    T back() const { return\
    \ data.back(); }\n    bool empty() const { return data.empty(); }\n    int size()\
    \ const { return data.size(); }\n\n    void emplace_front(T x) {\n        history.emplace(0,\
    \ x);\n        data.emplace_front(x);\n    }\n\n    void emplace_back(T x) {\n\
    \        history.emplace(1, x);\n        data.emplace_back(x);\n    }\n\n    void\
    \ pop_front() {\n        history.emplace(2, data.front());\n        data.pop_front();\n\
    \    }\n\n    void pop_back() {\n        history.emplace(3, data.back());\n  \
    \      data.pop_back();\n    }\n\n    void undo() {\n        auto [x, y] = history.top();\n\
    \        history.pop();\n        if (x == 0) data.pop_front();\n        else if\
    \ (x == 1) data.pop_back();\n        else if (x == 2) data.emplace_front(y);\n\
    \        else data.emplace_back(y);\n    }\n\n    int snapshot() const { return\
    \ history.size(); }\n\n    void rollback(int x = 0) {\n        while (x < (int)history.size())\
    \ undo();\n    }\n\n  private:\n    std::deque<T> data;\n    std::stack<std::pair<int,\
    \ T>> history;\n};\n"
  code: "#include <deque>\n#include <stack>\n#include <utility>\n\ntemplate <class\
    \ T>\nstruct undo_deque {\n    T front() const { return data.front(); }\n    T\
    \ back() const { return data.back(); }\n    bool empty() const { return data.empty();\
    \ }\n    int size() const { return data.size(); }\n\n    void emplace_front(T\
    \ x) {\n        history.emplace(0, x);\n        data.emplace_front(x);\n    }\n\
    \n    void emplace_back(T x) {\n        history.emplace(1, x);\n        data.emplace_back(x);\n\
    \    }\n\n    void pop_front() {\n        history.emplace(2, data.front());\n\
    \        data.pop_front();\n    }\n\n    void pop_back() {\n        history.emplace(3,\
    \ data.back());\n        data.pop_back();\n    }\n\n    void undo() {\n      \
    \  auto [x, y] = history.top();\n        history.pop();\n        if (x == 0) data.pop_front();\n\
    \        else if (x == 1) data.pop_back();\n        else if (x == 2) data.emplace_front(y);\n\
    \        else data.emplace_back(y);\n    }\n\n    int snapshot() const { return\
    \ history.size(); }\n\n    void rollback(int x = 0) {\n        while (x < (int)history.size())\
    \ undo();\n    }\n\n  private:\n    std::deque<T> data;\n    std::stack<std::pair<int,\
    \ T>> history;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/data_structure/undo_deque.hpp
  requiredBy: []
  timestamp: '2024-05-03 19:54:42+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/undo_deque.hpp
layout: document
redirect_from:
- /library/lib/data_structure/undo_deque.hpp
- /library/lib/data_structure/undo_deque.hpp.html
title: lib/data_structure/undo_deque.hpp
---
