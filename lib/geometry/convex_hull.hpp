#pragma once
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include "geometry/geometry.hpp"

/// @brief 二次元点集合の凸包を構築する
/// @details monotone chainにより、凸包上の点を巡回順で返す。
/// @tparam T 座標の型
/// @param points 点集合
/// @return 凸包上の点列
/// @complexity 点数を $n$ として $O(n\log n)$
template <class T>
std::vector<Point<T>> convex_hull(std::vector<Point<T>> points) {
    int n = points.size(), k = 0;
    std::sort(std::begin(points), std::end(points),
              [](const Point<T> &a, const Point<T> &b) { return a.x == b.x ? a.y < b.y : a.x < b.x; });
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
