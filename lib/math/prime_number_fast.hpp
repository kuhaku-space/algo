#include "lib/template/template.hpp"

struct prime_number {
    const int sz = 1 << 22;
    vector<int> factor;

    prime_number() { init(); }

    void init() {
        factor.resize(sz);
        iota(factor.begin(), factor.end(), 0);
        for (int i = 2; i < sz; ++i) {
            if (factor[i] < i) continue;
            if ((int64_t)i * i > sz) continue;
            for (int j = i * i; j < sz; j += i) {
                if (factor[j] == j) factor[j] = i;
            }
        }
    }

    bool is_prime(int x) {
        assert(0 <= x && x < sz);
        return factor[x] == x;
    }

    vector<int> prime_numbers(int x) {
        vector<int> res;
        for (int i = 2; i <= x; ++i) {
            if (is_prime(i)) res.emplace_back(i);
        }
        return res;
    }

    // 素因数分解
    vector<int> prime_factorization(int x) {
        vector<int> res;
        while (x > 1) {
            res.emplace_back(factor[x]);
            x /= factor[x];
        }
        return res;
    }
};
prime_number pn;
