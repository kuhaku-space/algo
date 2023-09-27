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
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\ntemplate <class T>\nint longest_common_prefix(const\
    \ std::vector<T> &a, const std::vector<T> &b) {\n    int m = (int)std::min(a.size(),\
    \ b.size());\n    for (int i = 0; i < m; ++i) {\n        if (a[i] != b[i]) return\
    \ i;\n    }\n    return m;\n}\n\nint longest_common_prefix(const string &a, const\
    \ string &b) {\n    int m = (int)std::min(a.size(), b.size());\n    for (int i\
    \ = 0; i < m; ++i) {\n        if (a[i] != b[i]) return i;\n    }\n    return m;\n\
    }\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/lcp.hpp
  requiredBy: []
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/lcp.hpp
layout: document
redirect_from:
- /library/lib/string/lcp.hpp
- /library/lib/string/lcp.hpp.html
title: lib/string/lcp.hpp
---
