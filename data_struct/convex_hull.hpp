#include "_base.hpp"

// reference : http://www.prefield.com/algorithm/geometry/convex_hull.html
// verify : https://onlinejudge.u-aizu.ac.jp/problems/CGL_4_A

template <class T>
pair<T, T> &operator-=(pair<T, T> &a, const pair<T, T> &b) {
    a.first -= b.first, a.second -= b.second;
    return a;
}
template <class T>
vector<pair<T, T>> convex_hull(vector<pair<T, T>> ps) {
    int64_t n = ps.size(), k = 0;
    auto asc = [](pair<T, T> a, pair<T, T> b) {
        return a.first != b.first ? a.first < b.first : a.second < b.second;
    };
    sort(ps.begin(), ps.end(), asc);
    vector<pair<T, T>> ch(n << 1);
    auto cross = [](pair<T, T> a, pair<T, T> b, const pair<T, T> &c) {
        a -= c, b -= c;
        return a.first * b.second - a.second * b.first;
    };
    for (int64_t i = 0; i < n; ++i) {
        while (k > 1 && cross(ps[i], ch[k - 2], ch[k - 1]) < 0) --k;
        ch[k++] = ps[i];
    }
    for (int64_t i = n - 2, t = k; i >= 0; --i) {
        while (k > t && cross(ps[i], ch[k - 2], ch[k - 1]) < 0) --k;
        ch[k++] = ps[i];
    }
    ch.resize(k - 1);
    return ch;
}
