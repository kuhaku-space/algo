// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/4
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
#include "dp/subset_sum.hpp"

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &x : a) std::cin >> x;

    long long s = std::accumulate(a.begin(), a.end(), 0LL);
    bool ans = false;
    if (s % 2 == 0) {
        int c = static_cast<int>(s / 2);
        ans = subset_sum_all(a)[c];
        assert(ans == subset_sum(a, c));
    }
    std::cout << (ans ? "possible" : "impossible") << '\n';

    return 0;
}
