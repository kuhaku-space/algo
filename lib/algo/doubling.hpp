#include "_base.hpp"

struct Doubling {
    const int size = 64;
    int64_t n;
    vector<vector<int64_t>> data;

    Doubling(int64_t _n) : n(_n) {
        data = vector<vector<int64_t>>(size, vector<int64_t>(n));
    }

    void build(const vector<int64_t> &v) {
        for (int64_t i = 0; i < n; ++i) data[0][i] = v[i];

        for (int64_t i = 0; i < size - 1; ++i) {
            for (int64_t j = 0; j < n; ++j) {
                data[i + 1][j] = data[i][data[i][j]];
            }
        }
    }

    int64_t solve(int64_t f, int64_t k) {
        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
            if (k & 1) f = data[cnt][f];
        }
        return f;
    }
};
