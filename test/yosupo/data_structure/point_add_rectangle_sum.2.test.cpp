#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "segment_tree/segment_tree_2d.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    segment_tree_2d<Add<ll>> st(Inf, Inf);
    while (n--) {
        int x, y, w;
        std::cin >> x >> y >> w;
        st.set(x, y, st.get(x, y) + w);
    }
    while (q--) {
        int com;
        std::cin >> com;
        if (com == 0) {
            int x, y, w;
            std::cin >> x >> y >> w;
            st.set(x, y, st.get(x, y) + w);
        } else {
            int l, d, r, u;
            std::cin >> l >> d >> r >> u;
            co(st.prod(l, r, d, u));
        }
    }

    return 0;
}
