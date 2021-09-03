#include "_base.hpp"

struct prime_number {
    const int sz = 1 << 22;
    bitset<1 << 22> is_not_prime;
    vector<int> data;

    prime_number() { init(); }

    void init() {
        is_not_prime[0] = is_not_prime[1] = true;
        for (int i = 2; i < sz; ++i) {
            if (!is_not_prime[i]) {
                data.emplace_back(i);
                if ((int64_t)i * i >= sz) continue;
                for (int j = i * i; j < sz; j += i) {
                    is_not_prime[j] = true;
                }
            }
        }
    }

    bool is_prime(int64_t n) {
        assert(n >= 0);
        if (n < sz) return !is_not_prime[n];
        for (auto i : data) {
            if ((int64_t)i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    vector<int> prime_numbers(int x) {
        vector<int> res;
        for (auto i : data) {
            if (i > x) break;
            res.emplace_back(i);
        }
        return res;
    }

    // 素因数分解
    template <class T>
    vector<pair<T, int>> prime_factorization(T x) {
        if (x == 1) return vector<pair<T, int>>(1, {1, 1});
        vector<pair<T, int>> res;
        for (auto i : data) {
            int cnt = 0;
            for (; x % i == 0; x /= i) ++cnt;
            if (cnt) res.emplace_back(i, cnt);
            if ((int64_t)i * i > x) break;
        }
        if (x != 1) res.emplace_back(x, 1);
        return res;
    }

    // 約数列挙
    template <class T>
    vector<T> divisors(T x) {
        auto v = this->prime_factorization(x);
        vector<T> res, a, b, cp;
        res.emplace_back(1);
        for (auto p : v) {
            int n = res.size();
            cp.resize(n);
            copy(res.begin(), res.end(), cp.begin());
            a.resize(n);
            T t = 1;
            for (int k = 0; k < p.second; ++k) {
                t *= p.first;
                for (int i = 0; i < n; ++i) a[i] = cp[i] * t;
                merge(res.begin(), res.end(), a.begin(), a.end(),
                      back_inserter(b));
                swap(res, b);
                b.clear();
            }
        }
        return res;
    }

    // 因数分解列挙
    template <class T>
    vector<vector<T>> factorization(T x) {
        vector<vector<T>> res;
        auto f = [&](auto self, vector<T> v, T a) -> void {
            if (a == 1) res.emplace_back(v);
            for (auto i : divisors(a)) {
                if (i == 1 || (!v.empty() && v.back() > i)) continue;
                v.emplace_back(i);
                self(self, v, a / i);
                v.pop_back();
            }
        };
        f(f, vector<T>(), x);
        return res;
    }
};
prime_number pn;
