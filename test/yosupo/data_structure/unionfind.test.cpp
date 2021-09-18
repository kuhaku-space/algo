#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include "template/template.hpp"
#include "tree/union_find.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    union_find uf(n);
    for (int i = 0; i < q; ++i) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 0)
            uf.unite(u, v);
        else
            cout << uf.same(u, v) << endl;
    }

    return 0;
}
