---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: modint
  - icon: ':heavy_check_mark:'
    path: lib/math/pow.hpp
    title: lib/math/pow.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/macro.hpp
    title: lib/template/macro.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/sonic.hpp
    title: lib/template/sonic.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n#include \"math/modint.hpp\"\n#include \"segment_tree/segment_tree.hpp\"\n#include\
    \ \"template/atcoder.hpp\"\n\nusing Mint = ModInt<>;\n\nstruct M {\n    using\
    \ T = pair<Mint, Mint>;\n    using value_type = T;\n    static constexpr T id\
    \ = T(1, 0);\n    static constexpr T op(T lhs, T rhs) {\n        return {rhs.first\
    \ * lhs.first, rhs.first * lhs.second + rhs.second};\n    }\n};\n\nint main(void)\
    \ {\n    int n, q;\n    cin >> n >> q;\n    vector<pair<Mint, Mint>> p(n);\n \
    \   cin >> p;\n    segment_tree<M> st(p);\n\n    while (q--) {\n        int c;\n\
    \        cin >> c;\n        if (c == 0) {\n            int k, a, b;\n        \
    \    cin >> k >> a >> b;\n            st.set(k, {a, b});\n        } else {\n \
    \           int l, r, x;\n            cin >> l >> r >> x;\n            auto p\
    \ = st.prod(l, r);\n            co(p.first * x + p.second);\n        }\n    }\n\
    \n    return 0;\n}\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/template/template.hpp
  - lib/segment_tree/segment_tree.hpp
  - lib/math/pow.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/point_set_range_composite.test.cpp
  requiredBy: []
  timestamp: '2023-04-17 09:43:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/point_set_range_composite.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/point_set_range_composite.test.cpp
- /verify/test/yosupo/data_structure/point_set_range_composite.test.cpp.html
title: test/yosupo/data_structure/point_set_range_composite.test.cpp
---
