#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
#include "graph/two_sat.hpp"
#include "template/atcoder.hpp"

int main(void) {
    string tmp;
    int n, m;
    cin >> tmp >> tmp >> n >> m;
    two_sat ts(n);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        bool f = true, g = true;
        if (a < 0) {
            a = -a;
            f = false;
        }
        if (b < 0) {
            b = -b;
            g = false;
        }
        ts.add(a - 1, f, b - 1, g);
    }
    auto v = ts.solve();
    if (!ts.is_satisfy(v)) {
        co("s UNSATISFIABLE");
        return 0;
    }
    co("s SATISFIABLE");
    auto u = ts.build(v);
    vector<int> ans(n);
    rep (i, n) {
        if (u[i]) ans[i] = i + 1;
        else ans[i] = -i - 1;
    }
    co('v', ans, 0);

    return 0;
}
