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
  code: "#include \"template/template.hpp\"\r\n\r\nusing ld = long double;\r\n\r\n\
    template <class T1, class T2>\r\ninline bool eq(T1 a, T2 b) {\r\n    return abs(a\
    \ - b) < EPS;\r\n}\r\ntemplate <class T>\r\nusing Point = complex<T>;\r\ntemplate\
    \ <class T>\r\nusing Points = vector<Point<T>>;\r\n\r\n// \u5185\u7A4D\r\ntemplate\
    \ <class T>\r\nT dot(Point<T> a, Point<T> b) {\r\n    return (conj(a) * b).real();\r\
    \n}\r\n\r\n// \u5916\u7A4D\r\ntemplate <class T>\r\nT cross(Point<T> a, Point<T>\
    \ b) {\r\n    return (conj(a) * b).imag();\r\n}\r\n\r\ntemplate <class T>\r\n\
    struct Line {\r\n    Point<T> a, b;\r\n\r\n    Line(Point<T> _a, Point<T> _b)\
    \ : a(_a), b(_b) {}\r\n\r\n    bool in_line(Point<T> p) { return eq(cross(p -\
    \ a, p - b), 0); }\r\n\r\n    Point<T> proj(Point<T> p) {\r\n        return a\
    \ + dot(b - a, p - a) / norm(b - a) * (b - a);\r\n    }\r\n\r\n    T dist(Point<T>\
    \ p) { return abs(p - proj(p)); }\r\n};\r\n\r\nconstexpr Point<ld> PINF = Point<ld>(INF,\
    \ INF);\r\nconst Line<ld> LINF = Line<ld>(PINF, PINF);\r\n\r\ntemplate <class\
    \ T>\r\nPoint<T> cross_point(Line<T> l1, Line<T> l2) {\r\n    T d1 = cross(l2.b\
    \ - l1.b, l1.b - l1.a);\r\n    T d2 = cross(l2.b - l1.b, l2.a - l1.a);\r\n   \
    \ if (eq(d1, 0) && eq(d2, 0)) return l1.a;\r\n    if (eq(d2, 0)) return PINF;\r\
    \n    return l1.a + d1 / d2 * (l2.a - l1.a);\r\n}\r\n\r\n// \u5782\u76F4\u4E8C\
    \u7B49\u5206\u7DDA\r\ntemplate <class T>\r\nLine<T> perpendicular_bisector(Point<T>\
    \ p1, Point<T> p2) {\r\n    if (eq(p1, p2)) return LINF;\r\n    Point<T> m = (p1\
    \ + p2) / 2.0L, d = p2 - p1;\r\n    return Line<T>(m, m + d * Point<T>(cos(PI\
    \ / 2), sin(PI / 2)));\r\n}\r\n\r\ntemplate <class T>\r\nLine<T> vertical_line(Point<T>\
    \ p, Line<T> l) {\r\n    if (l.in_line(p)) return LINF;\r\n    return Line<T>(p,\
    \ l.proj(p));\r\n}\r\n\r\ntemplate <class T>\r\nPoint<T> rotate(const Point<T>\
    \ p, const Point<T> center, const ld theta) {\r\n    const Point<T> d = p - center;\r\
    \n    return center + d * Point<T>(cos(theta), sin(theta));\r\n}\r\n\r\ntemplate\
    \ <class T>\r\nT triangle_area(Point<T> p1, Point<T> p2, Point<T> p3) {\r\n  \
    \  p1 -= p3;\r\n    p2 -= p3;\r\n    return abs(p1.real() * p2.imag() + p1.imag()\
    \ * p2.real()) / 2;\r\n}\r\n\r\ntemplate <class T>\r\nstruct Circle2 {\r\n   \
    \ Point<T> p;\r\n    T r;\r\n\r\n    Circle2() : p(INF), r(0) {}\r\n\r\n    Circle2(Point<T>\
    \ _p, T _r) : p(_p), r(_r) {}\r\n};\r\n\r\ntemplate <class T>\r\nint64_t checker(Circle2<T>\
    \ c1, Circle2<T> c2) {\r\n    if (c1.r < c2.r) swap(c1, c2);\r\n    T d = abs(c1.p\
    \ - c2.p);\r\n    if (c1.r + c2.r < d) return 4;\r\n    if (eq(c1.r + c2.r, d))\
    \ return 3;\r\n    if (c1.r - c2.r < d) return 2;\r\n    if (eq(c1.r - c2.r, d))\
    \ return 1;\r\n    return 0;\r\n}\r\n\r\ntemplate <class T>\r\nbool intersect(Circle2<T>\
    \ c1, Circle2<T> c2) {\r\n    ll tmp = checker(c1, c2);\r\n    return tmp >= 1\
    \ && tmp <= 3;\r\n}\r\n\r\ntemplate <class T>\r\nPoints<T> cross_point(const Circle2<T>\
    \ c1, const Circle2<T> c2) {\r\n    T d = abs(c1.p - c2.p);\r\n    ll tmp = checker(c1,\
    \ c2);\r\n    Points<T> res;\r\n    if (tmp == 3) res.push_back((c1.p * c2.r +\
    \ c2.p * c1.r) / d);\r\n    if (tmp == 2) {\r\n        T a = acos((c1.r * c1.r\
    \ + d * d - c2.r * c2.r) / (2.0 * c1.r * d));\r\n        T t = atan2(c2.p.imag()\
    \ - c1.p.imag(), c2.p.real() - c1.p.real());\r\n        res.push_back(c1.p + Point<T>(cos(t\
    \ + a) * c1.r, sin(t + a) * c1.r));\r\n        res.push_back(c1.p + Point<T>(cos(t\
    \ - a) * c1.r, sin(t - a) * c1.r));\r\n    }\r\n    return res;\r\n}\r\n\r\n//\
    \ \u6700\u5C0F\u5305\u542B\u5186\r\ntemplate <class T>\r\nCircle2<T> min_ball(Points<T>\
    \ &ps, Point<T> p = Point<T>(0.0, 0.0)) {\r\n    T r = 0.0, move = 0.5;\r\n  \
    \  Point<T> k(0.0, 0.0);\r\n    while (move > EPS * EPS) {\r\n        r = 0.0;\r\
    \n        for (auto i : ps)\r\n            if (chmax(r, abs(p - i))) k = i;\r\n\
    \        p += (k - p) * move;\r\n        move *= 0.999;\r\n    }\r\n\r\n    return\
    \ Circle2<T>(p, r);\r\n}\r\n\r\nusing point = Point<ld>;\r\nusing points = Points<ld>;\r\
    \nusing circle = Circle2<ld>;\r\n\r\nstruct Pos {\r\n    ld x, y, z;\r\n    Pos(ld\
    \ x, ld y, ld z) : x(x), y(y), z(z) {}\r\n};\r\n\r\nstruct Circle3 {\r\n    Pos\
    \ p;\r\n    ld r;\r\n    Circle3(Pos p, ld r) : p(p), r(r) {}\r\n};\r\n\r\nCircle3\
    \ min_ball(vector<Pos> &ps, Pos p = {0.0, 0.0, 0.0}) {\r\n    auto dist = [](const\
    \ Pos &a, const Pos &b) -> ld {\r\n        ld dx = a.x - b.x;\r\n        ld dy\
    \ = a.y - b.y;\r\n        ld dz = a.z - b.z;\r\n        return sqrt(dx * dx +\
    \ dy * dy + dz * dz);\r\n    };\r\n\r\n    ld r = 0.0, move = 0.5;\r\n    Pos\
    \ k = {0.0, 0.0, 0.0};\r\n    while (move > EPS * EPS) {\r\n        r = 0.0;\r\
    \n        for (Pos i : ps)\r\n            if (chmax(r, dist(p, i))) k = i;\r\n\
    \        p.x += (k.x - p.x) * move;\r\n        p.y += (k.y - p.y) * move;\r\n\
    \        p.x += (k.z - p.z) * move;\r\n        move *= 0.999;\r\n    }\r\n\r\n\
    \    return Circle3(p, r);\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/geometry/geometry_T.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/geometry/geometry_T.hpp
layout: document
redirect_from:
- /library/lib/geometry/geometry_T.hpp
- /library/lib/geometry/geometry_T.hpp.html
title: lib/geometry/geometry_T.hpp
---
