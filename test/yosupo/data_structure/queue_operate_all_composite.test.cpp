#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include <iostream>
#include "data_structure/swag.hpp"
#include "math/modint.hpp"

using Mint = modint998;

int main(void) {
    int q;
    std::cin >> q;
    sliding_window_aggregation<Affine<Mint>> swag;
    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            int a, b;
            std::cin >> a >> b;
            swag.emplace({a, b});
        } else if (c == 1) {
            swag.pop();
        } else {
            int x;
            std::cin >> x;
            auto p = swag.top();
            std::cout << (p.first * x + p.second) << '\n';
        }
    }

    return 0;
}
