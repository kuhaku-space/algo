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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T>\r\nstruct Pos\
    \ {\r\n    T x, y, z;\r\n    constexpr Pos() : x(), y(), z() {}\r\n    constexpr\
    \ Pos(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}\r\n};\r\n\r\ntemplate <class\
    \ T>\r\nstruct Circle3 {\r\n    Pos<T> p;\r\n    T r;\r\n    constexpr Circle3(Pos<T>\
    \ _p, T _r) : p(_p), r(_r) {}\r\n};\r\n\r\ntemplate <class T>\r\nCircle3<T> min_ball(vector<Pos<T>>\
    \ &ps, Pos<T> p = {0.0, 0.0, 0.0}) {\r\n    auto dist = [](const Pos<T> &a, const\
    \ Pos<T> &b) -> T {\r\n        T dx = a.x - b.x;\r\n        T dy = a.y - b.y;\r\
    \n        T dz = a.z - b.z;\r\n        return sqrt(dx * dx + dy * dy + dz * dz);\r\
    \n    };\r\n\r\n    T r = 0.0, move = 0.5;\r\n    Pos<T> k = {0.0, 0.0, 0.0};\r\
    \n    while (move > EPS * EPS) {\r\n        r = 0.0;\r\n        for (Pos<T> i\
    \ : ps)\r\n            if (chmax(r, dist(p, i))) k = i;\r\n        p.x += (k.x\
    \ - p.x) * move;\r\n        p.y += (k.y - p.y) * move;\r\n        p.x += (k.z\
    \ - p.z) * move;\r\n        move *= 0.999;\r\n    }\r\n\r\n    return Circle3<T>(p,\
    \ r);\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/geometry/geometry3d.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/geometry/geometry3d.hpp
layout: document
redirect_from:
- /library/lib/geometry/geometry3d.hpp
- /library/lib/geometry/geometry3d.hpp.html
title: lib/geometry/geometry3d.hpp
---
