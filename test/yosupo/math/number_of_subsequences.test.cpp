#define PROBLEM "https://judge.yosupo.jp/problem/number_of_subsequences"
#include "algorithm/compress.hpp"
#include "math/modint.hpp"
#include "template/atcoder.hpp"

using Mint = modint998;

int main(void) {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::cin >> a;
    a = compress(a);
    Mint ans = 0;
    std::vector<Mint> dp(*max_element(all(a)) + 1);
    for (auto x : a) {
        auto t = ans - dp[x] + 1;
        ans += t;
        dp[x] += t;
    }
    co(ans);

    return 0;
}
