#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>
#include "binary_tree/range_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    range_tree<Add<std::int64_t>> rt;
    std::vector<std::tuple<int, int, int>> points(n);
    for (auto &[x, y, z] : points) {
        std::cin >> x >> y >> z;
        rt.add(x, y);
    }
    std::vector<std::tuple<int, int, int, int, int>> queries(q);
    for (auto &[x, y, z, w, v] : queries) {
        std::cin >> x >> y >> z >> w;
        if (x == 0) rt.add(y, z);
        else std::cin >> v;
    }

    rt.build();
    for (auto [x, y, z] : points) rt.set(x, y, rt.get(x, y) + z);
    for (auto [x, y, z, w, v] : queries) {
        if (x == 0) rt.set(y, z, rt.get(y, z) + w);
        else std::cout << rt.prod(y, z, w, v) << '\n';
    }

    return 0;
}
