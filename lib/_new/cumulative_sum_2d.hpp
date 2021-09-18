#include "lib/template/template.hpp"

template <class T>
struct cumulative_sum_2d {
    vector<vector<T>> v;

    cumulative_sum_2d(const vector<vector<T>> &_v) : v(_v) { make(); }

    void make() {
        int n = v.size();
        int m = v[0].size();
        v.resize(n + 1);
        for (int i = 0; i < n; ++i) v[i].resize(m + 1);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                v[i][j] += v[i + 1][j];
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                v[i][j] += v[i][j + 1];
            }
        }
    }

    T get(int x1, int y1, int x2, int y2) {
        return v[x1][y1] - v[x1][y2] - v[x2][y1] + v[x2][y2];
    }
};
