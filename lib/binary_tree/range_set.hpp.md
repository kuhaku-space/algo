---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/rupc/range_set.test.cpp
    title: test/aoj/rupc/range_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
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
  code: "#include \"template/template.hpp\"\n\ntemplate <class T>\nstruct range_set\
    \ {\n    range_set() = default;\n\n    std::pair<T, T> get(T x) const {\n    \
    \    auto it = intervals.lower_bound(std::make_pair(x, x));\n        if (it ==\
    \ std::end(intervals) || !contains(x, *it))\n            return std::make_pair(inf,\
    \ inf);\n        return std::make_pair(it->second, it->first);\n    }\n\n    bool\
    \ contains(T x) const {\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        return it != std::end(intervals) && contains(x, *it);\n    }\n\
    \n    bool same(T x, T y) const {\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        return it != std::end(intervals) && contains(x, *it) && contains(y,\
    \ *it);\n    }\n\n    std::pair<T, T> insert(T x, T y) {\n        assert(x < y);\n\
    \        auto it = intervals.lower_bound(std::make_pair(x, std::numeric_limits<T>::lowest()));\n\
    \        while (it != std::end(intervals) && it->second <= y) {\n            x\
    \ = std::min(x, it->second);\n            y = std::max(y, it->first);\n      \
    \      it = intervals.erase(it);\n        }\n        intervals.emplace(y, x);\n\
    \        return std::make_pair(x, y);\n    }\n\n    std::pair<T, T> insert(T x)\
    \ {\n        return insert(x, x + 1);\n    }\n\n    void erase(T x, T y) {\n \
    \       assert(x < y);\n        auto it = intervals.lower_bound(std::make_pair(x,\
    \ x));\n        if (it == std::end(intervals))\n            return;\n        if\
    \ (it->second != x) {\n            T l = it->second, r = it->first;\n        \
    \    intervals.erase(it);\n            intervals.emplace(x, l);\n            intervals.emplace(r,\
    \ x);\n        }\n        it = intervals.lower_bound(std::make_pair(x, x));\n\
    \        while (it != std::end(intervals)) {\n            if (y <= it->second)\n\
    \                break;\n            if (y < it->first) {\n                T r\
    \ = it->first;\n                intervals.erase(it);\n                intervals.emplace(r,\
    \ y);\n                break;\n            }\n            it = intervals.erase(it);\n\
    \        }\n    }\n\n    void erase(T x) {\n        erase(x, x + 1);\n    }\n\n\
    \  private:\n    static constexpr T inf = std::numeric_limits<T>::max();\n   \
    \ std::set<std::pair<T, T>> intervals;\n\n    static bool contains(T x, const\
    \ std::pair<T, T> &p) {\n        return p.second <= x && x < p.first;\n    }\n\
    };\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/range_set.hpp
  requiredBy: []
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/rupc/range_set.test.cpp
documentation_of: lib/binary_tree/range_set.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/range_set.hpp
- /library/lib/binary_tree/range_set.hpp.html
title: lib/binary_tree/range_set.hpp
---
