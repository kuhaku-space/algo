#define IGNORE
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2429"
#include "flow/min_cost_flow.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

int main(void) {
    int n;
    std::cin >> n;
    std::vector w(n, std::vector(n, 0));
    std::vector e(n, std::vector(n, 0));
    for (auto &v : w) {
        for (auto &x : v) std::cin >> x;
    }
    for (auto &v : e) {
        for (auto &x : v) std::cin >> x;
    }
    std::vector<std::string> f(n);
    for (auto &s : f) std::cin >> s;

    mcf_graph<int, int> mcf(n * 2 + 2);
    int st = n * 2, gl = st + 1;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (f[i][j] == 'o') {
                ans += e[i][j];
                mcf.add_edge(i, n + j, 1, 1000 - e[i][j]);
            } else {
                mcf.add_edge(i, n + j, 1, 1000 + w[i][j]);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        mcf.add_edge(st, i, 1, 0);
        mcf.add_edge(n + i, gl, 1, 0);
    }

    int c = mcf.flow(st, gl).second;
    std::cout << ans + c - 1000 * n << '\n';
    std::vector<std::tuple<int, int, std::string>> ops;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (f[i][j] == 'o') {
                if (mcf.get_edge(i * n + j).flow == 0) ops.emplace_back(i + 1, j + 1, "erase");
            } else {
                if (mcf.get_edge(i * n + j).flow) ops.emplace_back(i + 1, j + 1, "write");
            }
        }
    }
    std::cout << ops.size() << '\n';
    for (auto [x, y, s] : ops) std::cout << x << ' ' << y << ' ' << s << '\n';

    return 0;
}
