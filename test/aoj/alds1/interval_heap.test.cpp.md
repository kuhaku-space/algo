---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/heap/interval_heap.hpp
    title: Interval Heap
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: heap/interval_heap.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C\"\n\
    #include \"heap/interval_heap.hpp\"\n#include <iostream>\n#include <string>\n\n\
    int main(void) {\n    interval_heap<int> heap;\n    while (true) {\n        std::string\
    \ s;\n        std::cin >> s;\n        if (s == \"end\") {\n            break;\n\
    \        } else if (s == \"insert\") {\n            int x;\n            std::cin\
    \ >> x;\n            heap.push(x);\n        } else {\n            std::cout <<\
    \ heap.get_max() << std::endl;\n            heap.pop_max();\n        }\n    }\n\
    \n    return 0;\n}\n"
  dependsOn:
  - lib/heap/interval_heap.hpp
  isVerificationFile: true
  path: test/aoj/alds1/interval_heap.test.cpp
  requiredBy: []
  timestamp: '2023-10-01 21:33:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/alds1/interval_heap.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/alds1/interval_heap.test.cpp
- /verify/test/aoj/alds1/interval_heap.test.cpp.html
title: test/aoj/alds1/interval_heap.test.cpp
---
