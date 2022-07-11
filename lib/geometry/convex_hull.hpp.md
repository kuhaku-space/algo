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
    links:
    - http://www.prefield.com/algorithm/geometry/convex_hull.html
    - https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n// reference : http://www.prefield.com/algorithm/geometry/convex_hull.html\r\
    \n// verify : https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_A\r\n\r\ntemplate\
    \ <class T>\r\npair<T, T> &operator-=(pair<T, T> &a, const pair<T, T> &b) {\r\n\
    \    a.first -= b.first, a.second -= b.second;\r\n    return a;\r\n}\r\ntemplate\
    \ <class T>\r\nvector<pair<T, T>> convex_hull(vector<pair<T, T>> ps) {\r\n   \
    \ int n = ps.size(), k = 0;\r\n    auto asc = [](pair<T, T> a, pair<T, T> b) {\r\
    \n        return a.first != b.first ? a.first < b.first : a.second < b.second;\r\
    \n    };\r\n    sort(ps.begin(), ps.end(), asc);\r\n    vector<pair<T, T>> ch(n\
    \ << 1);\r\n    auto cross = [](pair<T, T> a, pair<T, T> b, const pair<T, T> &c)\
    \ {\r\n        a -= c, b -= c;\r\n        return a.first * b.second - a.second\
    \ * b.first;\r\n    };\r\n    for (int i = 0; i < n; ++i) {\r\n        while (k\
    \ > 1 && cross(ps[i], ch[k - 2], ch[k - 1]) < 0) --k;\r\n        ch[k++] = ps[i];\r\
    \n    }\r\n    for (int i = n - 2, t = k; i >= 0; --i) {\r\n        while (k >\
    \ t && cross(ps[i], ch[k - 2], ch[k - 1]) < 0) --k;\r\n        ch[k++] = ps[i];\r\
    \n    }\r\n    ch.resize(k - 1);\r\n    return ch;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/geometry/convex_hull.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/geometry/convex_hull.hpp
layout: document
redirect_from:
- /library/lib/geometry/convex_hull.hpp
- /library/lib/geometry/convex_hull.hpp.html
title: lib/geometry/convex_hull.hpp
---
