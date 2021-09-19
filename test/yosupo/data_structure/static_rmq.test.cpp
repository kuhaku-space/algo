#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "template/atcoder.hpp"
#include "binary_tree/segment_tree.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    segment_tree st(n, Inf, [](auto a, auto b) { return min(a, b); });
    st.build(a);
    rep(i, q) {
        int l, r;
        cin >> l >> r;
        co(st.query(l, r));
    }

    return 0;
}
