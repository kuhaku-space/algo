// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2672
#include <cstdint>
#include <iostream>
#include <vector>
#include "linalg/xor_basis.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::uint64_t> a(n);
    std::uint64_t total = 0;
    for (auto &x : a) {
        std::cin >> x;
        total ^= x;
    }
    if (total != 0) {
        std::cout << "No\n";
        return 0;
    }
    XorBasis<std::uint64_t> xb;
    int rank = 0;
    for (auto x : a) rank += xb.insert(x);
    std::cout << (rank <= n - 2 ? "Yes" : "No") << '\n';

    return 0;
}
