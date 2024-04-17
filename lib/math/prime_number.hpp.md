---
data:
  _extendedDependsOn: []
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
  bundledCode: "#line 1 \"lib/math/prime_number.hpp\"\n#include <algorithm>\r\n#include\
    \ <bitset>\r\n#include <cassert>\r\n#include <iterator>\r\n#include <utility>\r\
    \n#include <vector>\r\n\r\n/**\r\n * @brief \u7D20\u6570\u30E9\u30A4\u30D6\u30E9\
    \u30EA\r\n *\r\n * @tparam N\r\n */\r\ntemplate <int N = 1 << 22>\r\nstruct prime_number\
    \ {\r\n    prime_number() : is_not_prime(), data() { init(); }\r\n\r\n    /**\r\
    \n     * @brief \u7D20\u6570\u5224\u5B9A\r\n     *\r\n     * @param n\r\n    \
    \ * @return bool\r\n     */\r\n    bool is_prime(std::int64_t n) const {\r\n \
    \       assert(n >= 0);\r\n        if (n < N) return !is_not_prime[n];\r\n   \
    \     for (auto i : data) {\r\n            if ((std::int64_t)i * i > n) break;\r\
    \n            if (n % i == 0) return false;\r\n        }\r\n        return true;\r\
    \n    }\r\n\r\n    std::vector<int> prime_numbers(int x) const {\r\n        std::vector<int>\
    \ res;\r\n        for (auto i : data) {\r\n            if (i > x) break;\r\n \
    \           res.emplace_back(i);\r\n        }\r\n        return res;\r\n    }\r\
    \n\r\n    /**\r\n     * @brief \u7D20\u56E0\u6570\u5206\u89E3\r\n     *\r\n  \
    \   * @tparam T\r\n     * @param x\r\n     * @return std::vector<std::pair<T,\
    \ int>>\r\n     */\r\n    template <class T>\r\n    std::vector<std::pair<T, int>>\
    \ prime_factorization(T x) const {\r\n        if (x == 1) return std::vector<std::pair<T,\
    \ int>>();\r\n        std::vector<std::pair<T, int>> res;\r\n        for (auto\
    \ p : data) {\r\n            int cnt = 0;\r\n            for (; x % p == 0; x\
    \ /= p) ++cnt;\r\n            if (cnt) res.emplace_back(p, cnt);\r\n         \
    \   if ((std::int64_t)p * p > x) break;\r\n        }\r\n        if (x != 1) res.emplace_back(x,\
    \ 1);\r\n        return res;\r\n    }\r\n\r\n    /**\r\n     * @brief \u7D04\u6570\
    \u5217\u6319\r\n     *\r\n     * @tparam T\r\n     * @param x\r\n     * @return\
    \ std::vector<T>\r\n     */\r\n    template <class T>\r\n    std::vector<T> divisors(T\
    \ x) const {\r\n        if (x == 1) return std::vector<T>(1, 1);\r\n        auto\
    \ v = prime_factorization(x);\r\n        std::vector<T> res;\r\n        res.emplace_back(1);\r\
    \n        for (auto p : v) {\r\n            int n = res.size();\r\n          \
    \  res.resize(n * (p.second + 1));\r\n            for (int i = 0; i < n * p.second;\
    \ ++i) res[n + i] = res[i] * p.first;\r\n            for (int i = 1; i <= p.second;\
    \ ++i) {\r\n                std::inplace_merge(res.begin(), res.begin() + n *\
    \ i, res.begin() + n * (i + 1));\r\n            }\r\n        }\r\n        return\
    \ res;\r\n    }\r\n\r\n    /**\r\n     * @brief \u56E0\u6570\u5206\u89E3\u5217\
    \u6319\r\n     *\r\n     * @tparam T\r\n     * @param x\r\n     * @return std::vector<std::vector<T>>\r\
    \n     */\r\n    template <class T>\r\n    std::vector<std::vector<T>> factorization(T\
    \ x) const {\r\n        std::vector<std::vector<T>> res;\r\n        auto f = [&](auto\
    \ self, std::vector<T> v, T a) -> void {\r\n            if (a == 1) res.emplace_back(v);\r\
    \n            for (auto i : this->divisors(a)) {\r\n                if (i == 1\
    \ || (!v.empty() && v.back() > i)) continue;\r\n                v.emplace_back(i);\r\
    \n                self(self, v, a / i);\r\n                v.pop_back();\r\n \
    \           }\r\n        };\r\n        f(f, std::vector<T>(), x);\r\n        return\
    \ res;\r\n    }\r\n\r\n  private:\r\n    std::bitset<N> is_not_prime;\r\n    std::vector<int>\
    \ data;\r\n\r\n    void init() {\r\n        is_not_prime[0] = is_not_prime[1]\
    \ = true;\r\n        for (int i = 2; i < N; ++i) {\r\n            if (!is_not_prime[i])\
    \ {\r\n                data.emplace_back(i);\r\n                if ((std::int64_t)i\
    \ * i >= N) continue;\r\n                if (i == 2) {\r\n                   \
    \ for (int j = i * i; j < N; j += i) is_not_prime[j] = true;\r\n             \
    \   } else {\r\n                    for (int j = i * i; j < N; j += i << 1) is_not_prime[j]\
    \ = true;\r\n                }\r\n            }\r\n        }\r\n    }\r\n};\r\n"
  code: "#include <algorithm>\r\n#include <bitset>\r\n#include <cassert>\r\n#include\
    \ <iterator>\r\n#include <utility>\r\n#include <vector>\r\n\r\n/**\r\n * @brief\
    \ \u7D20\u6570\u30E9\u30A4\u30D6\u30E9\u30EA\r\n *\r\n * @tparam N\r\n */\r\n\
    template <int N = 1 << 22>\r\nstruct prime_number {\r\n    prime_number() : is_not_prime(),\
    \ data() { init(); }\r\n\r\n    /**\r\n     * @brief \u7D20\u6570\u5224\u5B9A\r\
    \n     *\r\n     * @param n\r\n     * @return bool\r\n     */\r\n    bool is_prime(std::int64_t\
    \ n) const {\r\n        assert(n >= 0);\r\n        if (n < N) return !is_not_prime[n];\r\
    \n        for (auto i : data) {\r\n            if ((std::int64_t)i * i > n) break;\r\
    \n            if (n % i == 0) return false;\r\n        }\r\n        return true;\r\
    \n    }\r\n\r\n    std::vector<int> prime_numbers(int x) const {\r\n        std::vector<int>\
    \ res;\r\n        for (auto i : data) {\r\n            if (i > x) break;\r\n \
    \           res.emplace_back(i);\r\n        }\r\n        return res;\r\n    }\r\
    \n\r\n    /**\r\n     * @brief \u7D20\u56E0\u6570\u5206\u89E3\r\n     *\r\n  \
    \   * @tparam T\r\n     * @param x\r\n     * @return std::vector<std::pair<T,\
    \ int>>\r\n     */\r\n    template <class T>\r\n    std::vector<std::pair<T, int>>\
    \ prime_factorization(T x) const {\r\n        if (x == 1) return std::vector<std::pair<T,\
    \ int>>();\r\n        std::vector<std::pair<T, int>> res;\r\n        for (auto\
    \ p : data) {\r\n            int cnt = 0;\r\n            for (; x % p == 0; x\
    \ /= p) ++cnt;\r\n            if (cnt) res.emplace_back(p, cnt);\r\n         \
    \   if ((std::int64_t)p * p > x) break;\r\n        }\r\n        if (x != 1) res.emplace_back(x,\
    \ 1);\r\n        return res;\r\n    }\r\n\r\n    /**\r\n     * @brief \u7D04\u6570\
    \u5217\u6319\r\n     *\r\n     * @tparam T\r\n     * @param x\r\n     * @return\
    \ std::vector<T>\r\n     */\r\n    template <class T>\r\n    std::vector<T> divisors(T\
    \ x) const {\r\n        if (x == 1) return std::vector<T>(1, 1);\r\n        auto\
    \ v = prime_factorization(x);\r\n        std::vector<T> res;\r\n        res.emplace_back(1);\r\
    \n        for (auto p : v) {\r\n            int n = res.size();\r\n          \
    \  res.resize(n * (p.second + 1));\r\n            for (int i = 0; i < n * p.second;\
    \ ++i) res[n + i] = res[i] * p.first;\r\n            for (int i = 1; i <= p.second;\
    \ ++i) {\r\n                std::inplace_merge(res.begin(), res.begin() + n *\
    \ i, res.begin() + n * (i + 1));\r\n            }\r\n        }\r\n        return\
    \ res;\r\n    }\r\n\r\n    /**\r\n     * @brief \u56E0\u6570\u5206\u89E3\u5217\
    \u6319\r\n     *\r\n     * @tparam T\r\n     * @param x\r\n     * @return std::vector<std::vector<T>>\r\
    \n     */\r\n    template <class T>\r\n    std::vector<std::vector<T>> factorization(T\
    \ x) const {\r\n        std::vector<std::vector<T>> res;\r\n        auto f = [&](auto\
    \ self, std::vector<T> v, T a) -> void {\r\n            if (a == 1) res.emplace_back(v);\r\
    \n            for (auto i : this->divisors(a)) {\r\n                if (i == 1\
    \ || (!v.empty() && v.back() > i)) continue;\r\n                v.emplace_back(i);\r\
    \n                self(self, v, a / i);\r\n                v.pop_back();\r\n \
    \           }\r\n        };\r\n        f(f, std::vector<T>(), x);\r\n        return\
    \ res;\r\n    }\r\n\r\n  private:\r\n    std::bitset<N> is_not_prime;\r\n    std::vector<int>\
    \ data;\r\n\r\n    void init() {\r\n        is_not_prime[0] = is_not_prime[1]\
    \ = true;\r\n        for (int i = 2; i < N; ++i) {\r\n            if (!is_not_prime[i])\
    \ {\r\n                data.emplace_back(i);\r\n                if ((std::int64_t)i\
    \ * i >= N) continue;\r\n                if (i == 2) {\r\n                   \
    \ for (int j = i * i; j < N; j += i) is_not_prime[j] = true;\r\n             \
    \   } else {\r\n                    for (int j = i * i; j < N; j += i << 1) is_not_prime[j]\
    \ = true;\r\n                }\r\n            }\r\n        }\r\n    }\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/math/prime_number.hpp
  requiredBy: []
  timestamp: '2023-10-02 05:01:21+09:00'
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
