#include "_base.hpp"

struct Doubling {
    const int _size = 64;
    int64_t n;
    vector<vector<int64_t>> data;

    Doubling(int64_t _n) : n(_n) {
        data.resize(_size);
        for (size_t i = 0; i < _size; ++i) {
            data[i].resize(n);
        }
    }

    void build(vector<int64_t> v) {
        for (int64_t i = 0; i < n; ++i) {
            data[0][i] = v[i];
        }
        
        for (int64_t i = 0; i < _size - 1; ++i) {
            for (int64_t j = 0; j < n; ++j) {
                data[i + 1][j] = data[i][data[i][j]];
            }
        }
    }

    int64_t solve(int64_t f, int64_t k) {
        int cnt = 0;
        while (k) {
            if (k & 1) f = data[cnt][f];
            k >>= 1;
            ++cnt;
        }
        return f;
    }
};
