// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0534
#include "algorithm/rle.hpp"
#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>
#include "template/vector.hpp"

int main(void) {
    while (true) {
        int n;
        std::cin >> n;
        if (!n) break;
        std::vector<int> a(n);
        for (auto &e : a) std::cin >> e;
        Dec >> a;
        int ans = n;
        for (int i = 0; i < n; ++i) {
            auto b = a;
            for (int j = 0; j < 3; ++j) {
                if (a[i] == j) continue;
                b[i] = j;
                auto v = run_length_encoding(b);
                std::stack<std::pair<int, int>> st;
                for (auto p : v) {
                    if (p.second >= 4) continue;
                    if (!st.empty() && st.top().first == p.first && st.top().second + p.second >= 4) st.pop();
                    else st.emplace(p);
                }
                int sum = 0;
                while (!st.empty()) {
                    sum += st.top().second;
                    st.pop();
                }
                ans = std::min(ans, sum);
            }
        }
        std::cout << ans << '\n';
    }

    return 0;
}
