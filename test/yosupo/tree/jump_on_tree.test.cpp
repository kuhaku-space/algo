#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n, q;
    cin >> n >> q;
    HLD hld(n);
    hld.input_edges(0);
    hld.build();

    while (q--) {
        int u, v, k;
        cin >> u >> v >> k;
        co(hld.jump(u, v, k));
    }

    return 0;
}
