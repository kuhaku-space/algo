#include "template/template.hpp"

struct prime_number {
    static constexpr int sz = 1 << 22;
    array<int, sz> factor;

    prime_number() { init(); }

    void init() {
        iota(factor.begin(), factor.end(), 0);
        for (int i = 2; i < sz; ++i) {
            if (factor[i] < i) continue;
            if ((int64_t)i * i > sz) continue;
            for (int j = i * i; j < sz; j += i) {
                if (factor[j] == j) factor[j] = i;
            }
        }
    }

    bool is_prime(int x) const {
        assert(0 <= x && x < sz);
        return this->factor[x] == x;
    }

    vector<int> prime_numbers(int x) const {
        if (x < 2) return vector<int>();
        vector<int> res = {2};
        for (int i = 3; i <= x; i += 2) {
            if (this->is_prime(i)) res.emplace_back(i);
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
