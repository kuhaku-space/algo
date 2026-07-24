#pragma once
#include "template/template.hpp"

/// @brief `a` と `b` の差が `EPS` 未満なら true を返す
/// @complexity $O(1)$
template <class T, class U>
constexpr bool eq(T a, U b) {
    return abs(a - b) < EPS;
}

/// @brief 二次元幾何の点・直線・円と基本演算
/// @details `Point<T>` を中心に内積、外積、位置関係、交点、射影、回転などを提供する。
/// @complexity 基本演算は $O(1)$。`min_ball` は点数を $n$ として
/// $O(n\log(1/\mathrm{EPS}))$
template <class T>
struct Point {
    /// @brief x 座標と y 座標
    /// @complexity $O(1)$ で参照可能
    T x, y;
    /// @brief 原点を作る
    /// @complexity $O(1)$
    constexpr Point() : x(), y() {}
    /// @brief 座標 `(_x, _y)` の点を作る
    /// @complexity $O(1)$
    constexpr Point(T _x, T _y = T()) : x(_x), y(_y) {}

    /// @brief ベクトル `rhs` を加算する
    /// @complexity $O(1)$
    constexpr Point &operator+=(const Point &rhs) {
        this->x += rhs.x, this->y += rhs.y;
        return *this;
    }
    /// @brief ベクトル `rhs` を減算する
    /// @complexity $O(1)$
    constexpr Point &operator-=(const Point &rhs) {
        this->x -= rhs.x, this->y -= rhs.y;
        return *this;
    }
    /// @brief 各座標をスカラー `rhs` 倍する
    /// @complexity $O(1)$
    constexpr Point &operator*=(T rhs) {
        this->x *= rhs, this->y *= rhs;
        return *this;
    }
    /// @brief 各座標をスカラー `rhs` で割る
    /// @complexity $O(1)$
    constexpr Point &operator/=(T rhs) {
        this->x /= rhs, this->y /= rhs;
        return *this;
    }
    /// @brief ベクトル和を返す
    /// @complexity $O(1)$
    constexpr Point operator+(const Point &rhs) const { return Point(*this) += rhs; }
    /// @brief ベクトル差を返す
    /// @complexity $O(1)$
    constexpr Point operator-(const Point &rhs) const { return Point(*this) -= rhs; }
    /// @brief スカラー倍を返す
    /// @complexity $O(1)$
    constexpr Point operator*(T rhs) const { return Point(*this) *= rhs; }
    /// @brief スカラー除算を返す
    /// @complexity $O(1)$
    constexpr Point operator/(T rhs) const { return Point(*this) /= rhs; }

    /// @brief 原点からの距離の二乗を返す
    /// @complexity $O(1)$
    constexpr T norm() const { return this->x * this->x + this->y * this->y; }
    /// @brief 原点からの距離を返す
    /// @complexity $O(1)$
    T abs() const { return sqrt(this->norm()); }
    /// @brief `p` との内積を返す
    /// @complexity $O(1)$
    constexpr T dot(const Point<T> &p) const { return this->x * p.x + this->y * p.y; }
    /// @brief `p` との外積を返す
    /// @complexity $O(1)$
    constexpr T cross(const Point<T> &p) const { return this->x * p.y - this->y * p.x; }

    /// @brief 入力ストリームから x 座標と y 座標を読み込む
    /// @complexity $O(1)$
    friend std::istream &operator>>(std::istream &is, Point<T> &rhs) {
        T x, y;
        is >> x >> y;
        rhs = Point<T>(x, y);
        return (is);
    }
    /// @brief x 座標と y 座標を空白区切りで出力する
    /// @complexity $O(1)$
    friend std::ostream &operator<<(std::ostream &os, const Point<T> &rhs) { return os << rhs.x << ' ' << rhs.y; }
};

/// @brief 二次元の点列
/// @complexity 型エイリアスのため実行時コストなし
template <class T>
using Points = std::vector<Point<T>>;

/// @brief 点 `p` の原点からの距離の二乗を返す
/// @complexity $O(1)$
template <class T>
constexpr T norm(Point<T> p) {
    return p.x * p.x + p.y * p.y;
}
/// @brief 点 `p` の原点からの距離を返す
/// @complexity $O(1)$
template <class T>
T abs(Point<T> p) {
    return std::sqrt(norm(p));
}
/// @brief ベクトル `a`, `b` の内積を返す
/// @complexity $O(1)$
template <class T>
constexpr T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}
/// @brief ベクトル `a`, `b` の外積を返す
/// @complexity $O(1)$
template <class T>
constexpr T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

/// @brief 有向線分 `a -> b` に対する点 `c` の位置関係を返す
/// @details 反時計回りは 1、時計回りは -1、後方は 2、前方は -2、線分上は 0。
/// @complexity $O(1)$
template <class T>
int ccw(const Point<T> &a, Point<T> b, Point<T> c) {
    b -= a, c -= a;
    if (cross(b, c) > EPS) return +1;   // "COUNTER_CLOCKWISE"
    if (cross(b, c) < -EPS) return -1;  // "CLOCKWISE"
    if (dot(b, c) < 0) return +2;       // "ONLINE_BACK"
    if (norm(b) < norm(c)) return -2;   // "ONLINE_FRONT"
    return 0;                           // "ON_SEGMENT"
}

/// @brief 2 点を通る直線
/// @complexity 各操作は $O(1)$
template <class T>
struct Line {
    /// @brief 直線上の 2 点
    /// @complexity $O(1)$ で参照可能
    Point<T> a, b;

