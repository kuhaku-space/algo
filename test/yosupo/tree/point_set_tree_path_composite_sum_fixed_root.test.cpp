// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root
#include <iostream>
#include <vector>
#include "graph/graph.hpp"
#include "math/modint.hpp"
#include "tree/static_top_tree.hpp"

using Mint = modint998;

struct DP {
    struct Path {
        Mint b, c, S, sz;
    };
    struct Light {
        Mint S, sz;
    };

    int n;
    const std::vector<Mint> &A;
    const std::vector<Mint> &B;
    const std::vector<Mint> &C;

    DP(int n, const std::vector<Mint> &A, const std::vector<Mint> &B, const std::vector<Mint> &C)
        : n(n), A(A), B(B), C(C) {}

    Path vertex(int u) const {
        if (u < n) {
            return {1, 0, A[u], 1};
        } else {
            return {B[u - n], C[u - n], 0, 0};
        }
    }

    Path add_vertex(Path d, Light l) const { return {d.b, d.c, (d.b * l.S + d.c * l.sz + d.S), (d.sz + l.sz)}; }

    Light add_edge(Path d) const { return {d.S, d.sz}; }

    Light rake(Light l, Light r) const { return {(l.S + r.S), (l.sz + r.sz)}; }

    Path compress(Path p, Path c) const {
        Mint nb = p.b * c.b;
        Mint nc = (p.b * c.c + p.c);
        Mint nS = (p.b * c.S + p.c * c.sz + p.S);
        Mint nsz = (c.sz + p.sz);
        return {nb, nc, nS, nsz};
    }
};

int main() {
    int n, q;
    std::cin >> n >> q;

    std::vector<Mint> a(n);
    for (auto &e : a) std::cin >> e;

    std::vector<Mint> b(n - 1), c(n - 1);
    list_graph<void> g(2 * n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v >> b[i] >> c[i];
        g.add_edges(u, n + i);
        g.add_edges(n + i, v);
    }

    static_top_tree<list_graph<void>> stt(g, 0);
    DP dp_obj(n, a, b, c);
    static_top_tree_dp<list_graph<void>, DP> stt_dp(stt, dp_obj);

    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int w;
            long long x;
            std::cin >> w >> x;
            a[w] = x;
            stt_dp.update(w);
            std::cout << stt_dp.get().S << "\n";
        } else {
            int idx;
            long long y, z;
            std::cin >> idx >> y >> z;
            b[idx] = y;
            c[idx] = z;
            stt_dp.update(n + idx);
            std::cout << stt_dp.get().S << "\n";
        }
    }

    return 0;
}
