---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Add f(x) = a
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T, class U>\r\n\
    struct slope_trick {\r\n    U min_f;\r\n    priority_queue<T> l;\r\n    priority_queue<T,\
    \ vector<T>, greater<>> r;\r\n\r\n    slope_trick() : min_f(), l(), r() {}\r\n\
    \r\n    T get_x() { return this->l.top(); }\r\n    U get() { return this->min_f;\
    \ }\r\n    U get_y() { return this->get(); }\r\n\r\n    /**\r\n     * @brief Add\
    \ f(x) = a\r\n     *\r\n     * @param a\r\n     */\r\n    void add(U a) { this->min_f\
    \ += a; }\r\n\r\n    /**\r\n     * @brief Add f(x) = max(0, x - a)\r\n     *\r\
    \n     * @param a\r\n     */\r\n    void add_f(T a) {\r\n        if (!this->l.empty())\
    \ this->min_f += max(U(), this->l.top() - a);\r\n        this->l.emplace(a);\r\
    \n        auto x = tihs->l.top();\r\n        this->l.pop();\r\n        this->r.emplace(x);\r\
    \n    }\r\n\r\n    /**\r\n     * @brief Add f(x) = max(0, a - x)\r\n     *\r\n\
    \     * @param a\r\n     */\r\n    void add_g(U a) {\r\n        if (!this->r.empty())\
    \ this->min_f += max(U(), a - this->r.top());\r\n        this->r.emplace(a);\r\
    \n        auto x = this->r.top();\r\n        this->r.pop();\r\n        this->l.emplace(x);\r\
    \n    }\r\n\r\n    /**\r\n     * @brief Add f(x) = abs(x - a) = max(0, x - a)\
    \ + max(0, a - x)\r\n     *\r\n     * @param a\r\n     */\r\n    void add_abs(U\
    \ a) {\r\n        this->add_f(a);\r\n        this->add_g(a);\r\n    }\r\n\r\n\
    \    void min_l() { this->r = priority_queue<T, vector<T>, greater<>>(); }\r\n\
    \    void min_r() { this->l = priority_queue<T>(); }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/slope_trick.hpp
  requiredBy: []
  timestamp: '2021-11-25 19:37:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/slope_trick.hpp
layout: document
redirect_from:
- /library/lib/math/slope_trick.hpp
- /library/lib/math/slope_trick.hpp.html
title: Add f(x) = a
---
