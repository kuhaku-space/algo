#include "template/template.hpp"

/**
 * @brief ダブリング
 * 
 * @tparam L 
 */
template <int L>
struct Doubling {
    Doubling(int _n) : n(_n), data(L, std::vector<int>(_n)) {}

    void build(const std::vector<int> &v) {
        for (int i = 0; i < this->n; ++i) this->data[0][i] = v[i];

        for (int i = 0; i < L - 1; ++i) {
            for (int j = 0; j < this->n; ++j) {
                this->data[i + 1][j] = this->data[i][this->data[i][j]];
            }
        }
    }

    int solve(int f, int64_t k) {
        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
            if (k & 1) f = this->data[cnt][f];
        }
        return f;
    }

  private:
    int n;
    std::vector<std::vector<int>> data;
};
