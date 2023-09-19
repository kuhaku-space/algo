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
    document_title: Mex
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
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief Mex\r\n *\r\n\
    \ */\r\nstruct minimum_excluded {\r\n    minimum_excluded() : n(), _size(), exists(64),\
    \ v() {}\r\n\r\n    constexpr int operator()() const noexcept { return n; }\r\n\
    \    constexpr int get() const noexcept { return n; }\r\n\r\n    void add(int\
    \ x) {\r\n        if (x < 0) return;\r\n        ++_size;\r\n        if (_size\
    \ == (int)std::size(exists)) {\r\n            exists.resize(_size << 1);\r\n \
    \           int cnt = 0;\r\n            for (int i = 0; i < (int)std::size(v);\
    \ ++i) {\r\n                if (v[i] < (int)std::size(exists)) {\r\n         \
    \           if (exists[v[i]]) --_size;\r\n                    else exists[v[i]]\
    \ = true;\r\n                } else {\r\n                    v[cnt++] = v[i];\r\
    \n                }\r\n            }\r\n            v.erase(std::begin(v) + cnt,\
    \ std::end(v));\r\n        }\r\n        if (x < (int)std::size(exists)) {\r\n\
    \            if (exists[x]) --_size;\r\n            else exists[x] = true;\r\n\
    \        } else {\r\n            v.emplace_back(x);\r\n        }\r\n        while\
    \ (exists[n]) ++n;\r\n    }\r\n\r\n  private:\r\n    int n, _size;\r\n    std::vector<bool>\
    \ exists;\r\n    std::vector<int> v;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/mex.hpp
  requiredBy: []
  timestamp: '2023-09-12 08:19:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/mex.hpp
layout: document
redirect_from:
- /library/lib/algorithm/mex.hpp
- /library/lib/algorithm/mex.hpp.html
title: Mex
---
