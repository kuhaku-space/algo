#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"
#include "template/atcoder.hpp"
#include "tree/hld.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    Graph<void> g(n);
    g.input_edges(n - 1, 0);
    HLD hld(g);
    while (q--) {
        int u, v, k;
        std::cin >> u >> v >> k;
        co(hld.jump(u, v, k));
    }

    return 0;
}
