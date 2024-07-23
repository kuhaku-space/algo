// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1208
#include "tree/stern_brocot_tree.hpp"
#include <cstdint>
#include <iostream>

int main(void) {
    while (true) {
        int n, p;
        std::cin >> p >> n;
        if (n == 0 && p == 0) break;
        int u, v, x, y;
        auto f = [&](std::int64_t a, std::int64_t b) -> bool {
            bool f = a * a < b * b * p;
            if (f) u = a, v = b;
            else x = a, y = b;
            return f;
        };
        stern_brocot_tree sbt;
        while (true) {
            auto [s, t] = sbt.get();
            if (s > n || t > n) break;
            if (f(s, t)) sbt = sbt.get_right();
            else sbt = sbt.get_left();
        }

        std::cout << x << "/" << y << " " << u << "/" << v << '\n';
    }

    return 0;
}
