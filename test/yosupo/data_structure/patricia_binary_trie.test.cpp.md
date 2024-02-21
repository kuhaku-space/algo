---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/patricia_binary_trie.hpp
    title: "2\u5206\u30D1\u30C8\u30EA\u30B7\u30A2\u6728"
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/set_xor_min
    links:
    - https://judge.yosupo.jp/problem/set_xor_min
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/patricia_binary_trie.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\n#include\
    \ \"binary_tree/patricia_binary_trie.hpp\"\n#include <iostream>\n\nint main(void)\
    \ {\n    int q;\n    std::cin >> q;\n    patricia_binary_trie<int, 30> bt;\n \
    \   while (q--) {\n        int t, x;\n        std::cin >> t >> x;\n        if\
    \ (t == 0) bt.insert(x);\n        else if (t == 1) bt.erase(x);\n        else\
    \ std::cout << (bt.min_element(x) ^ x) << '\\n';\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/patricia_binary_trie.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/patricia_binary_trie.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 06:42:05+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/patricia_binary_trie.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/patricia_binary_trie.test.cpp
- /verify/test/yosupo/data_structure/patricia_binary_trie.test.cpp.html
title: test/yosupo/data_structure/patricia_binary_trie.test.cpp
---
