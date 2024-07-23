// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1036
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>
#include "data_structure/swag.hpp"

template <class T>
struct Gcd {
    using value_type = T;
    static constexpr T id() { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) {
        return lhs == Gcd::id() ? rhs : (rhs == Gcd::id() ? lhs : std::gcd(lhs, rhs));
    }
};

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::int64_t> a(n);
    for (std::int64_t &e : a) std::cin >> e;

    sliding_window_aggregation<Gcd<std::int64_t>> swag;
    std::int64_t ans = 0;
    for (int i = 0; i < n; ++i) {
        swag.emplace(a[i]);
        while (!swag.empty() && swag.fold() == 1) swag.pop();
        ans += i + 1 - swag.size();
    }
    std::cout << ans << '\n';

    return 0;
}
