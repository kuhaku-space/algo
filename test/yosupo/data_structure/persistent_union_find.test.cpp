#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"
#include "template/atcoder.hpp"
#include "tree/persistent_union_find.hpp"

int main(void) {
    sonic();
    int n, q;
    cin >> n >> q;
    vector<persistent_union_find> ufs;
    ufs.emplace_back(n);

    rep (i, q) {
        int t, k, u, v;
        cin >> t >> k >> u >> v;
        if (t == 0) {
            ufs.emplace_back(ufs[k + 1].unite(u, v));
        } else {
            co(ufs[k + 1].same(u, v));
            ufs.emplace_back();
        }
    }

    return 0;
}
