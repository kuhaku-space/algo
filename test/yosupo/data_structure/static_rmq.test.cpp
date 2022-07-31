#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "data_structure/sparse_table.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    sparse_table<Min<int>> st(a);

    while (q--) {
        int l, r;
        cin >> l >> r;
        co(st.prod(l, r));
    }

    return 0;
}
