// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/line_add_get_min
#include <cstdint>
#include <iostream>
#include "data_structure/li_chao_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    li_chao_tree lct(-1000000000, 1000000001);
    while (n--) {
        std::int64_t a, b;
        std::cin >> a >> b;
        lct.add_line(a, b);
    }

    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            std::int64_t a, b;
            std::cin >> a >> b;
            lct.add_line(a, b);
        } else {
            std::int64_t x;
            std::cin >> x;
            std::cout << lct.query(x) << '\n';
        }
    }

    return 0;
}
