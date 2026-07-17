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

    Path add_vertex(Path d, Light l) const { return {d.b, d.c, (d.S + l.S), (d.sz + l.sz)}; }

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
    Graph<int> orig_g(n);
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> U[i] >> V[i] >> b[i] >> c[i];
        orig_g.add_edges(U[i], V[i], i);
    }

    std::vector<std::vector<int>> g(2 * n - 1);
    std::vector<int> q_bfs;
    q_bfs.push_back(0);
    std::vector<bool> vis(n, false);
    vis[0] = true;
    int head = 0;
    while (head < (int)q_bfs.size()) {
        int u = q_bfs[head++];
        for (auto &e : orig_g[u]) {
            int v = e.to();
            int idx = e.weight();
            if (!vis[v]) {
                vis[v] = true;
                q_bfs.push_back(v);
                g[u].push_back(n + idx);
                g[n + idx].push_back(u);
                g[n + idx].push_back(v);
                g[v].push_back(n + idx);
            }
        }
    }

    static_top_tree<std::vector<std::vector<int>>> stt(g, 0);
    DP dp_obj(n, a, b, c);
    static_top_tree_dp<std::vector<std::vector<int>>, DP> stt_dp(stt, dp_obj);

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
