#define PROBLEM "https://judge.yosupo.jp/problem/addition_of_big_integers"
#include "data_structure/bigint.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int t;
    std::cin >> t;
    while (t--) {
        BigInt a, b;
        std::cin >> a >> b;
        co(a + b);
    }

    return 0;
}
