#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include <iostream>
#include <iterator>
#include "binary_tree/fenwick_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::copy_n(std::istream_iterator<int>(std::cin), n, std::begin(a));
    fenwick_tree<std::int64_t> ft(a);
    while (q--) {
        int x, y, z;
        std::cin >> x >> y >> z;
        if (x == 0) ft.add(y, z);
        else std::cout << ft.sum(y, z) << std::endl;
    }

    return 0;
}
