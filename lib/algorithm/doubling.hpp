#include "template/template.hpp"

/**
 * @brief ダブリング
 *
 * @tparam L
 */
template <int L>
struct Doubling {
    Doubling(int n) : _size(n), data(L, std::vector<int>(n)) {}
    Doubling(const std::vector<int> &v) : _size(v.size()), data(L, std::vector<int>(v.size())) {
        this->build(v);
    }

    void build(const std::vector<int> &v) {
        for (int i = 0; i < this->_size; ++i) {
            assert(0 <= v[i] && v[i] < this->_size);
            this->data[0][i] = v[i];
        }

        for (int i = 0; i < L - 1; ++i) {
            for (int j = 0; j < this->_size; ++j) {
                this->data[i + 1][j] = this->data[i][this->data[i][j]];
            }
        }
    }

    int solve(int f, std::int64_t k) {
        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
            if (k & 1) f = this->data[cnt][f];
        }
        return f;
    }

  private:
    int _size;
    std::vector<std::vector<int>> data;
};
