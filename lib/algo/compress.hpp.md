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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n// \u5EA7\u6A19\u5727\u7E2E\u30E9\
    \u30A4\u30D6\u30E9\u30EA\r\ntemplate <class T>\r\nstruct Compress {\r\n    vector<T>\
    \ data;\r\n    Compress() {}\r\n    Compress(const vector<T>& _data) : data(_data)\
    \ { build(); }\r\n\r\n    const T& operator[](int i) const { return data[i]; }\r\
    \n    T& operator[](int i) { return data[i]; }\r\n\r\n    void add(T x) { data.emplace_back(x);\
    \ }\r\n\r\n    void build() {\r\n        sort(data.begin(), data.end());\r\n \
    \       data.erase(unique(data.begin(), data.end()), data.end());\r\n    }\r\n\
    \    void build(const vector<T>& _data) {\r\n        data = _data;\r\n       \
    \ sort(data.begin(), data.end());\r\n        data.erase(unique(data.begin(), data.end()),\
    \ data.end());\r\n    }\r\n    int get(T x) {\r\n        auto it = lower_bound(data.begin(),\
    \ data.end(), x);\r\n        assert(*it == x);\r\n        return it - data.begin();\r\
    \n    }\r\n\r\n    int size() { return data.size(); }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algo/compress.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algo/compress.hpp
layout: document
redirect_from:
- /library/lib/algo/compress.hpp
- /library/lib/algo/compress.hpp.html
title: lib/algo/compress.hpp
---
