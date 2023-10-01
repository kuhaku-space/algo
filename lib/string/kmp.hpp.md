---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/kmp.test.cpp
    title: test/aoj/alds1/kmp.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/hupc/kmp.test.cpp
    title: test/aoj/hupc/kmp.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "KMP\u6CD5"
    links:
    - https://snuke.hatenablog.com/entry/2014/12/01/235807
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief KMP\u6CD5\r\n\
    \ *\r\n * @tparam Container\r\n *\r\n * @see https://snuke.hatenablog.com/entry/2014/12/01/235807\r\
    \n */\r\ntemplate <class Container>\r\nstruct knuth_morris_pratt {\r\n    knuth_morris_pratt(const\
    \ Container &_t) : t(_t), data(_t.size() + 1) {\r\n        data[0] = -1;\r\n \
    \       int j = -1;\r\n        for (int i = 0; i < t.size(); ++i) {\r\n      \
    \      while (j >= 0 && t[i] != t[j]) j = data[j];\r\n            if (t[i + 1]\
    \ == t[++j]) data[i + 1] = data[j];\r\n            else data[i + 1] = j;\r\n \
    \       }\r\n    }\r\n\r\n    const int operator[](int i) const { return data[i];\
    \ }\r\n\r\n    /**\r\n     * @brief \u691C\u7D22\r\n     *\r\n     * @param s\
    \ \u5BFE\u8C61\u5217\r\n     * @return std::vector<int>\r\n     */\r\n    std::vector<int>\
    \ search(const Container &s) {\r\n        int n = s.size(), m = t.size();\r\n\
    \        std::vector<int> res(n);\r\n        int i = 0, j = 0;\r\n        while\
    \ (i + j < n) {\r\n            if (j < m && t[j] == s[i + j]) {\r\n          \
    \      ++j;\r\n                res[i + j - 1] = j;\r\n                continue;\r\
    \n            }\r\n            i += j - data[j];\r\n            j = std::max(data[j],\
    \ int(0));\r\n        }\r\n        return res;\r\n    }\r\n\r\n  private:\r\n\
    \    Container t;\r\n    std::vector<int> data;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/kmp.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/hupc/kmp.test.cpp
  - test/aoj/alds1/kmp.test.cpp
documentation_of: lib/string/kmp.hpp
layout: document
redirect_from:
- /library/lib/string/kmp.hpp
- /library/lib/string/kmp.hpp.html
title: "KMP\u6CD5"
---
