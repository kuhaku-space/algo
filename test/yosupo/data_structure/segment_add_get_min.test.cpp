#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"
#include <cstdint>
#include <iostream>
#include "data_structure/li_chao_tree.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    li_chao_tree lct(-Inf, Inf);
    while (n--) {
        std::int64_t l, r, a, b;
        std::cin >> l >> r >> a >> b;
        lct.add_segment(a, b, l, r);
    }

    while (q--) {
        int c;
        std::cin >> c;
        if (c == 0) {
            std::int64_t l, r, a, b;
            std::cin >> l >> r >> a >> b;
            lct.add_segment(a, b, l, r);
        } else {
            std::int64_t x;
            std::cin >> x;
            auto ans = lct.query(x);
            if (ans == lct.inf) std::cout << "INFINITY\n";
            else std::cout << ans << '\n';
        }
    }

    return 0;
}
