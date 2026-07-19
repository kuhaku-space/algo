// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/3354
#include <cstdint>
#include <iostream>
#include "math/fraction.hpp"

int main(void) {
    std::int64_t n1, d1, n2, d2;
    std::cin >> n1 >> d1 >> n2 >> d2;
    Fraction p(n1, d1), q(n2, d2);
    if (p < q) {
        std::cout << '<' << '\n';
    } else if (p > q) {
        std::cout << '>' << '\n';
    } else {
        std::cout << '=' << '\n';
    }

    return 0;
}
