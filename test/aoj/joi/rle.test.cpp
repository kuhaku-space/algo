#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/0534"
#include "algorithm/rle.hpp"
#include "template/atcoder.hpp"
#include "template/vector.hpp"

int main(void) {
    while (true) {
        int n;
        std::cin >> n;
        if (!n) break;
        std::vector<int> a(n);
        std::cin >> a;
        Dec >> a;
        int ans = n;
        rep (i, n) {
            auto b = a;
            rep (j, 3) {
                if (a[i] == j) continue;
                b[i] = j;
                auto v = run_length_encoding(b);
                std::stack<std::pair<int, int>> st;
                for (auto p : v) {
                    if (p.second >= 4) continue;
                    if (!st.empty() && st.top().first == p.first && st.top().second + p.second >= 4)
                        st.pop();
                    else st.emplace(p);
                }
                int sum = 0;
                while (!st.empty()) {
                    sum += st.top().second;
                    st.pop();
                }
                chmin(ans, sum);
            }
        }
        co(ans);
    }

    return 0;
}
