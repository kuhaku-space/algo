// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2971
#include <iostream>
#include "math/hashint.hpp"
#include "tree/weighted_union_find.hpp"

struct S {
    HashInt x;

    constexpr S() : x(1) {}
    constexpr S(HashInt x) : x(x) {}

    constexpr S &operator+=(const S &rhs) noexcept {
        x *= rhs.x;
        return *this;
    }
    constexpr S &operator-=(const S &rhs) noexcept {
        x /= rhs.x;
        return *this;
    }

    constexpr S operator-() const noexcept { return S(x.inverse()); }
    constexpr S operator+(const S &rhs) const noexcept { return S(*this) += rhs; }
    constexpr S operator-(const S &rhs) const noexcept { return S(*this) -= rhs; }

    constexpr bool operator==(const S &rhs) const noexcept { return x == rhs.x; }
    constexpr bool operator!=(const S &rhs) const noexcept { return x != rhs.x; }
};

int main(void) {
    int n, m;
    std::cin >> n >> m;
    weighted_union_find<S> uf(n);
    while (m--) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        if (uf.same(u, v)) {
            if (uf.diff(u, v) != S(w)) {
                std::cout << "No\n";
                return 0;
            }
        } else {
            uf.unite(u, v, S(w));
        }
    }
    std::cout << "Yes\n";

    return 0;
}
