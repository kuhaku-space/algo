#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree"
#include "template/atcoder.hpp"
#include "tree/cartesian_tree.hpp"

int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    auto ans = cartesian_tree(a);
    rep (i, n) {
        if (ans[i] == -1) ans[i] = i;
    }
    co(ans);

    return 0;
}
