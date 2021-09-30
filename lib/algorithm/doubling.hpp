#include "template/template.hpp"

struct Doubling {
    const int size = 64;
    int n;
    vector<vector<int>> data;

    Doubling(int _n) : n(_n), data(size, vector<int>(_n)) {}

    void build(const vector<int> &v) {
        for (int i = 0; i < n; ++i) data[0][i] = v[i];

        for (int i = 0; i < size - 1; ++i) {
            for (int j = 0; j < n; ++j) {
                data[i + 1][j] = data[i][data[i][j]];
            }
        }
    }

    int solve(int f, int64_t k) {
        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
            if (k & 1) f = data[cnt][f];
        }
        return f;
    }
};
