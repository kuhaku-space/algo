#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
#include "template/atcoder.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<tuple<int, int, long double>> v;
    rep (i, n) {
        int x, y;
        cin >> x >> y;
        v.emplace_back(x, y, atan2l(y, x));
    }
    std::sort(v.begin(), v.end(), [&](auto x, auto y) {
        return get<2>(x) < get<2>(y);
    });
    for (auto &&[x, y, z] : v) co(x, y);

    return 0;
}
