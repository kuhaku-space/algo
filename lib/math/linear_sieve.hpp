#pragma once
#include <array>
#include <cassert>
#include <vector>

/// @brief 線形篩
template <int N = (1 << 22)>
struct linear_sieve {
    linear_sieve() : lpf{}, pr() { build(); }

    bool is_prime(int x) {
        assert(1 <= x && x <= N);
        return lpf[x] == x;
    }

    std::vector<int> prime_factorization(int x) {
        assert(1 <= x && x <= N);
        std::vector<int> res;
        while (x > 1) {
            res.emplace_back(lpf[x]);
            x /= lpf[x];
        }
        return res;
    }

  private:
    std::array<int, N + 1> lpf;
    std::vector<int> pr;

    void build() {
        for (int i = 2; i <= N; ++i) {
            if (lpf[i] == 0) {
                lpf[i] = i;
                pr.emplace_back(i);
            }
            for (int j = 0; i * pr[j] <= N; ++j) {
                lpf[i * pr[j]] = pr[j];
                if (pr[j] == lpf[i]) break;
            }
        }
    }
};
