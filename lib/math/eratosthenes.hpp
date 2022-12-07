#include "template/template.hpp"

template <int N = (1 << 22)>
struct eratosthenes {
    constexpr eratosthenes() : prime_number() {
        this->prime_number.set();
        this->prime_number[0] = this->prime_number[1] = false;
        for (int i = 2; i <= N; ++i) {
            if (!this->prime_number[i]) continue;
            if ((std::int64_t)i * i > N) continue;
            for (int j = i * i; j <= N; j += i) {
                if (this->prime_number[j]) this->prime_number[j] = false;
            }
        }
    }

    bool is_prime(int x) const {
        return this->prime_number[x];
    }

    std::vector<int> prime_numbers(int x) const {
        if (x < 2) return std::vector<int>();
        std::vector<int> res = {2};
        for (int i = 3; i <= x; i += 2) {
            if (this->is_prime(i)) res.emplace_back(i);
        }
        return res;
    }

  private:
    std::bitset<N + 1> prime_number;
};
