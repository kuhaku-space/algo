---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_math.hpp
    title: lib/internal/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_type_traits.hpp
    title: lib/internal/internal_type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/rerooting.hpp
    title: "\u5168\u65B9\u4F4D\u6728dp"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tree_path_composite_sum
    links:
    - https://judge.yosupo.jp/problem/tree_path_composite_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_path_composite_sum\"\
    \n#include <iostream>\n#include <utility>\n#include <vector>\n#include \"math/modint.hpp\"\
    \n#include \"tree/rerooting.hpp\"\n\nusing Mint = modint998;\n\ntemplate <class\
    \ T, class U>\nstd::istream &operator>>(std::istream &is, std::pair<T, U> &p)\
    \ {\n    return is >> p.first >> p.second;\n}\n\nstruct Monoid {\n    using value_type\
    \ = std::pair<Mint, Mint>;\n    static constexpr value_type id = {0, 0};\n   \
    \ static inline std::vector<Mint> a = std::vector<Mint>();\n    static constexpr\
    \ value_type op(const value_type &lhs, const value_type &rhs) {\n        return\
    \ {lhs.first + rhs.first, lhs.second + rhs.second};\n    }\n\n    template <class\
    \ T>\n    static constexpr value_type f(const value_type &v, T u) {\n        return\
    \ {u.first * v.first + u.second * v.second, v.second};\n    }\n\n    static value_type\
    \ g(const value_type &v, int u) { return {v.first + a[u], v.second + 1}; }\n};\n\
    \nint main(void) {\n    int n;\n    std::cin >> n;\n    Monoid::a = std::vector<Mint>(n);\n\
    \    for (auto &e : Monoid::a) std::cin >> e;\n    Graph<std::pair<Mint, Mint>>\
    \ g(n);\n    g.input_edges(n - 1, 0);\n    ReRooting<Monoid, std::pair<Mint, Mint>>\
    \ rr(g);\n    std::vector<Mint> ans;\n    for (int i = 0; i < n; ++i) ans.emplace_back(rr[i].first);\n\
    \    for (int i = 0; i < (int)ans.size(); ++i)\n        std::cout << ans[i] <<\
    \ (i == (int)ans.size() - 1 ? '\\n' : ' ');\n\n    return 0;\n}\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/template/template.hpp
  - lib/tree/rerooting.hpp
  - lib/graph/graph.hpp
  isVerificationFile: true
  path: test/yosupo/tree/tree_path_composite_sum.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 21:39:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/tree/tree_path_composite_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/tree/tree_path_composite_sum.test.cpp
- /verify/test/yosupo/tree/tree_path_composite_sum.test.cpp.html
title: test/yosupo/tree/tree_path_composite_sum.test.cpp
---
