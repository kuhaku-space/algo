// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/product_of_polynomial_sequence
#include <iostream>
#include <utility>
#include <vector>

#include "fft/ntt.hpp"

using Mint = modint998;

std::vector<Mint> prod(const std::vector<std::vector<Mint>> &a, int l, int r) {
    if (l + 1 == r)
        return a[l];
    int m = (l + r) / 2;
    return convolution(prod(a, l, m), prod(a, m, r));
}

int main(void) {
    int n;
    std::cin >> n;
    std::vector<std::vector<Mint>> a(n);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>>
        p_que;
    for (int i = 0; i < n; ++i) {
        int d;
        std::cin >> d;
        p_que.emplace(d + 1, i);
        a[i].resize(d + 1);
        for (int j = 0; j < d + 1; ++j) std::cin >> a[i][j];
    }

    if (n == 0) {
        std::cout << 1 << '\n';
    } else {
        auto ans = prod(a, 0, n);
        for (int i = 0; i < (int)ans.size(); ++i)
            std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');
    }

    return 0;
}
