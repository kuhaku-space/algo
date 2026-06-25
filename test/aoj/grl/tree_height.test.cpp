// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_B
#include <algorithm>
#include <iostream>
#include <vector>
#include "graph/graph.hpp"
#include "tree/rerooting.hpp"

// 各頂点を根としたときの木の高さ（その頂点から最も遠い葉までの距離）。
// op = max、f = 辺重みを足す、g = 集約値をそのまま返す（頂点データは使わない）。
struct Monoid {
    using value_type = long long;
    static constexpr long long id() { return 0; }
    static constexpr long long op(long long a, long long b) { return std::max(a, b); }
    template <class W>
    static constexpr long long f(long long v, W w) {
        return v + w;
    }
    template <class U>
    static constexpr long long g(long long v, U) {
        return v;
    }
};

int main() {
    int n;
    std::cin >> n;
    list_graph<long long> g(n);
    g.input_edges(n - 1, 0);
    std::vector<int> data(n, 0);  // 頂点データは未使用（ダミー）
    Rerooting<Monoid, list_graph<long long>, int> rr(g, data);
    for (int i = 0; i < n; ++i) std::cout << rr[i] << '\n';
    return 0;
}
