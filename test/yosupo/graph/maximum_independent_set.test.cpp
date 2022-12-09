#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#include "graph/maximum_independent_set.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, m;
    cin >> n >> m;
    Graph<void> g(n);
    g.input_edges(m, 0);

    auto ans = maximum_independent_set(g);
    co(ans.size());
    co(ans);

    return 0;
}
