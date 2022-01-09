---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u30C0\u30D6\u30EA\u30F3\u30B0"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u30C0\u30D6\u30EA\
    \u30F3\u30B0\r\n * \r\n * @tparam L \r\n */\r\ntemplate <int L>\r\nstruct Doubling\
    \ {\r\n    Doubling(int _n) : n(_n), data(L, std::vector<int>(_n)) {}\r\n\r\n\
    \    void build(const std::vector<int> &v) {\r\n        for (int i = 0; i < this->n;\
    \ ++i) this->data[0][i] = v[i];\r\n\r\n        for (int i = 0; i < L - 1; ++i)\
    \ {\r\n            for (int j = 0; j < this->n; ++j) {\r\n                this->data[i\
    \ + 1][j] = this->data[i][this->data[i][j]];\r\n            }\r\n        }\r\n\
    \    }\r\n\r\n    int solve(int f, int64_t k) {\r\n        for (int cnt = 0; k\
    \ > 0; k >>= 1, ++cnt) {\r\n            if (k & 1) f = this->data[cnt][f];\r\n\
    \        }\r\n        return f;\r\n    }\r\n\r\n  private:\r\n    int n;\r\n \
    \   std::vector<std::vector<int>> data;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/doubling.hpp
  requiredBy: []
  timestamp: '2022-01-09 16:16:11+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/doubling.hpp
layout: document
redirect_from:
- /library/lib/algorithm/doubling.hpp
- /library/lib/algorithm/doubling.hpp.html
title: "\u30C0\u30D6\u30EA\u30F3\u30B0"
---
