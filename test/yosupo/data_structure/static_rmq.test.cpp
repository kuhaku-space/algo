#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#include "segment_tree/segment_tree.hpp"
#include "template/atcoder.hpp"

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
        co(st.prod(l, r));
    }

    return 0;
}
