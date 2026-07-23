// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1242
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>
#include "algorithm/doubling.hpp"
#include "graph/functional_graph.hpp"

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
    functional_graph fg(to);
    doubling<60> db(to);
    int cur = 1, cur_db = 1;
    for (int i = 0; i < k - 1; ++i) {
        cur = fg.jump(cur, a[i] - a[i + 1]);
        cur |= 1;
        cur_db = db.solve(cur_db, a[i] - a[i + 1]);
        cur_db |= 1;
        assert(cur == cur_db);
    }
    int last = fg.jump(cur, a.back() - 1);
    assert(last == db.solve(cur_db, a.back() - 1));
    std::cout << ((last & 1) ? "No\n" : "Yes\n");

    return 0;
}
