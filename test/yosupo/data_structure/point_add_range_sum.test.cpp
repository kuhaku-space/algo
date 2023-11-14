#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include <iostream>
#include "binary_tree/fenwick_tree.hpp"
#include "template/sonic.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    fenwick_tree<std::int64_t> ft(a);
    while (q--) {
        int x, y, z;
        std::cin >> x >> y >> z;
        if (x == 0) ft.add(y, z);
        else std::cout << ft.sum(y, z) << '\n';
    }

    return 0;
}
