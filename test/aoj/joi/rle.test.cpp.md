---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/rle.hpp
    title: "\u30E9\u30F3\u30EC\u30F3\u30B0\u30B9\u5727\u7E2E"
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
  - icon: ':heavy_check_mark:'
    path: lib/template/vector.hpp
    title: lib/template/vector.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/0534
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/0534
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/rle.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/0534\"\n#include\
    \ \"algorithm/rle.hpp\"\n#include \"template/atcoder.hpp\"\n#include \"template/vector.hpp\"\
    \n\nint main(void) {\n    while (true) {\n        int n;\n        std::cin >>\
    \ n;\n        if (!n) break;\n        std::vector<int> a(n);\n        std::cin\
    \ >> a;\n        Dec >> a;\n        int ans = n;\n        rep (i, n) {\n     \
    \       auto b = a;\n            rep (j, 3) {\n                if (a[i] == j)\
    \ continue;\n                b[i] = j;\n                auto v = run_length_encoding(b);\n\
    \                std::stack<std::pair<int, int>> st;\n                for (auto\
    \ p : v) {\n                    if (p.second >= 4) continue;\n               \
    \     if (!st.empty() && st.top().first == p.first && st.top().second + p.second\
    \ >= 4)\n                        st.pop();\n                    else st.emplace(p);\n\
    \                }\n                int sum = 0;\n                while (!st.empty())\
    \ {\n                    sum += st.top().second;\n                    st.pop();\n\
    \                }\n                chmin(ans, sum);\n            }\n        }\n\
    \        co(ans);\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/algorithm/rle.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  - lib/template/vector.hpp
  isVerificationFile: true
  path: test/aoj/joi/rle.test.cpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/joi/rle.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/joi/rle.test.cpp
- /verify/test/aoj/joi/rle.test.cpp.html
title: test/aoj/joi/rle.test.cpp
---
