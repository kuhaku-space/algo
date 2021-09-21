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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <typename T>\r\nstruct\
    \ geometry {\r\n    inline bool eq(T a, T b = T(0)) { return a == b; }\r\n   \
    \ using Point = complex<T>;\r\n    const Point PINF = Point(INF, INF);\r\n   \
    \ using Points = vector<Point>;\r\n\r\n    struct Line {\r\n        // a * x +\
    \ b * y = c\r\n        T a, b, c;\r\n\r\n        Line(T a, T b, T c) : a(a), b(b),\
    \ c(c) {}\r\n\r\n        Line(Point p1, Point p2) { drow(p1, p2); }\r\n\r\n  \
    \      bool operator==(const Line &p) const {\r\n            return eq(a * p.b,\
    \ b * p.a) && eq(a * p.c, c * p.a);\r\n        }\r\n\r\n        void drow(Point\
    \ p1, Point p2) {\r\n            a = (p2.imag() - p1.imag());\r\n            b\
    \ = (p1.real() - p2.real());\r\n            c = a * p1.real() + b * p1.imag();\r\
    \n        }\r\n\r\n        T dist(Point p) {\r\n            T res = a * p.real()\
    \ + b * p.imag() - c;\r\n            if (res < T(0)) res *= T(-1);\r\n       \
    \     res /= a * a + b * b;\r\n            return res;\r\n        }\r\n\r\n  \
    \      bool is_parallel(Line l) { return eq(a * l.b, b * l.a); }\r\n\r\n     \
    \   bool in_line(Point p) { return eq(a * p.real() + b * p.imag(), c); }\r\n \
    \   };\r\n\r\n    Point rotate(const Point p, const Point center, const double\
    \ theta) {\r\n        const Point d = p - center;\r\n        return center + d\
    \ * Point(cos(theta), sin(theta));\r\n        // return center + d * Point(cosl(theta),\
    \ sinl(theta));\r\n    }\r\n\r\n    Point intersection(Line l1, Line l2) {\r\n\
    \        T det = l1.a * l2.b - l2.a * l1.b;\r\n        if (eq(det)) return PINF;\r\
    \n\r\n        Point res;\r\n        res.real((l2.b * l1.c - l1.b * l2.c) / det);\r\
    \n        res.imag((l1.a * l2.c - l2.a * l1.c) / det);\r\n        return res;\r\
    \n    }\r\n\r\n    // \u5782\u76F4\u4E8C\u7B49\u5206\u7DDA\r\n    Line perpendicular_bisector(Point\
    \ p1, Point p2) {\r\n        if (eq(p1, p2)) return Line(PINF, PINF);\r\n    \
    \    Point m = (p1 + p2) / T(2);\r\n        return Line(m, rotate(p1, m, PI /\
    \ 2));\r\n    }\r\n\r\n    Line drow_vertical_line(Point p, Line l) {\r\n    \
    \    if (l.in_line(p)) return Line(Point(INF, INF), INF);\r\n        return Line(p,\
    \ p + Point(l.a, l.b));\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/geometry/geometry.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/geometry/geometry.hpp
layout: document
redirect_from:
- /library/lib/geometry/geometry.hpp
- /library/lib/geometry/geometry.hpp.html
title: lib/geometry/geometry.hpp
---
