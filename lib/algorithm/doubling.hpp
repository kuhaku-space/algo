#pragma once
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

/// @brief ダブリング
template <int L = 20, class M = void>
struct doubling {
  private:
    using T = typename M::value_type;

  public:
    template <class U>
    doubling(const std::vector<int> &to, const std::vector<U> &v) : doubling(to.size()) {
        build(to, v);
    }
    std::pair<int, T> jump(int f, std::uint64_t k) { return solve(f, k); }
    std::pair<int, T> solve(int f, std::uint64_t k) {
        assert(-1 <= f && f < _size);
        T res = M::id();
        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
            if ((k & 1) && f != -1) {
                res = M::op(res, data[cnt][f]);
                f = table[cnt][f];
            }
        }
        return std::make_pair(f, res);
    }

  private:
    int _size;
    std::vector<std::vector<int>> table;
    std::vector<std::vector<T>> data;

    doubling(int n) : _size(n), table(L, std::vector<int>(n)), data(L, std::vector<T>(n)) {}

    template <class U>
    void build(const std::vector<int> &to, const std::vector<U> &v) {
        assert(to.size() == v.size());
        for (int i = 0; i < _size; ++i) {
            assert(-1 <= to[i] && to[i] < _size);
            table[0][i] = to[i];
            data[0][i] = v[i];
        }

        for (int i = 0; i < L - 1; ++i) {
            for (int j = 0; j < _size; ++j) {
                int k = table[i][j];
                if (k != -1) {
                    table[i + 1][j] = table[i][k];
                    data[i + 1][j] = M::op(data[i][j], data[i][k]);
                } else {
                    table[i + 1][j] = table[i][j];
                    data[i + 1][j] = data[i][j];
                }
            }
        }
    }
};

/// @brief ダブリング
template <int L>
struct doubling<L, void> {
    doubling(const std::vector<int> &v) : doubling(v.size()) { build(v); }

    int jump(int f, std::uint64_t k) { return solve(f, k); }
    int solve(int f, std::uint64_t k) {
        assert(-1 <= f && f < _size);
        for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
            if ((k & 1) && f != -1) f = table[cnt][f];
        }
        return f;
    }

  private:
    int _size;
    std::vector<std::vector<int>> table;

    doubling(int n) : _size(n), table(L, std::vector<int>(n)) {}

    void build(const std::vector<int> &v) {
        for (int i = 0; i < _size; ++i) {
            assert(-1 <= v[i] && v[i] < _size);
            table[0][i] = v[i];
        }

        for (int i = 0; i < L - 1; ++i) {
            for (int j = 0; j < _size; ++j) {
                if (table[i][j] != -1) table[i + 1][j] = table[i][table[i][j]];
            }
        }
    }
};