    /// @brief 既定値で直線を作る
    /// @complexity $O(1)$
    constexpr Line() : a(), b() {}
    /// @brief 2 点 `_a`, `_b` を通る直線を作る
    /// @complexity $O(1)$
    constexpr Line(const Point<T> &_a, const Point<T> &_b) : a(_a), b(_b) {}

    /// @brief 点 `p` が直線上にあれば true を返す
    /// @complexity $O(1)$
    constexpr bool in_line(Point<T> p) const { return eq(cross(p - a, p - b), 0); }

    /// @brief 点 `p` の直線への射影を返す
    /// @complexity $O(1)$
    constexpr Point<T> proj(const Point<T> &p) const { return a + (b - a) * dot(b - a, p - a) / norm(b - a); }
    /// @brief 点 `p` を直線に関して反転した点を返す
    /// @complexity $O(1)$
    constexpr Point<T> refl(const Point<T> &p) const { return this->proj(p) * 2 - p; }

    /// @brief 点 `p` と直線の距離を返す
    /// @complexity $O(1)$
    T dist(Point<T> p) { return abs(p - this->proj(p)); }
};

/// @brief 無効な点を表す番兵値
/// @complexity 変数テンプレートのため呼び出しコストなし
template <class T>
constexpr Point<T> PINF = Point<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
/// @brief 無効な直線を表す番兵値
/// @complexity 変数テンプレートのため呼び出しコストなし
template <class T>
constexpr Line<T> LINF = Line<T>(PINF<T>, PINF<T>);

/// @brief 2 直線 `a`, `b` が平行なら true を返す
/// @complexity $O(1)$
template <class T>
bool parallel(const Line<T> &a, const Line<T> &b) {
    return eq(cross(a.b - a.a, b.b - b.a), 0.0);
}
/// @brief 2 直線 `a`, `b` が直交するなら true を返す
/// @complexity $O(1)$
template <class T>
bool orthogonal(const Line<T> &a, const Line<T> &b) {
    return eq(dot(a.a - a.b, b.a - b.b), 0.0);
}
/// @brief 線分 `a`, `b` が交差するなら true を返す
/// @complexity $O(1)$
template <class T>
bool intersection(const Line<T> &a, const Line<T> &b) {
    return ccw(a.a, a.b, b.a) * ccw(a.a, a.b, b.b) <= 0 && ccw(b.a, b.b, a.a) * ccw(b.a, b.b, a.b) <= 0;
}
/// @brief 2 直線 `a`, `b` の交点を返す
/// @details 平行なら `PINF<T>`、一致するなら `a.a` を返す。
/// @complexity $O(1)$
template <class T>
Point<T> cross_point(const Line<T> &a, const Line<T> &b) {
    T d = cross(b.b - b.a, b.b - a.a);
    T e = cross(b.b - b.a, a.b - a.a);
    if (eq(d, 0) && eq(e, 0)) return a.a;
    if (eq(e, 0)) return PINF<T>;
    return a.a + (a.b - a.a) * d / e;
}

/// @brief 2 点 `p1`, `p2` の垂直二等分線を返す
/// @complexity $O(1)$
template <class T>
Line<T> perpendicular_bisector(Point<T> p1, Point<T> p2) {
    if (eq(p1, p2)) return LINF<T>;
    Point<T> m = (p1 + p2) / 2.0L, d = p2 - p1;
    return Line<T>(m, m + d * Point<T>(cos(PI / 2), sin(PI / 2)));
}

/// @brief 点 `p` を通り直線 `l` に垂直な直線を返す
/// @complexity $O(1)$
template <class T>
Line<T> vertical_line(Point<T> p, Line<T> l) {
    if (l.in_line(p)) return LINF<T>;
    return Line<T>(p, l.proj(p));
}

/// @brief 点 `p` を `center` の周りに `theta` ラジアン回転する
/// @complexity $O(1)$
template <class T>
Point<T> rotate(const Point<T> &p, const Point<T> &center, const double theta) {
    const Point<T> d = p - center;
    return center + d * Point<T>(cos(theta), sin(theta));
}

/// @brief 3 点 `p1`, `p2`, `p3` が作る三角形の面積を返す
/// @complexity $O(1)$
template <class T>
T triangle_area(Point<T> p1, Point<T> p2, Point<T> p3) {
    p1 -= p3;
    p2 -= p3;
    return abs(p1.x * p2.y + p1.y * p2.x) / 2;
}

/// @brief 二次元の円
/// @complexity 構築とフィールド参照は $O(1)$
template <class T>
struct Circle {
    /// @brief 円の中心
    /// @complexity $O(1)$ で参照可能
    Point<T> p;
    /// @brief 円の半径
    /// @complexity $O(1)$ で参照可能
    T r;

    /// @brief 既定値で円を作る
    /// @complexity $O(1)$
    constexpr Circle() : p(), r() {}
    /// @brief 中心 `_p`、半径 `_r` の円を作る
    /// @complexity $O(1)$
    constexpr Circle(Point<T> _p, T _r) : p(_p), r(_r) {}
};

/// @brief 2 円の位置関係を 0 から 4 の整数で返す
/// @details 内包は 0、内接は 1、2 交点は 2、外接は 3、離れていれば 4。
/// @complexity $O(1)$
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

/// @brief 2 円が 1 点以上で交わるなら true を返す
/// @complexity $O(1)$
template <class T>
bool intersect(Circle<T> c1, Circle<T> c2) {
    int tmp = checker(c1, c2);
    return tmp >= 1 && tmp <= 3;
}

/// @brief 2 円の交点を返す
/// @complexity $O(1)$
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

/// @brief 点集合 `ps` を覆う円を反復近似で求める
/// @param p 中心の初期値
/// @complexity $O(n\log(1/\mathrm{EPS}))$
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
