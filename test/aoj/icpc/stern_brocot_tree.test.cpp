#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/1208"
#include "tree/stern_brocot_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    while (true) {
        int n, p;
        cin >> p >> n;
        if (n == 0 && p == 0) break;
        int u, v, x, y;
        auto f = [&](ll a, ll b) -> bool {
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

        cout << x << "/" << y << " " << u << "/" << v << endl;
    }

    return 0;
}
