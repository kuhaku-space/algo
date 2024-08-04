#pragma once
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <utility>
#include <vector>

/**
 * @brief 素数ライブラリ
 *
 * @tparam N
 */
template <int N = 1 << 22>
struct prime_number {
    prime_number() : is_not_prime(), data() { init(); }

    /**
     * @brief 素数判定
     *
     * @param n
     * @return bool
     */
    bool is_prime(std::int64_t n) const {
        assert(n >= 0);
        if (n < N) return !is_not_prime[n];
        for (auto i : data) {
            if ((std::int64_t)i * i > n) break;
            if (n % i == 0) return false;
        }
        return true;
    }

    std::vector<int> prime_numbers(int x) const {
        std::vector<int> res;
        for (auto i : data) {
            if (i > x) break;
            res.emplace_back(i);
        }
        return res;
    }

    /**
     * @brief 素因数分解
     *
     * @tparam T
     * @param x
     * @return std::vector<std::pair<T, int>>
     */
    template <class T>
    std::vector<std::pair<T, int>> prime_factorization(T x) const {
        if (x == 1) return std::vector<std::pair<T, int>>();
        std::vector<std::pair<T, int>> res;
        for (auto p : data) {
            int cnt = 0;
            for (; x % p == 0; x /= p) ++cnt;
            if (cnt) res.emplace_back(p, cnt);
            if ((std::int64_t)p * p > x) break;
        }
        if (x != 1) res.emplace_back(x, 1);
        return res;
    }

    /**
     * @brief 約数列挙
     *
     * @tparam T
     * @param x
     * @return std::vector<T>
     */
    template <class T>
    std::vector<T> divisors(T x) const {
        if (x == 1) return std::vector<T>(1, 1);
        auto v = prime_factorization(x);
        std::vector<T> res;
        res.emplace_back(1);
        for (auto p : v) {
            int n = res.size();
            res.resize(n * (p.second + 1));
            for (int i = 0; i < n * p.second; ++i) res[n + i] = res[i] * p.first;
            for (int i = 1; i <= p.second; ++i) {
                std::inplace_merge(res.begin(), res.begin() + n * i, res.begin() + n * (i + 1));
            }
        }
        return res;
    }

    /**
     * @brief 因数分解列挙
     *
     * @tparam T
     * @param x
     * @return std::vector<std::vector<T>>
     */
    template <class T>
    std::vector<std::vector<T>> factorization(T x) const {
        std::vector<std::vector<T>> res;
        auto f = [&](auto self, std::vector<T> v, T a) -> void {
            if (a == 1) res.emplace_back(v);
            for (auto i : this->divisors(a)) {
                if (i == 1 || (!v.empty() && v.back() > i)) continue;
                v.emplace_back(i);
                self(self, v, a / i);
                v.pop_back();
            }
        };
        f(f, std::vector<T>(), x);
        return res;
    }

  private:
    std::bitset<N> is_not_prime;
    std::vector<int> data;

    void init() {
        is_not_prime[0] = is_not_prime[1] = true;
        for (int i = 2; i < N; ++i) {
            if (!is_not_prime[i]) {
                data.emplace_back(i);
                if ((std::int64_t)i * i >= N) continue;
                if (i == 2) {
                    for (int j = i * i; j < N; j += i) is_not_prime[j] = true;
                } else {
                    for (int j = i * i; j < N; j += i << 1) is_not_prime[j] = true;
                }
            }
        }
    }
};
