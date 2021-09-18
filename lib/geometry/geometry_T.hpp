#include "template/template.hpp"

using ld = long double;

template <class T1, class T2>
inline bool eq(T1 a, T2 b) {
    return abs(a - b) < EPS;
}
template <class T>
using Point = complex<T>;
template <class T>
using Points = vector<Point<T>>;

// 内積
template <class T>
T dot(Point<T> a, Point<T> b) {
    return (conj(a) * b).real();
}

// 外積
template <class T>
T cross(Point<T> a, Point<T> b) {
    return (conj(a) * b).imag();
}

template <class T>
struct Line {
    Point<T> a, b;

    Line(Point<T> _a, Point<T> _b) : a(_a), b(_b) {}

    bool in_line(Point<T> p) { return eq(cross(p - a, p - b), 0); }

    Point<T> proj(Point<T> p) {
        return a + dot(b - a, p - a) / norm(b - a) * (b - a);
    }

    T dist(Point<T> p) { return abs(p - proj(p)); }
};

constexpr Point<ld> PINF = Point<ld>(INF, INF);
const Line<ld> LINF = Line<ld>(PINF, PINF);

template <class T>
Point<T> cross_point(Line<T> l1, Line<T> l2) {
    T d1 = cross(l2.b - l1.b, l1.b - l1.a);
    T d2 = cross(l2.b - l1.b, l2.a - l1.a);
    if (eq(d1, 0) && eq(d2, 0)) return l1.a;
    if (eq(d2, 0)) return PINF;
    return l1.a + d1 / d2 * (l2.a - l1.a);
}

// 垂直二等分線
template <class T>
Line<T> perpendicular_bisector(Point<T> p1, Point<T> p2) {
    if (eq(p1, p2)) return LINF;
    Point<T> m = (p1 + p2) / 2.0L, d = p2 - p1;
    return Line<T>(m, m + d * Point<T>(cos(PI / 2), sin(PI / 2)));
}

template <class T>
Line<T> vertical_line(Point<T> p, Line<T> l) {
    if (l.in_line(p)) return LINF;
    return Line<T>(p, l.proj(p));
}

template <class T>
Point<T> rotate(const Point<T> p, const Point<T> center, const ld theta) {
    const Point<T> d = p - center;
    return center + d * Point<T>(cos(theta), sin(theta));
}

template <class T>
T triangle_area(Point<T> p1, Point<T> p2, Point<T> p3) {
    p1 -= p3;
    p2 -= p3;
    return abs(p1.real() * p2.imag() + p1.imag() * p2.real()) / 2;
}

template <class T>
struct Circle2 {
    Point<T> p;
    T r;

    Circle2() : p(INF), r(0) {}

    Circle2(Point<T> _p, T _r) : p(_p), r(_r) {}
};

template <class T>
int64_t checker(Circle2<T> c1, Circle2<T> c2) {
    if (c1.r < c2.r) swap(c1, c2);
    T d = abs(c1.p - c2.p);
    if (c1.r + c2.r < d) return 4;
    if (eq(c1.r + c2.r, d)) return 3;
    if (c1.r - c2.r < d) return 2;
    if (eq(c1.r - c2.r, d)) return 1;
    return 0;
}

template <class T>
bool intersect(Circle2<T> c1, Circle2<T> c2) {
    ll tmp = checker(c1, c2);
    return tmp >= 1 && tmp <= 3;
}

template <class T>
Points<T> cross_point(const Circle2<T> c1, const Circle2<T> c2) {
    T d = abs(c1.p - c2.p);
    ll tmp = checker(c1, c2);
    Points<T> res;
    if (tmp == 3) res.push_back((c1.p * c2.r + c2.p * c1.r) / d);
    if (tmp == 2) {
        T a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0 * c1.r * d));
        T t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());
        res.push_back(c1.p + Point<T>(cos(t + a) * c1.r, sin(t + a) * c1.r));
        res.push_back(c1.p + Point<T>(cos(t - a) * c1.r, sin(t - a) * c1.r));
    }
    return res;
}

// 最小包含円
template <class T>
Circle2<T> min_ball(Points<T> &ps, Point<T> p = Point<T>(0.0, 0.0)) {
    T r = 0.0, move = 0.5;
    Point<T> k(0.0, 0.0);
    while (move > EPS * EPS) {
        r = 0.0;
        for (auto i : ps)
            if (chmax(r, abs(p - i))) k = i;
        p += (k - p) * move;
        move *= 0.999;
    }

    return Circle2<T>(p, r);
}

using point = Point<ld>;
using points = Points<ld>;
using circle = Circle2<ld>;

struct Pos {
    ld x, y, z;
    Pos(ld x, ld y, ld z) : x(x), y(y), z(z) {}
};

struct Circle3 {
    Pos p;
    ld r;
    Circle3(Pos p, ld r) : p(p), r(r) {}
};

Circle3 min_ball(vector<Pos> &ps, Pos p = {0.0, 0.0, 0.0}) {
    auto dist = [](const Pos &a, const Pos &b) -> ld {
        ld dx = a.x - b.x;
        ld dy = a.y - b.y;
        ld dz = a.z - b.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    };

    ld r = 0.0, move = 0.5;
    Pos k = {0.0, 0.0, 0.0};
    while (move > EPS * EPS) {
        r = 0.0;
        for (Pos i : ps)
            if (chmax(r, dist(p, i))) k = i;
        p.x += (k.x - p.x) * move;
        p.y += (k.y - p.y) * move;
        p.x += (k.z - p.z) * move;
        move *= 0.999;
    }

    return Circle3(p, r);
}
