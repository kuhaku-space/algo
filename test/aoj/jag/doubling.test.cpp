// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2320
#include "algorithm/doubling.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
#include "graph/grid.hpp"

int main(void) {
    while (true) {
        int h, w;
        std::int64_t l;
        std::cin >> h >> w >> l;
        if (!h && !w && !l) break;
        std::vector<std::string> s(h);
        for (auto &e : s) std::cin >> e;

        Grid<2> grid(h, w);
        auto in_grid = [&](int x, int y) { return grid.in_field(x, y) && s[x][y] != '#'; };
        auto flatten = [h, w](int x, int y, int d) { return (x * w + y) * 4 + d; };

        std::vector<int> to(h * w * 4);
        std::iota(to.begin(), to.end(), 0);
        std::vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (!in_grid(i, j)) continue;
                for (int k = 0; k < 4; ++k) {
                    for (int d = 0; d < 4; ++d) {
                        int nx = i + dx[(k + d) % 4];
                        int ny = j + dy[(k + d) % 4];
                        if (in_grid(nx, ny)) {
                            to[flatten(i, j, k)] = flatten(nx, ny, (k + d) % 4);
                            break;
                        }
                    }
                }
            }
        }

        std::string dir = "NESW";
        Doubling<64> db(to);
        int x, y, d;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                for (int k = 0; k < 4; ++k) {
                    if (s[i][j] == dir[k]) x = i, y = j, d = k;
                }
            }
        }

        int ans = db.solve(flatten(x, y, d), l);
        x = ans / w / 4;
        ans %= w * 4;
        y = ans / 4;
        d = ans % 4;
        std::cout << x + 1 << ' ' << y + 1 << ' ' << dir[d] << std::endl;
    }

    return 0;
}
