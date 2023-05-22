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
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <int N, class D = void>\r\
    \nstruct tree64 {\r\n    static constexpr int C = calc_c(N);\r\n\r\n    uint64_t\
    \ map;\r\n    array<tree64<C>, (N - 1) / C + 1> child;\r\n\r\n    tree64() : map(0),\
    \ child() {}\r\n\r\n    constexpr int calc_c(int n) {\r\n        int res = 1;\r\
    \n        while (n > 64) {\r\n            res *= 64;\r\n            n /= 64;\r\
    \n        }\r\n        return res;\r\n    }\r\n    int bsf(const uint64_t x) {\
    \ return __builtin_ctzll(x); }\r\n    int bsr(const uint64_t x) { return 63 -\
    \ __builtin_clzll(x); }\r\n\r\n    bool insert(const int key) {\r\n        const\
    \ int pos = key / C;\r\n        map |= 1ULL << pos;\r\n        return child[pos].insert(key\
    \ % C);\r\n    }\r\n\r\n    bool erase(const int key) {\r\n        const int pos\
    \ = key / C;\r\n        const bool res = child[pos].erase(key % C);\r\n      \
    \  if (child[pos]._get_map() == 0) {\r\n            map &= ~(1ULL << pos);\r\n\
    \        }\r\n        return res;\r\n    }\r\n\r\n    bool contains(const int\
    \ key) const {\r\n        return child[key / C].contains(key % C);\r\n    }\r\n\
    \r\n    int min() const {\r\n        const int pos = bsf(map);\r\n        return\
    \ pos * C + child[pos].min();\r\n    }\r\n\r\n    int max() const {\r\n      \
    \  const int pos = bsr(map);\r\n        return pos * C + child[pos].max();\r\n\
    \    }\r\n\r\n    int pred(const int key) const {\r\n        const int pos = key\
    \ / C;\r\n        const int t = child[pos].pred(key % C);\r\n        if (t !=\
    \ -1) {\r\n            return pos * C + t;\r\n        }\r\n        const uint64_t\
    \ masked = map & ~(~0ULL << pos);\r\n        if (masked == 0) {\r\n          \
    \  return -1;\r\n        }\r\n        const int pos2 = bsr(masked);\r\n      \
    \  return pos2 * C + child[pos2].max();\r\n    }\r\n\r\n    int succ(const int\
    \ key) const {\r\n        const int pos = key / C;\r\n        const int t = child[pos].succ(key\
    \ % C);\r\n        if (t != -1) {\r\n            return pos * C + t;\r\n     \
    \   }\r\n        const uint64_t masked = map & ~(~0ULL >> (63 - pos));\r\n   \
    \     if (masked == 0) {\r\n            return -1;\r\n        }\r\n        const\
    \ int pos2 = bsf(masked);\r\n        return pos2 * C + child[pos2].min();\r\n\
    \    }\r\n\r\n    uint64_t _get_map() const { return map; }\r\n};\r\n\r\ntemplate\
    \ <int N>\r\nstruct tree64<N, typename enable_if<(N <= 64)>::type> {\r\n    uint64_t\
    \ map;\r\n\r\n    tree64() : map(0) {}\r\n\r\n    int bsf(const uint64_t x) {\
    \ return __builtin_ctzll(x); }\r\n    int bsr(const uint64_t x) { return 63 -\
    \ __builtin_clzll(x); }\r\n\r\n    bool insert(const int key) {\r\n        const\
    \ uint64_t pop = 1ULL << key;\r\n        if ((map & pop) != 0) {\r\n         \
    \   return false;\r\n        } else {\r\n            map |= pop;\r\n         \
    \   return true;\r\n        }\r\n    }\r\n\r\n    bool erase(const int key) {\r\
    \n        const uint64_t pop = 1ULL << key;\r\n        if ((map & pop) != 0) {\r\
    \n            map &= ~pop;\r\n            return true;\r\n        } else {\r\n\
    \            return false;\r\n        }\r\n    }\r\n\r\n    bool contains(const\
    \ int key) const { return (map & 1ULL << key) != 0; }\r\n\r\n    int min() const\
    \ { return bsf(map); }\r\n\r\n    int max() const { return bsr(map); }\r\n\r\n\
    \    int pred(const int key) const {\r\n        const uint64_t masked = map &\
    \ ~(~0ULL << key);\r\n        if (masked == 0) {\r\n            return -1;\r\n\
    \        }\r\n        return bsr(masked);\r\n    }\r\n\r\n    int succ(const int\
    \ key) const {\r\n        const uint64_t masked = map & (~0ULL << key);\r\n  \
    \      if (masked == 0) {\r\n            return -1;\r\n        }\r\n        return\
    \ bsf(masked);\r\n    }\r\n\r\n    uint64_t _get_map() const { return map; }\r\
    \n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/tree64.hpp
  requiredBy: []
  timestamp: '2023-05-22 19:46:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/tree64.hpp
layout: document
redirect_from:
- /library/lib/_new/tree64.hpp
- /library/lib/_new/tree64.hpp.html
title: lib/_new/tree64.hpp
---
