---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/prime_numbers.test.cpp
    title: test/aoj/alds1/prime_numbers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/prime_factorize.test.cpp
    title: test/aoj/ntl/prime_factorize.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7D20\u6570\u30E9\u30A4\u30D6\u30E9\u30EA"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u7D20\u6570\u30E9\
    \u30A4\u30D6\u30E9\u30EA\r\n */\r\nstruct prime_number {\r\n    prime_number()\
    \ { this->init(); }\r\n\r\n    void init() {\r\n        this->is_not_prime[0]\
    \ = this->is_not_prime[1] = true;\r\n        for (int i = 2; i < _size; ++i) {\r\
    \n            if (!this->is_not_prime[i]) {\r\n                this->data.emplace_back(i);\r\
    \n                if ((int64_t)i * i >= _size) continue;\r\n                if\
    \ (i == 2) {\r\n                    for (int j = i * i; j < _size; j += i) this->is_not_prime[j]\
    \ = true;\r\n                } else {\r\n                    for (int j = i *\
    \ i; j < _size; j += i << 1) this->is_not_prime[j] = true;\r\n               \
    \ }\r\n            }\r\n        }\r\n    }\r\n\r\n    /**\r\n     * @brief \u7D20\
    \u6570\u5224\u5B9A\r\n     *\r\n     * @param n\r\n     * @return bool\r\n   \
    \  */\r\n    bool is_prime(int64_t n) const {\r\n        assert(n >= 0);\r\n \
    \       if (n < _size) return !this->is_not_prime[n];\r\n        for (auto i :\
    \ this->data) {\r\n            if ((int64_t)i * i > n) break;\r\n            if\
    \ (n % i == 0) return false;\r\n        }\r\n        return true;\r\n    }\r\n\
    \r\n    std::vector<int> prime_numbers(int x) const {\r\n        std::vector<int>\
    \ res;\r\n        for (auto i : this->data) {\r\n            if (i > x) break;\r\
    \n            res.emplace_back(i);\r\n        }\r\n        return res;\r\n   \
    \ }\r\n\r\n    /**\r\n     * @brief \u7D20\u56E0\u6570\u5206\u89E3\r\n     *\r\
    \n     * @tparam T\r\n     * @param x\r\n     * @return std::vector<pair<T, int>>\r\
    \n     */\r\n    template <class T>\r\n    std::vector<pair<T, int>> prime_factorization(T\
    \ x) const {\r\n        if (x == 1) return std::vector<pair<T, int>>(1, {1, 1});\r\
    \n        std::vector<pair<T, int>> res;\r\n        for (auto i : this->data)\
    \ {\r\n            int cnt = 0;\r\n            for (; x % i == 0; x /= i) ++cnt;\r\
    \n            if (cnt) res.emplace_back(i, cnt);\r\n            if ((int64_t)i\
    \ * i > x) break;\r\n        }\r\n        if (x != 1) res.emplace_back(x, 1);\r\
    \n        return res;\r\n    }\r\n\r\n    /**\r\n     * @brief \u7D04\u6570\u5217\
    \u6319\r\n     *\r\n     * @tparam T\r\n     * @param x\r\n     * @return std::vector<T>\r\
    \n     */\r\n    template <class T>\r\n    std::vector<T> divisors(T x) const\
    \ {\r\n        if (x == 1) return std::vector<T>(1, 1);\r\n        auto v = this->prime_factorization(x);\r\
    \n        std::vector<T> res;\r\n        res.emplace_back(1);\r\n        for (auto\
    \ p : v) {\r\n            int n = res.size();\r\n            res.resize(n * (p.second\
    \ + 1));\r\n            for (int i = 0; i < n * p.second; ++i) { res[n + i] =\
    \ res[i] * p.first; }\r\n            for (int i = 1; i <= p.second; ++i) {\r\n\
    \                std::inplace_merge(res.begin(), res.begin() + n * i, res.begin()\
    \ + n * (i + 1));\r\n            }\r\n        }\r\n        return res;\r\n   \
    \ }\r\n\r\n    /**\r\n     * @brief \u56E0\u6570\u5206\u89E3\u5217\u6319\r\n \
    \    *\r\n     * @tparam T\r\n     * @param x\r\n     * @return std::vector<std::vector<T>>\r\
    \n     */\r\n    template <class T>\r\n    std::vector<std::vector<T>> factorization(T\
    \ x) const {\r\n        std::vector<std::vector<T>> res;\r\n        auto f = [&](auto\
    \ self, std::vector<T> v, T a) -> void {\r\n            if (a == 1) res.emplace_back(v);\r\
    \n            for (auto i : this->divisors(a)) {\r\n                if (i == 1\
    \ || (!v.empty() && v.back() > i)) continue;\r\n                v.emplace_back(i);\r\
    \n                self(self, v, a / i);\r\n                v.pop_back();\r\n \
    \           }\r\n        };\r\n        f(f, std::vector<T>(), x);\r\n        return\
    \ res;\r\n    }\r\n\r\n  private:\r\n    static constexpr int _size = 1 << 22;\r\
    \n    std::bitset<_size> is_not_prime;\r\n    std::vector<int> data;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/prime_number.hpp
  requiredBy: []
  timestamp: '2022-05-13 04:24:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/ntl/prime_factorize.test.cpp
  - test/aoj/alds1/prime_numbers.test.cpp
documentation_of: lib/math/prime_number.hpp
layout: document
redirect_from:
- /library/lib/math/prime_number.hpp
- /library/lib/math/prime_number.hpp.html
title: "\u7D20\u6570\u30E9\u30A4\u30D6\u30E9\u30EA"
---
