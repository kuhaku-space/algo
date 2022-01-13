---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/graph/dijkstra.hpp
    title: lib/graph/dijkstra.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\nstruct radix_heap {\r\n    vector<unsigned\
    \ int> v[33];\r\n    unsigned int last, sz;\r\n    bool is_top;\r\n\r\n    radix_heap()\
    \ : last(), sz(), is_top() {}\r\n\r\n    int bsr(unsigned int x) {\r\n       \
    \ if (x == 0) return -1;\r\n        return 31 - __builtin_clz(x);\r\n    }\r\n\
    \r\n    void push(unsigned int x) {\r\n        assert(x >= last);\r\n        ++sz;\r\
    \n        v[bsr(x ^ last) + 1].emplace_back(x);\r\n    }\r\n\r\n    unsigned int\
    \ top() {\r\n        if (is_top) pop();\r\n        is_top = true;\r\n        return\
    \ last;\r\n    }\r\n\r\n    void pop() {\r\n        if (is_top) {\r\n        \
    \    is_top = false;\r\n            return;\r\n        }\r\n        assert(sz);\r\
    \n        if (!v[0].size()) {\r\n            int i = 1;\r\n            while (!v[i].size())\
    \ ++i;\r\n            auto new_last = *min_element(v[i].begin(), v[i].end());\r\
    \n            for (auto x : v[i]) {\r\n                v[bsr(x ^ new_last) + 1].emplace_back(x);\r\
    \n            }\r\n            last = new_last;\r\n            v[i].clear();\r\
    \n        }\r\n        --sz;\r\n        v[0].pop_back();\r\n    }\r\n};\r\n\r\n\
    struct radix_heap_64 {\r\n    vector<uint64_t> v[65];\r\n    uint64_t last, sz;\r\
    \n    bool is_top;\r\n\r\n    radix_heap_64() : last(), sz(), is_top() {}\r\n\r\
    \n    int bsr(uint64_t x) {\r\n        if (x == 0) return -1;\r\n        return\
    \ 63 - __builtin_clz(x);\r\n    }\r\n\r\n    void push(uint64_t x) {\r\n     \
    \   assert(x >= last);\r\n        ++sz;\r\n        v[bsr(x ^ last) + 1].emplace_back(x);\r\
    \n    }\r\n\r\n    uint64_t top() {\r\n        if (!is_top) pop();\r\n       \
    \ is_top = true;\r\n        return last;\r\n    }\r\n\r\n    void pop() {\r\n\
    \        if (is_top) {\r\n            is_top = false;\r\n            return;\r\
    \n        }\r\n        assert(sz);\r\n        if (!v[0].size()) {\r\n        \
    \    int i = 1;\r\n            while (!v[i].size()) ++i;\r\n            auto new_last\
    \ = *min_element(v[i].begin(), v[i].end());\r\n            for (auto x : v[i])\
    \ v[bsr(x ^ new_last) + 1].emplace_back(x);\r\n            last = new_last;\r\n\
    \            v[i].clear();\r\n        }\r\n        --sz;\r\n        v[0].pop_back();\r\
    \n    }\r\n};\r\n\r\ntemplate <class T>\r\nstruct radix_heap_dijkstra {\r\n  \
    \  vector<T> v[33];\r\n    T last;\r\n    unsigned int sz;\r\n    bool is_top;\r\
    \n\r\n    radix_heap_dijkstra() : last(), sz(), is_top() {}\r\n\r\n    int bsr(unsigned\
    \ int x) {\r\n        if (x == 0) return -1;\r\n        return 31 - __builtin_clz(x);\r\
    \n    }\r\n\r\n    bool empty() const { return sz == 0; }\r\n    auto size() const\
    \ { return sz; }\r\n\r\n    void push(T x) {\r\n        assert(x.dist >= last.dist);\r\
    \n        ++sz;\r\n        v[bsr(x.dist ^ last.dist) + 1].emplace_back(x);\r\n\
    \    }\r\n\r\n    auto top() {\r\n        if (!is_top) pop();\r\n        is_top\
    \ = true;\r\n        return last;\r\n    }\r\n\r\n    void pop() {\r\n       \
    \ if (is_top) {\r\n            is_top = false;\r\n            return;\r\n    \
    \    }\r\n        assert(sz);\r\n        if (!v[0].size()) {\r\n            int\
    \ i = 1;\r\n            while (!v[i].size()) ++i;\r\n            auto new_last\
    \ = *min_element(v[i].begin(), v[i].end());\r\n            for (auto x : v[i])\
    \ {\r\n                v[bsr(x.dist ^ new_last.dist) + 1].emplace_back(x);\r\n\
    \            }\r\n            v[i].clear();\r\n        }\r\n        --sz;\r\n\
    \        last = v[0].back();\r\n        v[0].pop_back();\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/data_structure/radix_heap.hpp
  requiredBy:
  - lib/graph/dijkstra.hpp
  timestamp: '2021-10-01 05:33:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/data_structure/radix_heap.hpp
layout: document
redirect_from:
- /library/lib/data_structure/radix_heap.hpp
- /library/lib/data_structure/radix_heap.hpp.html
title: lib/data_structure/radix_heap.hpp
---
