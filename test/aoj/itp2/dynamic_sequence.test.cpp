// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ITP2_1_B
#include "data_structure/dynamic_sequence.hpp"
#include "segment_tree/monoid.hpp"
#include "template/atcoder.hpp"

struct Monoid {
    using T = int;
    using value_type = T;
    static constexpr T id() { return 0; }
    static constexpr T op(const T &lhs, const T &rhs) { return lhs; }
};

int main(void) {
    int q;
    std::cin >> q;
    dynamic_sequence<Monoid> ds;
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            int d, x;
            std::cin >> d >> x;
            if (d == 0) ds.insert(0, x);
            else ds.insert(ds.size(), x);
        } else if (t == 1) {
            int p;
            std::cin >> p;
            std::cout << ds.get(p) << '\n';
        } else {
            int d;
            std::cin >> d;
            if (d == 0) ds.erase(0);
            else ds.erase(ds.size() - 1);
        }
    }

    return 0;
}
