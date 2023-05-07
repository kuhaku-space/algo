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
    document_title: slope trick
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
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief slope trick\r\n\
    \ *\r\n * @tparam T\r\n */\r\ntemplate <class T>\r\nstruct slope_trick {\r\n \
    \   T min_f;\r\n    std::priority_queue<T> l;\r\n    std::priority_queue<T, std::vector<T>,\
    \ std::greater<>> r;\r\n\r\n    slope_trick() : min_f(), l(), r() {}\r\n\r\n \
    \   T get_x() { return this->l.top(); }\r\n    T get() { return this->min_f; }\r\
    \n    T get_y() { return this->get(); }\r\n\r\n    /**\r\n     * @brief Add f(x)\
    \ = a\r\n     *\r\n     * @param a\r\n     */\r\n    void add(T a) { this->min_f\
    \ += a; }\r\n\r\n    /**\r\n     * @brief Add f(x) = max(0, x - a)\r\n     *\r\
    \n     * @param a\r\n     */\r\n    void add_f(T a) {\r\n        if (!this->l.empty())\
    \ this->min_f += max(T(), this->l.top() - a);\r\n        this->l.emplace(a);\r\
    \n        auto x = tihs->l.top();\r\n        this->l.pop();\r\n        this->r.emplace(x);\r\
    \n    }\r\n\r\n    /**\r\n     * @brief Add f(x) = max(0, a - x)\r\n     *\r\n\
    \     * @param a\r\n     */\r\n    void add_g(T a) {\r\n        if (!this->r.empty())\
    \ this->min_f += max(T(), a - this->r.top());\r\n        this->r.emplace(a);\r\
    \n        auto x = this->r.top();\r\n        this->r.pop();\r\n        this->l.emplace(x);\r\
    \n    }\r\n\r\n    /**\r\n     * @brief Add f(x) = abs(x - a) = max(0, x - a)\
    \ + max(0, a - x)\r\n     *\r\n     * @param a\r\n     */\r\n    void add_abs(T\
    \ a) {\r\n        this->add_f(a);\r\n        this->add_g(a);\r\n    }\r\n\r\n\
    \    void min_l() { this->r = std::priority_queue<T, std::vector<T>, std::greater<>>();\
    \ }\r\n    void min_r() { this->l = std::priority_queue<T>(); }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/slope_trick.hpp
  requiredBy: []
  timestamp: '2023-05-07 20:09:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/slope_trick.hpp
layout: document
redirect_from:
- /library/lib/math/slope_trick.hpp
- /library/lib/math/slope_trick.hpp.html
title: slope trick
---
