#include "_base.hpp"

template <typename T>
struct geomatry {
    inline bool eq(T a, T b = T(0)) { return a == b; }
    using Point = complex<T>;
    const Point PINF = Point(LINF, LINF);
    using Points = vector<Point>;

    struct Line {
        // a * x + b * y = c
        T a, b, c;

        Line(T a, T b, T c) : a(a), b(b), c(c) {}

        Line(Point p1, Point p2) { drow(p1, p2); }

        bool operator==(const Line &p) const {
            return eq(a * p.b, b * p.a) && eq(a * p.c, c * p.a);
        }

        void drow(Point p1, Point p2) {
            a = (p2.imag() - p1.imag());
            b = (p1.real() - p2.real());
            c = a * p1.real() + b * p1.imag();
        }

        T dist_2(Point p) {
            T res = a * p.real() + b * p.imag() - c;
            if (res < T(0)) res *= T(-1);
            res /= a * a + b * b;
            return res;
        }

        bool is_parallel(Line l) { return eq(a * l.b, b * l.a); }

        bool in_line(Point p) { return eq(a * p.real() + b * p.imag(), c); }
    };

    Point rotate(const Point p, const Point center, const ld theta) {
        const Point d = p - center;
        return center + d * Point(cos(theta), sin(theta));
    }

    Point intersection(Line l1, Line l2) {
        T det = l1.a * l2.b - l2.a * l1.b;
        if (eq(det)) return PINF;

        Point res;
        res.real((l2.b * l1.c - l1.b * l2.c) / det);
        res.imag((l1.a * l2.c - l2.a * l1.c) / det);
        return res;
    }

    // 垂直二等分線
    Line perpendicular_bisector(Point p1, Point p2) {
        if (eq(p1, p2)) return Line(PINF, PINF);
        Point m = (p1 + p2) / T(2);
        return Line(m, rotate(p1, m, PI / 2));
    }

    Line drow_vertical_line(Point p, Line l) {
        if (l.in_line(p)) return Line(Point(LINF, LINF), LINF);
        return Line(p, p + Point(l.a, l.b));
    }
};
