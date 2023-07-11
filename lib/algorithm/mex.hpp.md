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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief Mex\r\n *\r\n\
    \ */\r\nstruct minimum_excluded {\r\n    minimum_excluded() : n(), _size(), is_exist(64),\
    \ v() {}\r\n\r\n    constexpr int operator()() const noexcept { return this->n;\
    \ }\r\n    constexpr int get() const noexcept { return this->n; }\r\n\r\n    void\
    \ add(int x) {\r\n        if (x < 0) return;\r\n        ++this->_size;\r\n   \
    \     if (this->_size == (int)this->is_exist.size()) {\r\n            this->is_exist.resize(this->_size\
    \ << 1);\r\n            int cnt = 0;\r\n            for (int i = 0; i < (int)this->v.size();\
    \ ++i) {\r\n                if (this->v[i] < (int)this->is_exist.size()) {\r\n\
    \                    if (this->is_exist[this->v[i]]) --this->_size;\r\n      \
    \              else this->is_exist[this->v[i]] = true;\r\n                } else\
    \ {\r\n                    this->v[cnt++] = this->v[i];\r\n                }\r\
    \n            }\r\n            this->v.erase(this->v.begin() + cnt, this->v.end());\r\
    \n        }\r\n        if (x < (int)this->is_exist.size()) {\r\n            if\
    \ (this->is_exist[x]) --this->_size;\r\n            else this->is_exist[x] = true;\r\
    \n        } else {\r\n            this->v.emplace_back(x);\r\n        }\r\n  \
    \      while (this->is_exist[this->n]) ++this->n;\r\n    }\r\n\r\n  private:\r\
    \n    int n, _size;\r\n    std::vector<bool> is_exist;\r\n    std::vector<int>\
    \ v;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/mex.hpp
  requiredBy: []
  timestamp: '2023-05-22 19:46:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/mex.hpp
layout: document
redirect_from:
- /library/lib/algorithm/mex.hpp
- /library/lib/algorithm/mex.hpp.html
title: Mex
---
