#include "template/template.hpp"

template <class T, class U>
constexpr bool eq(T a, U b) {
    return abs(a - b) < EPS;
}
template <class T>
struct Point {
    T x, y;
    constexpr Point() : x(), y() {}
    constexpr Point(T _x, T _y = T()) : x(_x), y(_y) {}

    constexpr Point &operator+=(const Point &rhs) {
        this->x += rhs.x, this->y += rhs.y;
        return *this;
    }
    constexpr Point &operator-=(const Point &rhs) {
        this->x -= rhs.x, this->y -= rhs.y;
        return *this;
    }
    constexpr Point &operator*=(T rhs) {
        this->x *= rhs, this->y *= rhs;
        return *this;
    }
    constexpr Point &operator/=(T rhs) {
        this->x /= rhs, this->y /= rhs;
        return *this;
    }
    constexpr Point operator+(const Point &rhs) const { return Point(*this) += rhs; }
    constexpr Point operator-(const Point &rhs) const { return Point(*this) -= rhs; }
    constexpr Point operator*(T rhs) const { return Point(*this) *= rhs; }
    constexpr Point operator/(T rhs) const { return Point(*this) /= rhs; }

    constexpr T norm() const { return this->x * this->x + this->y * this->y; }
    T abs() const { return sqrt(this->norm()); }
    constexpr T dot(const Point<T> &p) const { return this->x * p.x + this->y * p.y; }
    constexpr T cross(const Point<T> &p) const { return this->x * p.y - this->y * p.x; }

    friend std::istream &operator>>(std::istream &is, Point<T> &rhs) {
        T x, y;
        is >> x >> y;
        rhs = Point<T>(x, y);
        return (is);
    }
    friend std::ostream &operator<<(std::ostream &os, const Point<T> &rhs) {
        return os << rhs.x << ' ' << rhs.y;
    }
};

template <class T>
using Points = std::vector<Point<T>>;

// ノルム
template <class T>
constexpr T norm(Point<T> p) {
    return p.x * p.x + p.y * p.y;
}
// 絶対値
template <class T>
T abs(Point<T> p) {
    return std::sqrt(norm(p));
}
// 内積
template <class T>
constexpr T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}
// 外積
template <class T>
constexpr T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template <class T>
int ccw(const Point<T> &a, Point<T> b, Point<T> c) {
    b -= a, c -= a;
    if (cross(b, c) > EPS) return +1;   // "COUNTER_CLOCKWISE"
    if (cross(b, c) < -EPS) return -1;  // "CLOCKWISE"
    if (dot(b, c) < 0) return +2;       // "ONLINE_BACK"
    if (norm(b) < norm(c)) return -2;   // "ONLINE_FRONT"
    return 0;                           // "ON_SEGMENT"
}

template <class T>
struct Line {
    Point<T> a, b;

    constexpr Line() : a(), b() {}
    constexpr Line(const Point<T> &_a, const Point<T> &_b) : a(_a), b(_b) {}

    constexpr bool in_line(Point<T> p) const { return eq(cross(p - a, p - b), 0); }

    // 射影
    constexpr Point<T> proj(const Point<T> &p) const {
        return a + (b - a) * dot(b - a, p - a) / norm(b - a);
    }
    // 反射
    constexpr Point<T> refl(const Point<T> &p) const { return this->proj(p) * 2 - p; }

    T dist(Point<T> p) { return abs(p - this->proj(p)); }
};

template <class T>
constexpr Point<T> PINF = Point<T>(numeric_limits<T>::max(), numeric_limits<T>::max());
template <class T>
constexpr Line<T> LINF = Line<T>(PINF<T>, PINF<T>);

template <class T>
bool parallel(const Line<T> &a, const Line<T> &b) {
    return eq(cross(a.b - a.a, b.b - b.a), 0.0);
}
template <class T>
bool orthogonal(const Line<T> &a, const Line<T> &b) {
    return eq(dot(a.a - a.b, b.a - b.b), 0.0);
}
template <class T>
bool intersection(const Line<T> &a, const Line<T> &b) {
    return ccw(a.a, a.b, b.a) * ccw(a.a, a.b, b.b) <= 0 &&
           ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) <= 0;
}
template <class T>
Point<T> cross_point(const Line<T> &a, const Line<T> &b) {
    T d = cross(b.b - b.a, b.b - a.a);
    T e = cross(b.b - b.a, a.b - a.a);
    if (eq(d, 0) && eq(e, 0)) return a.a;
    if (eq(e, 0)) return PINF<T>;
    return a.a + (a.b - a.a) * d / e;
}

// 垂直二等分線
template <class T>
Line<T> perpendicular_bisector(Point<T> p1, Point<T> p2) {
    if (eq(p1, p2)) return LINF<T>;
    Point<T> m = (p1 + p2) / 2.0L, d = p2 - p1;
    return Line<T>(m, m + d * Point<T>(cos(PI / 2), sin(PI / 2)));
}

template <class T>
Line<T> vertical_line(Point<T> p, Line<T> l) {
    if (l.in_line(p)) return LINF<T>;
    return Line<T>(p, l.proj(p));
}

template <class T>
Point<T> rotate(const Point<T> &p, const Point<T> &center, const double theta) {
    const Point<T> d = p - center;
    return center + d * Point<T>(cos(theta), sin(theta));
}

template <class T>
T triangle_area(Point<T> p1, Point<T> p2, Point<T> p3) {
    p1 -= p3;
    p2 -= p3;
    return abs(p1.x * p2.y + p1.y * p2.x) / 2;
}

template <class T>
struct Circle {
    Point<T> p;
    T r;

    constexpr Circle() : p(), r() {}
    constexpr Circle(Point<T> _p, T _r) : p(_p), r(_r) {}
};

template <class T>
int checker(Circle<T> c1, Circle<T> c2) {
    if (c1.r < c2.r) swap(c1, c2);
    T d = abs(c1.p - c2.p);
    if (c1.r + c2.r < d) return 4;
    if (eq(c1.r + c2.r, d)) return 3;
    if (c1.r - c2.r < d) return 2;
    if (eq(c1.r - c2.r, d)) return 1;
    return 0;
}

template <class T>
bool intersect(Circle<T> c1, Circle<T> c2) {
    int tmp = checker(c1, c2);
    return tmp >= 1 && tmp <= 3;
}

template <class T>
Points<T> cross_point(const Circle<T> c1, const Circle<T> c2) {
    T d = abs(c1.p - c2.p);
    int tmp = checker(c1, c2);
    Points<T> res;
    if (tmp == 3) res.push_back((c1.p * c2.r + c2.p * c1.r) / d);
    if (tmp == 2) {
        T a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2.0 * c1.r * d));
        T t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());
        res.emplace_back(c1.p + Point<T>(cos(t + a) * c1.r, sin(t + a) * c1.r));
        res.emplace_back(c1.p + Point<T>(cos(t - a) * c1.r, sin(t - a) * c1.r));
    }
    return res;
}

// 最小包含円
template <class T>
Circle<T> min_ball(Points<T> &ps, Point<T> p = Point<T>(0.0, 0.0)) {
    T r = 0.0, move = 0.5;
    Point<T> k(0.0, 0.0);
    while (move > EPS * EPS) {
        r = 0.0;
        for (auto i : ps)
            if (chmax(r, abs(p - i))) k = i;
        p += (k - p) * move;
        move *= 0.999;
    }

    return Circle<T>(p, r);
}
