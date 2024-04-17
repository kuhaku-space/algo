---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/flow/min_cost_flow.hpp
    title: "\u6700\u5C0F\u8CBB\u7528\u6D41"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    IGNORE: ''
    IGNORE_IF_GCC: ''
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2429
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/min_cost_flow.hpp:\
    \ line -1: no such header\n"
  code: "#define IGNORE\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2429\"\
    \n#include \"flow/min_cost_flow.hpp\"\n#include <iostream>\n#include <string>\n\
    #include <tuple>\n#include <vector>\n\nint main(void) {\n    int n;\n    std::cin\
    \ >> n;\n    std::vector w(n, std::vector(n, 0));\n    std::vector e(n, std::vector(n,\
    \ 0));\n    for (auto &v : w) {\n        for (auto &x : v) std::cin >> x;\n  \
    \  }\n    for (auto &v : e) {\n        for (auto &x : v) std::cin >> x;\n    }\n\
    \    std::vector<std::string> f(n);\n    for (auto &s : f) std::cin >> s;\n\n\
    \    mcf_graph<int, int> mcf(n * 2 + 2);\n    int st = n * 2, gl = st + 1;\n \
    \   int ans = 0;\n    for (int i = 0; i < n; ++i) {\n        for (int j = 0; j\
    \ < n; ++j) {\n            if (f[i][j] == 'o') {\n                ans += e[i][j];\n\
    \                mcf.add_edge(i, n + j, 1, 1000 - e[i][j]);\n            } else\
    \ {\n                mcf.add_edge(i, n + j, 1, 1000 + w[i][j]);\n            }\n\
    \        }\n    }\n    for (int i = 0; i < n; ++i) {\n        mcf.add_edge(st,\
    \ i, 1, 0);\n        mcf.add_edge(n + i, gl, 1, 0);\n    }\n\n    int c = mcf.flow(st,\
    \ gl).second;\n    std::cout << ans + c - 1000 * n << '\\n';\n    std::vector<std::tuple<int,\
    \ int, std::string>> ops;\n    for (int i = 0; i < n; ++i) {\n        for (int\
    \ j = 0; j < n; ++j) {\n            if (f[i][j] == 'o') {\n                if\
    \ (mcf.get_edge(i * n + j).flow == 0) ops.emplace_back(i + 1, j + 1, \"erase\"\
    );\n            } else {\n                if (mcf.get_edge(i * n + j).flow) ops.emplace_back(i\
    \ + 1, j + 1, \"write\");\n            }\n        }\n    }\n    std::cout << ops.size()\
    \ << '\\n';\n    for (auto [x, y, s] : ops) std::cout << x << ' ' << y << ' '\
    \ << s << '\\n';\n\n    return 0;\n}\n"
  dependsOn:
  - lib/flow/min_cost_flow.hpp
  isVerificationFile: true
  path: test/aoj/jag/min_cost_flow.test.cpp
  requiredBy: []
  timestamp: '2024-04-17 15:00:06+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aoj/jag/min_cost_flow.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/jag/min_cost_flow.test.cpp
- /verify/test/aoj/jag/min_cost_flow.test.cpp.html
title: test/aoj/jag/min_cost_flow.test.cpp
---
