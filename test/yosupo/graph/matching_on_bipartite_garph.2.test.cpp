#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include "flow/hopcroft_karp.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int l, r, m;
    cin >> l >> r >> m;
    hopcroft_karp g(l, r);
    while (m--) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }
    co(g.matching());
    for (auto p : g.get_pairs()) co(p.first, p.second);

    return 0;
}
