---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
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
  code: "#include \"template/template.hpp\"\r\n\r\nstruct MEX {\r\n    int n;\r\n\
    \    int sz;\r\n    vector<bool> is_exist;\r\n    vector<int> v;\r\n\r\n    MEX()\
    \ : n(), sz(), is_exist(64) {}\r\n\r\n    int operator()() const { return n; }\r\
    \n\r\n    void add(int x) {\r\n        ++sz;\r\n        if (sz == is_exist.size())\
    \ {\r\n            is_exist.resize(sz << 1);\r\n            int cnt = 0;\r\n \
    \           for (int i = 0; i < v.size(); ++i) {\r\n                if (v[i] <\
    \ is_exist.size()) {\r\n                    if (is_exist[v[i]])\r\n          \
    \              --sz;\r\n                    else\r\n                        is_exist[v[i]]\
    \ = true;\r\n                } else {\r\n                    v[cnt++] = v[i];\r\
    \n                }\r\n            }\r\n            v.erase(v.begin() + cnt, v.end());\r\
    \n        }\r\n        if (x < is_exist.size()) {\r\n            if (is_exist[x])\r\
    \n                --sz;\r\n            else\r\n                is_exist[x] = true;\r\
    \n        } else {\r\n            v.emplace_back(x);\r\n        }\r\n        while\
    \ (is_exist[n]) ++n;\r\n    }\r\n\r\n    int get() const { return n; }\r\n};\r\
    \n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/mex.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/mex.hpp
layout: document
redirect_from:
- /library/lib/_new/mex.hpp
- /library/lib/_new/mex.hpp.html
title: lib/_new/mex.hpp
---
