// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum
#include <iostream>
#include <vector>
#include "math/modint.hpp"
#include "tree/dynamic_top_tree.hpp"

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

    std::vector<int> U(n - 1), V(n - 1);
    std::vector<Mint> b(n - 1), c(n - 1);
    for (int i = 0; i < n - 1; ++i) std::cin >> U[i] >> V[i] >> b[i] >> c[i];

    DP dp_obj(n, a, b, c);
    DynamicTopTree<DP> dtt(2 * n - 1, dp_obj);
    for (int i = 0; i < n - 1; ++i) {
        dtt.link(n + i, U[i]);
        dtt.link(n + i, V[i]);
    }

    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int w, r;
            long long x;
            std::cin >> w >> x >> r;
            a[w] = x;
            dtt.update(w);
            std::cout << dtt.query(r).S << "\n";
        } else {
            int idx, r;
            long long y, z;
            std::cin >> idx >> y >> z >> r;
            b[idx] = y;
            c[idx] = z;
            dtt.update(n + idx);
            std::cout << dtt.query(r).S << "\n";
        }
    }

    return 0;
}
