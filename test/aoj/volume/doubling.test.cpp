#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2320"
#include "algorithm/doubling.hpp"
#include <cstdint>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

int main(void) {
    while (true) {
        int h, w;
        std::int64_t l;
        std::cin >> h >> w >> l;
        if (!h && !w && !l) break;
        std::vector<std::string> s(h);
        std::copy_n(std::istream_iterator<std::string>(std::cin), h, s.begin());

        auto in_field = [h, w, s](int x, int y) {
            return 0 <= x && x < h && 0 <= y && y < w && s[x][y] != '#';
        };

        auto to_line = [h, w](int x, int y, int d) { return (x * w + y) * 4 + d; };

        std::vector<int> to(h * w * 4);
        std::iota(to.begin(), to.end(), 0);
        std::vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (!in_field(i, j)) continue;
                for (int k = 0; k < 4; ++k) {
                    for (int d = 0; d < 4; ++d) {
                        int nx = i + dx[(k + d) % 4];
                        int ny = j + dy[(k + d) % 4];
                        if (in_field(nx, ny)) {
                            to[to_line(i, j, k)] = to_line(nx, ny, (k + d) % 4);
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

        int ans = db.solve(to_line(x, y, d), l);
        x = ans / w / 4;
        ans %= w * 4;
        y = ans / 4;
        d = ans % 4;
        std::cout << x + 1 << ' ' << y + 1 << ' ' << dir[d] << std::endl;
    }

    return 0;
}
