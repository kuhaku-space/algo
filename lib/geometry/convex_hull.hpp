#include "template/template.hpp"

/**
 * @brief 点
 *
 * @tparam T 座標の型
 */
template <class T>
struct Point {
    T x, y;

    constexpr Point() : x(), y() {}
    constexpr Point(T _x, T _y) : x(_x), y(_y) {}

    constexpr Point &operator-=(const Point &rhs) {
        this->x -= rhs.x, this->y -= rhs.y;
        return *this;
    }

    friend std::istream &operator>>(std::istream &is, Point &rhs) {
        T x, y;
        is >> x >> y;
        rhs = Point(x, y);
        return (is);
    }
};

/**
 * @brief 凸法
 *
 * @tparam T 座標の型
 * @param points 点集合
 * @return std::vector<Point<T>>
 */
template <class T>
std::vector<Point<T>> convex_hull(std::vector<Point<T>> points) {
    int n = points.size(), k = 0;
    sort(points.begin(), points.end(), [](const Point<T> &a, const Point<T> &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    });
    std::vector<Point<T>> res(n << 1);
    auto cross = [](Point<T> a, Point<T> b, const Point<T> &c) {
        a -= c, b -= c;
        return a.x * b.y - a.y * b.x;
    };
    for (int i = 0; i < n; ++i) {
        while (k > 1 && cross(points[i], res[k - 2], res[k - 1]) < 0) --k;
        res[k++] = points[i];
    }
    for (int i = n - 2, t = k; i >= 0; --i) {
        while (k > t && cross(points[i], res[k - 2], res[k - 1]) < 0) --k;
        res[k++] = points[i];
    }
    res.resize(k - 1);
    return res;
}
