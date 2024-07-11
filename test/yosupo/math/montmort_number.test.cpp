// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/montmort_number_mod
#include <cstdint>
#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::int64_t sum = 0;
    std::vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = sum;
        sum *= i + 2;
        if (i & 1) sum += m - 1;
        else ++sum;
        sum %= m;
    }
    for (int i = 0; i < (int)ans.size(); ++i)
        std::cout << ans[i] << (i == (int)ans.size() - 1 ? '\n' : ' ');

    return 0;
}
