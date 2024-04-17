---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/range_tree.hpp
    title: "\u9818\u57DF\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/range_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n#include <cstdint>\n#include <iostream>\n#include <tuple>\n#include <vector>\n\
    #include \"binary_tree/range_tree.hpp\"\n\nint main(void) {\n    int n, q;\n \
    \   std::cin >> n >> q;\n    range_tree<Add<std::int64_t>> rt;\n    std::vector<std::tuple<int,\
    \ int, int>> points(n);\n    for (auto &[x, y, z] : points) {\n        std::cin\
    \ >> x >> y >> z;\n        rt.add(x, y);\n    }\n    std::vector<std::tuple<int,\
    \ int, int, int, int>> queries(q);\n    for (auto &[x, y, z, w, v] : queries)\
    \ {\n        std::cin >> x >> y >> z >> w;\n        if (x == 0) rt.add(y, z);\n\
    \        else std::cin >> v;\n    }\n\n    rt.build();\n    for (auto [x, y, z]\
    \ : points) rt.set(x, y, rt.get(x, y) + z);\n    for (auto [x, y, z, w, v] : queries)\
    \ {\n        if (x == 0) rt.set(y, z, rt.get(y, z) + w);\n        else std::cout\
    \ << rt.prod(y, z, w, v) << '\\n';\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/range_tree.hpp
  - lib/segment_tree/segment_tree.hpp
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2024-02-27 00:57:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
- /verify/test/yosupo/data_structure/point_add_rectangle_sum.test.cpp.html
title: test/yosupo/data_structure/point_add_rectangle_sum.test.cpp
---
