---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/doubling.hpp
    title: "\u30C0\u30D6\u30EA\u30F3\u30B0"
  - icon: ':heavy_check_mark:'
    path: lib/graph/grid.hpp
    title: lib/graph/grid.hpp
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/doubling.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2320\"\n#include\
    \ \"algorithm/doubling.hpp\"\n#include <algorithm>\n#include <cstdint>\n#include\
    \ <iostream>\n#include <iterator>\n#include <numeric>\n#include <string>\n#include\
    \ <vector>\n#include \"graph/grid.hpp\"\n\nint main(void) {\n    while (true)\
    \ {\n        int h, w;\n        std::int64_t l;\n        std::cin >> h >> w >>\
    \ l;\n        if (!h && !w && !l) break;\n        std::vector<std::string> s(h);\n\
    \        for (auto &e : s) std::cin >> e;\n\n        Grid<2> grid(h, w);\n   \
    \     auto in_grid = [&](int x, int y) { return grid.in_field(x, y) && s[x][y]\
    \ != '#'; };\n        auto flatten = [h, w](int x, int y, int d) { return (x *\
    \ w + y) * 4 + d; };\n\n        std::vector<int> to(h * w * 4);\n        std::iota(to.begin(),\
    \ to.end(), 0);\n        std::vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};\n\
    \        for (int i = 0; i < h; ++i) {\n            for (int j = 0; j < w; ++j)\
    \ {\n                if (!in_grid(i, j)) continue;\n                for (int k\
    \ = 0; k < 4; ++k) {\n                    for (int d = 0; d < 4; ++d) {\n    \
    \                    int nx = i + dx[(k + d) % 4];\n                        int\
    \ ny = j + dy[(k + d) % 4];\n                        if (in_grid(nx, ny)) {\n\
    \                            to[flatten(i, j, k)] = flatten(nx, ny, (k + d) %\
    \ 4);\n                            break;\n                        }\n       \
    \             }\n                }\n            }\n        }\n\n        std::string\
    \ dir = \"NESW\";\n        Doubling<64> db(to);\n        int x, y, d;\n      \
    \  for (int i = 0; i < h; ++i) {\n            for (int j = 0; j < w; ++j) {\n\
    \                for (int k = 0; k < 4; ++k) {\n                    if (s[i][j]\
    \ == dir[k]) x = i, y = j, d = k;\n                }\n            }\n        }\n\
    \n        int ans = db.solve(flatten(x, y, d), l);\n        x = ans / w / 4;\n\
    \        ans %= w * 4;\n        y = ans / 4;\n        d = ans % 4;\n        std::cout\
    \ << x + 1 << ' ' << y + 1 << ' ' << dir[d] << std::endl;\n    }\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - lib/algorithm/doubling.hpp
  - lib/graph/grid.hpp
  isVerificationFile: true
  path: test/aoj/jag/doubling.test.cpp
  requiredBy: []
  timestamp: '2024-02-22 18:29:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/jag/doubling.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/jag/doubling.test.cpp
- /verify/test/aoj/jag/doubling.test.cpp.html
title: test/aoj/jag/doubling.test.cpp
---
