---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/matrix/determinant_of_matrix.test.cpp
    title: test/yosupo/matrix/determinant_of_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/matrix/matrix_product.test.cpp
    title: test/yosupo/matrix/matrix_product.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u884C\u5217\u30E9\u30A4\u30D6\u30E9\u30EA"
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
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u884C\u5217\u30E9\
    \u30A4\u30D6\u30E9\u30EA\r\n *\r\n * @tparam T \u8981\u7D20\u306E\u578B\r\n */\r\
    \ntemplate <class T>\r\nstruct Matrix {\r\n    Matrix() = default;\r\n    Matrix(int\
    \ x) : v(x, std::vector<T>(x)) {}\r\n    Matrix(int x, int y) : v(x, std::vector<T>(y))\
    \ {}\r\n    Matrix(const std::vector<std::vector<T>> &_v) : v(_v) {}\r\n\r\n \
    \   const auto &operator[](int i) const { return v[i]; }\r\n    auto &operator[](int\
    \ i) { return v[i]; }\r\n    const auto begin() const { return v.begin(); }\r\n\
    \    auto begin() { return v.begin(); }\r\n    const auto end() const { return\
    \ v.end(); }\r\n    auto end() { return v.end(); }\r\n\r\n    Matrix &operator+=(const\
    \ Matrix &rhs) {\r\n        assert(v.size() == rhs.v.size());\r\n        assert(v[0].size()\
    \ == rhs.v[0].size());\r\n        for (int i = 0; i < v.size(); ++i) {\r\n   \
    \         for (int j = 0; j < v[0].size(); ++j) v[i][j] += rhs.v[i][j];\r\n  \
    \      }\r\n        return *this;\r\n    }\r\n    Matrix &operator-=(const Matrix\
    \ &rhs) {\r\n        assert(v.size() == rhs.v.size());\r\n        assert(v[0].size()\
    \ == rhs.v[0].size());\r\n        for (int i = 0; i < v.size(); ++i) {\r\n   \
    \         for (int j = 0; j < v[0].size(); ++j) v[i][j] -= rhs.v[i][j];\r\n  \
    \      }\r\n        return *this;\r\n    }\r\n    Matrix &operator*=(const Matrix\
    \ &rhs) {\r\n        assert(v[0].size() == rhs.v.size());\r\n        int x = v.size(),\
    \ y = rhs.v[0].size(), z = rhs.v.size();\r\n        std::vector<std::vector<T>>\
    \ tmp(x, std::vector<T>(y));\r\n        for (int i = 0; i < x; ++i) {\r\n    \
    \        for (int k = 0; k < z; ++k) {\r\n                for (int j = 0; j <\
    \ y; ++j) tmp[i][j] += v[i][k] * rhs.v[k][j];\r\n            }\r\n        }\r\n\
    \        std::swap(v, tmp);\r\n        return *this;\r\n    }\r\n\r\n    Matrix\
    \ operator-() const {\r\n        std::vector<std::vector<T>> tmp(v);\r\n     \
    \   for (auto &v : tmp)\r\n            for (auto &x : v) x = -x;\r\n        return\
    \ Matrix(tmp);\r\n    }\r\n\r\n    Matrix operator+(const Matrix &rhs) const {\
    \ return Matrix(*this) += rhs; }\r\n    Matrix operator-(const Matrix &rhs) const\
    \ { return Matrix(*this) -= rhs; }\r\n    Matrix operator*(const Matrix &rhs)\
    \ const { return Matrix(*this) *= rhs; }\r\n\r\n    std::vector<T> operator*(const\
    \ std::vector<T> &rhs) {\r\n        assert(v[0].size() == rhs.size());\r\n   \
    \     int x = v.size(), y = v[0].size();\r\n        std::vector<T> res(x);\r\n\
    \        for (int i = 0; i < x; ++i) {\r\n            for (int j = 0; j < y; ++j)\
    \ res[i] += v[i][j] * rhs[j];\r\n        }\r\n        return res;\r\n    }\r\n\
    \r\n    T det() const {\r\n        assert(v.size() == v[0].size());\r\n      \
    \  std::vector<std::vector<T>> u(v);\r\n        int n = u.size();\r\n        T\
    \ ans = 1;\r\n        for (int i = 0; i < n; ++i) {\r\n            if (u[i][i]\
    \ == T(0)) {\r\n                for (int j = i + 1; j < n; ++j) {\r\n        \
    \            if (u[j][i] != T(0)) {\r\n                        std::swap(u[j],\
    \ u[i]);\r\n                        ans *= -1;\r\n                        break;\r\
    \n                    }\r\n                }\r\n                if (u[i][i] ==\
    \ T(0)) return T(0);\r\n            }\r\n            ans *= u[i][i];\r\n     \
    \       T t = T(1) / u[i][i];\r\n            for (int j = i; j < n; ++j) u[i][j]\
    \ *= t;\r\n            for (int k = i + 1; k < n; ++k) {\r\n                if\
    \ (u[k][i] == T(0)) continue;\r\n                ans *= u[k][i];\r\n         \
    \       t = T(1) / u[k][i];\r\n                for (int j = i; j < n; ++j) u[k][j]\
    \ = u[k][j] * t - u[i][j];\r\n            }\r\n        }\r\n        return ans;\r\
    \n    }\r\n\r\n    Matrix pow(std::int64_t k) const {\r\n        assert(v.size()\
    \ == v[0].size());\r\n        int n = v.size();\r\n        Matrix res(n, n), mul(v);\r\
    \n        res.unit_matrix();\r\n        for (; k > 0; k >>= 1) {\r\n         \
    \   if (k & 1) res *= mul;\r\n            mul *= mul;\r\n        }\r\n       \
    \ return res;\r\n    }\r\n\r\n    void unit_matrix() {\r\n        assert(v.size()\
    \ == v[0].size());\r\n        int n = v.size();\r\n        for (int i = 0; i <\
    \ n; ++i) {\r\n            v[i].assign(n, T(0));\r\n            v[i][i] = T(1);\r\
    \n        }\r\n    }\r\n\r\n    Matrix transposed() const {\r\n        int x =\
    \ v[0].size(), y = v.size();\r\n        std::vector<std::vector<T>> res(x, std::vector<T>(y));\r\
    \n        for (int i = 0; i < x; ++i) {\r\n            for (int j = 0; j < y;\
    \ ++j) {\r\n                res[i][j] = v[j][i];\r\n            }\r\n        }\r\
    \n        return Matrix(res);\r\n    }\r\n\r\n    void print_debug() const {\r\
    \n        for (auto u : v) {\r\n            std::cerr << \"[\";\r\n          \
    \  for (auto x : u) std::cerr << x << \", \";\r\n            std::cerr << \"]\"\
    \ << std::endl;\r\n        }\r\n    }\r\n\r\n  private:\r\n    std::vector<std::vector<T>>\
    \ v;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/matrix.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/matrix/matrix_product.test.cpp
  - test/yosupo/matrix/determinant_of_matrix.test.cpp
documentation_of: lib/math/matrix.hpp
layout: document
redirect_from:
- /library/lib/math/matrix.hpp
- /library/lib/math/matrix.hpp.html
title: "\u884C\u5217\u30E9\u30A4\u30D6\u30E9\u30EA"
---
