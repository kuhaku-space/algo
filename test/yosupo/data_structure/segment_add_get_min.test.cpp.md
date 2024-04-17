---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/li_chao_tree.hpp
    title: Li Chao Tree
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
    PROBLEM: https://judge.yosupo.jp/problem/segment_add_get_min
    links:
    - https://judge.yosupo.jp/problem/segment_add_get_min
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/li_chao_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/segment_add_get_min\"\n\
    #include <cstdint>\n#include <iostream>\n#include \"data_structure/li_chao_tree.hpp\"\
    \n\nint main(void) {\n    int n, q;\n    std::cin >> n >> q;\n    li_chao_tree\
    \ lct(-Inf, Inf);\n    while (n--) {\n        std::int64_t l, r, a, b;\n     \
    \   std::cin >> l >> r >> a >> b;\n        lct.add_segment(a, b, l, r);\n    }\n\
    \n    while (q--) {\n        int c;\n        std::cin >> c;\n        if (c ==\
    \ 0) {\n            std::int64_t l, r, a, b;\n            std::cin >> l >> r >>\
    \ a >> b;\n            lct.add_segment(a, b, l, r);\n        } else {\n      \
    \      std::int64_t x;\n            std::cin >> x;\n            auto ans = lct.query(x);\n\
    \            if (ans == lct.inf) std::cout << \"INFINITY\\n\";\n            else\
    \ std::cout << ans << '\\n';\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/data_structure/li_chao_tree.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/segment_add_get_min.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 06:42:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/segment_add_get_min.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/segment_add_get_min.test.cpp
- /verify/test/yosupo/data_structure/segment_add_get_min.test.cpp.html
title: test/yosupo/data_structure/segment_add_get_min.test.cpp
---
