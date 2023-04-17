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
    document_title: "\u524A\u9664\u4ED8\u304D\u512A\u5148\u9806\u4F4D\u4ED8\u304D\u30AD\
      \u30E5\u30FC"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u524A\u9664\u4ED8\
    \u304D\u512A\u5148\u9806\u4F4D\u4ED8\u304D\u30AD\u30E5\u30FC\r\n *\r\n * @tparam\
    \ T\r\n */\r\ntemplate <class T>\r\nstruct erasable_priority_queue {\r\n    bool\
    \ empty() const { return this->a.empty(); }\r\n    auto top() const { return this->a.top();\
    \ }\r\n\r\n    void emplace(T x) { this->a.emplace(x); }\r\n    void insert(T\
    \ x) { this->a.emplace(x); }\r\n    void push(T x) { this->a.emplace(x); }\r\n\
    \r\n    void pop() { this->erase(this->a.top()); }\r\n\r\n    void erase(T x)\
    \ {\r\n        this->b.emplace(x);\r\n        while (!this->a.empty() && this->a.top()\
    \ == this->b.top()) { this->a.pop(), this->b.pop(); }\r\n    }\r\n\r\n  private:\r\
    \n    std::priority_queue<T> a, b;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/erasable_priority_queue.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/erasable_priority_queue.hpp
layout: document
redirect_from:
- /library/lib/data_structure/erasable_priority_queue.hpp
- /library/lib/data_structure/erasable_priority_queue.hpp.html
title: "\u524A\u9664\u4ED8\u304D\u512A\u5148\u9806\u4F4D\u4ED8\u304D\u30AD\u30E5\u30FC"
---
