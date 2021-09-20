#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "binary_tree/BIT.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    BIT<ll> bit(n);
    bit.build(a);
    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;
        if (x == 0)
            bit.add(y, z);
        else
            co(bit.sum(y, z));
    }

    return 0;
}
