---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/counter-clockwise.test.cpp
    title: test/aoj/cgl/counter-clockwise.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/cross_point.test.cpp
    title: test/aoj/cgl/cross_point.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/intersection.test.cpp
    title: test/aoj/cgl/intersection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/parallel_orthogonal.test.cpp
    title: test/aoj/cgl/parallel_orthogonal.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/projection.test.cpp
    title: test/aoj/cgl/projection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/reflection.test.cpp
    title: test/aoj/cgl/reflection.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.9/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T, class U>\r\n\
    constexpr bool eq(T a, U b) {\r\n    return abs(a - b) < EPS;\r\n}\r\ntemplate\
    \ <class T>\r\nstruct Point {\r\n    T x, y;\r\n    constexpr Point() : x(), y()\
    \ {}\r\n    constexpr Point(T _x, T _y = T()) : x(_x), y(_y) {}\r\n\r\n    constexpr\
    \ Point &operator+=(const Point &rhs) {\r\n        this->x += rhs.x, this->y +=\
    \ rhs.y;\r\n        return *this;\r\n    }\r\n    constexpr Point &operator-=(const\
    \ Point &rhs) {\r\n        this->x -= rhs.x, this->y -= rhs.y;\r\n        return\
    \ *this;\r\n    }\r\n    constexpr Point &operator*=(T rhs) {\r\n        this->x\
    \ *= rhs, this->y *= rhs;\r\n        return *this;\r\n    }\r\n    constexpr Point\
    \ &operator/=(T rhs) {\r\n        this->x /= rhs, this->y /= rhs;\r\n        return\
    \ *this;\r\n    }\r\n    constexpr Point operator+(const Point &rhs) const { return\
    \ Point(*this) += rhs; }\r\n    constexpr Point operator-(const Point &rhs) const\
    \ { return Point(*this) -= rhs; }\r\n    constexpr Point operator*(T rhs) const\
    \ { return Point(*this) *= rhs; }\r\n    constexpr Point operator/(T rhs) const\
    \ { return Point(*this) /= rhs; }\r\n\r\n    constexpr T norm() const { return\
    \ this->x * this->x + this->y * this->y; }\r\n    T abs() const { return sqrt(this->norm());\
    \ }\r\n    constexpr T dot(const Point<T> &p) const { return this->x * p.x + this->y\
    \ * p.y; }\r\n    constexpr T cross(const Point<T> &p) const { return this->x\
    \ * p.y - this->y * p.x; }\r\n\r\n    friend istream &operator>>(istream &is,\
    \ Point<T> &rhs) {\r\n        T x, y;\r\n        is >> x >> y;\r\n        rhs\
    \ = Point<T>(x, y);\r\n        return (is);\r\n    }\r\n    friend ostream &operator<<(ostream\
    \ &os, const Point<T> &rhs) {\r\n        return os << rhs.x << ' ' << rhs.y;\r\
    \n    }\r\n};\r\n\r\ntemplate <class T>\r\nusing Points = vector<Point<T>>;\r\n\
    \r\n// \u30CE\u30EB\u30E0\r\ntemplate <class T>\r\nconstexpr T norm(Point<T> p)\
    \ {\r\n    return p.x * p.x + p.y * p.y;\r\n}\r\n// \u7D76\u5BFE\u5024\r\ntemplate\
    \ <class T>\r\nT abs(Point<T> p) {\r\n    return sqrt(norm(p));\r\n}\r\n// \u5185\
    \u7A4D\r\ntemplate <class T>\r\nconstexpr T dot(Point<T> a, Point<T> b) {\r\n\
    \    return a.x * b.x + a.y * b.y;\r\n}\r\n// \u5916\u7A4D\r\ntemplate <class\
    \ T>\r\nconstexpr T cross(Point<T> a, Point<T> b) {\r\n    return a.x * b.y -\
    \ a.y * b.x;\r\n}\r\n\r\ntemplate <class T>\r\nint ccw(const Point<T> &a, Point<T>\
    \ b, Point<T> c) {\r\n    b -= a, c -= a;\r\n    if (cross(b, c) > EPS) return\
    \ +1;   // \"COUNTER_CLOCKWISE\"\r\n    if (cross(b, c) < -EPS) return -1;  //\
    \ \"CLOCKWISE\"\r\n    if (dot(b, c) < 0) return +2;       // \"ONLINE_BACK\"\r\
    \n    if (norm(b) < norm(c)) return -2;   // \"ONLINE_FRONT\"\r\n    return 0;\
    \                           // \"ON_SEGMENT\"\r\n}\r\n\r\ntemplate <class T>\r\
    \nstruct Line {\r\n    Point<T> a, b;\r\n\r\n    constexpr Line() : a(), b() {}\r\
    \n    constexpr Line(const Point<T> &_a, const Point<T> &_b) : a(_a), b(_b) {}\r\
    \n\r\n    constexpr bool in_line(Point<T> p) const { return eq(cross(p - a, p\
    \ - b), 0); }\r\n\r\n    // \u5C04\u5F71\r\n    constexpr Point<T> proj(const\
    \ Point<T> &p) const {\r\n        return a + (b - a) * dot(b - a, p - a) / norm(b\
    \ - a);\r\n    }\r\n    // \u53CD\u5C04\r\n    constexpr Point<T> refl(const Point<T>\
    \ &p) const { return this->proj(p) * 2 - p; }\r\n\r\n    T dist(Point<T> p) {\
    \ return abs(p - this->proj(p)); }\r\n};\r\n\r\ntemplate <class T>\r\nconstexpr\
    \ Point<T> PINF = Point<T>(numeric_limits<T>::max(), numeric_limits<T>::max());\r\
    \ntemplate <class T>\r\nconstexpr Line<T> LINF = Line<T>(PINF<T>, PINF<T>);\r\n\
    \r\ntemplate <class T>\r\nbool parallel(const Line<T> &a, const Line<T> &b) {\r\
    \n    return eq(cross(a.b - a.a, b.b - b.a), 0.0);\r\n}\r\ntemplate <class T>\r\
    \nbool orthogonal(const Line<T> &a, const Line<T> &b) {\r\n    return eq(dot(a.a\
    \ - a.b, b.a - b.b), 0.0);\r\n}\r\ntemplate <class T>\r\nbool intersection(const\
    \ Line<T> &a, const Line<T> &b) {\r\n    return ccw(a.a, a.b, b.a) * ccw(a.a,\
    \ a.b, b.b) <= 0 &&\r\n           ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) <= 0;\r\
    \n}\r\ntemplate <class T>\r\nPoint<T> cross_point(const Line<T> &a, const Line<T>\
    \ &b) {\r\n    T d = cross(b.b - b.a, b.b - a.a);\r\n    T e = cross(b.b - b.a,\
    \ a.b - a.a);\r\n    if (eq(d, 0) && eq(e, 0)) return a.a;\r\n    if (eq(e, 0))\
    \ return PINF<T>;\r\n    return a.a + (a.b - a.a) * d / e;\r\n}\r\n\r\n// \u5782\
    \u76F4\u4E8C\u7B49\u5206\u7DDA\r\ntemplate <class T>\r\nLine<T> perpendicular_bisector(Point<T>\
    \ p1, Point<T> p2) {\r\n    if (eq(p1, p2)) return LINF<T>;\r\n    Point<T> m\
    \ = (p1 + p2) / 2.0L, d = p2 - p1;\r\n    return Line<T>(m, m + d * Point<T>(cos(PI\
    \ / 2), sin(PI / 2)));\r\n}\r\n\r\ntemplate <class T>\r\nLine<T> vertical_line(Point<T>\
    \ p, Line<T> l) {\r\n    if (l.in_line(p)) return LINF<T>;\r\n    return Line<T>(p,\
    \ l.proj(p));\r\n}\r\n\r\ntemplate <class T>\r\nPoint<T> rotate(const Point<T>\
    \ &p, const Point<T> &center, const double theta) {\r\n    const Point<T> d =\
    \ p - center;\r\n    return center + d * Point<T>(cos(theta), sin(theta));\r\n\
    }\r\n\r\ntemplate <class T>\r\nT triangle_area(Point<T> p1, Point<T> p2, Point<T>\
    \ p3) {\r\n    p1 -= p3;\r\n    p2 -= p3;\r\n    return abs(p1.x * p2.y + p1.y\
    \ * p2.x) / 2;\r\n}\r\n\r\ntemplate <class T>\r\nstruct Circle {\r\n    Point<T>\
    \ p;\r\n    T r;\r\n\r\n    constexpr Circle() : p(), r() {}\r\n    constexpr\
    \ Circle(Point<T> _p, T _r) : p(_p), r(_r) {}\r\n};\r\n\r\ntemplate <class T>\r\
    \nint checker(Circle<T> c1, Circle<T> c2) {\r\n    if (c1.r < c2.r) swap(c1, c2);\r\
    \n    T d = abs(c1.p - c2.p);\r\n    if (c1.r + c2.r < d) return 4;\r\n    if\
    \ (eq(c1.r + c2.r, d)) return 3;\r\n    if (c1.r - c2.r < d) return 2;\r\n   \
    \ if (eq(c1.r - c2.r, d)) return 1;\r\n    return 0;\r\n}\r\n\r\ntemplate <class\
    \ T>\r\nbool intersect(Circle<T> c1, Circle<T> c2) {\r\n    int tmp = checker(c1,\
    \ c2);\r\n    return tmp >= 1 && tmp <= 3;\r\n}\r\n\r\ntemplate <class T>\r\n\
    Points<T> cross_point(const Circle<T> c1, const Circle<T> c2) {\r\n    T d = abs(c1.p\
    \ - c2.p);\r\n    int tmp = checker(c1, c2);\r\n    Points<T> res;\r\n    if (tmp\
    \ == 3) res.push_back((c1.p * c2.r + c2.p * c1.r) / d);\r\n    if (tmp == 2) {\r\
    \n        T a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0 * c1.r * d));\r\
    \n        T t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());\r\
    \n        res.emplace_back(c1.p + Point<T>(cos(t + a) * c1.r, sin(t + a) * c1.r));\r\
    \n        res.emplace_back(c1.p + Point<T>(cos(t - a) * c1.r, sin(t - a) * c1.r));\r\
    \n    }\r\n    return res;\r\n}\r\n\r\n// \u6700\u5C0F\u5305\u542B\u5186\r\ntemplate\
    \ <class T>\r\nCircle<T> min_ball(Points<T> &ps, Point<T> p = Point<T>(0.0, 0.0))\
    \ {\r\n    T r = 0.0, move = 0.5;\r\n    Point<T> k(0.0, 0.0);\r\n    while (move\
    \ > EPS * EPS) {\r\n        r = 0.0;\r\n        for (auto i : ps)\r\n        \
    \    if (chmax(r, abs(p - i))) k = i;\r\n        p += (k - p) * move;\r\n    \
    \    move *= 0.999;\r\n    }\r\n\r\n    return Circle<T>(p, r);\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/geometry/geometry.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/cgl/cross_point.test.cpp
  - test/aoj/cgl/projection.test.cpp
  - test/aoj/cgl/intersection.test.cpp
  - test/aoj/cgl/reflection.test.cpp
  - test/aoj/cgl/parallel_orthogonal.test.cpp
  - test/aoj/cgl/counter-clockwise.test.cpp
documentation_of: lib/geometry/geometry.hpp
layout: document
redirect_from:
- /library/lib/geometry/geometry.hpp
- /library/lib/geometry/geometry.hpp.html
title: lib/geometry/geometry.hpp
---
