#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2320"
#include "algorithm/doubling.hpp"
#include "template/atcoder.hpp"

int main(void) {
    while (true) {
        int h, w;
        ll l;
        cin >> h >> w >> l;
        if (!h && !w && !l) break;
        vector<string> s(h);
        cin >> s;

        auto in_field = [h, w, s](int x, int y) {
            return 0 <= x && x < h && 0 <= y && y < w && s[x][y] != '#';
        };

        auto to_line = [h, w](int x, int y, int d) {
            return (x * w + y) * 4 + d;
        };

        vector<int> to(h * w * 4);
        iota(all(to), 0);
        vector<int> dx = {-1, 0, 1, 0}, dy = {0, 1, 0, -1};
        rep (i, h) {
            rep (j, w) {
                if (!in_field(i, j)) continue;
                rep (k, 4) {
                    rep (d, 4) {
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

        string dir = "NESW";
        Doubling<64> db(to);
        int x, y, d;
        rep (i, h) {
            rep (j, w) {
                rep (k, 4) {
                    if (s[i][j] == dir[k]) x = i, y = j, d = k;
                }
            }
        }

        int ans = db.solve(to_line(x, y, d), l);
        x = ans / w / 4;
        ans %= w * 4;
        y = ans / 4;
        d = ans % 4;
        co(x + 1, y + 1, dir[d]);
    }

    return 0;
}
