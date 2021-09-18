---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/string.hpp\"\n\n\n\r\n#include <algorithm>\r\
    \n#include <cassert>\r\n#include <numeric>\r\n#include <string>\r\n#include <vector>\r\
    \n\r\nnamespace atcoder {\r\n\r\nnamespace internal {\r\n\r\nstd::vector<int>\
    \ sa_naive(const std::vector<int>& s) {\r\n    int n = int(s.size());\r\n    std::vector<int>\
    \ sa(n);\r\n    std::iota(sa.begin(), sa.end(), 0);\r\n    std::sort(sa.begin(),\
    \ sa.end(), [&](int l, int r) {\r\n        if (l == r) return false;\r\n     \
    \   while (l < n && r < n) {\r\n            if (s[l] != s[r]) return s[l] < s[r];\r\
    \n            l++;\r\n            r++;\r\n        }\r\n        return l == n;\r\
    \n    });\r\n    return sa;\r\n}\r\n\r\nstd::vector<int> sa_doubling(const std::vector<int>&\
    \ s) {\r\n    int n = int(s.size());\r\n    std::vector<int> sa(n), rnk = s, tmp(n);\r\
    \n    std::iota(sa.begin(), sa.end(), 0);\r\n    for (int k = 1; k < n; k *= 2)\
    \ {\r\n        auto cmp = [&](int x, int y) {\r\n            if (rnk[x] != rnk[y])\
    \ return rnk[x] < rnk[y];\r\n            int rx = x + k < n ? rnk[x + k] : -1;\r\
    \n            int ry = y + k < n ? rnk[y + k] : -1;\r\n            return rx <\
    \ ry;\r\n        };\r\n        std::sort(sa.begin(), sa.end(), cmp);\r\n     \
    \   tmp[sa[0]] = 0;\r\n        for (int i = 1; i < n; i++) {\r\n            tmp[sa[i]]\
    \ = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);\r\n        }\r\n       \
    \ std::swap(tmp, rnk);\r\n    }\r\n    return sa;\r\n}\r\n\r\n// SA-IS, linear-time\
    \ suffix array construction\r\n// Reference:\r\n// G. Nong, S. Zhang, and W. H.\
    \ Chan,\r\n// Two Efficient Algorithms for Linear Time Suffix Array Construction\r\
    \ntemplate <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>\r\nstd::vector<int>\
    \ sa_is(const std::vector<int>& s, int upper) {\r\n    int n = int(s.size());\r\
    \n    if (n == 0) return {};\r\n    if (n == 1) return {0};\r\n    if (n == 2)\
    \ {\r\n        if (s[0] < s[1]) {\r\n            return {0, 1};\r\n        } else\
    \ {\r\n            return {1, 0};\r\n        }\r\n    }\r\n    if (n < THRESHOLD_NAIVE)\
    \ {\r\n        return sa_naive(s);\r\n    }\r\n    if (n < THRESHOLD_DOUBLING)\
    \ {\r\n        return sa_doubling(s);\r\n    }\r\n\r\n    std::vector<int> sa(n);\r\
    \n    std::vector<bool> ls(n);\r\n    for (int i = n - 2; i >= 0; i--) {\r\n \
    \       ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);\r\n    }\r\
    \n    std::vector<int> sum_l(upper + 1), sum_s(upper + 1);\r\n    for (int i =\
    \ 0; i < n; i++) {\r\n        if (!ls[i]) {\r\n            sum_s[s[i]]++;\r\n\
    \        } else {\r\n            sum_l[s[i] + 1]++;\r\n        }\r\n    }\r\n\
    \    for (int i = 0; i <= upper; i++) {\r\n        sum_s[i] += sum_l[i];\r\n \
    \       if (i < upper) sum_l[i + 1] += sum_s[i];\r\n    }\r\n\r\n    auto induce\
    \ = [&](const std::vector<int>& lms) {\r\n        std::fill(sa.begin(), sa.end(),\
    \ -1);\r\n        std::vector<int> buf(upper + 1);\r\n        std::copy(sum_s.begin(),\
    \ sum_s.end(), buf.begin());\r\n        for (auto d : lms) {\r\n            if\
    \ (d == n) continue;\r\n            sa[buf[s[d]]++] = d;\r\n        }\r\n    \
    \    std::copy(sum_l.begin(), sum_l.end(), buf.begin());\r\n        sa[buf[s[n\
    \ - 1]]++] = n - 1;\r\n        for (int i = 0; i < n; i++) {\r\n            int\
    \ v = sa[i];\r\n            if (v >= 1 && !ls[v - 1]) {\r\n                sa[buf[s[v\
    \ - 1]]++] = v - 1;\r\n            }\r\n        }\r\n        std::copy(sum_l.begin(),\
    \ sum_l.end(), buf.begin());\r\n        for (int i = n - 1; i >= 0; i--) {\r\n\
    \            int v = sa[i];\r\n            if (v >= 1 && ls[v - 1]) {\r\n    \
    \            sa[--buf[s[v - 1] + 1]] = v - 1;\r\n            }\r\n        }\r\n\
    \    };\r\n\r\n    std::vector<int> lms_map(n + 1, -1);\r\n    int m = 0;\r\n\
    \    for (int i = 1; i < n; i++) {\r\n        if (!ls[i - 1] && ls[i]) {\r\n \
    \           lms_map[i] = m++;\r\n        }\r\n    }\r\n    std::vector<int> lms;\r\
    \n    lms.reserve(m);\r\n    for (int i = 1; i < n; i++) {\r\n        if (!ls[i\
    \ - 1] && ls[i]) {\r\n            lms.push_back(i);\r\n        }\r\n    }\r\n\r\
    \n    induce(lms);\r\n\r\n    if (m) {\r\n        std::vector<int> sorted_lms;\r\
    \n        sorted_lms.reserve(m);\r\n        for (int v : sa) {\r\n           \
    \ if (lms_map[v] != -1) sorted_lms.push_back(v);\r\n        }\r\n        std::vector<int>\
    \ rec_s(m);\r\n        int rec_upper = 0;\r\n        rec_s[lms_map[sorted_lms[0]]]\
    \ = 0;\r\n        for (int i = 1; i < m; i++) {\r\n            int l = sorted_lms[i\
    \ - 1], r = sorted_lms[i];\r\n            int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l]\
    \ + 1] : n;\r\n            int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] +\
    \ 1] : n;\r\n            bool same = true;\r\n            if (end_l - l != end_r\
    \ - r) {\r\n                same = false;\r\n            } else {\r\n        \
    \        while (l < end_l) {\r\n                    if (s[l] != s[r]) {\r\n  \
    \                      break;\r\n                    }\r\n                   \
    \ l++;\r\n                    r++;\r\n                }\r\n                if\
    \ (l == n || s[l] != s[r]) same = false;\r\n            }\r\n            if (!same)\
    \ rec_upper++;\r\n            rec_s[lms_map[sorted_lms[i]]] = rec_upper;\r\n \
    \       }\r\n\r\n        auto rec_sa =\r\n            sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s,\
    \ rec_upper);\r\n\r\n        for (int i = 0; i < m; i++) {\r\n            sorted_lms[i]\
    \ = lms[rec_sa[i]];\r\n        }\r\n        induce(sorted_lms);\r\n    }\r\n \
    \   return sa;\r\n}\r\n\r\n}  // namespace internal\r\n\r\nstd::vector<int> suffix_array(const\
    \ std::vector<int>& s, int upper) {\r\n    assert(0 <= upper);\r\n    for (int\
    \ d : s) {\r\n        assert(0 <= d && d <= upper);\r\n    }\r\n    auto sa =\
    \ internal::sa_is(s, upper);\r\n    return sa;\r\n}\r\n\r\ntemplate <class T>\
    \ std::vector<int> suffix_array(const std::vector<T>& s) {\r\n    int n = int(s.size());\r\
    \n    std::vector<int> idx(n);\r\n    iota(idx.begin(), idx.end(), 0);\r\n   \
    \ sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });\r\n\
    \    std::vector<int> s2(n);\r\n    int now = 0;\r\n    for (int i = 0; i < n;\
    \ i++) {\r\n        if (i && s[idx[i - 1]] != s[idx[i]]) now++;\r\n        s2[idx[i]]\
    \ = now;\r\n    }\r\n    return internal::sa_is(s2, now);\r\n}\r\n\r\nstd::vector<int>\
    \ suffix_array(const std::string& s) {\r\n    int n = int(s.size());\r\n    std::vector<int>\
    \ s2(n);\r\n    for (int i = 0; i < n; i++) {\r\n        s2[i] = s[i];\r\n   \
    \ }\r\n    return internal::sa_is(s2, 255);\r\n}\r\n\r\n// Reference:\r\n// T.\
    \ Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,\r\n// Linear-Time Longest-Common-Prefix\
    \ Computation in Suffix Arrays and Its\r\n// Applications\r\ntemplate <class T>\r\
    \nstd::vector<int> lcp_array(const std::vector<T>& s,\r\n                    \
    \       const std::vector<int>& sa) {\r\n    int n = int(s.size());\r\n    assert(n\
    \ >= 1);\r\n    std::vector<int> rnk(n);\r\n    for (int i = 0; i < n; i++) {\r\
    \n        rnk[sa[i]] = i;\r\n    }\r\n    std::vector<int> lcp(n - 1);\r\n   \
    \ int h = 0;\r\n    for (int i = 0; i < n; i++) {\r\n        if (h > 0) h--;\r\
    \n        if (rnk[i] == 0) continue;\r\n        int j = sa[rnk[i] - 1];\r\n  \
    \      for (; j + h < n && i + h < n; h++) {\r\n            if (s[j + h] != s[i\
    \ + h]) break;\r\n        }\r\n        lcp[rnk[i] - 1] = h;\r\n    }\r\n    return\
    \ lcp;\r\n}\r\n\r\nstd::vector<int> lcp_array(const std::string& s, const std::vector<int>&\
    \ sa) {\r\n    int n = int(s.size());\r\n    std::vector<int> s2(n);\r\n    for\
    \ (int i = 0; i < n; i++) {\r\n        s2[i] = s[i];\r\n    }\r\n    return lcp_array(s2,\
    \ sa);\r\n}\r\n\r\n// Reference:\r\n// D. Gusfield,\r\n// Algorithms on Strings,\
    \ Trees, and Sequences: Computer Science and\r\n// Computational Biology\r\ntemplate\
    \ <class T> std::vector<int> z_algorithm(const std::vector<T>& s) {\r\n    int\
    \ n = int(s.size());\r\n    if (n == 0) return {};\r\n    std::vector<int> z(n);\r\
    \n    z[0] = 0;\r\n    for (int i = 1, j = 0; i < n; i++) {\r\n        int& k\
    \ = z[i];\r\n        k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i - j]);\r\
    \n        while (i + k < n && s[k] == s[i + k]) k++;\r\n        if (j + z[j] <\
    \ i + z[i]) j = i;\r\n    }\r\n    z[0] = n;\r\n    return z;\r\n}\r\n\r\nstd::vector<int>\
    \ z_algorithm(const std::string& s) {\r\n    int n = int(s.size());\r\n    std::vector<int>\
    \ s2(n);\r\n    for (int i = 0; i < n; i++) {\r\n        s2[i] = s[i];\r\n   \
    \ }\r\n    return z_algorithm(s2);\r\n}\r\n\r\n}  // namespace atcoder\r\n\r\n\
    \n"
  code: "#ifndef ATCODER_STRING_HPP\r\n#define ATCODER_STRING_HPP 1\r\n\r\n#include\
    \ <algorithm>\r\n#include <cassert>\r\n#include <numeric>\r\n#include <string>\r\
    \n#include <vector>\r\n\r\nnamespace atcoder {\r\n\r\nnamespace internal {\r\n\
    \r\nstd::vector<int> sa_naive(const std::vector<int>& s) {\r\n    int n = int(s.size());\r\
    \n    std::vector<int> sa(n);\r\n    std::iota(sa.begin(), sa.end(), 0);\r\n \
    \   std::sort(sa.begin(), sa.end(), [&](int l, int r) {\r\n        if (l == r)\
    \ return false;\r\n        while (l < n && r < n) {\r\n            if (s[l] !=\
    \ s[r]) return s[l] < s[r];\r\n            l++;\r\n            r++;\r\n      \
    \  }\r\n        return l == n;\r\n    });\r\n    return sa;\r\n}\r\n\r\nstd::vector<int>\
    \ sa_doubling(const std::vector<int>& s) {\r\n    int n = int(s.size());\r\n \
    \   std::vector<int> sa(n), rnk = s, tmp(n);\r\n    std::iota(sa.begin(), sa.end(),\
    \ 0);\r\n    for (int k = 1; k < n; k *= 2) {\r\n        auto cmp = [&](int x,\
    \ int y) {\r\n            if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];\r\n  \
    \          int rx = x + k < n ? rnk[x + k] : -1;\r\n            int ry = y + k\
    \ < n ? rnk[y + k] : -1;\r\n            return rx < ry;\r\n        };\r\n    \
    \    std::sort(sa.begin(), sa.end(), cmp);\r\n        tmp[sa[0]] = 0;\r\n    \
    \    for (int i = 1; i < n; i++) {\r\n            tmp[sa[i]] = tmp[sa[i - 1]]\
    \ + (cmp(sa[i - 1], sa[i]) ? 1 : 0);\r\n        }\r\n        std::swap(tmp, rnk);\r\
    \n    }\r\n    return sa;\r\n}\r\n\r\n// SA-IS, linear-time suffix array construction\r\
    \n// Reference:\r\n// G. Nong, S. Zhang, and W. H. Chan,\r\n// Two Efficient Algorithms\
    \ for Linear Time Suffix Array Construction\r\ntemplate <int THRESHOLD_NAIVE =\
    \ 10, int THRESHOLD_DOUBLING = 40>\r\nstd::vector<int> sa_is(const std::vector<int>&\
    \ s, int upper) {\r\n    int n = int(s.size());\r\n    if (n == 0) return {};\r\
    \n    if (n == 1) return {0};\r\n    if (n == 2) {\r\n        if (s[0] < s[1])\
    \ {\r\n            return {0, 1};\r\n        } else {\r\n            return {1,\
    \ 0};\r\n        }\r\n    }\r\n    if (n < THRESHOLD_NAIVE) {\r\n        return\
    \ sa_naive(s);\r\n    }\r\n    if (n < THRESHOLD_DOUBLING) {\r\n        return\
    \ sa_doubling(s);\r\n    }\r\n\r\n    std::vector<int> sa(n);\r\n    std::vector<bool>\
    \ ls(n);\r\n    for (int i = n - 2; i >= 0; i--) {\r\n        ls[i] = (s[i] ==\
    \ s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);\r\n    }\r\n    std::vector<int>\
    \ sum_l(upper + 1), sum_s(upper + 1);\r\n    for (int i = 0; i < n; i++) {\r\n\
    \        if (!ls[i]) {\r\n            sum_s[s[i]]++;\r\n        } else {\r\n \
    \           sum_l[s[i] + 1]++;\r\n        }\r\n    }\r\n    for (int i = 0; i\
    \ <= upper; i++) {\r\n        sum_s[i] += sum_l[i];\r\n        if (i < upper)\
    \ sum_l[i + 1] += sum_s[i];\r\n    }\r\n\r\n    auto induce = [&](const std::vector<int>&\
    \ lms) {\r\n        std::fill(sa.begin(), sa.end(), -1);\r\n        std::vector<int>\
    \ buf(upper + 1);\r\n        std::copy(sum_s.begin(), sum_s.end(), buf.begin());\r\
    \n        for (auto d : lms) {\r\n            if (d == n) continue;\r\n      \
    \      sa[buf[s[d]]++] = d;\r\n        }\r\n        std::copy(sum_l.begin(), sum_l.end(),\
    \ buf.begin());\r\n        sa[buf[s[n - 1]]++] = n - 1;\r\n        for (int i\
    \ = 0; i < n; i++) {\r\n            int v = sa[i];\r\n            if (v >= 1 &&\
    \ !ls[v - 1]) {\r\n                sa[buf[s[v - 1]]++] = v - 1;\r\n          \
    \  }\r\n        }\r\n        std::copy(sum_l.begin(), sum_l.end(), buf.begin());\r\
    \n        for (int i = n - 1; i >= 0; i--) {\r\n            int v = sa[i];\r\n\
    \            if (v >= 1 && ls[v - 1]) {\r\n                sa[--buf[s[v - 1] +\
    \ 1]] = v - 1;\r\n            }\r\n        }\r\n    };\r\n\r\n    std::vector<int>\
    \ lms_map(n + 1, -1);\r\n    int m = 0;\r\n    for (int i = 1; i < n; i++) {\r\
    \n        if (!ls[i - 1] && ls[i]) {\r\n            lms_map[i] = m++;\r\n    \
    \    }\r\n    }\r\n    std::vector<int> lms;\r\n    lms.reserve(m);\r\n    for\
    \ (int i = 1; i < n; i++) {\r\n        if (!ls[i - 1] && ls[i]) {\r\n        \
    \    lms.push_back(i);\r\n        }\r\n    }\r\n\r\n    induce(lms);\r\n\r\n \
    \   if (m) {\r\n        std::vector<int> sorted_lms;\r\n        sorted_lms.reserve(m);\r\
    \n        for (int v : sa) {\r\n            if (lms_map[v] != -1) sorted_lms.push_back(v);\r\
    \n        }\r\n        std::vector<int> rec_s(m);\r\n        int rec_upper = 0;\r\
    \n        rec_s[lms_map[sorted_lms[0]]] = 0;\r\n        for (int i = 1; i < m;\
    \ i++) {\r\n            int l = sorted_lms[i - 1], r = sorted_lms[i];\r\n    \
    \        int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;\r\n     \
    \       int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;\r\n      \
    \      bool same = true;\r\n            if (end_l - l != end_r - r) {\r\n    \
    \            same = false;\r\n            } else {\r\n                while (l\
    \ < end_l) {\r\n                    if (s[l] != s[r]) {\r\n                  \
    \      break;\r\n                    }\r\n                    l++;\r\n       \
    \             r++;\r\n                }\r\n                if (l == n || s[l]\
    \ != s[r]) same = false;\r\n            }\r\n            if (!same) rec_upper++;\r\
    \n            rec_s[lms_map[sorted_lms[i]]] = rec_upper;\r\n        }\r\n\r\n\
    \        auto rec_sa =\r\n            sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s,\
    \ rec_upper);\r\n\r\n        for (int i = 0; i < m; i++) {\r\n            sorted_lms[i]\
    \ = lms[rec_sa[i]];\r\n        }\r\n        induce(sorted_lms);\r\n    }\r\n \
    \   return sa;\r\n}\r\n\r\n}  // namespace internal\r\n\r\nstd::vector<int> suffix_array(const\
    \ std::vector<int>& s, int upper) {\r\n    assert(0 <= upper);\r\n    for (int\
    \ d : s) {\r\n        assert(0 <= d && d <= upper);\r\n    }\r\n    auto sa =\
    \ internal::sa_is(s, upper);\r\n    return sa;\r\n}\r\n\r\ntemplate <class T>\
    \ std::vector<int> suffix_array(const std::vector<T>& s) {\r\n    int n = int(s.size());\r\
    \n    std::vector<int> idx(n);\r\n    iota(idx.begin(), idx.end(), 0);\r\n   \
    \ sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });\r\n\
    \    std::vector<int> s2(n);\r\n    int now = 0;\r\n    for (int i = 0; i < n;\
    \ i++) {\r\n        if (i && s[idx[i - 1]] != s[idx[i]]) now++;\r\n        s2[idx[i]]\
    \ = now;\r\n    }\r\n    return internal::sa_is(s2, now);\r\n}\r\n\r\nstd::vector<int>\
    \ suffix_array(const std::string& s) {\r\n    int n = int(s.size());\r\n    std::vector<int>\
    \ s2(n);\r\n    for (int i = 0; i < n; i++) {\r\n        s2[i] = s[i];\r\n   \
    \ }\r\n    return internal::sa_is(s2, 255);\r\n}\r\n\r\n// Reference:\r\n// T.\
    \ Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,\r\n// Linear-Time Longest-Common-Prefix\
    \ Computation in Suffix Arrays and Its\r\n// Applications\r\ntemplate <class T>\r\
    \nstd::vector<int> lcp_array(const std::vector<T>& s,\r\n                    \
    \       const std::vector<int>& sa) {\r\n    int n = int(s.size());\r\n    assert(n\
    \ >= 1);\r\n    std::vector<int> rnk(n);\r\n    for (int i = 0; i < n; i++) {\r\
    \n        rnk[sa[i]] = i;\r\n    }\r\n    std::vector<int> lcp(n - 1);\r\n   \
    \ int h = 0;\r\n    for (int i = 0; i < n; i++) {\r\n        if (h > 0) h--;\r\
    \n        if (rnk[i] == 0) continue;\r\n        int j = sa[rnk[i] - 1];\r\n  \
    \      for (; j + h < n && i + h < n; h++) {\r\n            if (s[j + h] != s[i\
    \ + h]) break;\r\n        }\r\n        lcp[rnk[i] - 1] = h;\r\n    }\r\n    return\
    \ lcp;\r\n}\r\n\r\nstd::vector<int> lcp_array(const std::string& s, const std::vector<int>&\
    \ sa) {\r\n    int n = int(s.size());\r\n    std::vector<int> s2(n);\r\n    for\
    \ (int i = 0; i < n; i++) {\r\n        s2[i] = s[i];\r\n    }\r\n    return lcp_array(s2,\
    \ sa);\r\n}\r\n\r\n// Reference:\r\n// D. Gusfield,\r\n// Algorithms on Strings,\
    \ Trees, and Sequences: Computer Science and\r\n// Computational Biology\r\ntemplate\
    \ <class T> std::vector<int> z_algorithm(const std::vector<T>& s) {\r\n    int\
    \ n = int(s.size());\r\n    if (n == 0) return {};\r\n    std::vector<int> z(n);\r\
    \n    z[0] = 0;\r\n    for (int i = 1, j = 0; i < n; i++) {\r\n        int& k\
    \ = z[i];\r\n        k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i - j]);\r\
    \n        while (i + k < n && s[k] == s[i + k]) k++;\r\n        if (j + z[j] <\
    \ i + z[i]) j = i;\r\n    }\r\n    z[0] = n;\r\n    return z;\r\n}\r\n\r\nstd::vector<int>\
    \ z_algorithm(const std::string& s) {\r\n    int n = int(s.size());\r\n    std::vector<int>\
    \ s2(n);\r\n    for (int i = 0; i < n; i++) {\r\n        s2[i] = s[i];\r\n   \
    \ }\r\n    return z_algorithm(s2);\r\n}\r\n\r\n}  // namespace atcoder\r\n\r\n\
    #endif  // ATCODER_STRING_HPP\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/atcoder/string.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/string.hpp
layout: document
redirect_from:
- /library/lib/atcoder/string.hpp
- /library/lib/atcoder/string.hpp.html
title: lib/atcoder/string.hpp
---
