---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u884C\u5217\u30E9\u30A4\u30D6\u30E9\u30EA"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u884C\u5217\u30E9\
    \u30A4\u30D6\u30E9\u30EA\r\n *\r\n * @tparam T \u8981\u7D20\u306E\u578B\r\n */\r\
    \ntemplate <class T>\r\nstruct Matrix {\r\n    Matrix() = default;\r\n    Matrix(int\
    \ x) : v(x, std::vector<T>(x)) {}\r\n    Matrix(int x, int y) : v(x, std::vector<T>(y))\
    \ {}\r\n    Matrix(const std::vector<std::vector<T>> &_v) : v(_v) {}\r\n\r\n \
    \   const std::vector<T> &operator[](int i) const {\r\n        assert(0 <= i &&\
    \ i < this->v.size());\r\n        return this->v[i];\r\n    }\r\n    std::vector<T>\
    \ &operator[](int i) {\r\n        assert(0 <= i && i < this->v.size());\r\n  \
    \      return this->v[i];\r\n    }\r\n\r\n    Matrix &operator+=(const Matrix\
    \ &rhs) {\r\n        assert(this->v.size() == rhs.v.size());\r\n        assert(this->v[0].size()\
    \ == rhs.v[0].size());\r\n        for (int i = 0; i < this->v.size(); ++i) {\r\
    \n            for (int j = 0; j < this->v[0].size(); ++j) this->v[i][j] += rhs.v[i][j];\r\
    \n        }\r\n        return *this;\r\n    }\r\n    Matrix &operator-=(const\
    \ Matrix &rhs) {\r\n        assert(this->v.size() == rhs.v.size());\r\n      \
    \  assert(this->v[0].size() == rhs.v[0].size());\r\n        for (int i = 0; i\
    \ < this->v.size(); ++i) {\r\n            for (int j = 0; j < this->v[0].size();\
    \ ++j) this->v[i][j] -= rhs.v[i][j];\r\n        }\r\n        return *this;\r\n\
    \    }\r\n    Matrix &operator*=(const Matrix &rhs) {\r\n        assert(this->v[0].size()\
    \ == rhs.v.size());\r\n        int x = this->v.size(), y = rhs.v[0].size(), z\
    \ = rhs.v.size();\r\n        std::vector<std::vector<T>> tmp(x, std::vector<T>(y));\r\
    \n        for (int i = 0; i < x; ++i) {\r\n            for (int k = 0; k < z;\
    \ ++k) {\r\n                for (int j = 0; j < y; ++j) tmp[i][j] += this->v[i][k]\
    \ * rhs.v[k][j];\r\n            }\r\n        }\r\n        swap(this->v, tmp);\r\
    \n        return *this;\r\n    }\r\n\r\n    Matrix operator-() const {\r\n   \
    \     std::vector<std::vector<T>> tmp = v;\r\n        for (auto &i : tmp)\r\n\
    \            for (auto &j : i) j = -j;\r\n        return Matrix(tmp);\r\n    }\r\
    \n\r\n    Matrix operator+(const Matrix &rhs) const { return Matrix(*this) +=\
    \ rhs; }\r\n    Matrix operator-(const Matrix &rhs) const { return Matrix(*this)\
    \ -= rhs; }\r\n    Matrix operator*(const Matrix &rhs) const { return Matrix(*this)\
    \ *= rhs; }\r\n\r\n    std::vector<T> operator*(const std::vector<T> &rhs) {\r\
    \n        assert(this->v[0].size() == rhs.size());\r\n        int x = this->v.size(),\
    \ y = this->v[0].size();\r\n        std::vector<T> res(x);\r\n        for (int\
    \ i = 0; i < x; ++i) {\r\n            for (int j = 0; j < y; ++j) res[i] += this->v[i][j]\
    \ * rhs[j];\r\n        }\r\n        return res;\r\n    }\r\n\r\n    Matrix pow(int64_t\
    \ n) const {\r\n        Matrix res(v), mul(v);\r\n        res.unit_matrix();\r\
    \n        for (; n > 0; n >>= 1) {\r\n            if (n & 1) res *= mul;\r\n \
    \           mul *= mul;\r\n        }\r\n        return res;\r\n    }\r\n\r\n \
    \   void unit_matrix() {\r\n        assert(this->v.size() == this->v[0].size());\r\
    \n        int n = this->v.size();\r\n        for (int i = 0; i < n; ++i) {\r\n\
    \            this->v[i].assign(n, T(0));\r\n            this->v[i][i] = T(1);\r\
    \n        }\r\n    }\r\n\r\n    Matrix transposed() const {\r\n        int x =\
    \ this->v[0].size(), y = this->v.size();\r\n        std::vector<std::vector<T>>\
    \ res(x, std::vector<T>(y));\r\n        for (int i = 0; i < x; ++i) {\r\n    \
    \        for (int j = 0; j < y; ++j) { res[i][j] = v[j][i]; }\r\n        }\r\n\
    \        return Matrix(res);\r\n    }\r\n\r\n    void print_debug() const {\r\n\
    \        for (auto i : v) {\r\n            cerr << \"[\";\r\n            for (auto\
    \ j : i) cerr << j << \", \";\r\n            cerr << \"]\" << endl;\r\n      \
    \  }\r\n    }\r\n\r\n  private:\r\n    std::vector<std::vector<T>> v;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/matrix/matrix.hpp
  requiredBy: []
  timestamp: '2022-03-20 16:15:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/matrix/matrix.hpp
layout: document
redirect_from:
- /library/lib/matrix/matrix.hpp
- /library/lib/matrix/matrix.hpp.html
title: "\u884C\u5217\u30E9\u30A4\u30D6\u30E9\u30EA"
---
