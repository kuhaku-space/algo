// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/DPL_3_B
#include <algorithm>
#include <iostream>
#include <vector>
#include "algorithm/largest_rectangle.hpp"

int main(void) {
    int h, w;
    std::cin >> h >> w;
    std::vector<int> height(w, 0);
    long long ans = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int x;
            std::cin >> x;
            height[j] = x == 0 ? height[j] + 1 : 0;
        }
        ans = std::max(ans, largest_rectangle<int, long long>(height));
    }
    std::cout << ans << '\n';

    return 0;
}
