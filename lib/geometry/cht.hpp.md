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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/*\r\n * Usage:\r\n * CHT cht(ll(1e13),\
    \ [](ll l, ll r) { return l >= r; });\r\n */\r\ntemplate <class T, class F>\r\n\
    struct CHT {\r\n    vector<pair<T, T>> lines;\r\n    F comp;\r\n    int head;\r\
    \n    CHT(T _e, F _comp) : comp(_comp), head(0) { lines.emplace_back(0, _e); };\r\
    \n\r\n    bool check(pair<T, T> l1, pair<T, T> l2, pair<T, T> l3) {\r\n      \
    \  if (l1 < l3) swap(l1, l3);\r\n        return (l3.second - l2.second) * (l2.first\
    \ - l1.first) >=\r\n               (l2.second - l1.second) * (l3.first - l2.first);\r\
    \n    }\r\n\r\n    void add(T a, T b) {\r\n        pair<T, T> line(a, b);\r\n\
    \        while (lines.size() >= 2 &&\r\n               check(*(lines.end() - 2),\
    \ lines.back(), line))\r\n            lines.pop_back();\r\n        lines.emplace_back(line);\r\
    \n    }\r\n\r\n    T f(int i, T x) { return lines[i].first * x + lines[i].second;\
    \ }\r\n    T f(pair<T, T> line, T x) { return line.first * x + line.second; }\r\
    \n\r\n    T get(T x) {\r\n        // while(lines.size() >= 2 + head && comp(f(head,\
    \ x), f(head + 1, x))){\r\n        //     head++;\r\n        // }\r\n        //\
    \ return f(head, x);\r\n        int low = -1, high = lines.size() - 1;\r\n   \
    \     while (high - low > 1) {\r\n            int mid = (high + low) / 2;\r\n\
    \            if (comp(f(mid, x), f(mid + 1, x)))\r\n                low = mid;\r\
    \n            else\r\n                high = mid;\r\n        }\r\n        return\
    \ f(high, x);\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/geometry/cht.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/geometry/cht.hpp
layout: document
redirect_from:
- /library/lib/geometry/cht.hpp
- /library/lib/geometry/cht.hpp.html
title: lib/geometry/cht.hpp
---
