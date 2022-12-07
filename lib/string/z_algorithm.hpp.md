---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/string/zalgorithm.test.cpp
    title: test/yosupo/string/zalgorithm.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Z algorithm
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief Z algorithm\r\n\
    \ * @details Z[i] := S[i:Z[i]] == S[0:Z[i]-i]\r\n *\r\n * @tparam Container\r\n\
    \ */\r\ntemplate <class Container>\r\nstruct z_algorithm {\r\n    z_algorithm(const\
    \ Container &_s) : s(_s), z(_s.size()) {\r\n        this->z[0] = this->s.size();\r\
    \n        int i = 1, j = 0;\r\n        while (i < s.size()) {\r\n            while\
    \ (i + j < (int)this->s.size() && this->s[j] == this->s[i + j]) ++j;\r\n     \
    \       this->z[i] = j;\r\n            if (!j) {\r\n                ++i;\r\n \
    \               continue;\r\n            }\r\n            int k = 1;\r\n     \
    \       while (i + k < (int)this->s.size() && k + this->z[k] < j)\r\n        \
    \        this->z[i + k] = this->z[k], ++k;\r\n            i += k, j -= k;\r\n\
    \        }\r\n    }\r\n\r\n    const auto &operator[](int i) const { return this->z[i];\
    \ }\r\n    auto &operator[](int i) { return this->z[i]; }\r\n    const auto begin()\
    \ const { return this->z.begin(); }\r\n    auto begin() { return this->z.begin();\
    \ }\r\n    const auto end() const { return this->z.end(); }\r\n    auto end()\
    \ { return this->z.end(); }\r\n\r\n    const std::vector<int> &get() { return\
    \ this->z; }\r\n\r\n  private:\r\n    const Container &s;\r\n    std::vector<int>\
    \ z;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/z_algorithm.hpp
  requiredBy: []
  timestamp: '2022-07-20 04:55:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/string/zalgorithm.test.cpp
documentation_of: lib/string/z_algorithm.hpp
layout: document
redirect_from:
- /library/lib/string/z_algorithm.hpp
- /library/lib/string/z_algorithm.hpp.html
title: Z algorithm
---
