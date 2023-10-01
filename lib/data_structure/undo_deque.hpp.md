---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\ntemplate <class T>\nstruct undo_deque\
    \ {\n    T front() const { return this->data.front(); }\n    T back() const {\
    \ return this->data.back(); }\n    bool empty() const { return this->data.empty();\
    \ }\n    int size() const { return this->data.size(); }\n\n    void emplace_front(T\
    \ x) {\n        this->history.emplace(0, x);\n        this->data.emplace_front(x);\n\
    \    }\n\n    void emplace_back(T x) {\n        this->history.emplace(1, x);\n\
    \        this->data.emplace_back(x);\n    }\n\n    void pop_front() {\n      \
    \  this->history.emplace(2, this->data.front());\n        this->data.pop_front();\n\
    \    }\n\n    void pop_back() {\n        this->history.emplace(3, this->data.back());\n\
    \        this->data.pop_back();\n    }\n\n    void undo() {\n        auto [x,\
    \ y] = this->history.top();\n        this->history.pop();\n        if (x == 0)\
    \ this->data.pop_front();\n        else if (x == 1) this->data.pop_back();\n \
    \       else if (x == 2) this->data.emplace_front(y);\n        else this->data.emplace_back(y);\n\
    \    }\n\n    int snapshot() const { return this->history.size(); }\n\n    void\
    \ rollback(int x = 0) {\n        while (x < (int)this->history.size()) this->undo();\n\
    \    }\n\n  private:\n    std::deque<T> data;\n    std::stack<std::pair<int, T>>\
    \ history;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/undo_deque.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/undo_deque.hpp
layout: document
redirect_from:
- /library/lib/data_structure/undo_deque.hpp
- /library/lib/data_structure/undo_deque.hpp.html
title: lib/data_structure/undo_deque.hpp
---
