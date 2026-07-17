// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/predecessor_problem
#include <iostream>
#include <string>
#include "binary_tree/tree64.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    std::string t;
    std::cin >> t;
    tree64<10000000> st;
    for (int i = 0; i < n; ++i) {
        if (t[i] == '1') st.insert(i);
    }
    while (q--) {
        int c, k;
        std::cin >> c >> k;
        if (c == 0) st.insert(k);
        else if (c == 1) st.erase(k);
        else if (c == 2) std::cout << st.contains(k) << '\n';
        else if (c == 3) std::cout << st.succ(k) << '\n';
        else std::cout << st.pred(k + 1) << '\n';
    }

    return 0;
}
