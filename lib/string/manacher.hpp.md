---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/hupc/manacher.test.cpp
    title: test/aoj/hupc/manacher.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/string/enumerate_palindromes.test.cpp
    title: test/yosupo/string/enumerate_palindromes.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Manacher
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
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief Manacher\r\n *\
    \ @details R[i] := S[i-R[i]:i] == S[i:i+R[i]]\r\n *\r\n * @tparam Container\r\n\
    \ */\r\ntemplate <typename Container>\r\nstruct Manacher {\r\n    Manacher(const\
    \ Container &_s) : _size(_s.size()), s(_s), r(_s.size()) {\r\n        int i =\
    \ 0, j = 0;\r\n        while (i < this->_size) {\r\n            while (i - j >=\
    \ 0 && i + j < this->_size && this->s[i - j] == this->s[i + j]) ++j;\r\n     \
    \       this->r[i] = j;\r\n            int k = 1;\r\n            while (i - k\
    \ >= 0 && i + k < this->_size && k + this->r[i - k] < j)\r\n                this->r[i\
    \ + k] = this->r[i - k], ++k;\r\n            i += k, j -= k;\r\n        }\r\n\
    \    }\r\n\r\n    const auto &operator[](int i) const { return this->r[i]; }\r\
    \n    auto &operator[](int i) { return this->r[i]; }\r\n    const auto begin()\
    \ const { return this->r.begin(); }\r\n    auto begin() { return this->r.begin();\
    \ }\r\n    const auto end() const { return this->r.end(); }\r\n    auto end()\
    \ { return this->r.end(); }\r\n\r\n    const std::vector<int> &get() { return\
    \ this->r; }\r\n\r\n  private:\r\n    int _size;\r\n    const Container &s;\r\n\
    \    std::vector<int> r;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/manacher.hpp
  requiredBy: []
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/hupc/manacher.test.cpp
  - test/yosupo/string/enumerate_palindromes.test.cpp
documentation_of: lib/string/manacher.hpp
layout: document
redirect_from:
- /library/lib/string/manacher.hpp
- /library/lib/string/manacher.hpp.html
title: Manacher
---
