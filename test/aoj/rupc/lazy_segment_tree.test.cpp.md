---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/lazy_segment_tree.hpp
    title: "\u9045\u5EF6\u8A55\u4FA1\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/eular_tour.hpp
    title: "\u30AA\u30A4\u30E9\u30FC\u30C4\u30A2\u30FC"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2871
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2871
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/lazy_segment_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2871\"\n#include\
    \ \"segment_tree/lazy_segment_tree.hpp\"\n#include <iostream>\n#include <vector>\n\
    #include \"tree/eular_tour.hpp\"\n\nstruct S {\n    int g, w;\n};\n\nstruct M\
    \ {\n    using value_type = S;\n    static constexpr value_type id = S{0, 0};\n\
    \    static constexpr value_type op(const value_type &lhs, const value_type &rhs)\
    \ {\n        return S{lhs.g + rhs.g, lhs.w + rhs.w};\n    }\n};\n\nstruct F {\n\
    \    using value_type = int;\n    static constexpr value_type id = 0;\n    static\
    \ constexpr value_type op(const value_type &lhs, const value_type &rhs) {\n  \
    \      return lhs ^ rhs;\n    }\n\n    static S f(const value_type &lhs, S rhs)\
    \ {\n        if (lhs == 0) return rhs;\n        std::swap(rhs.g, rhs.w);\n   \
    \     return rhs;\n    }\n};\n\nint main(void) {\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    Graph<void> g(n);\n    for (int i = 0; i < n - 1; ++i) {\n \
    \       int p;\n        std::cin >> p;\n        g.add_edges(p - 1, i + 1);\n \
    \   }\n    eular_tour et(g);\n    std::vector<S> v(n);\n    for (int i = 0; i\
    \ < n; ++i) {\n        char c;\n        std::cin >> c;\n        if (c == 'G')\
    \ v[et.get_l(i)] = S{1, 0};\n        else v[et.get_l(i)] = S{0, 1};\n    }\n \
    \   lazy_segment_tree<M, F> lst(v);\n    while (q--) {\n        int x;\n     \
    \   std::cin >> x;\n        --x;\n        lst.apply(et.get_l(x), et.get_r(x),\
    \ 1);\n        auto [g, w] = lst.all_prod();\n        if (g >= w) std::cout <<\
    \ \"broccoli\" << std::endl;\n        else std::cout << \"cauliflower\" << std::endl;\n\
    \    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/segment_tree/lazy_segment_tree.hpp
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  - lib/tree/eular_tour.hpp
  - lib/graph/graph.hpp
  isVerificationFile: true
  path: test/aoj/rupc/lazy_segment_tree.test.cpp
  requiredBy: []
  timestamp: '2024-05-06 21:20:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/rupc/lazy_segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/rupc/lazy_segment_tree.test.cpp
- /verify/test/aoj/rupc/lazy_segment_tree.test.cpp.html
title: test/aoj/rupc/lazy_segment_tree.test.cpp
---
