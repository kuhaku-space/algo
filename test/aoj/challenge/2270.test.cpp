// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2270
#include <iostream>
#include <vector>
#include "algorithm/binary_search.hpp"
#include "algorithm/compress.hpp"
#include "data_structure/wavelet_matrix_rectangle_sum.hpp"
#include "graph/graph.hpp"
#include "tree/linear_lca.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (auto &e : a) std::cin >> e;
    Graph<void> g(n);
    g.input_edges(n - 1);
    coordinate_compression cps(a);
    a = cps.compress(a);
    std::vector<int> in(n), val(n * 2), w(n * 2);
    int c = 0;
    auto dfs = [&](auto self, int x, int p) -> void {
        in[x] = c;
        w[c] = 1;
        val[c++] = a[x];
        for (auto e : g[x]) {
            if (e.to() == p) continue;
            self(self, e.to(), x);
        }
        w[c] = -1;
        val[c++] = a[x];
    };
    dfs(dfs, 0, -1);
    linear_lca lca(g);
    wavelet_matrix_rectangle_sum<int, int, 18> wm(val, w);
    while (q--) {
        int u, v, k;
        std::cin >> u >> v >> k;
        --u, --v;
        auto f = [&](int y) {
            return wm.rect_sum(0, in[u] + 1, y) + wm.rect_sum(0, in[v] + 1, y) -
                       wm.rect_sum(0, in[lca(u, v)] + 1, y) - wm.rect_sum(0, in[lca(u, v)], y) <
                   k;
        };
        auto ans = meguru_binary_search(0, cps.size() + 1, f);
        std::cout << cps[ans] << '\n';
    }

    return 0;
}
