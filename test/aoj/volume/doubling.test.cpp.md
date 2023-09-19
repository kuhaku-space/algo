---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/doubling.hpp
    title: "\u30C0\u30D6\u30EA\u30F3\u30B0"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2320
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2320
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/doubling.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2320\"\n#include\
    \ \"algorithm/doubling.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void)\
    \ {\n    while (true) {\n        int h, w;\n        ll l;\n        cin >> h >>\
    \ w >> l;\n        if (!h && !w && !l) break;\n        vector<string> s(h);\n\
    \        cin >> s;\n\n        auto in_field = [h, w, s](int x, int y) {\n    \
    \        return 0 <= x && x < h && 0 <= y && y < w && s[x][y] != '#';\n      \
    \  };\n\n        auto to_line = [h, w](int x, int y, int d) {\n            return\
    \ (x * w + y) * 4 + d;\n        };\n\n        vector<int> to(h * w * 4);\n   \
    \     iota(all(to), 0);\n        vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0,\
    \ -1};\n        rep (i, h) {\n            rep (j, w) {\n                if (!in_field(i,\
    \ j)) continue;\n                rep (k, 4) {\n                    rep (d, 4)\
    \ {\n                        int nx = i + dx[(k + d) % 4];\n                 \
    \       int ny = j + dy[(k + d) % 4];\n                        if (in_field(nx,\
    \ ny)) {\n                            to[to_line(i, j, k)] = to_line(nx, ny, (k\
    \ + d) % 4);\n                            break;\n                        }\n\
    \                    }\n                }\n            }\n        }\n\n      \
    \  string dir = \"NESW\";\n        Doubling<64> db(to);\n        int x, y, d;\n\
    \        rep (i, h) {\n            rep (j, w) {\n                rep (k, 4) {\n\
    \                    if (s[i][j] == dir[k]) x = i, y = j, d = k;\n           \
    \     }\n            }\n        }\n\n        int ans = db.solve(to_line(x, y,\
    \ d), l);\n        x = ans / w / 4;\n        ans %= w * 4;\n        y = ans /\
    \ 4;\n        d = ans % 4;\n        co(x + 1, y + 1, dir[d]);\n    }\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - lib/algorithm/doubling.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/aoj/volume/doubling.test.cpp
  requiredBy: []
  timestamp: '2023-09-19 13:03:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/volume/doubling.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/volume/doubling.test.cpp
- /verify/test/aoj/volume/doubling.test.cpp.html
title: test/aoj/volume/doubling.test.cpp
---
