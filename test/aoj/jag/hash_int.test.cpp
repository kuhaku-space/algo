// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2971
#include <iostream>
#include "math/hashint.hpp"
#include "data_structure/potentialized_union_find.hpp"

/// HashInt の乗法群（単位元 1・合成 `*`・逆元 `inv()`）としての薄いラッパ
struct S {
    HashInt x;

    constexpr S() : x(1) {}
    constexpr S(HashInt x) : x(x) {}

    constexpr S operator*(const S &rhs) const noexcept { return S(x * rhs.x); }
    constexpr S inv() const noexcept { return S(x.inv()); }

    constexpr bool operator==(const S &rhs) const noexcept { return x == rhs.x; }
    constexpr bool operator!=(const S &rhs) const noexcept { return x != rhs.x; }
};

int main(void) {
    int n, m;
    std::cin >> n >> m;
    potentialized_union_find<S> uf(n);
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
