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
    document_title: "\u5EA7\u6A19\u5727\u7E2E"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u5EA7\u6A19\u5727\
    \u7E2E\r\n *\r\n * @tparam T\r\n */\r\ntemplate <class T>\r\nstruct Compress {\r\
    \n    vector<T> data;\r\n    Compress() {}\r\n    Compress(const vector<T>& _data)\
    \ : data(_data) { build(); }\r\n\r\n    const T& operator[](int i) const { return\
    \ data[i]; }\r\n    T& operator[](int i) { return data[i]; }\r\n\r\n    void add(T\
    \ x) { data.emplace_back(x); }\r\n\r\n    void build() {\r\n        sort(data.begin(),\
    \ data.end());\r\n        data.erase(unique(data.begin(), data.end()), data.end());\r\
    \n    }\r\n    void build(const vector<T>& _data) {\r\n        data = _data;\r\
    \n        sort(data.begin(), data.end());\r\n        data.erase(unique(data.begin(),\
    \ data.end()), data.end());\r\n    }\r\n    int get(T x) {\r\n        auto it\
    \ = lower_bound(data.begin(), data.end(), x);\r\n        assert(*it == x);\r\n\
    \        return it - data.begin();\r\n    }\r\n\r\n    int size() { return data.size();\
    \ }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algorithm/compress.hpp
  requiredBy: []
  timestamp: '2021-10-01 05:33:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algorithm/compress.hpp
layout: document
redirect_from:
- /library/lib/algorithm/compress.hpp
- /library/lib/algorithm/compress.hpp.html
title: "\u5EA7\u6A19\u5727\u7E2E"
---
