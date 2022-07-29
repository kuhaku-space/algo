#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "binary_tree/fenwick_tree.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    fenwick_tree<ll> ft(a);
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == 0)
            ft.add(y, z);
        else
            co(ft.sum(y, z));
    }

    return 0;
}
