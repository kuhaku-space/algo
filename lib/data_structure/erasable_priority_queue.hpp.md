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
    document_title: "\u524A\u9664\u53EF\u80FD\u512A\u5148\u5EA6\u4ED8\u304D\u30AD\u30E5\
      \u30FC"
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
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u524A\u9664\u53EF\
    \u80FD\u512A\u5148\u5EA6\u4ED8\u304D\u30AD\u30E5\u30FC\r\n *\r\n * @tparam T\r\
    \n */\r\ntemplate <class T, class Comp = std::less<>>\r\nstruct erasable_priority_queue\
    \ {\r\n    bool empty() const { return a.empty(); }\r\n    int size() const {\
    \ return a.size() - b.size(); }\r\n    T top() const { return a.top(); }\r\n\r\
    \n    void insert(const T &x) { a.push(x); }\r\n    void insert(T &&x) { a.push(std::move(x));\
    \ }\r\n    void push(const T &x) { a.push(x); }\r\n    void push(T &&x) { a.push(std::move(x));\
    \ }\r\n    template <typename... Args>\r\n    void emplace(Args &&...args) {\r\
    \n        a.emplace(std::forward<Args>(args)...);\r\n    }\r\n\r\n    void pop()\
    \ { erase(a.top()); }\r\n\r\n    void erase(T x) {\r\n        b.emplace(x);\r\n\
    \        while (!b.empty() && a.top() == b.top()) {\r\n            a.pop(), b.pop();\r\
    \n        }\r\n    }\r\n\r\n  private:\r\n    std::priority_queue<T, std::vector<T>,\
    \ Comp> a, b;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/erasable_priority_queue.hpp
  requiredBy: []
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/erasable_priority_queue.hpp
layout: document
redirect_from:
- /library/lib/data_structure/erasable_priority_queue.hpp
- /library/lib/data_structure/erasable_priority_queue.hpp.html
title: "\u524A\u9664\u53EF\u80FD\u512A\u5148\u5EA6\u4ED8\u304D\u30AD\u30E5\u30FC"
---
