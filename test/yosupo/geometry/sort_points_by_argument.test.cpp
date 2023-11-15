#define PROBLEM "https://judge.yosupo.jp/problem/sort_points_by_argument"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::tuple<int, int, long double>> v;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        v.emplace_back(x, y, std::atan2(y, x));
    }
    std::sort(v.begin(), v.end(), [&](auto x, auto y) { return get<2>(x) < get<2>(y); });
    for (auto &&[x, y, z] : v) std::cout << x << ' ' << y << '\n';

    return 0;
}
