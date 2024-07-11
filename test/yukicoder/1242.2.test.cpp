// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1242
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include "algorithm/doubling.hpp"

int main(void) {
    std::int64_t n;
    int k;
    std::cin >> n >> k;
    std::vector<std::int64_t> a(k);
    for (auto &e : a) std::cin >> e;
    std::reverse(a.begin(), a.end());
    std::vector<int> to(1 << 6);
    for (int bit = 0; bit < 1 << 6; ++bit) {
        int f = 0;
        for (int i = 0; i < 3; ++i) f |= (bit >> i & 1) && (bit >> (5 - i) & 1);
        to[bit] = ((bit << 1) | f) & ((1 << 6) - 1);
    }
    Doubling<60> db(to);
    int cur = 1;
    for (int i = 0; i < k - 1; ++i) {
        cur = db.solve(cur, a[i] - a[i + 1]);
        cur |= 1;
    }
    std::cout << ((db.solve(cur, a.back() - 1) & 1) ? "No\n" : "Yes\n");

    return 0;
}
